#include "stdafx.h"
#include "ShaderFactory.h"
#include <d3dcompiler.h>
#include "DXManager.h"

#pragma comment(lib, "d3dcompiler.lib")
using namespace MyDirectX;

void ShaderFactory::Create(ShaderInfo * info, 
	ID3D11Device * device, 
	ID3D11VertexShader ** vertex, 
	ID3D11PixelShader ** pixel, 
	ID3D11InputLayout ** inputLayout, 
	ID3D11RasterizerState ** rasterizerState,
	ID3D11Buffer ** constantBuffer)
{
	CreateShader(info,device,vertex,pixel,inputLayout);
	CreateConstantBuffer(info, device,constantBuffer);
	CreateRasterizerState(info, device, rasterizerState);
}

void ShaderFactory::CreateShader(ShaderInfo * info, 
	ID3D11Device * device,
	ID3D11VertexShader ** vertex, 
	ID3D11PixelShader ** pixel,
	ID3D11InputLayout ** inputLayout)
{
	HRESULT hr;
	//シェーダの設定
	ID3DBlob* compileVS = NULL;
	ID3DBlob* compilePS = NULL;
	//シェーダーのコンパイル
	hr = D3DCompileFromFile(info->shader->PixelName, nullptr, nullptr, info->shader->PixelEntry, info->shader->PixelVersion, 0, 0, &compilePS, NULL);
	if(FAILED(hr))
	{
		return;
	}
	hr = D3DCompileFromFile(info->shader->VertexName, nullptr, nullptr, info->shader->VertexEntry, info->shader->VertexVersion, 0, 0, &compileVS, NULL);
	if (FAILED(hr))
	{
		return;
	}
	//デバイスにコンパイルしたシェーダーをあてがう	
	device->CreateVertexShader(compileVS->GetBufferPointer(), compileVS->GetBufferSize(), NULL, vertex);
	device->CreatePixelShader(compilePS->GetBufferPointer(), compilePS->GetBufferSize(), NULL, pixel);
	//入力レイアウトを生成する
	device->CreateInputLayout(info->shader->InputLayout, info->shader->LayoutNum, compileVS->GetBufferPointer(), compileVS->GetBufferSize(), inputLayout);
	compileVS->Release();
	compilePS->Release();
}

void ShaderFactory::CreateRasterizerState(ShaderInfo * info, ID3D11Device * device, ID3D11RasterizerState ** rasterizerState)
{
	//ラスタライザ設定
	D3D11_RASTERIZER_DESC rd = {};
	//塗りつぶし設定　SOLIDは塗りつぶし
	rd.FillMode = D3D11_FILL_SOLID;
	//描画面設定　今は前面描画
	rd.CullMode = D3D11_CULL_FRONT;
	//表面設定　反時計回りすると表と認識　FALSEだと逆転する
	rd.FrontCounterClockwise = TRUE;
	device->CreateRasterizerState(&rd, rasterizerState);
}

void ShaderFactory::CreateConstantBuffer(ShaderInfo * info, ID3D11Device * device, ID3D11Buffer ** constantBuffer)
{
	//定数バッファ生成
	D3D11_BUFFER_DESC cb;
	//バッファサイズ
	cb.ByteWidth = info->GetSize();
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
	device->CreateBuffer(&cb, NULL, constantBuffer);
}
