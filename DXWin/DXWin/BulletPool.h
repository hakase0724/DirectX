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
		//�I�u�W�F�N�g�v�[���ɗ\�ߒe���i�[���Ă���
		//preNum = ���O�ɐ������Ă����e�̐�
		void CreatePreBullets(int preNum = 500);
		//�e���擾����
		DXGameObject* GetBullet(TRANSFORM* transform, Tag tag);
		DXGameObject* GetBullet(TRANSFORM* transform, Tag tag, float x, float y);
		//�e���I�u�W�F�N�g�v�[���Ɋi�[����
		void ReturnBullet(DXGameObject* bullet);
	private:
		Scene* mScene;
		//�e�𐶐�����
		DXGameObject* CreateBullet();
		std::list<DXGameObject*> mBulletList;
	};

}
