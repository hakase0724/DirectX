#pragma once
#include "DXManager.h"
#include "DXCube.h"
#include "DXCamera.h"
#include "DXInput.h"
#include "DXSphere.h"
#include <memory>
#include <vector> 
#include "DXGameObject.h"


namespace MyDirectX 
{
	class DXGameObjectManager
	{
	public:
		DXGameObjectManager(HWND hwnd);
		~DXGameObjectManager();
		HRESULT Init(HWND hwnd);
		DXManager* GetDXManager() const { return mDXManager.get(); }
		DXCamera* GetDXCamera() const { return mDXCamera.get(); }
		DXInput* GetDXInput() const { return mDXInput.get(); }
		BOOL Update();
		void Render();
	private:
		void CreateResources(HWND hwnd);
		void CreateGameObject();
		template <typename T> 
		void Instantiate();
		template <typename T>
		void Instantiate(TRANSFORM *transform);
		DXGameObject* InstantiateGameObjcet();
		std::unique_ptr<DXManager> mDXManager;
		std::unique_ptr<DXCamera> mDXCamera;
		std::unique_ptr<DXInput> mDXInput;
		std::vector<std::unique_ptr<DXGameObject>> mDXGameObjectArray;
		std::unique_ptr<DXCube> mDXCube;
	};
	
}



