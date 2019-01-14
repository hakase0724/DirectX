#pragma once
#include "MeshAndShader.h"
#include <vector>
#include <memory>
#include <typeinfo>
#include "DirLoder.h"

namespace MyDirectX
{
	class DXRenderDataPool
	{
	public:
		DXRenderDataPool(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		~DXRenderDataPool() {};
		//メッシュデータを取得
		template<typename T>
		T* GetMesh();
		//シェーダーデータを取得
		template<typename T>
		T* GetShader();
		//テクスチャデータを取得
		//fileName = テクスチャのファイルパス
		TEXTURE_DATA* GetTexture(wchar_t* fileName);
		//文字のテクスチャを取得　なければnullptrを返す
		TEXTURE_DATA* GetFontTexture(wchar_t* text, WCHAR* fontName = (WCHAR*)L"ＭＳ Ｐ明朝");
		
	private:
		//テクスチャデータを探す見つからなければnullptrを返す
		//text = 探すデータの名前
		TEXTURE_DATA* FindTextureData(wchar_t* text);
		TEXTURE_DATA* FindTextureData(wchar_t text);
		//テクスチャを作る
		//filePath = 読み込むファイルパス
		TEXTURE_DATA* CreateTexture(std::wstring filePath);
		void LoadTextureInDir();
		ID3D11Device* mDevice;
		ID3D11DeviceContext* mDeviceContext;
		std::unique_ptr<DirLoder> mDirLoder;
		std::vector<std::unique_ptr<MeshInfo>> mMeshInfoList;
		std::vector<std::unique_ptr<ShaderInfo>> mShaderInfoList;
		std::vector<std::unique_ptr<TEXTURE_DATA>> mTextureList;
	};
	template<typename T>
	inline T * DXRenderDataPool::GetMesh()
	{
		T* pReturn = nullptr;
		for(auto &mesh:mMeshInfoList)
		{
			pReturn = dynamic_cast<T*>(mesh.get());
			if (pReturn != NULL)
				break;
		}
		if(pReturn == NULL)
		{
			pReturn = new T();
			mMeshInfoList.push_back(std::unique_ptr<T>(pReturn));
		}
		return pReturn;
	}
	template<typename T>
	inline T * DXRenderDataPool::GetShader()
	{
		T* pReturn = nullptr;
		for (auto &shader : mShaderInfoList)
		{
			pReturn = dynamic_cast<T*>(shader.get());
			if (pReturn != NULL)
				break;
		}
		if (pReturn == NULL)
		{
			pReturn = new T();
			mShaderInfoList.push_back(std::unique_ptr<T>(pReturn));
		}
		return pReturn;
	}
}

