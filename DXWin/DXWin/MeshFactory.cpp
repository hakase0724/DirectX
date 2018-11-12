#include "stdafx.h"
#include "MeshFactory.h"

using namespace MyDirectX;

void MeshFactory::Create(MeshInfo * info, ID3D11Device * device, ID3D11Buffer ** vertexBuffer, ID3D11Buffer ** indexBuffer)
{
	CreateVertex(info, device, vertexBuffer);
	CreateIndex(info, device, indexBuffer);
}

void MeshFactory::CreateVertex(MeshInfo * info, ID3D11Device * device, ID3D11Buffer ** vertexBuffer)
{
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = info->GetSize() * info->vertexNum;
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
	data.pSysMem = info->vertexInfo;
	device->CreateBuffer(&bd, &data, vertexBuffer);
}

void MeshFactory::CreateIndex(MeshInfo * info, ID3D11Device * device, ID3D11Buffer ** indexBuffer)
{
	D3D11_BUFFER_DESC bd_index;
	bd_index.ByteWidth = sizeof(int) * info->indexNum;
	bd_index.Usage = D3D11_USAGE_DEFAULT;
	bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd_index.CPUAccessFlags = 0;
	bd_index.MiscFlags = 0;
	bd_index.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_index;
	data_index.pSysMem = info->indexes;
	device->CreateBuffer(&bd_index, &data_index, indexBuffer);
}
