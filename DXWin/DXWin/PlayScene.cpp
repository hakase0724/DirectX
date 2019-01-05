#include "stdafx.h"
#include "PlayScene.h"
#include <DirectXMath.h>
#include "Mover.h"
#include "BossEnemy.h"
#include "NormalEnemy.h"
#include "HPGauge.h"
#include "DXAnimation.h"
#include <sstream>
#include "Bomb.h"
#include "PowerUpItem.h"

using namespace DirectX;
using namespace MyDirectX;

void PlayScene::Init()
{
	//�e���Ǘ��N���X
	mBarrageManager = std::make_unique<BarrageManager>();

	CreateBulletPool();
	CreateUIItem();
	CreateItem();
	CreateFromCSVData();
	CreateBackGround();

	//�e��J�E���g��������
	mWaveCount = 0;
	mFrameCount = FPS_CHEACK_FRAME_COUNT;

	//���w���������X�g�ɒǉ�
	for(auto game:mEnemyWaveList[0])
	{
		mAwakeObject.push_back(game);
	}

	//�S�ẴI�u�W�F�N�g�̏����ʒu��ݒ肷��
	for(auto &game: mGameObjectsList)
	{
		game->SetDefaultTransform();
	}
}

void PlayScene::SceneStart()
{
	//�E�F�[�u��񃊃Z�b�g
	mWaveCount = 0;
	mIsLastWave = false;
	*mScoreRP = 0;
	//�S�ẴI�u�W�F�N�g�̏�����
	for(auto &game:mGameObjectsList)
	{
		game->InitializeComponent();
	}
	//�ŏ����炢��I�u�W�F�N�g�̃A�N�e�B�u��
	for(auto game:mAwakeObject)
	{
		game->SetEnable(true);
	}
	//�ȍĐ�
	mDXRescourceManager->GetBGMDXSound()->Play();
}

void PlayScene::SceneUpdate()
{
	auto fps = mDXRescourceManager->GetFPS();
	mFrameCount++;
	*mHpRP = mPlayerCom->GetHP();
	
	//FPS���v�Z���o�͂���
	//���t���[���o���ƕω�������������̂ň��Ԋu�ōX�V
	if (mFrameCount % FPS_CHEACK_FRAME_COUNT == 0)
	{
		*mFPSRP = fps;
	}
	//�w�i�𓮂���
	mBackGround->UpdateBackGrounds();

	//���̃E�F�[�u�֍s����
	bool isNext = true;
	//���݃E�F�[�u�̓G����̂ł��������Ă����玟�E�F�[�u�֍s���Ȃ�
	for(auto game:mEnemyWaveList[mWaveCount])
	{
		if (game->GetEnable()) isNext = false;
	}

	if(isNext)
	{
		mWaveCount++;
		//�ŏI�E�F�[�u��
		if (mWaveCount == mEnemyWaveList.size() - 1) mIsLastWave = true;
		//�������E�F�[�u�����p�ӂ��Ă��鐔�𒴂����珈�����Ȃ�
		if (mWaveCount >= (int)mEnemyWaveList.size()) return;
		//���E�F�[�u�̓G���A�N�e�B�u��
		for (auto game : mEnemyWaveList[mWaveCount])
		{
			game->SetEnable(true);
		}
	}
}

void PlayScene::SceneEnd()
{
	//�S�ẴI�u�W�F�N�g�̃A�N�e�B�u��؂�
	for (auto &game : mGameObjectsList)
	{
		game->SetEnable(false);
	}
	//�Ȃ��~�߂�
	mDXRescourceManager->GetBGMDXSound()->Stop();
}

bool PlayScene::IsSceneEnd()
{
	//���@�����񂾂�
	if (!mPlayer->GetEnable()) 
	{
		mDXRescourceManager->GetSEDXSound()->Stop();
		return true;
	}
	//�ŏI�E�F�[�u�Ŏw��G�����񂾂�
	if (mIsLastWave) if (!mEnemy->GetEnable()) 
	{
		//mDXRescourceManager->GetSEDXSound()->Stop();
		return true;
	}
	return false;
}

