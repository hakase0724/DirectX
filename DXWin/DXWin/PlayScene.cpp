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
#include "OptionUnit.h"
#include "ItemMover.h"
#include "ExplosionEffect.h"

using namespace DirectX;
using namespace MyDirectX;

void PlayScene::Init()
{
	//弾幕管理クラス
	mBarrageManager = std::make_unique<BarrageManager>();

	CreateBulletPool();
	CreateUIItem();
	CreateFromCSVData();
	CreateBackGround();

	//各種カウントを初期化
	mWaveCount = 0;
	mFrameCount = FPS_CHEACK_FRAME_COUNT;

	//第一陣を初期リストに追加
	for(auto game:mEnemyWaveList[0])
	{
		mAwakeObject.push_back(game);
	}

	//全てのオブジェクトの初期位置を設定する
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
	mComboScore = 0.0;
	mComboCountFrame = 0;
	mIsCombo = false;
	*mScoreRP = 0;
	for(auto itr = mGameObjectsList.begin();itr != mGameObjectsList.end();)
	{
		if(itr->get()->GetTag() == Item)
		{
			itr->reset();
			itr = mGameObjectsList.erase(itr);
			continue;
		}
		else ++itr;
	}
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
	mDXRescourceManager->GetBGMDXSound()->Play();
}

void PlayScene::SceneUpdate()
{
	mFrameCount++;
	*mHpRP = mPlayerCom->GetHP();
	ComboAction();
	//FPSを計算し出力する
	//毎フレーム出すと変化が激しすぎるので一定間隔で更新
	if (mFrameCount % FPS_CHEACK_FRAME_COUNT == 0)
	{
		*mFPSRP = mDXRescourceManager->GetFPS();
	}
	//背景を動かす
	mBackGround->UpdateBackGrounds();

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
	mDXRescourceManager->SetScore((float)mScoreRP->GetValue());
	//全てのオブジェクトのアクティブを切る
	for (auto &game : mGameObjectsList)
	{
		game->SetEnable(false);
	}
	//曲を止める
	mDXRescourceManager->GetBGMDXSound()->Stop();
}

bool PlayScene::IsSceneEnd()
{
	//自機がしんだら
	if (!mPlayer->GetEnable()) 
	{
		mDXRescourceManager->GetSEDXSound()->Stop();
		return true;
	}
	//最終ウェーブで指定敵がしんだら
	if (mIsLastWave) if (!mEnemy->GetEnable()) 
	{
		mDXRescourceManager->GetSEDXSound()->Stop();
		return true;
	}
	return false;
}

void PlayScene::CreateBomb(DirectX::XMFLOAT3 pos)
{
	//ボム
	auto bomb = Instantiate();
	bomb->SetTag(Item);
	auto bombTransform = bomb->GetTransform();
	bombTransform->Position = pos;
	bombTransform->Scale = DirectX::XMFLOAT3(0.25f, 0.25f, 0.25f);
	auto bombTex = bomb->AddComponent<DXTexture>();
	bombTex->SetTexture(L"Texture/Bomb.png");
	bomb->AddComponent<Bomb>();
	auto bombCol = bomb->AddComponent<SquareCollider2D>();
	//コライダーは3分の1に
	bombCol->SetOneSide(bombCol->GetOneSide() / 3.0f);
	bomb->AddComponent<ItemMover>();
	bomb->SetEnable(true);
}

void PlayScene::CreatePowerUp(DirectX::XMFLOAT3 pos)
{
	//パワーアップ
	auto powerUp = Instantiate();
	powerUp->SetTag(Item);
	auto powerUpTransform = powerUp->GetTransform();
	powerUpTransform->Position = pos;
	powerUpTransform->Scale = DirectX::XMFLOAT3(0.25f, 0.25f, 0.25f);
	auto powerUpTex = powerUp->AddComponent<DXTexture>();
	powerUpTex->SetTexture(L"Texture/Power.png");
	powerUp->AddComponent<PowerUpItem>();
	auto powerUpCol = powerUp->AddComponent<SquareCollider2D>();
	//コライダーは3分の1に
	powerUpCol->SetOneSide(powerUpCol->GetOneSide() / 3.0f);
	powerUp->AddComponent<ItemMover>();
	powerUp->SetEnable(true);
}

void PlayScene::CreateExplosionEffect(DirectX::XMFLOAT3 pos)
{
	auto explosion = Instantiate();
	explosion->SetTag(Item);
	auto exTransform = explosion->GetTransform();
	exTransform->Position = pos;
	exTransform->Scale = DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f);
	auto exTex = explosion->AddComponent<DXTexture>();
	exTex->SetTexture(L"Texture/explosion.png");
	explosion->AddComponent<ExplosionEffect>();
	explosion->InitializeComponent();
	explosion->SetEnable(true);
}

