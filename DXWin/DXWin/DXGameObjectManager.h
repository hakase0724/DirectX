#pragma once
#include "DXManager.h"
#include "DXCube.h"
#include "DXSphere.h"
#include <memory>
#include <vector> 
#include "DXGameObject.h"
#include "Mover.h"


namespace MyDirectX 
{
	class DXGameObjectManager
	{
	public:
		DXGameObjectManager(HWND hwnd);
		~DXGameObjectManager() {};
		DXManager* GetDXManager() const { return mDXManager.get(); }
		DXGameObject* Instantiate();
		BOOL Update();
		void Render();
	private:
		void CreateResources(HWND hwnd);
		void CreateGameObject();
		std::unique_ptr<DXManager> mDXManager;
		std::unique_ptr<DXCube> mDXCube;
		std::unique_ptr<DXSphere> mDXSphere;
		std::vector<std::unique_ptr<DXGameObject>> mGameObjectsList;
	};
	
}



