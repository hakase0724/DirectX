#pragma once
#include "Scene.h"
#include "DXResourceManager.h"
#include "CollisionManager.h"
namespace MyDirectX
{
	class DXExcuter
	{
	public:
		DXExcuter();
		~DXExcuter();
		void SetScene(Scene* scene);
		void SetDXResourceManager(DXResourceManager* manager) { mDXRescourceManager = manager; }
		void Excute();
	private:
		Scene* mScene;
		void Update();
		void LateUpdate();
		void Render();
		std::vector<DXGameObject*> mExcuteObjectsList;
		std::unique_ptr<CollisionManager> mCollisionManager;
		DXResourceManager* mDXRescourceManager;
	};
}

