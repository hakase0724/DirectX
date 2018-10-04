#include "stdafx.h"
#include "DXSphere.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace MyDirectX;
const int u_max = 30;
const int v_max = 15;
VERTEX2 *vertices;
int *indexes;
int vertex_num = u_max * (v_max + 1);
int index_num = 2 * v_max * (u_max + 1);
float x = -1.0f;
float y = 1.0f;
float z = -2.0f;
float w = 1.0f;
DXSphere::DXSphere(DXManager * dxManager, DXInput* input, DXCamera* camera) :DXGameObject(dxManager, input, camera) 
{
	Init(dxManager, input, camera);
}

DXSphere::DXSphere(TRANSFORM * transform, DXManager * dxManager, DXInput* input, DXCamera* camera) : DXGameObject(transform, dxManager, input, camera)
{
	Init(dxManager, input, camera);
}


DXSphere::~DXSphere()
{
	Exit();
}


HRESULT DXSphere::Init(DXManager* dxManager, DXInput* input, DXCamera* camera)
{
	if (FAILED(CreateShader())) return S_FALSE;
	if (FAILED(CreateConstantBuffer())) return S_FALSE;
	if (FAILED(CreateVertex())) return S_FALSE;
	if (FAILED(CreateIndex())) return S_FALSE;
	return S_OK;
}

void DXSphere::Update()
{
	auto cameraParam = mDXCamera->GetCameraParam();
	if (mDXInput->GetInputState(DIK_H)) x += 0.01f;
	if (mDXInput->GetInputState(DIK_J)) x -= 0.01f;
	if (mDXInput->GetInputState(DIK_K)) y += 0.01f;
	if (mDXInput->GetInputState(DIK_L)) y -= 0.01f;
	if (mDXInput->GetInputState(DIK_U)) z += 0.01f;
	if (mDXInput->GetInputState(DIK_I)) z -= 0.01f;
	if (mDXInput->GetInputState(DIK_O)) w += 0.01f;
	if (mDXInput->GetInputState(DIK_P)) w -= 0.01f;
	if (mDXInput->GetInputState(DIK_W)) mTransform.Position.y += 0.01f;
	if (mDXInput->GetInputState(DIK_S)) mTransform.Position.y -= 0.01f;
	if (mDXInput->GetInputState(DIK_A)) mTransform.Position.x -= 0.01f;
	if (mDXInput->GetInputState(DIK_D)) mTransform.Position.x += 0.01f;
	if (mDXInput->GetInputState(DIK_Z)) mTransform.Position.z += 0.01f;
	if (mDXInput->GetInputState(DIK_X)) mTransform.Position.z -= 0.01f;
	if (mDXInput->GetInputState(DIK_RIGHT)) mTransform.Rotation.x += 0.01f;
	if (mDXInput->GetInputState(DIK_LEFT)) mTransform.Rotation.x -= 0.01f;
	if (mDXInput->GetInputState(DIK_UP)) mTransform.Rotation.y += 0.01f;
	if (mDXInput->GetInputState(DIK_DOWN)) mTransform.Rotation.y -= 0.01f;
	cBuffer.mW = mDXCamera->GetWorld(mTransform);
	cBuffer.mWVP = mDXCamera->GetDXCameraParam(mTransform);
	cBuffer.vColor = XMVectorSet(0, 1, 0, 1);
	cBuffer.vLightPos = XMVectorSet(x, y, z, w);
	cBuffer.vEyePos = cameraParam.mPos;
}

void DXSphere::Render()
{
	//データを渡す
	mDXManager->GetDeviceContext()->UpdateSubresource(mConstantBuffer, 0, NULL, &cBuffer, 0, 0);

	//パイプライン構築
	UINT stride = sizeof(VERTEX2);
	UINT offset = 0;
	//頂点バッファを設定
	mDXManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	//インデックスバッファの設定
	mDXManager->GetDeviceContext()->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	//入力レイアウト設定
	mDXManager->GetDeviceContext()->IASetInputLayout(mVertexLayout);
	//頂点情報の解釈の仕方を設定
	mDXManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//頂点シェーダーを設定
	mDXManager->GetDeviceContext()->VSSetShader(mVertexShader, NULL, 0);
	//ピクセルシェーダーを設定
	mDXManager->GetDeviceContext()->PSSetShader(mPixelShader, NULL, 0);
	//定数バッファを設定
	mDXManager->GetDeviceContext()->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	mDXManager->GetDeviceContext()->PSSetConstantBuffers(0, 1, &mConstantBuffer);
	//ラスタライズステートを設定
	mDXManager->GetDeviceContext()->RSSetState(mRasterizerState);
	//深度バッファ状態を設定
	auto depth = mDXManager->GetDepthStencilState();
	mDXManager->GetDeviceContext()->OMSetDepthStencilState(depth, 0);
	//描画
	mDXManager->GetDeviceContext()->DrawIndexed(mDrawNum, 0,0);
}

