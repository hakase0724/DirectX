#include "stdafx.h"
#include "DXManager.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

struct VERTEX
{
	XMFLOAT3 mV;
};

struct CONSTANT_BUFFER
{
	XMMATRIX mWVP;
};

//初期化済みか
bool mIsInit = false;
//描画する頂点数
int mDrawNum = 0;
//ウィンドルのハンドル
HWND mHwnd = NULL;
//ドライバーの種類オプション　NULLはデバッグ用らしい
D3D_DRIVER_TYPE mDriverType = D3D_DRIVER_TYPE_NULL;
//DirectXの機能サポートレベルを設定する　今回はDirectX11の勉強だから11を設定した
D3D_FEATURE_LEVEL mLevel = D3D_FEATURE_LEVEL_11_0;
//DirectXの仮想ドライバー　多分こいつが一番大事なもの
ID3D11Device* mDevice = NULL;
//レンダリングについて色々設定できるものらしい
ID3D11DeviceContext* mDeviceContext = NULL;
//描画処理に必要な情報が入るバッファーらしい
IDXGISwapChain* mSwapChain = NULL;
//レンダリング時に使えるサブリソース識別
ID3D11RenderTargetView* mRenderTargetView = NULL;
//入力アセンブラステージの入力データにアクセス　入力してなんかするときに使いそう
ID3D11InputLayout* mVertexLayout;
//頂点シェーダー管理
ID3D11VertexShader* mVertexShader;
//ピクセルシェーダー管理
ID3D11PixelShader* mPixelShader;
//データバッファ　シェーダーとのデータのやり取りに使っている
ID3D11Buffer* mConstantBuffer;
//頂点シェーダー用のバッファ
ID3D11Buffer* mVertexBuffer;
//ラスタライザステージのラスタライザステートへアクセス　面とか出すときラスタ形式で出しているから必要らしい
ID3D11RasterizerState* mRasterizerState;

HRESULT InitDX11(HWND hwnd)
{
	//初期化してたら処理しない
	if (mIsInit) return S_FALSE;
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
	ZeroMemory(&sd,sizeof(sd));
	//バッファー数
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
	//バックバッファーのサーフェス使用法CPUアクセスオプションを設定する　出力で使うようにする
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
	if (FAILED(hr)) return hr;
	//バックバッファーの確保　裏面描画とかで使ってそう
	ID3D11Texture2D* back_buff = NULL;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buff);
	if (FAILED(hr)) return hr;
	//レンダーターゲットビュー生成
	hr = mDevice->CreateRenderTargetView(back_buff,NULL,&mRenderTargetView);
	back_buff->Release();
	if (FAILED(hr)) return hr;
	//レンダーターゲットを設定する
	mDeviceContext->OMSetRenderTargets(1,&mRenderTargetView,NULL);

	//ビューポート設定
	D3D11_VIEWPORT view;
	view.Width = (FLOAT)width;
	view.Height = (FLOAT)height;
	view.MinDepth = 0.0f;
	view.MaxDepth = 1.0f;
	view.TopLeftX = 0.0f;
	view.TopLeftY = 0.0f;
	mDeviceContext->RSSetViewports(1, &view);

	//シェーダの設定
	ID3DBlob* compileVS = NULL;
	ID3DBlob* compilePS = NULL;
	//シェーダーのコンパイル
	//失敗したら終了する
	if (FAILED(D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &compilePS, NULL))) return S_FALSE;
	if (FAILED(D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &compileVS, NULL))) return S_FALSE;
	//デバイスにコンパイルしたシェーダーをあてがう
	mDevice->CreateVertexShader(compileVS->GetBufferPointer(), compileVS->GetBufferSize(), NULL, &mVertexShader);
	mDevice->CreatePixelShader(compilePS->GetBufferPointer(), compilePS->GetBufferSize(), NULL, &mPixelShader);
	
	//頂点レイアウト設定
	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		0,
		D3D11_INPUT_PER_VERTEX_DATA,
		0
	};
	//入力レイアウトを生成する
	mDevice->CreateInputLayout(layout, 1, compileVS->GetBufferPointer(), compileVS->GetBufferSize(), &mVertexLayout);
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
	//定数バッファーとしてバインド
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//CPUアクセスフラグ
	//書き込みができる
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//今まで設定したフラグ以外のもの
	cb.MiscFlags = 0;
	//構造体が構造体バッファーを表す時のサイズ(バイト単位)
	cb.StructureByteStride = 0;
	//バッファーを作る　NULLのところにデータを入れるとその値で初期化してくれる
	mDevice->CreateBuffer(&cb, NULL, &mConstantBuffer);

	//頂点データとバッファ生成
	VERTEX vertex[] = 
	{
		XMFLOAT3(-0.2f, 0.5f, 0.0f),
		XMFLOAT3(0.2f, 0.5f, 0.0f),
		XMFLOAT3(-0.0f, 0.3f, 0.0f)
	};
	//頂点数計算
	//配列の要素数を求めるために配列全体のサイズを先頭要素のサイズで割る
	mDrawNum = sizeof(vertex) / sizeof(vertex[0]);
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(VERTEX) * mDrawNum;
	//GPUから読み書きができる
	bd.Usage = D3D11_USAGE_DEFAULT;
	//頂点バッファーとしてバインド
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//用意された定数を設定しないと勝手に最適化されるらしい
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	//サブリソースの初期化ポインター
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertex;
	mDevice->CreateBuffer(&bd, &data, &mVertexBuffer);

	//ラスタライザ設定
	D3D11_RASTERIZER_DESC rd;
	//塗りつぶし設定　SOLIDは塗りつぶし
	rd.FillMode = D3D11_FILL_SOLID;
	//描画面設定　今は両面描画
	rd.CullMode = D3D11_CULL_NONE;
	//表面設定　反時計回りすると表と認識　FALSEだと逆転する
	rd.FrontCounterClockwise = TRUE;
	mDevice->CreateRasterizerState(&rd, &mRasterizerState);

	//パイプライン構築
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	//頂点バッファーを設定
	mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	//入力レイアウト設定
	mDeviceContext->IASetInputLayout(mVertexLayout);
	//頂点情報の解釈の仕方を設定
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//頂点シェーダーを設定
	mDeviceContext->VSSetShader(mVertexShader, NULL, 0);
	//ピクセルシェーダーを設定
	mDeviceContext->PSSetShader(mPixelShader, NULL, 0);
	//定数バッファーを設定
	mDeviceContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	mIsInit = true;
	return S_OK;
}