void PlayScene::CreatePlayer(LOAD_FROM_CSV_DATA data)
{
	//自機
	mPlayer = Instantiate();
	mPlayer->SetName(data.Name);
	auto transform = mPlayer->GetTransform();
	transform->Position = data.StartPos;
	transform->Scale.x /= 3.0f;
	transform->Scale.y /= 3.0f;
	transform->Scale.z /= 3.0f;
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
	//自機のコライダーは30分の1
	playerCol->SetOneSide(playerCol->GetOneSide() / 30.0f);
	mAwakeObject.push_back(mPlayer);

	auto rightOptionUnit = Instantiate();
	auto rightOptionTransform = rightOptionUnit->GetTransform();
	rightOptionTransform->Scale.x /= 5.0f;
	rightOptionTransform->Scale.y /= 5.0f;
	rightOptionTransform->Scale.z /= 5.0f;
	auto rightOptionCom = rightOptionUnit->AddComponent<OptionUnit>();
	rightOptionCom->SetPlayer(mPlayer);
	rightOptionCom->SetXOffset(0.3f);
	rightOptionCom->SetYOffset(0.3f);
	rightOptionCom->SetBulletPool(mBulletPool.get());
	auto rightOptionTex = rightOptionUnit->AddComponent<DXTexture>();
	rightOptionTex->SetTexture(L"Texture/Square.png");
	rightOptionTex->SetDefaultColor(1.0f, 0.0f, 0.0f, 0.1f);
	mAwakeObject.push_back(rightOptionUnit);

	auto leftOptionUnit = Instantiate();
	auto leftOptionTransform = leftOptionUnit->GetTransform();
	leftOptionTransform->Scale.x /= 5.0f;
	leftOptionTransform->Scale.y /= 5.0f;
	leftOptionTransform->Scale.z /= 5.0f;
	auto leftOptionCom =leftOptionUnit->AddComponent<OptionUnit>();
	leftOptionCom->SetPlayer(mPlayer);
	leftOptionCom->SetXOffset(-0.3f);
	leftOptionCom->SetYOffset(0.3f);
	leftOptionCom->SetBulletPool(mBulletPool.get());
	auto leftOptionTex = leftOptionUnit->AddComponent<DXTexture>();
	leftOptionTex->SetTexture(L"Texture/Square.png");
	leftOptionTex->SetDefaultColor(1.0f, 0.0f, 0.0f, 1.0f);
	mAwakeObject.push_back(leftOptionUnit);
}

void PlayScene::CreateBossEnemy(LOAD_FROM_CSV_DATA data)
{
	//ボス敵
	mEnemy = Instantiate();
	mEnemy->SetName(data.Name);
	mEnemy->SetTag(data.Tag);
	auto enemyPos = mEnemy->GetTransform();
	enemyPos->Position = data.StartPos;
	auto enemyTex = mEnemy->AddComponent<DXTexture>();
	enemyTex->SetTexture(_T("Texture/Enemy.png"));
	
	auto enemy = mEnemy->AddComponent<BossEnemy>();
	enemy->SetBulletPool(mBulletPool.get());
	enemy->SetPlayer(mPlayer);
	enemy->SetBarrageManager(mBarrageManager.get());
	enemy->SetHP(data.HP);
	auto battleStartPos = data.StartPos;
	//初期位置から1進んだら弾幕展開を開始するようにする
	battleStartPos.y -= 1;
	enemy->SetBattleStartPos(battleStartPos);
	auto enemyCol = mEnemy->AddComponent<SquareCollider2D>();
	//ボスのコライダーは2分の1に
	enemyCol->SetOneSide(enemyCol->GetOneSide() / 2.0f);
	enemy->SetCollider(enemyCol);

	//体力ゲージ
	auto gauge = Instantiate();
	auto gaugeTransform = gauge->GetTransform();
	//ゲージの位置と長さ
	gaugeTransform->Position.y = 1.3f;
	gaugeTransform->Position.z = -0.1f;
	gaugeTransform->Scale.y = 0.1f;
	gaugeTransform->Scale.x = 3.0f;
	auto renderer = gauge->AddComponent<TextureRenderer>();
	auto gaugeTex = gauge->AddComponent<DXTexture>();
	auto gaugeCom = gauge->AddComponent<HPGauge>();
	gaugeCom->SetHPViewObject(enemy);
	//ゲージの色
	renderer->SetDefaultColor(1.0f, 0.8f, 0.0f, 0.5f);
	gaugeTex->SetTexture(_T("Texture/Square.png"));
	

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
	//サイズを半分に
	normalEnemyTexPos->Scale.x /= 2;
	normalEnemyTexPos->Scale.y /= 2;
	normalEnemyTexPos->Scale.z /= 2;
	auto normaEenemyCom = normalEnemy->AddComponent<NormalEnemy>();
	normaEenemyCom->SetHP(data.HP);
	normaEenemyCom->SetBulletPool(mBulletPool.get());
	normaEenemyCom->SetPlayer(mPlayer);
	normaEenemyCom->SetBarrageManager(mBarrageManager.get());
	auto normalEnemyCol = normalEnemy->AddComponent<SquareCollider2D>();
	//敵のコライダーは2分の1に
	normalEnemyCol->SetOneSide(normalEnemyCol->GetOneSide() / 2.0f);

	mEnemyWaveList[data.Wave - 1].push_back(normalEnemy);
}