void DXSphere::Exit()
{
	if (mVertexBuffer)mVertexBuffer->Release();
	if (mVertexLayout)mVertexLayout->Release();
	if (mVertexShader)mVertexShader->Release();
	if (mPixelShader)mPixelShader->Release();
	if (mIndexBuffer)mIndexBuffer->Release();
	if (mConstantBuffer)mConstantBuffer->Release();
	if (mRasterizerState)mRasterizerState->Release();
}

HRESULT DXSphere::CreateShader()
{
	//シェーダの設定
	ID3DBlob* compileVS = NULL;
	ID3DBlob* compilePS = NULL;
	//シェーダーのコンパイル
	//失敗したら終了する
	HRESULT hr = D3DCompileFromFile(L"shader2.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &compilePS, NULL);
	if (FAILED(hr))
	{
		return S_FALSE;
	}
	hr = D3DCompileFromFile(L"shader2.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &compileVS, NULL);
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
		{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
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

HRESULT DXSphere::CreateConstantBuffer()
{
	//定数バッファ生成
	D3D11_BUFFER_DESC cb;
	//バッファサイズ
	cb.ByteWidth = sizeof(CONSTANT_BUFFER2);
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

HRESULT DXSphere::CreateVertex()
{
	D3D11_BUFFER_DESC bd;
	vertices = new VERTEX2[vertex_num];
	for (int v = 0; v <= v_max; v++) {
		for (int u = 0; u < u_max; u++) {
			double theta = XMConvertToRadians(180.0f * v / v_max);
			double phi = XMConvertToRadians(360.0f * u / u_max);
			double x = sin(theta) * cos(phi);
			double y = cos(theta);
			double z = sin(theta) * sin(phi);
			vertices[u_max * v + u].V = { (float)x, (float)y, (float)z };
			vertices[u_max * v + u].N = { (float)x, (float)y, (float)z };
		}
	}
	bd.ByteWidth = sizeof(VERTEX2) * vertex_num;
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
	data.pSysMem = vertices;
	HRESULT hr = mDXManager->GetDevice()->CreateBuffer(&bd, &data, &mVertexBuffer);
	delete vertices;
	if (FAILED(hr)) return S_FALSE;
	else return S_OK;
}

HRESULT DXSphere::CreateIndex()
{
	// ポリゴンのインデックスデータの作成
	int i = 0;
	indexes = new int[index_num];
	for (int v = 0; v < v_max; v++) {
		for (int u = 0; u <= u_max; u++) {
			if (u == u_max) {
				indexes[i++] = v * u_max;
				indexes[i++] = (v + 1) * u_max;
			}
			else {
				indexes[i++] = (v * u_max) + u;
				indexes[i++] = indexes[i - 1] + u_max;
			}
		}
	}
	mDrawNum = index_num;
	D3D11_BUFFER_DESC bd_index;
	bd_index.ByteWidth = sizeof(int) * mDrawNum;
	bd_index.Usage = D3D11_USAGE_DEFAULT;
	bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd_index.CPUAccessFlags = 0;
	bd_index.MiscFlags = 0;
	bd_index.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_index;
	data_index.pSysMem = indexes;
	HRESULT hr = mDXManager->GetDevice()->CreateBuffer(&bd_index, &data_index, &mIndexBuffer);
	delete indexes;
	if (FAILED(hr)) return S_FALSE;
	else return S_OK;
}

HRESULT DXSphere::CreateRasterizeState()
{
	//ラスタライザ設定
	D3D11_RASTERIZER_DESC rd = {};
	//塗りつぶし設定　SOLIDは塗りつぶし
	rd.FillMode = D3D11_FILL_SOLID;
	//描画面設定　今は前面描画
	rd.CullMode = D3D11_CULL_BACK;
	//表面設定　反時計回りすると表と認識　FALSEだと逆転する
	rd.FrontCounterClockwise = TRUE;
	mDXManager->GetDevice()->CreateRasterizerState(&rd, &mRasterizerState);
	return S_OK;
}