void PlayScene::CreatePlayer(LOAD_FROM_CSV_DATA data)
{
	//���@
	mPlayer = Instantiate();
	mPlayer->SetName(data.Name);
	auto transform = mPlayer->GetTransform();
	transform->Position = data.StartPos;
	auto texture = mPlayer->AddComponent<DXTexture>();
	auto anim = mPlayer->AddComponent<DXAnimation>();
	anim->SetAnimationTexture(texture);
	anim->SetAnimationFile(_T("Texture/Player1.png"));
	anim->SetAnimationFile(_T("Texture/Player2.png"));
	mPlayer->SetTag(data.Tag);
	mPlayer->AddComponent<Mover>();
	mPlayerCom = mPlayer->AddComponent<Player>();
	mPlayerCom->SetBulletPool(mBulletPool.get());
	mPlayerCom->SetHP(data.HP);
	auto playerCol = mPlayer->AddComponent<SquareCollider2D>();
	//���@�̃R���C�_�[��30����1
	playerCol->SetOneSide(playerCol->GetOneSide() / 30.0f);
	mAwakeObject.push_back(mPlayer);
}

void PlayScene::CreateBossEnemy(LOAD_FROM_CSV_DATA data)
{
	//�{�X�G
	mEnemy = Instantiate();
	mEnemy->SetName(data.Name);
	mEnemy->SetTag(data.Tag);
	auto enemyTex = mEnemy->AddComponent<DXTexture>();
	enemyTex->SetTexture(_T("Texture/Enemy.png"));
	auto texPos = mEnemy->GetTransform();
	texPos->Position = data.StartPos;
	auto enemy = mEnemy->AddComponent<BossEnemy>();
	enemy->SetBulletPool(mBulletPool.get());
	enemy->SetPlayer(mPlayer);
	enemy->SetBarrageManager(mBarrageManager.get());
	enemy->SetHP(data.HP);
	auto battleStartPos = data.StartPos;
	battleStartPos.y -= 1;
	enemy->SetBattleStartPos(battleStartPos);
	auto enemyCol = mEnemy->AddComponent<SquareCollider2D>();
	//�{�X�̃R���C�_�[��2����1��
	enemyCol->SetOneSide(enemyCol->GetOneSide() / 2.0f);
	enemy->SetCollider(enemyCol);

	//�̗̓Q�[�W
	auto gauge = Instantiate();
	auto renderer = gauge->AddComponent<TextureRenderer>();
	auto gaugeTex = gauge->AddComponent<DXTexture>();
	auto gaugeCom = gauge->AddComponent<HPGauge>();
	gaugeCom->SetHPViewObject(enemy);
	//�Q�[�W�̐F
	renderer->SetDefaultColor(1.0f, 0.8f, 0.0f, 0.5f);
	gaugeTex->SetTexture(_T("Texture/Square.png"));
	auto gaugeTransform = gauge->GetTransform();
	//�Q�[�W�̈ʒu�ƒ���
	gaugeTransform->Position.y = 1.3f;
	gaugeTransform->Position.z = -0.1f;
	gaugeTransform->Scale.y = 0.1f;
	gaugeTransform->Scale.x = 3.0f;

	mEnemyWaveList[data.Wave - 1].push_back(mEnemy);
	mEnemyWaveList[data.Wave - 1].push_back(gauge);
}

void PlayScene::CreateNormalEnemy(LOAD_FROM_CSV_DATA data)
{
	auto normalEnemy = Instantiate();
	normalEnemy->SetName(data.Name);
	normalEnemy->SetTag(data.Tag);
	auto normalEnemyTex = normalEnemy->AddComponent<DXTexture>();
	normalEnemyTex->SetTexture(_T("Texture/NormalEnemy.png"));
	auto normalEnemyTexPos = normalEnemy->GetTransform();
	normalEnemyTexPos->Position = data.StartPos;
	//�T�C�Y�𔼕���
	normalEnemyTexPos->Scale.x /= 2;
	normalEnemyTexPos->Scale.y /= 2;
	normalEnemyTexPos->Scale.z /= 2;
	auto normaEenemyCom = normalEnemy->AddComponent<NormalEnemy>();
	normaEenemyCom->SetHP(data.HP);
	normaEenemyCom->SetBulletPool(mBulletPool.get());
	normaEenemyCom->SetPlayer(mPlayer);
	normaEenemyCom->SetBarrageManager(mBarrageManager.get());
	auto normalEnemyCol = normalEnemy->AddComponent<SquareCollider2D>();
	//�G�̃R���C�_�[��2����1��
	normalEnemyCol->SetOneSide(normalEnemyCol->GetOneSide() / 2.0f);

	mEnemyWaveList[data.Wave - 1].push_back(normalEnemy);
}

