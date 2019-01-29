#pragma once
#include "ExplosionEffect.h"
#include "DXGameObject.h"
#include "Colliders.h"
#include "MyStructs.h"
#include <list>
#include "Scene.h"
namespace MyDirectX
{
	class ExplosionEffectPool
	{
	public:
		ExplosionEffectPool() {};
		~ExplosionEffectPool() {};
		void SetScene(Scene* scene) { mScene = scene; }
		void CreatePreExplosionEffect(int preNum);
		DXGameObject* GetExplosionEffect(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 scale);
		void ReturnExplosionEffect(DXGameObject* explosionEffect);
	private:
		Scene* mScene;
		//スコアアイテムを生成する
		DXGameObject* CreateExplosionEffect();
		std::list<DXGameObject*> mExplosionEffectList;
	};
}


