#pragma once
namespace MyDirectX
{
	//�e�Q�[���I�u�W�F�N�g�ɐݒ�ł���^�O
	enum Tag
	{
		//�v���C���[
		PlayerTag = 0,
		//�G
		EnemyTag = 1,
		//���e
		PlayerBullet = 2,
		//�G�e
		EnemyBullet = 3,
		//���I��������A�C�e���@�V�[���J�n���ɂ���Δj�������
		DynamicInstantiateItem = 4,
		//�ÓI��������A�C�e���@�V�[���J�n���ɔj������Ȃ�
		StaticInstantiateItem = 5,
	};

	enum Category
	{
		CategoryPlayer = 0,
		CategoryBossEnemy = 1,
		CategoryNormalEnemy = 2,
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