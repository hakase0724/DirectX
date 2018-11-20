#include "stdafx.h"
#include "PlayScene.h"
#include "DXText.h"
#include <DirectXMath.h>
#include "DXTexture.h"
#include "Player.h"
#include "Mover.h"


using namespace DirectX;
using namespace MyDirectX;

void PlayScene::Init()
{
	auto play = Instantiate();
	auto text = play->AddComponent<DXText>();
	auto transform = play->GetTransform();
	transform->Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);
	transform->Position.x -= 1.0f;
	text->UpdateText(L"PLAY");

	//Ž©‹@
	auto mPlayer = Instantiate();
	auto playerTex = mPlayer->AddComponent<DXTexture>();
	playerTex->SetTexture();
	mPlayer->SetTag(Tag::PlayerTag);
	mPlayer->AddComponent<Mover>();
	//auto player = mPlayer->AddComponent<Player>();
	auto playerCol = mPlayer->AddComponent<SquareCollider2D>();
	playerCol->SetOneSide(playerCol->GetOneSide() / 30.0f);

	//“G
	auto mEnemy = Instantiate();
	mEnemy->SetTag(Tag::EnemyTag);
	auto enemyTex = mEnemy->AddComponent<DXTexture>();
	enemyTex->SetTexture(_T("Texture/Enemy.png"));
	auto texPos = mEnemy->GetTransform();
	texPos->Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	auto enemyCol = mEnemy->AddComponent<SquareCollider2D>();
	enemyCol->SetOneSide(enemyCol->GetOneSide() / 2.0f);
	
	//”wŒi—p‰æ‘œ1
	auto back = Instantiate();
	auto texBack = back->AddComponent<DXTexture>();
	texBack->SetTexture(_T("Texture/background.png"));
	auto backTransform = back->GetTransform();
	backTransform->Position.z = 2.0f;
	backTransform->Scale.x = 5.0f;
	backTransform->Scale.y = 5.0f;

	//”wŒi—p‰æ‘œ2
	auto back2 = Instantiate();
	auto texBack2 = back2->AddComponent<DXTexture>();
	texBack2->SetTexture(_T("Texture/background.png"));
	auto backTransform2 = back2->GetTransform();
	backTransform2->Position.y = 5.0f;
	backTransform2->Position.z = 2.0f;
	backTransform2->Scale.x = 5.0f;
	backTransform2->Scale.y = 5.0f;

	mBackGround = std::make_unique<BackGround>();
	mBackGround->SetBackGrounds(back,back2);

	//‰E‚Ì•‘Ñ
	auto black = Instantiate();
	auto blackBack = black->AddComponent<DXTexture>();
	blackBack->SetTexture(_T("Texture/black.png"));
	auto blackTransform = black->GetTransform();
	blackTransform->Position.z = -1.0f;
	blackTransform->Position.x = 1.63f;
	blackTransform->Scale.y = 3.0f;

	//¶‚Ì•‘Ñ
	auto black2 = Instantiate();
	auto blackBack2 = black2->AddComponent<DXTexture>();
	blackBack2->SetTexture(_T("Texture/black.png"));
	auto blackTransform2 = black2->GetTransform();
	blackTransform2->Position.z = -1.0f;
	blackTransform2->Position.x = -1.63f;
	blackTransform2->Scale.y = 3.0f;
}
