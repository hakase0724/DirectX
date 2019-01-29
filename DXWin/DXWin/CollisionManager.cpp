#include "stdafx.h"
#include "CollisionManager.h"

using namespace MyDirectX;

void CollisionManager::SetGameObjects(std::list<std::unique_ptr<DXGameObject>>* gameObjects)
{
	//各コライダー配列をクリア
	mShooterColliderList.clear();
	mItemColliderList.clear();
	mBulletColliderList.clear();
	for(auto &game:*gameObjects)
	{
		//アクティブでなければ無視
		if (!game->GetEnable()) continue;
		auto com = game->GetComponent<Collider2D>();
		//コライダーがなければ無視する
		if (com == nullptr) continue;
		//コライダーがアクティブでなければ無視
		if (!com->GetEnable()) continue;
		auto shooter = game->GetTag();
		//キャラクター
		if (shooter == PlayerTag || shooter == EnemyTag)
		{
			mShooterColliderList.push_back(com);
		}
		//弾
		else if (shooter == PlayerBullet || shooter == EnemyBullet)
		{
			mBulletColliderList.push_back(com);
		}
		//アイテム
		else if(shooter == DynamicInstantiateItem || shooter == StaticInstantiateItem)
		{
			mItemColliderList.push_back(com);
		}
	}
}

void CollisionManager::Collision()
{
	//当たり判定
	for (auto shooter : mShooterColliderList)
	{
		auto shooterTag = shooter->GetTag();
		//キャラクター同士の当たり判定
		for (auto shooter2 : mShooterColliderList)
		{
			auto shooter2Tag = shooter2->GetTag();
			if (!IsCollisionJudge(shooterTag, shooter2Tag)) continue;
			shooter->IsCollision(shooter2);
			shooter2->IsCollision(shooter);
		}
		//キャラクターとアイテムの当たり判定
		for(auto item:mItemColliderList)
		{
			auto itemTag = item->GetTag();
			if (!IsCollisionJudge(shooterTag, itemTag)) continue;
			shooter->IsCollision(item);
			item->IsCollision(shooter);
		}
		//キャラクターと弾の当たり判定
		for (auto bullet : mBulletColliderList)
		{
			auto bulletTag = bullet->GetTag();
			if (!IsCollisionJudge(shooterTag, bulletTag)) continue;
			shooter->IsCollision(bullet);
			bullet->IsCollision(shooter);
		}
	}

	//キャラクターの衝突応答
	for (auto shooter : mShooterColliderList)
	{
		//衝突していたら
		if (shooter->IsCollided()) shooter->OnCollision();
	}
	//アイテムの衝突応答
	for(auto item:mItemColliderList)
	{
		//衝突していたら
		if (item->IsCollided()) item->OnCollision();
	}
	//弾の衝突応答
	for (auto bullet : mBulletColliderList)
	{
		//衝突していたら
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
