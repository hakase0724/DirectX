#include "stdafx.h"
#include "DXRenderDataPool.h"
#include "WICTextureLoader.h"
#include "WICTextureLoader.cpp"

using namespace MyDirectX;

TextureData * DXRenderDataPool::GetTexture(wchar_t * fileName)
{
	TextureData* pReturn = nullptr;

	for (auto &tex : mTextureList)
	{
		if(fileName == tex.get()->fileName)
		{
			pReturn = tex.get();
			break;
		}
	}
	if(pReturn == nullptr)
	{
		auto pData = std::make_unique<TextureData>();
		pData.get()->fileName = fileName;
		HRESULT hr = CreateWICTextureFromFile(mDevice, fileName, &pData.get()->texture, &pData.get()->shaderView);
		pReturn = pData.get();
		mTextureList.push_back(std::move(pData));	
	}
	return pReturn;
}
