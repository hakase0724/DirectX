#pragma once
namespace MyDirectX
{
	//各ゲームオブジェクトに設定できるタグ
	enum Tag
	{
		PlayerTag = 0,
		EnemyTag = 1,
		PlayerBullet = 2,
		EnemyBullet = 3,
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
}