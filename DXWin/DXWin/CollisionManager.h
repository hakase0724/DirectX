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
		void SetGameObjects(std::vector<DXGameObject*> gameObjects);
		void Collision();
	private:
		bool IsCollisionJudge(Tag shooter,Tag bullet);
		std::vector<Collider2D*> mShooterColliderList;
		std::vector<Collider2D*> mBulletColliderList;
	};
}


