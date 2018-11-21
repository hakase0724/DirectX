#include "stdafx.h"
#include "PlayScene.h"
#include <DirectXMath.h>
#include "DXTexture.h"
#include "Player.h"
#include "Mover.h"
#include "Enemy.h"
#include <sstream>

using namespace DirectX;
using namespace MyDirectX;

void PlayScene::Init()
{
	mBulletPool = std::make_unique<BulletPool>();
	mBulletPool->SetScene(this);
	mBulletPool->CreatePreBullets(1000);

	auto play = Instantiate();
	mFPSText = play->AddComponent<DXText>();
	auto transform = play->GetTransform();
	transform->Scale = XMFLOAT3(0.07f, 0.07f, 1.0f);
	transform->Position = XMFLOAT3(1.2f, -0.8f, -1.1f);

	//���@
	auto mPlayer = Instantiate();
	auto playerTex = mPlayer->AddComponent<DXTexture>();
	playerTex->SetTexture();
	mPlayer->SetTag(Tag::PlayerTag);
	mPlayer->AddComponent<Mover>();
	auto player = mPlayer->AddComponent<Player>();
	player->SetBulletPool(mBulletPool.get());
	auto playerCol = mPlayer->AddComponent<SquareCollider2D>();
	playerCol->SetOneSide(playerCol->GetOneSide() / 30.0f);

	//�G
	auto mEnemy = Instantiate();
	mEnemy->SetTag(Tag::EnemyTag);
	auto enemyTex = mEnemy->AddComponent<DXTexture>();
	enemyTex->SetTexture(_T("Texture/Enemy.png"));
	auto texPos = mEnemy->GetTransform();
	texPos->Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	auto enemy = mEnemy->AddComponent<Enemy>();
	enemy->SetBulletPool(mBulletPool.get());
	enemy->SetPlayer(mPlayer);
	auto enemyCol = mEnemy->AddComponent<SquareCollider2D>();
	enemyCol->SetOneSide(enemyCol->GetOneSide() / 2.0f);
	
	//�w�i�p�摜1
	auto back = Instantiate();
	auto texBack = back->AddComponent<DXTexture>();
	texBack->SetTexture(_T("Texture/background.png"));
	auto backTransform = back->GetTransform();
	backTransform->Position.z = 2.0f;
	backTransform->Scale.x = 5.0f;
	backTransform->Scale.y = 5.0f;

	//�w�i�p�摜2
	auto back2 = Instantiate();
	auto texBack2 = back2->AddComponent<DXTexture>();
	texBack2->SetTexture(_T("Texture/background.png"));
	auto backTransform2 = back2->GetTransform();
	backTransform2->Position.y = 5.0f;
	backTransform2->Position.z = 2.0f;
	backTransform2->Scale.x = 5.0f;
	backTransform2->Scale.y = 5.0f;

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

	//���̍���
	auto black2 = Instantiate();
	auto blackBack2 = black2->AddComponent<DXTexture>();
	blackBack2->SetTexture(_T("Texture/black.png"));
	auto blackTransform2 = black2->GetTransform();
	blackTransform2->Position.z = -1.0f;
	blackTransform2->Position.x = -1.63f;
	blackTransform2->Scale.y = 3.0f;
}

void PlayScene::SceneStart()
{
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
}

void PlayScene::SceneEnd()
{
	mDXRescourceManager->GetDXSound()->Stop();
}
