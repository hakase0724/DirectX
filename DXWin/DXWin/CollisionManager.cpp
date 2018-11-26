#include "stdafx.h"
#include "CollisionManager.h"

using namespace MyDirectX;

void CollisionManager::SetGameObjects(std::vector<DXGameObject*> gameObjects)
{
	//各コライダー配列をクリア
	mShooterColliderList.clear();
	mBulletColliderList.clear();
	for(auto game:gameObjects)
	{
		if (!game->GetEnable()) continue;
		auto com = game->GetComponent<Collider2D>();
		//コライダーがなければ無視する
		if (com == nullptr) continue;
		auto tag = game->GetTag();
		//キャラクター
		if (tag == Tag::PlayerTag || tag == Tag::EnemyTag)
		{
			mShooterColliderList.push_back(com);
		}
		//弾
		else if (tag == Tag::PlayerBullet || tag == Tag::EnemyBullet)
		{
			mBulletColliderList.push_back(com);
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
	//弾の衝突応答
	for (auto bullet : mBulletColliderList)
	{
		//衝突していたら
		if (bullet->IsCollided()) bullet->OnCollision();
	}
}

bool CollisionManager::IsCollisionJudge(Tag shooter, Tag bullet)
{
	//同じタグなら判定しない
	if (shooter == bullet) return false;
	//自機と自機の弾は判定しない
	if (shooter == Tag::PlayerTag && bullet == Tag::PlayerBullet) return false;
	if (shooter == Tag::PlayerBullet && bullet == Tag::PlayerTag) return false;
	//敵機と敵機の弾は判定しない
	if (shooter == Tag::EnemyTag && bullet == Tag::EnemyBullet) return false;
	if (shooter == Tag::EnemyBullet && bullet == Tag::EnemyTag) return false;
	//弾同士は判定しない
	if (shooter == Tag::PlayerBullet && bullet == Tag::EnemyBullet) return false;
	return true;
}
