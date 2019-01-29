#pragma once
#include "ScoreItem.h"
#include "DXGameObject.h"
#include "Colliders.h"
#include "MyStructs.h"
#include <list>
#include "Scene.h"

namespace MyDirectX
{
	class ScoreItemPool
	{
	public:
		ScoreItemPool() {};
		~ScoreItemPool() {};
		void SetScene(Scene* scene) { mScene = scene; }
		void CreatePreScoreItem(int preNum);
		DXGameObject* GetScoreItem(DirectX::XMFLOAT3 pos);
		void ReturnScoreItem(DXGameObject* scoreItem);
	private:
		Scene* mScene;
		//スコアアイテムを生成する
		DXGameObject* CreateScoreItem();
		std::list<DXGameObject*> mScoreItemList;
	};
}


