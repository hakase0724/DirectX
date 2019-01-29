#pragma once
#include "PowerUpItem.h"
#include "DXGameObject.h"
#include "Colliders.h"
#include "MyStructs.h"
#include <list>
#include "Scene.h"

namespace MyDirectX
{
	class PowerUpItemPool
	{
	public:
		PowerUpItemPool() {};
		~PowerUpItemPool() {};
		void SetScene(Scene* scene) { mScene = scene; }
		void CreatePrePowerUpItem(int preNum);
		DXGameObject* GetPowerUpItem(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 scale);
		void ReturnPowerUpItem(DXGameObject* powerUpItem);
	private:
		Scene* mScene;
		//É{ÉÄÇê∂ê¨Ç∑ÇÈ
		DXGameObject* CreatePowerUpItem();
		std::list<DXGameObject*> mPowerUpItemList;
	};
}


