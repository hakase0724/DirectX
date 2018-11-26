#include "stdafx.h"
#include "CollisionManager.h"

using namespace MyDirectX;

void CollisionManager::SetGameObjects(std::vector<DXGameObject*> gameObjects)
{
	//�e�R���C�_�[�z����N���A
	mShooterColliderList.clear();
	mBulletColliderList.clear();
	for(auto game:gameObjects)
	{
		if (!game->GetEnable()) continue;
		auto com = game->GetComponent<Collider2D>();
		//�R���C�_�[���Ȃ���Ζ�������
		if (com == nullptr) continue;
		auto tag = game->GetTag();
		//�L�����N�^�[
		if (tag == Tag::PlayerTag || tag == Tag::EnemyTag)
		{
			mShooterColliderList.push_back(com);
		}
		//�e
		else if (tag == Tag::PlayerBullet || tag == Tag::EnemyBullet)
		{
			mBulletColliderList.push_back(com);
		}
	}
}

void CollisionManager::Collision()
{
	//�����蔻��
	for (auto shooter : mShooterColliderList)
	{
		auto shooterTag = shooter->GetTag();
		//�L�����N�^�[���m�̓����蔻��
		for (auto shooter2 : mShooterColliderList)
		{
			auto shooter2Tag = shooter2->GetTag();
			if (!IsCollisionJudge(shooterTag, shooter2Tag)) continue;
			shooter->IsCollision(shooter2);
			shooter2->IsCollision(shooter);
		}
		//�L�����N�^�[�ƒe�̓����蔻��
		for (auto bullet : mBulletColliderList)
		{
			auto bulletTag = bullet->GetTag();
			if (!IsCollisionJudge(shooterTag, bulletTag)) continue;
			shooter->IsCollision(bullet);
			bullet->IsCollision(shooter);
		}
	}

	//�L�����N�^�[�̏Փˉ���
	for (auto shooter : mShooterColliderList)
	{
		//�Փ˂��Ă�����
		if (shooter->IsCollided()) shooter->OnCollision();
	}
	//�e�̏Փˉ���
	for (auto bullet : mBulletColliderList)
	{
		//�Փ˂��Ă�����
		if (bullet->IsCollided()) bullet->OnCollision();
	}
}

bool CollisionManager::IsCollisionJudge(Tag shooter, Tag bullet)
{
	//�����^�O�Ȃ画�肵�Ȃ�
	if (shooter == bullet) return false;
	//���@�Ǝ��@�̒e�͔��肵�Ȃ�
	if (shooter == Tag::PlayerTag && bullet == Tag::PlayerBullet) return false;
	if (shooter == Tag::PlayerBullet && bullet == Tag::PlayerTag) return false;
	//�G�@�ƓG�@�̒e�͔��肵�Ȃ�
	if (shooter == Tag::EnemyTag && bullet == Tag::EnemyBullet) return false;
	if (shooter == Tag::EnemyBullet && bullet == Tag::EnemyTag) return false;
	//�e���m�͔��肵�Ȃ�
	if (shooter == Tag::PlayerBullet && bullet == Tag::EnemyBullet) return false;
	return true;
}
