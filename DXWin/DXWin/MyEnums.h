#pragma once
namespace MyDirectX
{
	//各ゲームオブジェクトに設定できるタグ
	enum Tag
	{
		//プレイヤー
		PlayerTag = 0,
		//敵
		EnemyTag = 1,
		//自弾
		PlayerBullet = 2,
		//敵弾
		EnemyBullet = 3,
		//動的生成するアイテム　シーン開始時にあれば破棄される
		DynamicInstantiateItem = 4,
		//静的生成するアイテム　シーン開始時に破棄されない
		StaticInstantiateItem = 5,
	};

	enum Category
	{
		CategoryPlayer = 0,
		CategoryBossEnemy = 1,
		CategoryNormalEnemy = 2,
	};

	//呼び出す衝突応答を示す
	enum CollisionType
	{
		//衝突していない
		NoCollision = 0,
		//衝突し始めた
		Enter = 1,
		//衝突している
		Stay = 2,
		//衝突が終わった
		Exit = 3
	};

	enum BarrageName
	{
		AllDirectionsSync = 0,
		AllDirectionsAsync = 1,
		TargetPlayer = 2,
		SixWayRazer = 3,
	};

	enum SceneState
	{
		Title = 0,
		Play = 1,
		Result = 2,
	};

	enum BossState
	{
		Entry = 0,
		Battle = 1,
		BossDie = 2
	};

	enum ItemType
	{
		NoDrop = -1,
		Score = 0,
		PowerUp = 1,
		BombItem = 2,
	};
}