void PlayScene::CreateBackGround()
{
	/*
	�w�i�𓮂����C���[�W

	�@�@�@�@�@�@ ��
		�w �i 2�@��
		   ���@�@��
		�w �i 1�@��
		   ���@�@��
		   ��������
	*/

	//�w�i�p�摜1
	auto back = Instantiate();
	auto texBack = back->AddComponent<DXTexture>();
	texBack->SetTexture(_T("Texture/background.png"));
	auto backTransform = back->GetTransform();
	backTransform->Position.z = 2.0f;
	backTransform->Scale.x = 5.0f;
	backTransform->Scale.y = 5.0f;
	mAwakeObject.push_back(back);

	//�w�i�p�摜2
	auto back2 = Instantiate();
	auto texBack2 = back2->AddComponent<DXTexture>();
	texBack2->SetTexture(_T("Texture/background.png"));
	auto backTransform2 = back2->GetTransform();
	backTransform2->Position.y = 5.0f;
	backTransform2->Position.z = 2.0f;
	backTransform2->Scale.x = 5.0f;
	backTransform2->Scale.y = 5.0f;
	mAwakeObject.push_back(back2);

	//�w�i�𓮂����N���X
	mBackGround = std::make_unique<BackGround>();
	mBackGround->SetBackGrounds(back, back2);

	/*

	���с@�@�@ ����
	 ���@�@�@�@ ��
	*** �w�@�i ***
	*** �w�@�i ***
	*** �w�@�i ***
	*** �w�@�i ***

	*/

	//�E�̍���
	auto black = Instantiate();
	auto blackBack = black->AddComponent<DXTexture>();
	blackBack->SetTexture(_T("Texture/black.png"));
	auto blackTransform = black->GetTransform();
	blackTransform->Position.z = -1.0f;
	blackTransform->Position.x = 1.63f;
	blackTransform->Scale.y = 3.0f;
	mAwakeObject.push_back(black);

	//���̍���
	auto black2 = Instantiate();
	auto blackBack2 = black2->AddComponent<DXTexture>();
	blackBack2->SetTexture(_T("Texture/black.png"));
	auto blackTransform2 = black2->GetTransform();
	blackTransform2->Position.z = -1.0f;
	blackTransform2->Position.x = -1.63f;
	blackTransform2->Scale.y = 3.0f;
	mAwakeObject.push_back(black2);
}

void PlayScene::CreateFromCSVData()
{
	//�f�[�^�ǂݍ���
	auto dataTable = mDXRescourceManager->LoadData("Data/Data.csv");

	//���E�F�[�u�܂ł���̂�
	int maxWave = 0;
	for (auto data : dataTable)
	{
		if (data.Wave > maxWave) maxWave = data.Wave;
	}

	//�E�F�[�u���z���p�ӂ���
	for (int i = 0; i < maxWave; i++)
	{
		std::vector<DXGameObject*> enemyList;
		mEnemyWaveList.push_back(enemyList);
	}

	//�ǂݍ��񂾃f�[�^�ɏ]���Ď��@�ƓG�����
	for (auto data : dataTable)
	{
		switch (data.Category)
		{
		case CategoryPlayer:
			CreatePlayer(data);
			break;
		case CategoryBossEnemy:
			CreateBossEnemy(data);
			break;
		case CategoryNormalEnemy:
			CreateNormalEnemy(data);
			break;
		default:
			break;
		}
	}
}

