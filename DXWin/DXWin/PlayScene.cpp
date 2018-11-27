#include "stdafx.h"
#include "PlayScene.h"
#include <DirectXMath.h>
#include "DXTexture.h"
#include "Player.h"
#include "Mover.h"
#include "BossEnemy.h"
#include "NormalEnemy.h"
#include "HPGauge.h"
#include <sstream>

using namespace DirectX;
using namespace MyDirectX;

void PlayScene::Init()
{
	//�e���Ǘ��N���X
	mBarrageManager = std::make_unique<BarrageManager>();
	//�e�̃I�u�W�F�N�g�v�[��
	mBulletPool = std::make_unique<BulletPool>();
	mBulletPool->SetScene(this);
	mBulletPool->CreatePreBullets(1000);

	//FPS�\���e�L�X�g
	auto fps = Instantiate();
	mFPSText = fps->AddComponent<DXText>();
	auto transform = fps->GetTransform();
	transform->Scale = XMFLOAT3(0.07f, 0.07f, 1.0f);
	transform->Position = XMFLOAT3(1.2f, -0.8f, -1.1f);
	mAwakeObject.push_back(fps);

	//���@
	mPlayer = Instantiate();
	auto playerTex = mPlayer->AddComponent<DXTexture>();
	playerTex->SetTexture();
	mPlayer->SetTag(Tag::PlayerTag);
	mPlayer->AddComponent<Mover>();
	auto player = mPlayer->AddComponent<Player>();
	player->SetBulletPool(mBulletPool.get());
	auto playerCol = mPlayer->AddComponent<SquareCollider2D>();
	playerCol->SetOneSide(playerCol->GetOneSide() / 30.0f);
	mAwakeObject.push_back(mPlayer);

	//���w
	std::vector<DXGameObject*> firstWave;
	//���w
	std::vector<DXGameObject*> secondWave;

	//�G���G
	auto normalEnemy = Instantiate();
	normalEnemy->SetTag(EnemyTag);
	auto normalEnemyTex = normalEnemy->AddComponent<DXTexture>();
	normalEnemyTex->SetTexture(_T("Texture/NormalEnemy.png"));
	auto normalEnemyTexPos = normalEnemy->GetTransform();
	normalEnemyTexPos->Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	normalEnemyTexPos->Scale.x /= 2;
	normalEnemyTexPos->Scale.y /= 2;
	normalEnemyTexPos->Scale.z /= 2;
	auto normaEenemyCom = normalEnemy->AddComponent<NormalEnemy>();
	normaEenemyCom->SetBulletPool(mBulletPool.get());
	normaEenemyCom->SetPlayer(mPlayer);
	normaEenemyCom->SetBarrageManager(mBarrageManager.get());
	auto normalEnemyCol = normalEnemy->AddComponent<SquareCollider2D>();
	normalEnemyCol->SetOneSide(normalEnemyCol->GetOneSide() / 2.0f);
	firstWave.push_back(normalEnemy);

	//�G���G
	auto normalEnemy2 = Instantiate();
	normalEnemy2->SetTag(EnemyTag);
	auto normalEnemyTex2 = normalEnemy2->AddComponent<DXTexture>();
	normalEnemyTex2->SetTexture(_T("Texture/NormalEnemy.png"));
	auto normalEnemyTexPos2 = normalEnemy2->GetTransform();
	normalEnemyTexPos2->Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	normalEnemyTexPos2->Scale.x /= 2;
	normalEnemyTexPos2->Scale.y /= 2;
	normalEnemyTexPos2->Scale.z /= 2;
	auto normaEenemyCom2 = normalEnemy2->AddComponent<NormalEnemy>();
	normaEenemyCom2->SetBulletPool(mBulletPool.get());
	normaEenemyCom2->SetPlayer(mPlayer);
	normaEenemyCom2->SetBarrageManager(mBarrageManager.get());
	auto normalEnemyCol2 = normalEnemy2->AddComponent<SquareCollider2D>();
	normalEnemyCol2->SetOneSide(normalEnemyCol2->GetOneSide() / 2.0f);
	firstWave.push_back(normalEnemy2);

	//�{�X�G
	mEnemy = Instantiate();
	mEnemy->SetTag(Tag::EnemyTag);
	auto enemyTex = mEnemy->AddComponent<DXTexture>();
	enemyTex->SetTexture(_T("Texture/Enemy.png"));
	auto texPos = mEnemy->GetTransform();
	texPos->Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	auto enemy = mEnemy->AddComponent<BossEnemy>();
	enemy->SetBulletPool(mBulletPool.get());
	enemy->SetPlayer(mPlayer);
	enemy->SetBarrageManager(mBarrageManager.get());
	enemy->SetHP(1000);
	auto enemyCol = mEnemy->AddComponent<SquareCollider2D>();
	enemyCol->SetOneSide(enemyCol->GetOneSide() / 2.0f);
	secondWave.push_back(mEnemy);

	auto gauge = Instantiate();
	auto renderer = gauge->AddComponent<TextureRenderer>();
	auto gaugeTex = gauge->AddComponent<DXTexture>();
	auto gaugeCom =  gauge->AddComponent<HPGauge>();
	gaugeCom->SetHPViewObject(enemy);
	renderer->SetDefaultColor(1.0f, 0.8f, 0.0f, 0.0f);
	gaugeTex->SetTexture(_T("Texture/Square.png"));
	auto gaugeTransform = gauge->GetTransform();
	gaugeTransform->Position.y = 1.3f;
	gaugeTransform->Position.z = -0.1f;
	gaugeTransform->Scale.y = 0.1f;
	gaugeTransform->Scale.x = 3.0f;
	secondWave.push_back(gauge);
	
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
	mBackGround->SetBackGrounds(back,back2);

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

	mWaveCount = 0;
	
	//���w���������X�g�ɒǉ�
	for(auto game:firstWave)
	{
		mAwakeObject.push_back(game);
	}
	//���ꂼ��̃E�F�[�u�z����Ǘ��z��ɒǉ�
	mEnemyWaveList.push_back(firstWave);
	mEnemyWaveList.push_back(secondWave);

	mFrameCount = FPS_CHEACK_FRAME_COUNT;
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
	mDXRescourceManager->GetDXSound()->Play();
}

void PlayScene::SceneUpdate()
{
	auto fps = mDXRescourceManager->GetFPS();
	mFrameCount++;
	//FPS���v�Z���o�͂���
	//���t���[���o���ƕω�������������̂ň��Ԋu�ōX�V
	if (mFrameCount % FPS_CHEACK_FRAME_COUNT == 0)
	{
		mFrameCount = 0;
		//�����o�ϐ��Ɏ��ƒl���Œ肳��Ă��܂��E�E�E
		std::wstringstream ws;
		//�L�������w��
		ws.precision(6);
		ws << fps << std::endl;
		auto t = ws.str();
		auto pt = t.c_str();
		mFPSText->UpdateText(pt);
		//���g���N���A����
		ws.clear();
	}

	//�w�i�𓮂���
	mBackGround->UpdateBackGrounds();

	/*�E�F�[�u����*/
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
	mDXRescourceManager->GetDXSound()->Stop();
}

bool PlayScene::IsSceneEnd()
{
	//���@�����񂾂�
	if (!mPlayer->GetEnable()) return true;
	//�ŏI�E�F�[�u�Ŏw��G�����񂾂�
	if (mIsLastWave) if (!mEnemy->GetEnable()) return true;
	return false;
}
