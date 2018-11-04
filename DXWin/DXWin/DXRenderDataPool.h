#pragma once
#include "MeshAndShader.h"
#include <vector>
#include <memory>
#include <typeinfo>

namespace MyDirectX
{
	class DXRenderDataPool
	{
	public:
		DXRenderDataPool() {};
		~DXRenderDataPool() {};
		template<typename T>
		T* GetMesh();
		template<typename T>
		T* GetShader();
		
	private:
		std::vector<std::unique_ptr<MeshInfo>> mMeshInfoList;
		std::vector<std::unique_ptr<ShaderInfo>> mShaderInfoList;
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

