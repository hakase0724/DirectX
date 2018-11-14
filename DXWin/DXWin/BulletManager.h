#pragma once
#include "Bullet.h"
#include "DXGameObject.h"
#include "Colliders.h"
#include "MyStructs.h"
#include <list>

namespace MyDirectX
{
	class DXGameObjectManager;

	class BulletManager 
	{
	public:
		BulletManager(DXGameObjectManager* manager);
		~BulletManager() {};
		//オブジェクトプールに予め弾を格納しておく
		//preNum = 事前に生成しておく弾の数
		void CreatePreBullets(int preNum = 500);
		//弾を取得する
		DXGameObject* GetBullet(TRANSFORM* transform,Tag tag);
		DXGameObject* GetBullet(TRANSFORM* transform, Tag tag,float x,float y);
		//弾をオブジェクトプールに格納する
		void ReturnBullet(DXGameObject* bullet);
	private:
		DXGameObjectManager* mDXGameObjectManager;
		//弾を生成する
		DXGameObject* CreateBullet();
		std::list<DXGameObject*> mBulletList;
	};

}

