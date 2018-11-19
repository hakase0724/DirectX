#pragma once
namespace MyDirectX
{
	//�e�Q�[���I�u�W�F�N�g�ɐݒ�ł���^�O
	enum Tag
	{
		PlayerTag = 0,
		EnemyTag = 1,
		PlayerBullet = 2,
		EnemyBullet = 3,
	};

	//�Ăяo���Փˉ���������
	enum CollisionType
	{
		//�Փ˂��Ă��Ȃ�
		NoCollision = 0,
		//�Փ˂��n�߂�
		Enter = 1,
		//�Փ˂��Ă���
		Stay = 2,
		//�Փ˂��I�����
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
}