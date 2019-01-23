#pragma once
#include "Bullet.h"
#include "DXGameObject.h"
#include "Colliders.h"
#include "MyStructs.h"
#include <list>
#include "Scene.h"

namespace MyDirectX
{
	class BulletPool
	{
	public:
		BulletPool() {};
		~BulletPool() {};
		void SetScene(Scene* scene) { mScene = scene; }
		//オブジェクトプールに予め弾を格納しておく
		//preNum = 事前に生成しておく弾の数
		void CreatePreBullets(int preNum);
		//弾を取得する
		DXGameObject* GetBullet(BULLET_SETTING_DATA data);
		//弾をオブジェクトプールに格納する
		void ReturnBullet(DXGameObject* bullet);
	private:
		Scene* mScene;
		//弾を生成する
		DXGameObject* CreateBullet();
		std::list<DXGameObject*> mBulletList;
	};

}

