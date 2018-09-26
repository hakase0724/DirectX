#include "stdafx.h"
#include "DXManager.h"
#include "DXInput.h"
#include "dinput.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

struct VERTEX
{
	XMFLOAT3 V;
	XMFLOAT4 C;
};

struct CONSTANT_BUFFER
{
	XMMATRIX mWVP;
};

//背景塗りつぶし色
const float mColor[4] = { 0.0f,0.0f,0.0f,1.0f};
//カメラを回すための変数　
float x = 0.0f;
float y = 0.0f;
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
//インデックス要のバッファ
ID3D11Buffer* mIndexBuffer;
//ラスタライザステージのラスタライザステートへアクセス　面とか出すときラスタ形式で出しているから必要らしい
ID3D11RasterizerState* mRasterizerState;

//初期化処理
HRESULT InitDX11(HWND hwnd)
{
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
	ID3D11Texture2D* back_buff = NULL;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buff);
	if (FAILED(hr)) 
	{
		ExitDX11();
		return S_FALSE;
	}

	//レンダーターゲットビュー生成
	hr = mDevice->CreateRenderTargetView(back_buff,NULL,&mRenderTargetView);
	back_buff->Release();
	if (FAILED(hr))
	{
		ExitDX11();
		return S_FALSE;
	}

	//入力初期化
	hr = InitDirectInput(hwnd);
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
	//頂点数計算
	//配列の要素数を求めるために配列全体のサイズを先頭要素のサイズで割る
	mDrawNum = sizeof(vertex) / sizeof(vertex[0]);
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
	mDrawNum = sizeof(index) / sizeof(index[0]);
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
	mDeviceContext->IASetInputLayout(mVertexLayout);
	//頂点情報の解釈の仕方を設定
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//頂点シェーダーを設定
	mDeviceContext->VSSetShader(mVertexShader, NULL, 0);
	//ピクセルシェーダーを設定
	mDeviceContext->PSSetShader(mPixelShader, NULL, 0);
	//ラスタライズステートの設定
	mDeviceContext->RSSetState(mRasterizerState);
	//定数バッファを設定
	mDeviceContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	//レンダーターゲットを設定する
	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, NULL);
	//ビューポートの設定
	mDeviceContext->RSSetViewports(1, &view);
	return S_OK;
}

//描画処理
BOOL RenderDX11()
{
	//背景塗りつぶし
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, mColor);

	//入力取得
	SetInputState();
	if (GetInputState(DIK_UP)) x += 0.001f;
	if (GetInputState(DIK_DOWN)) x -= 0.001f;
	if (GetInputState(DIK_RIGHT)) y -= 0.001f;
	if (GetInputState(DIK_LEFT)) y += 0.001f;
	if (GetInputState(DIK_ESCAPE)) return FALSE;

	//カメラパラメータ計算
	//カメラ位置
	XMVECTOR eye_pos = XMVectorSet(0.0f,1.0f,-2.3f,1.0f);
	//カメラ上方向
	XMVECTOR eye_lookup = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	//カメラの焦点
	XMVECTOR eye_up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	//カメラの位置、上方向、および焦点を使用して、左手座標系のビュー行列を作成
	XMMATRIX view = XMMatrixLookAtLH(eye_pos, eye_lookup, eye_up);
	//視野に基づいて、左手座標系のパースペクティブ射影行列を作成
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, cWidth / cHeight,0.1f,110.0f);
	//x軸回転
	XMMATRIX worldX = XMMatrixRotationX(x);
	//y軸回転
	XMMATRIX worldY = XMMatrixRotationY(y);

	//データを渡す
	D3D11_MAPPED_SUBRESOURCE data;
	CONSTANT_BUFFER buffer;
	//転置行列を計算 要はカメラの場所や視界を計算するってことだと思う
	buffer.mWVP = XMMatrixTranspose(worldX * worldY * view * proj);
	//描画停止
	mDeviceContext->Map(mConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	//データ更新
	memcpy_s(data.pData, data.RowPitch, (void*)(&buffer), sizeof(buffer));
	//描画再開
	mDeviceContext->Unmap(mConstantBuffer, 0);
	//描画
	mDeviceContext->DrawIndexed(mDrawNum, 0,0);
	//裏面描画したものを表に展開する
	mSwapChain->Present(0, 0);
	return TRUE;
}

//終了処理
void ExitDX11()
{
	//メモリを確保してあるものを全て開放する
	ExitDirectInput();
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
	if (mIndexBuffer) mIndexBuffer->Release();
	if (mDevice) mDevice->Release();
}