void PlayScene::CreateBackGround()
{
	/*
	背景を動かすイメージ

	　　　　　　 ←
		背 景 2　↑
		   ↓　　↑
		背 景 1　↑
		   ↓　　↑
		   →→→→
	*/

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
	mBackGround->SetBackGrounds(back, back2);

	/*

	黒帯　　　 黒帯
	 ↓　　　　 ↓
	*** 背　景 ***
	*** 背　景 ***
	*** 背　景 ***
	*** 背　景 ***

	*/

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
}

void PlayScene::CreateFromCSVData()
{
	//データ読み込み
	auto dataTable = mDXRescourceManager->LoadData("Data/Data.csv");

	//何ウェーブまであるのか
	int maxWave = 0;
	for (auto data : dataTable)
	{
		if (data.Wave > maxWave) maxWave = data.Wave;
	}

	//ウェーブ分配列を用意する
	for (int i = 0; i < maxWave; i++)
	{
		std::vector<DXGameObject*> enemyList;
		mEnemyWaveList.push_back(enemyList);
	}

	//読み込んだデータに従って自機と敵を作る
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
	//HP表示テキスト
	auto hp = Instantiate();
	mHPText = hp->AddComponent<DXText>();
	auto hpTransform = hp->GetTransform();
	//位置と大きさ
	hpTransform->Scale = XMFLOAT3(0.07f, 0.07f, 1.0f);
	hpTransform->Position = XMFLOAT3(1.2f, 0.8f, -1.1f);
	mAwakeObject.push_back(hp);

	//Score表示テキスト
	auto scoreNotice = Instantiate();
	auto scoreText = scoreNotice->AddComponent<DXText>();
	auto scoreNoticeTransform = scoreNotice->GetTransform();
	//位置と大きさ
	scoreNoticeTransform->Scale = XMFLOAT3(0.07f, 0.07f, 1.0f);
	scoreNoticeTransform->Position = XMFLOAT3(-1.7f, 0.9f, -1.1f);
	scoreText->UpdateText(L"SCORE");
	mAwakeObject.push_back(scoreNotice);

	//Score表示テキスト
	auto score = Instantiate();
	mScoreText = score->AddComponent<DXText>();
	auto scoreTransform = score->GetTransform();
	//位置と大きさ
	scoreTransform->Scale = XMFLOAT3(0.07f, 0.07f, 1.0f);
	scoreTransform->Position = XMFLOAT3(-1.7f, 0.8f, -1.1f);
	mAwakeObject.push_back(score);

	//FPS表示テキスト
	auto fps = Instantiate();
	mFPSText = fps->AddComponent<DXText>();
	auto transform = fps->GetTransform();
	//位置と大きさ
	transform->Scale = XMFLOAT3(0.07f, 0.07f, 1.0f);
	transform->Position = XMFLOAT3(1.2f, -0.8f, -1.1f);
	mAwakeObject.push_back(fps);

	//HP表示に使う変数
	mHpRP =
		std::unique_ptr<Property, Deleter>
		(new Property(), Deleter());

	//変数に変化があった時に表示する処理を登録
	mHpRP->Subscribe
	(
	[&](double value)->void
	{
		std::wstringstream hp;
		hp.precision(6);
		hp << value;
		mHPText->UpdateText(hp.str().c_str());
		hp.clear();
	}
	);

	// Score表示に使う変数
	mScoreRP =
		std::unique_ptr<Property, Deleter>
		(new Property(), Deleter());

	//変数に変化があった時に表示する処理を登録
	mScoreRP->Subscribe
	(
	[&](double value)->void
	{
		std::wstringstream score;
		score.precision(6);
		score << value;
		mScoreText->UpdateText(score.str().c_str());
		score.clear();
	}
	);

	//FPS表示に使う変数
	mFPSRP =
		std::unique_ptr<Property, Deleter>
		(new Property(), Deleter());

	//変数に変化があった時に表示する処理を登録
	mFPSRP->Subscribe
	(
	[&](double value)->void
	{
		mFrameCount = 0;
		//メンバ変数に持つと値が固定されてしまう・・・
		std::wstringstream ws;
		//有効桁数指定
		ws.precision(6);
		ws << value;
		mFPSText->UpdateText(ws.str().c_str());
		//中身をクリアする
		ws.clear();
	}
	);
}

void PlayScene::CreateBulletPool()
{
	//弾のオブジェクトプール
	mBulletPool = std::make_unique<BulletPool>();
	mBulletPool->SetScene(this);
	//予め弾を用意しておく
	mBulletPool->CreatePreBullets(PRE_CREATE_BULLET_NUM);
}

void PlayScene::ComboAction()
{
	//コンボ中でなければ処理をしない
	if (!mIsCombo) return;
	//経過フレームカウント
	mComboCountFrame++;
	//一定フレーム以上経過したら
	if(mComboCountFrame > COMBO_LIMIT_FRAME)
	{
		mIsCombo = false;
		*mScoreRP + mComboScore;
		mComboScore = 0;
		mComboCountFrame = 0;
	}
}

