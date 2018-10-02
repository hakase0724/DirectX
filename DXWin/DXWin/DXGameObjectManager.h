#pragma once
#include "DXManager.h"
#include "DXCube.h"
#include "DXCamera.h"
#include "DXInput.h"
#include <memory>


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
		DXCube* GetDXCube() const { return mDXCube.get(); }
		DXInput* GetDXInput() const { return mDXInput.get(); }
		BOOL Update();
		void Render();
	private:
		std::unique_ptr<DXManager> mDXManager;
		std::unique_ptr<DXCamera> mDXCamera;
		std::unique_ptr<DXCube> mDXCube;
		std::unique_ptr<DXCube> mDXCube2;
		std::unique_ptr<DXCube> mDXCube3;
		std::unique_ptr<DXInput> mDXInput;
	};
}



