#include "stdafx.h"
#include "DXCube.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "PrimitiveVertexInfo.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace MyDirectX;

DXCube::DXCube(DXManager * dxManager,DXInput* input, DXCamera* camera)
{
	mTransform.Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform.Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform.Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	mDXManager = dxManager;
	mDXInput = input;
	mDXCamera = camera;
}


DXCube::DXCube(TRANSFORM * transform, DXManager * dxManager, DXInput* input, DXCamera* camera)
{
	mTransform = *transform;
	mDXManager = dxManager;
	mDXInput = input;
	mDXCamera = camera;
}

DXCube::~DXCube()
{
	Exit();
}

void DXCube::SetTransform(TRANSFORM * transform)
{
	mTransform = *transform;
}

//初期化
bool DXCube::Init(TRANSFORM* transform, DXManager* dxManager, DXInput* input, DXCamera* camera)
{	
	mTransform = *transform;
	mDXManager = dxManager;
	mDXInput = input;
	mDXCamera = camera;
	if (FAILED(CreateShader())) return S_FALSE;
	if (FAILED(CreateConstantBuffer())) return S_FALSE;
	if (FAILED(CreateVertex())) return S_FALSE;
	if (FAILED(CreateIndex())) return S_FALSE;
	return S_OK;
}
//毎フレーム行う処理
void DXCube::Update()
{
	XMStoreFloat4x4(&cBuffer.gWVP, mDXCamera->GetDXCameraParam(mTransform));
}
//描画処理
void DXCube::Render()
{
	//データを渡す
	mDXManager->GetDeviceContext()->UpdateSubresource(mConstantBuffer, 0, NULL, &cBuffer, 0, 0);

	//パイプライン構築
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	//頂点バッファを設定
	mDXManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	//インデックスバッファーの設定
	mDXManager->GetDeviceContext()->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	//入力レイアウト設定
	mDXManager->GetDeviceContext()->IASetInputLayout(mVertexLayout);
	//頂点情報の解釈の仕方を設定
	mDXManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//頂点シェーダーを設定
	mDXManager->GetDeviceContext()->VSSetShader(mVertexShader, NULL, 0);
	//ピクセルシェーダーを設定
	mDXManager->GetDeviceContext()->PSSetShader(mPixelShader, NULL, 0);
	//定数バッファを設定
	mDXManager->GetDeviceContext()->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	//ラスタライズステートを設定
	mDXManager->GetDeviceContext()->RSSetState(mRasterizerState);
	//深度バッファ状態を設定
	auto depth = mDXManager->GetDepthStencilState();
	mDXManager->GetDeviceContext()->OMSetDepthStencilState(depth, 0);
	//描画
	mDXManager->GetDeviceContext()->DrawIndexed(mDrawNum, 0, 0);
}
//解放処理
void DXCube::Exit()
{
	if (mVertexBuffer)mVertexBuffer->Release();
	if (mVertexLayout)mVertexLayout->Release();
	if (mVertexShader)mVertexShader->Release();
	if (mPixelShader)mPixelShader->Release();
	if (mIndexBuffer)mIndexBuffer->Release();
	if (mConstantBuffer)mConstantBuffer->Release();
	if (mRasterizerState)mRasterizerState->Release();
}
//シェーダーと入力レイアウト作成
HRESULT DXCube::CreateShader()
{
	//シェーダの設定
	ID3DBlob* compileVS = NULL;
	ID3DBlob* compilePS = NULL;
	//シェーダーのコンパイル
	//失敗したら終了する
	HRESULT hr = D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &compilePS, NULL);
	if (FAILED(hr))
	{
		return S_FALSE;
	}
	hr = D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &compileVS, NULL);
	if (FAILED(hr))
	{
		return S_FALSE;
	}
	//デバイスにコンパイルしたシェーダーをあてがう	
	hr = mDXManager->GetDevice()->CreateVertexShader(compileVS->GetBufferPointer(), compileVS->GetBufferSize(), NULL, &mVertexShader);
	if (FAILED(hr))
	{
		return S_FALSE;
	}
	hr = mDXManager->GetDevice()->CreatePixelShader(compilePS->GetBufferPointer(), compilePS->GetBufferSize(), NULL, &mPixelShader);
	if (FAILED(hr))
	{
		return S_FALSE;
	}
	//頂点レイアウト設定
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	//入力レイアウトを生成する
	hr = mDXManager->GetDevice()->CreateInputLayout(layout, 2, compileVS->GetBufferPointer(), compileVS->GetBufferSize(), &mVertexLayout);
	if (FAILED(hr)) return S_FALSE;
	else
	{
		compileVS->Release();
		compilePS->Release();
		return S_OK;
	}	
}
//定数バッファ作成
HRESULT DXCube::CreateConstantBuffer()
{
	//定数バッファ生成
	D3D11_BUFFER_DESC cb;
	//バッファサイズ
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	//想定する読み書き方法　
	cb.Usage = D3D11_USAGE_DEFAULT;
	//パイプラインにどのようにバインドするか
	//定数バッファとしてバインド
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//CPUアクセスフラグ
	cb.CPUAccessFlags = 0;
	//今まで設定したフラグ以外のもの
	cb.MiscFlags = 0;
	//構造体が構造体バッファを表す時のサイズ(バイト単位)
	cb.StructureByteStride = 0;
	//バッファを作る　NULLのところにデータを入れるとその値で初期化してくれる
	HRESULT hr = mDXManager->GetDevice()->CreateBuffer(&cb, NULL, &mConstantBuffer);
	if (FAILED(hr)) return S_FALSE;
	else return S_OK;
}
//頂点データ作成
HRESULT DXCube::CreateVertex()
{
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(VERTEX) * ARRAYSIZE(CubeVertex);
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
	data.pSysMem = CubeVertex;
	HRESULT hr = mDXManager->GetDevice()->CreateBuffer(&bd, &data, &mVertexBuffer);
	if (FAILED(hr)) return S_FALSE;
	else return S_OK;
}
//インデックス作成
HRESULT DXCube::CreateIndex()
{
	mDrawNum = ARRAYSIZE(CubeIndex);
	D3D11_BUFFER_DESC bd_index;
	bd_index.ByteWidth = sizeof(int) * mDrawNum;
	bd_index.Usage = D3D11_USAGE_DEFAULT;
	bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd_index.CPUAccessFlags = 0;
	bd_index.MiscFlags = 0;
	bd_index.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_index;
	data_index.pSysMem = CubeIndex;
	HRESULT hr = mDXManager->GetDevice()->CreateBuffer(&bd_index, &data_index, &mIndexBuffer);
	if (FAILED(hr)) return S_FALSE;
	else return S_OK;
}
//ラスタライズステート作成
HRESULT DXCube::CreateRasterizeState()
{
	//ラスタライザ設定
	D3D11_RASTERIZER_DESC rd = {};
	//塗りつぶし設定　SOLIDは塗りつぶし
	rd.FillMode = D3D11_FILL_SOLID;
	//描画面設定　今は前面描画
	rd.CullMode = D3D11_CULL_FRONT;
	//表面設定　反時計回りすると表と認識　FALSEだと逆転する
	rd.FrontCounterClockwise = TRUE;
	mDXManager->GetDevice()->CreateRasterizerState(&rd, &mRasterizerState);

	return S_OK;
}
