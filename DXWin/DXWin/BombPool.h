#pragma once
#include "Bomb.h"
#include "DXGameObject.h"
#include "Colliders.h"
#include "MyStructs.h"
#include <list>
#include "Scene.h"

namespace MyDirectX 
{
	class BombPool
	{
	public:
		BombPool() {};
		~BombPool() {};
		void SetScene(Scene* scene) { mScene = scene; }
		void CreatePreBomb(int preNum);
		DXGameObject* GetBomb(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 scale);
		void ReturnBomb(DXGameObject* bomb);
	private:
		Scene* mScene;
		//É{ÉÄÇê∂ê¨Ç∑ÇÈ
		DXGameObject* CreateBomb();
		std::list<DXGameObject*> mBombList;
	};
}