void RenderDX11()
{
	//塗りつぶし色の設定と画面クリア
	float color[4] = { 0.0f,0.0f,0.0f,1.0f };
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, color);

	//カメラパラメータ計算
	XMVECTOR eye_pos = XMVectorSet(0.0f,0.0f,-2.0f,1.0f);
	XMVECTOR eye_lookup = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR eye_up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	XMMATRIX view = XMMatrixLookAtLH(eye_pos, eye_lookup, eye_up);
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, cWidth / cHeight,0.1f,100.0f);
	XMMATRIX world = XMMatrixRotationZ(0);

	//データを渡す
	D3D11_MAPPED_SUBRESOURCE data;
	CONSTANT_BUFFER buffer;
	buffer.mWVP = XMMatrixTranspose(world * view * proj);
	mDeviceContext->Map(mConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	memcpy_s(data.pData, data.RowPitch, (void*)(&buffer), sizeof(buffer));
	mDeviceContext->Unmap(mConstantBuffer, 0);

	//描画
	mDeviceContext->Draw(mDrawNum, 0);
	mSwapChain->Present(0, 0);
}

void ExitDX11()
{
	//初期化してなかったら処理しない
	if (!mIsInit) return;
	//メモリを確保してあるものを全て開放する
	if (mDeviceContext)
	{
		mDeviceContext->ClearState();
		mDeviceContext->Release();
	}
	if (mRenderTargetView) mRenderTargetView->Release();
	if (mSwapChain) mSwapChain->Release();
	if (mVertexLayout) mVertexLayout->Release();
	if (mVertexBuffer) mVertexBuffer->Release();
	if (mVertexShader) mVertexShader->Release();
	if (mPixelShader) mPixelShader->Release();
	if (mConstantBuffer) mConstantBuffer->Release();
	if (mRasterizerState) mRasterizerState->Release();
	if (mDevice) mDevice->Release();
	mIsInit = false;
}
