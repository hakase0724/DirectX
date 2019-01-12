#pragma once
#include "DXGameObject.h"
#include <vector>
#include "Colliders.h"

namespace MyDirectX
{
	class CollisionManager
	{
	public:
		CollisionManager() {};
		~CollisionManager() {};
		//コライダーをセットする
		void SetGameObjects(std::list<std::unique_ptr<DXGameObject>>* gameObjects);
		//衝突処理
		void Collision();
	private:
		//衝突判定を行うか
		bool IsCollisionJudge(Tag shooter,Tag bullet);
		//弾を発射するオブジェクトのコライダー
		std::vector<Collider2D*> mShooterColliderList;
		//弾のコライダー
		std::vector<Collider2D*> mBulletColliderList;
		//アイテムのコライダー
		std::vector<Collider2D*> mItemColliderList;
	};
}


