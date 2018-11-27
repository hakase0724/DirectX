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
	//弾幕管理クラス
	mBarrageManager = std::make_unique<BarrageManager>();
	//弾のオブジェクトプール
	mBulletPool = std::make_unique<BulletPool>();
	mBulletPool->SetScene(this);
	mBulletPool->CreatePreBullets(1000);

	//FPS表示テキスト
	auto fps = Instantiate();
	mFPSText = fps->AddComponent<DXText>();
	auto transform = fps->GetTransform();
	transform->Scale = XMFLOAT3(0.07f, 0.07f, 1.0f);
	transform->Position = XMFLOAT3(1.2f, -0.8f, -1.1f);
	mAwakeObject.push_back(fps);

	//自機
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

	//第一陣
	std::vector<DXGameObject*> firstWave;
	//第二陣
	std::vector<DXGameObject*> secondWave;

	//雑魚敵
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

	//雑魚敵
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

	//ボス敵
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
	
	//背景用画像1
	auto back = Instantiate();
	auto texBack = back->AddComponent<DXTexture>();
	texBack->SetTexture(_T("Texture/background.png"));
	auto backTransform = back->GetTransform();
	backTransform->Position.z = 2.0f;
	backTransform->Scale.x = 5.0f;
	backTransform->Scale.y = 5.0f;
	mAwakeObject.push_back(back);

	//背景用画像2
	auto back2 = Instantiate();
	auto texBack2 = back2->AddComponent<DXTexture>();
	texBack2->SetTexture(_T("Texture/background.png"));
	auto backTransform2 = back2->GetTransform();
	backTransform2->Position.y = 5.0f;
	backTransform2->Position.z = 2.0f;
	backTransform2->Scale.x = 5.0f;
	backTransform2->Scale.y = 5.0f;
	mAwakeObject.push_back(back2);

	//背景を動かすクラス
	mBackGround = std::make_unique<BackGround>();
	mBackGround->SetBackGrounds(back,back2);

	//右の黒帯
	auto black = Instantiate();
	auto blackBack = black->AddComponent<DXTexture>();
	blackBack->SetTexture(_T("Texture/black.png"));
	auto blackTransform = black->GetTransform();
	blackTransform->Position.z = -1.0f;
	blackTransform->Position.x = 1.63f;
	blackTransform->Scale.y = 3.0f;
	mAwakeObject.push_back(black);

	//左の黒帯
	auto black2 = Instantiate();
	auto blackBack2 = black2->AddComponent<DXTexture>();
	blackBack2->SetTexture(_T("Texture/black.png"));
	auto blackTransform2 = black2->GetTransform();
	blackTransform2->Position.z = -1.0f;
	blackTransform2->Position.x = -1.63f;
	blackTransform2->Scale.y = 3.0f;
	mAwakeObject.push_back(black2);

	mWaveCount = 0;
	
	//第一陣を初期リストに追加
	for(auto game:firstWave)
	{
		mAwakeObject.push_back(game);
	}
	//それぞれのウェーブ配列を管理配列に追加
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
	//ウェーブ情報リセット
	mWaveCount = 0;
	mIsLastWave = false;
	//全てのオブジェクトの初期化
	for(auto &game:mGameObjectsList)
	{
		game->InitializeComponent();
	}
	//最初からいるオブジェクトのアクティブ化
	for(auto game:mAwakeObject)
	{
		game->SetEnable(true);
	}
	//曲再生
	mDXRescourceManager->GetDXSound()->Play();
}

void PlayScene::SceneUpdate()
{
	auto fps = mDXRescourceManager->GetFPS();
	mFrameCount++;
	//FPSを計算し出力する
	//毎フレーム出すと変化が激しすぎるので一定間隔で更新
	if (mFrameCount % FPS_CHEACK_FRAME_COUNT == 0)
	{
		mFrameCount = 0;
		//メンバ変数に持つと値が固定されてしまう・・・
		std::wstringstream ws;
		//有効桁数指定
		ws.precision(6);
		ws << fps << std::endl;
		auto t = ws.str();
		auto pt = t.c_str();
		mFPSText->UpdateText(pt);
		//中身をクリアする
		ws.clear();
	}

	//背景を動かす
	mBackGround->UpdateBackGrounds();

	/*ウェーブ処理*/
	//次のウェーブへ行くか
	bool isNext = true;
	//現在ウェーブの敵が一体でも生存していたら次ウェーブへ行かない
	for(auto game:mEnemyWaveList[mWaveCount])
	{
		if (game->GetEnable()) isNext = false;
	}

	if(isNext)
	{
		mWaveCount++;
		//最終ウェーブか
		if (mWaveCount == mEnemyWaveList.size() - 1) mIsLastWave = true;
		//もしもウェーブ数が用意している数を超えたら処理しない
		if (mWaveCount >= (int)mEnemyWaveList.size()) return;
		//次ウェーブの敵をアクティブ化
		for (auto game : mEnemyWaveList[mWaveCount])
		{
			game->SetEnable(true);
		}
	}
}

void PlayScene::SceneEnd()
{
	//全てのオブジェクトのアクティブを切る
	for (auto &game : mGameObjectsList)
	{
		game->SetEnable(false);
	}
	//曲を止める
	mDXRescourceManager->GetDXSound()->Stop();
}

bool PlayScene::IsSceneEnd()
{
	//自機がしんだら
	if (!mPlayer->GetEnable()) return true;
	//最終ウェーブで指定敵がしんだら
	if (mIsLastWave) if (!mEnemy->GetEnable()) return true;
	return false;
}