void PlayScene::CreateUIItem()
{
	//HP�\���e�L�X�g
	auto hp = Instantiate();
	mHPText = hp->AddComponent<DXText>();
	auto hptransform = hp->GetTransform();
	//�ʒu�Ƒ傫��
	hptransform->Scale = XMFLOAT3(0.07f, 0.07f, 1.0f);
	hptransform->Position = XMFLOAT3(1.2f, 0.8f, -1.1f);
	mAwakeObject.push_back(hp);

	//Score�\���e�L�X�g
	auto scoreNotice = Instantiate();
	auto scoreText = scoreNotice->AddComponent<DXText>();
	auto scoreNoticetransform = scoreNotice->GetTransform();
	//�ʒu�Ƒ傫��
	scoreNoticetransform->Scale = XMFLOAT3(0.07f, 0.07f, 1.0f);
	scoreNoticetransform->Position = XMFLOAT3(-1.7f, 0.9f, -1.1f);
	scoreText->UpdateText(L"SCORE");
	mAwakeObject.push_back(scoreNotice);

	//Score�\���e�L�X�g
	auto score = Instantiate();
	mScoreText = score->AddComponent<DXText>();
	auto scoretransform = score->GetTransform();
	//�ʒu�Ƒ傫��
	scoretransform->Scale = XMFLOAT3(0.07f, 0.07f, 1.0f);
	scoretransform->Position = XMFLOAT3(-1.7f, 0.8f, -1.1f);
	mAwakeObject.push_back(score);

	//FPS�\���e�L�X�g
	auto fps = Instantiate();
	mFPSText = fps->AddComponent<DXText>();
	auto transform = fps->GetTransform();
	//�ʒu�Ƒ傫��
	transform->Scale = XMFLOAT3(0.07f, 0.07f, 1.0f);
	transform->Position = XMFLOAT3(1.2f, -0.8f, -1.1f);
	mAwakeObject.push_back(fps);

	//HP�\���Ɏg���ϐ�
	mHpRP =
		std::unique_ptr<Property, Deleter>
		(new Property(), Deleter());

	//�ϐ��ɕω������������ɕ\�����鏈����o�^
	mHpRP->Subscribe
	(
	[&](double value)->void
	{
		std::wstringstream hp;
		hp.precision(6);
		hp << value;
		auto hpt = hp.str();
		auto hpptr = hpt.c_str();
		mHPText->UpdateText(hpptr);
		hp.clear();
	}
	);

	// Score�\���Ɏg���ϐ�
	mScoreRP =
		std::unique_ptr<Property, Deleter>
		(new Property(), Deleter());

	//�ϐ��ɕω������������ɕ\�����鏈����o�^
	mScoreRP->Subscribe
	(
	[&](double value)->void
	{
		std::wstringstream score;
		score.precision(6);
		score << value;
		auto scoret = score.str();
		auto scoreptr = scoret.c_str();
		mScoreText->UpdateText(scoreptr);
		score.clear();
	}
	);

	//FPS�\���Ɏg���ϐ�
	mFPSRP =
		std::unique_ptr<Property, Deleter>
		(new Property(), Deleter());

	//�ϐ��ɕω������������ɕ\�����鏈����o�^
	mFPSRP->Subscribe
	(
	[&](double value)->void
	{
		mFrameCount = 0;
		//�����o�ϐ��Ɏ��ƒl���Œ肳��Ă��܂��E�E�E
		std::wstringstream ws;
		//�L�������w��
		ws.precision(6);
		ws << value;
		auto t = ws.str();
		auto pt = t.c_str();
		mFPSText->UpdateText(pt);
		//���g���N���A����
		ws.clear();
	}
	);
}

void PlayScene::CreateItem()
{
	//�{��
	auto bomb = Instantiate();
	auto bombTex = bomb->AddComponent<DXTexture>();
	bombTex->SetTexture(L"Texture/Bomb.png");
	auto bombTransform = bomb->GetTransform();
	bombTransform->Position = XMFLOAT3(0.0f, 0.3f, -1.0f);
	bombTransform->Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	bomb->AddComponent<Bomb>();
	auto bombCol = bomb->AddComponent<SquareCollider2D>();
	//�R���C�_�[��2����1��
	bombCol->SetOneSide(bombCol->GetOneSide() / 3.0f);
	mAwakeObject.push_back(bomb);

	//�p���[�A�b�v
	auto powerUp = Instantiate();
	auto powerUpTex = powerUp->AddComponent<DXTexture>();
	powerUpTex->SetTexture(L"Texture/Power.png");
	auto powerUpTransform = powerUp->GetTransform();
	powerUpTransform->Position = XMFLOAT3(0.3f, 0.3f, -1.0f);
	powerUpTransform->Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	powerUp->AddComponent<PowerUpItem>();
	auto powerUpCol = powerUp->AddComponent<SquareCollider2D>();
	//�R���C�_�[��3����1��
	powerUpCol->SetOneSide(powerUpCol->GetOneSide() / 3.0f);
	mAwakeObject.push_back(powerUp);
}

void PlayScene::CreateBulletPool()
{
	//�e�̃I�u�W�F�N�g�v�[��
	mBulletPool = std::make_unique<BulletPool>();
	mBulletPool->SetScene(this);
	//�\��1000���p�ӂ��Ă���
	mBulletPool->CreatePreBullets(1000);
}

