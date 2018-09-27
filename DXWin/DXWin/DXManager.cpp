#include "stdafx.h"
#include "DXManager.h"
#include "dinput.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace MyDirectX;
using namespace Microsoft::WRL;

struct VERTEX
{
	XMFLOAT3 V;
	XMFLOAT4 C;
};

struct CONSTANT_BUFFER
{
	XMMATRIX mWVP;
};

DXManager::DXManager(){}

HRESULT DXManager::InitDX11(HWND hwnd)
{
	//カメラを生成し初期設定
	mDXCamera = std::unique_ptr<DXCamera>(new DXCamera());
	mDXCamera->SetEyeParamWithRatio
	(
		XMVectorSet(0.0f, 1.0f, -2.3f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f),
		cWidth / cHeight
	);
	mHwnd = hwnd;
	HRESULT hr = S_OK;
	RECT rc;
	GetClientRect(mHwnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	UINT flags = 0;
#ifdef _DEBUG
	flags = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL fLevel = D3D_FEATURE_LEVEL_11_0;
	mDriverType = D3D_DRIVER_TYPE_HARDWARE;

	//スワップチェイン設定
	DXGI_SWAP_CHAIN_DESC sd;
	//渡したもの全てを0クリアする
	//クリアした後中身を入れずにアクセスするとエラーになることが多いため要注意らしい
	ZeroMemory(&sd,sizeof(sd));
	//バッファ数
	sd.BufferCount = 1;
	//解像度幅
	sd.BufferDesc.Width = width;
	//解像度高さ
	sd.BufferDesc.Height = height;
	//リフレッシュレートの最大有理数　要は60fpsだってことだと思う
	sd.BufferDesc.RefreshRate.Numerator = 60;
	//リフレッシュレートの最小有理数　少なくとも1fpsは保証するってことかな・・・？
	sd.BufferDesc.RefreshRate.Denominator = 1;
	//表示フォーマット　4要素符号無し32ビット
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//バックバッファのサーフェス使用法CPUアクセスオプションを設定する　出力で使うようにする
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//出力するウィンドウのハンドル
	sd.OutputWindow = mHwnd;
	//ピクセル単位のサンプリング数
	sd.SampleDesc.Count = 1;
	//イメージ品質　-1～0まで指定できる
	sd.SampleDesc.Quality = 0;
	//ウィンドウモードで起動する
	sd.Windowed = true;

	//DirectXのデバイスを作る
	hr = D3D11CreateDeviceAndSwapChain
	(NULL,mDriverType,NULL,flags,&fLevel,1,D3D11_SDK_VERSION,&sd,&mSwapChain,&mDevice,&mLevel,&mDeviceContext);
	if (FAILED(hr)) return S_FALSE;

	//バックバッファの確保　裏面描画とかで使ってそう
	std::unique_ptr<ID3D11Texture2D> back_buff;
	auto pBack_Buff = back_buff.get();;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBack_Buff);
	if (FAILED(hr)) 
	{
		ExitDX11();
		return S_FALSE;
	}

	//レンダーターゲットビュー生成
	hr = mDevice->CreateRenderTargetView(pBack_Buff,NULL,&mRenderTargetView);
	
	if (FAILED(hr))
	{
		ExitDX11();
		return S_FALSE;
	}

	//入力初期化
	mDXInput = std::unique_ptr<DXInput>(new DXInput());
	hr = mDXInput->InitDirectInput(hwnd);
	if (FAILED(hr))
	{
		ExitDX11();
		return S_FALSE;
	}

	//ビューポート設定
	D3D11_VIEWPORT view;
	view.Width = (FLOAT)width;
	view.Height = (FLOAT)height;
	view.MinDepth = 0.0f;
	view.MaxDepth = 1.0f;
	view.TopLeftX = 0.0f;
	view.TopLeftY = 0.0f;	

	//シェーダの設定
	ID3DBlob* compileVS = NULL;
	ID3DBlob* compilePS = NULL;
	//シェーダーのコンパイル
	//失敗したら終了する
	hr = D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &compilePS, NULL);
	if (FAILED(hr))
	{
		ExitDX11();
		return S_FALSE;
	}
	hr = D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &compileVS, NULL);
	if (FAILED(hr))
	{
		ExitDX11();
		return S_FALSE;
	}
	//デバイスにコンパイルしたシェーダーをあてがう
	mDevice->CreateVertexShader(compileVS->GetBufferPointer(), compileVS->GetBufferSize(), NULL, &mVertexShader);
	mDevice->CreatePixelShader(compilePS->GetBufferPointer(), compilePS->GetBufferSize(), NULL, &mPixelShader);
	
	//頂点レイアウト設定
	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			12,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}
	};
	//入力レイアウトを生成する
	mDevice->CreateInputLayout(layout, 2, compileVS->GetBufferPointer(), compileVS->GetBufferSize(), &mVertexLayout);
	compileVS->Release();
	compilePS->Release();

	//定数バッファ生成
	D3D11_BUFFER_DESC cb;
	//バッファサイズ
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	//想定する読み書き方法　
	//GPUから読み込みのみCPUからは書き込みのみができるようになる　1フレーム内にCPUから複数回更新が想定される場合に設定する
	cb.Usage = D3D11_USAGE_DYNAMIC;
	//パイプラインにどのようにバインドするか
	//定数バッファとしてバインド
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//CPUアクセスフラグ
	//書き込みができる
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//今まで設定したフラグ以外のもの
	cb.MiscFlags = 0;
	//構造体が構造体バッファを表す時のサイズ(バイト単位)
	cb.StructureByteStride = 0;
	//バッファを作る　NULLのところにデータを入れるとその値で初期化してくれる
	mDevice->CreateBuffer(&cb, NULL, &mConstantBuffer);

	//頂点データとバッファ生成
	VERTEX vertex[] = 
	{
		{ XMFLOAT3(-0.5f, -0.5f, 0.5f),  XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, 0.5f),   XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f),  XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f),   XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.5f),    XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(0.5f, 0.5f, -0.5f),   XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, -0.5f),  XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
	};
	
	mDrawNum = ARRAYSIZE(vertex);
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(VERTEX) * mDrawNum;
	//GPUから読み書きができる
	bd.Usage = D3D11_USAGE_DEFAULT;
	//頂点バッファとしてバインド
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//用意された定数を設定しないと勝手に最適化されるらしい
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	//サブリソースの初期化ポインター
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertex;
	mDevice->CreateBuffer(&bd, &data, &mVertexBuffer);

	//ポリゴンのインデックス情報
	int index[] =
	{
		0, 2, 1,
		0, 3, 2,

		0, 5, 4,
		0, 1, 5,

		1, 6, 5,
		1, 2, 6,

		2, 7, 6,
		2, 3, 7,

		0, 4, 7,
		0, 7, 3,

		4, 5, 7,
		5, 6, 7,

	};
	mDrawNum = ARRAYSIZE(index);
	D3D11_BUFFER_DESC bd_index;
	bd_index.ByteWidth = sizeof(int) * mDrawNum;
	bd_index.Usage = D3D11_USAGE_DEFAULT;
	bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd_index.CPUAccessFlags = 0;
	bd_index.MiscFlags = 0;
	bd_index.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_index;
	data_index.pSysMem = index;
	mDevice->CreateBuffer(&bd_index, &data_index, &mIndexBuffer);

	//ラスタライザ設定
	D3D11_RASTERIZER_DESC rd = {};
	//塗りつぶし設定　SOLIDは塗りつぶし
	rd.FillMode = D3D11_FILL_SOLID;
	//描画面設定　今は前面描画
	rd.CullMode = D3D11_CULL_FRONT;
	//表面設定　反時計回りすると表と認識　FALSEだと逆転する
	rd.FrontCounterClockwise = TRUE;
	mDevice->CreateRasterizerState(&rd, &mRasterizerState);

	//パイプライン構築
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	//頂点バッファを設定
	mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	//インデックスバッファーの設定
	mDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	//入力レイアウト設定
	mDeviceContext->IASetInputLayout(mVertexLayout.Get());
	//頂点情報の解釈の仕方を設定
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//頂点シェーダーを設定
	mDeviceContext->VSSetShader(mVertexShader.Get(), NULL, 0);
	//ピクセルシェーダーを設定
	mDeviceContext->PSSetShader(mPixelShader.Get(), NULL, 0);
	//ラスタライズステートの設定
	mDeviceContext->RSSetState(mRasterizerState.Get());
	//定数バッファを設定
	mDeviceContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	//レンダーターゲットを設定する
	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, NULL);
	//ビューポートの設定
	mDeviceContext->RSSetViewports(1, &view);
	return S_OK;
}
BOOL MyDirectX::DXManager::UpdateDX11()
{
	//入力取得
	mDXInput->SetInputState();
	if (mDXInput->GetInputState(DIK_UP)) xRote += 0.001f;
	if (mDXInput->GetInputState(DIK_DOWN)) xRote -= 0.001f;
	if (mDXInput->GetInputState(DIK_RIGHT)) yRote -= 0.001f;
	if (mDXInput->GetInputState(DIK_LEFT)) yRote += 0.001f;
	if (mDXInput->GetInputState(DIK_ESCAPE)) return FALSE;
	else return TRUE;
}
void DXManager::RenderDX11()
{
	//背景塗りつぶし
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, mColor);
	//データを渡す
	D3D11_MAPPED_SUBRESOURCE data;
	CONSTANT_BUFFER buffer;
	buffer.mWVP = mDXCamera->GetDXCameraParam(xRote, yRote);
	//描画停止
	mDeviceContext->Map(mConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	//データ更新
	memcpy_s(data.pData, data.RowPitch, (void*)(&buffer), sizeof(buffer));
	//描画再開
	mDeviceContext->Unmap(mConstantBuffer, 0);
	//描画
	mDeviceContext->DrawIndexed(mDrawNum, 0, 0);
	//裏面描画したものを表に展開する
	mSwapChain->Present(0, 0);
}
void DXManager::ExitDX11()
{
	//メモリを確保してあるものを全て開放する
	mDXInput->ExitDirectInput();
	if (mDeviceContext)
	{
		mDeviceContext->ClearState();
		mDeviceContext.Reset();
	}
	if (mRenderTargetView) mRenderTargetView->Release();
	if (mSwapChain) mSwapChain.Reset();
	if (mVertexLayout) mVertexLayout.Reset();
	if (mVertexBuffer) mVertexBuffer->Release();
	if (mVertexShader) mVertexShader.Reset();
	if (mPixelShader) mPixelShader.Reset();
	if (mConstantBuffer) mConstantBuffer->Release();
	if (mRasterizerState) mRasterizerState.Reset();
	if (mIndexBuffer) mIndexBuffer->Release();
	if (mDevice) mDevice.Reset();
}

