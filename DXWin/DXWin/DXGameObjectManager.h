#pragma once
#include "DXManager.h"
#include "DXCube.h"
#include "DXSphere.h"
#include <memory>
#include <vector> 
#include "DXGameObject.h"
#include "Mover.h"
#include "Collider.h"
#include "DXSquare.h"
#include "Roller.h"
#include "Colliders.h"


namespace MyDirectX 
{
	class DXGameObjectManager
	{
	public:
		DXGameObjectManager(HWND hwnd);
		~DXGameObjectManager() {};
		DXManager* GetDXManager() const { return mDXManager.get(); }
		DXGameObject* Instantiate();
		DXGameObject* CreateCube();
		DXGameObject* CreateSphere();
		DXGameObject* CreateSquare();
		template<typename T>
		DXGameObject* Create();
		BOOL Update();
		void LateUpdate();
		void FixedUpdate();
		void Render();
	private:
		void CreateResources(HWND hwnd);
		void CreateGameObject();
		std::unique_ptr<DXManager> mDXManager;
		std::vector<std::unique_ptr<DXGameObject>> mGameObjectsList;
		SquareCollider2D* testCollider1;
		SquareCollider2D* testCollider2;
	};
	
	template<typename T>
	inline DXGameObject * DXGameObjectManager::Create()
	{
		auto gameObject = Instantiate();
		gameObject->AddComponent<T>();
		return gameObject;
	}

}



