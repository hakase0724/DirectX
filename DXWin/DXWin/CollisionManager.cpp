#include "stdafx.h"
#include "CollisionManager.h"

using namespace MyDirectX;

void CollisionManager::SetGameObjects(std::list<std::unique_ptr<DXGameObject>>* gameObjects)
{
	//�e�R���C�_�[�z����N���A
	mShooterColliderList.clear();
	mItemColliderList.clear();
	mBulletColliderList.clear();
	for(auto &game:*gameObjects)
	{
		//�A�N�e�B�u�łȂ���Ζ���
		if (!game->GetEnable()) continue;
		auto com = game->GetComponent<Collider2D>();
		//�R���C�_�[���Ȃ���Ζ�������
		if (com == nullptr) continue;
		//�R���C�_�[���A�N�e�B�u�łȂ���Ζ���
		if (!com->GetEnable()) continue;
		auto shooter = game->GetTag();
		//�L�����N�^�[
		if (shooter == PlayerTag || shooter == EnemyTag)
		{
			mShooterColliderList.push_back(com);
		}
		//�e
		else if (shooter == PlayerBullet || shooter == EnemyBullet)
		{
			mBulletColliderList.push_back(com);
		}
		//�A�C�e��
		else if(shooter == Item)
		{
			mItemColliderList.push_back(com);
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
		//�L�����N�^�[�ƃA�C�e���̓����蔻��
		for(auto item:mItemColliderList)
		{
			auto itemTag = item->GetTag();
			if (!IsCollisionJudge(shooterTag, itemTag)) continue;
			shooter->IsCollision(item);
			item->IsCollision(shooter);
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
	//�A�C�e���̏Փˉ���
	for(auto item:mItemColliderList)
	{
		//�Փ˂��Ă�����
		if (item->IsCollided()) item->OnCollision();
	}
	//�e�̏Փˉ���
	for (auto bullet : mBulletColliderList)
	{
		//�Փ˂��Ă�����
		if (bullet->IsCollided()) bullet->OnCollision();
	}
}

bool CollisionManager::IsCollisionJudge(Tag shooter, Tag tag2)
{
	//�����^�O�Ȃ画�肵�Ȃ�
	if (shooter == tag2) return false;
	//���@�Ǝ��@�̒e�͔��肵�Ȃ�
	if (shooter == PlayerTag && tag2 == PlayerBullet) return false;
	if (shooter == PlayerBullet && tag2 == PlayerTag) return false;
	//�G�ƓG�̒e�͔��肵�Ȃ�
	if (shooter == EnemyTag && tag2 == EnemyBullet) return false;
	if (shooter == EnemyBullet && tag2 == EnemyTag) return false;
	//�A�C�e���ƓG�͔��肵�Ȃ�
	if (shooter == Item && tag2 == EnemyTag) return false;
	if (shooter == Item && tag2 == EnemyBullet) return false;
	if (shooter == EnemyTag && tag2 == Item) return false;
	if (shooter == EnemyBullet && tag2 == Item) return false;
	//�e���m�͔��肵�Ȃ�
	if (shooter == PlayerBullet && tag2 == EnemyBullet) return false;
	return true;
}
