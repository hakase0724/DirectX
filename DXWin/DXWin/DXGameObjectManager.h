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
		BOOL Update();
		void Render();
	private:
		void CreateResources(HWND hwnd);
		void CreateGameObject();
		std::unique_ptr<DXManager> mDXManager;
		std::unique_ptr<DXCube> mDXCube;
	};
	
}



