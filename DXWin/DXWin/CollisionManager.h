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
		//�R���C�_�[���Z�b�g����
		void SetGameObjects(std::list<std::unique_ptr<DXGameObject>>* gameObjects);
		//�Փˏ���
		void Collision();
	private:
		//�Փ˔�����s����
		bool IsCollisionJudge(Tag shooter,Tag bullet);
		//�e�𔭎˂���I�u�W�F�N�g�̃R���C�_�[
		std::vector<Collider2D*> mShooterColliderList;
		//�e�̃R���C�_�[
		std::vector<Collider2D*> mBulletColliderList;
		//�A�C�e���̃R���C�_�[
		std::vector<Collider2D*> mItemColliderList;
	};
}


