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
		else if(shooter == DynamicInstantiateItem || shooter == StaticInstantiateItem)
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

bool CollisionManager::CombinationIf(Tag comTag1, Tag comTag2, Tag checkTag1, Tag checkTag2)
{
	if (checkTag1 == comTag1 && checkTag2 == comTag2) return true;
	if (checkTag1 == comTag2 && checkTag2 == comTag1) return true;
	return false;
}

bool CollisionManager::IsCollisionJudge(Tag tag1, Tag tag2)
{
	if (CombinationIf(PlayerTag, EnemyTag, tag1, tag2)) return true;
	if (CombinationIf(PlayerTag, EnemyBullet, tag1, tag2)) return true;
	if (CombinationIf(PlayerTag, DynamicInstantiateItem, tag1, tag2)) return true;
	if (CombinationIf(PlayerTag, StaticInstantiateItem, tag1, tag2)) return true;
	if (CombinationIf(PlayerBullet, EnemyTag, tag1, tag2)) return true;
	return false;
}
