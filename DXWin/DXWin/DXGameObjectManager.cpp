#include "stdafx.h"
#include "DXGameObjectManager.h"
#include "DXManager.h"
#include <sstream>

using namespace MyDirectX;
using namespace DirectX;
DXGameObjectManager::DXGameObjectManager(HWND hwnd)
{
	CreateResources(hwnd);
	CreateGameObject();
}

void DXGameObjectManager::CreateResources(HWND hwnd)
{
	mDXSound = std::make_unique<DXSound>(hwnd);
	
	//DirectXリソース管理
	mDXManager = std::make_unique<DXManager>(hwnd);
	//FPSカウンターを生成
	mFPSCountor = std::make_unique<FPSCountor>();
	//弾管理クラスを生成
	mBulletManager = std::make_unique<BulletManager>(this);
	mBulletManager->CreatePreBullets(1000);
	mBackGround = std::make_unique<BackGround>();
	mDXSound->Play();
}

//ゲームに始めからいるオブジェクトを生成
void DXGameObjectManager::CreateGameObject()
{
	//自機
	auto player = Instantiate();
	auto playerTex = player->AddComponent<DXTexture>();
	playerTex->SetTexture();
	player->SetTag(Tag::PlayerTag);
	player->AddComponent<Mover>();
	player->AddComponent<Player>();
	auto playerCol = player->AddComponent<SquareCollider2D>();
	playerCol->SetOneSide(playerCol->GetOneSide() / 30.0f);

	//敵
	auto enemy = Instantiate();
	enemy->SetTag(Tag::EnemyTag);
	auto enemyTex = enemy->AddComponent<DXTexture>();
	enemyTex->SetTexture(_T("Texture/Enemy.png"));
	auto texPos = enemy->GetTransform();
	texPos->Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	auto enemyCol = enemy->AddComponent<SquareCollider2D>();
	enemyCol->SetOneSide(enemyCol->GetOneSide() / 2.0f);
	auto enemyCom = enemy->AddComponent<Enemy>();
	enemyCom->SetPlayer(player);

	//背景用画像1
	auto back = Instantiate();
	auto texBack = back->AddComponent<DXTexture>();
	texBack->SetTexture(_T("Texture/background.png"));
	auto backTransform = back->GetTransform();
	backTransform->Position.z = 2.0f;
	backTransform->Scale.x = 5.0f;
	backTransform->Scale.y = 5.0f;

	//背景用画像2
	auto back2 = Instantiate();
	auto texBack2 = back2->AddComponent<DXTexture>();
	texBack2->SetTexture(_T("Texture/background.png"));
	auto backTransform2 = back2->GetTransform();
	backTransform2->Position.y = 5.0f;
	backTransform2->Position.z = 2.0f;
	backTransform2->Scale.x = 5.0f;
	backTransform2->Scale.y = 5.0f;

	//動かす背景をセット
	mBackGround->SetBackGrounds(back, back2);

	//右の黒帯
	auto black = Instantiate();
	auto blackBack = black->AddComponent<DXTexture>();
	blackBack->SetTexture(_T("Texture/black.png"));
	auto blackTransform = black->GetTransform();
	blackTransform->Position.z = -1.0f;
	blackTransform->Position.x = 1.63f;
	blackTransform->Scale.y = 3.0f;

	//左の黒帯
	auto black2 = Instantiate();
	auto blackBack2 = black2->AddComponent<DXTexture>();
	blackBack2->SetTexture(_T("Texture/black.png"));
	auto blackTransform2 = black2->GetTransform();
	blackTransform2->Position.z = -1.0f;
	blackTransform2->Position.x = -1.63f;
	blackTransform2->Scale.y = 3.0f;
}

//生きているコライダーを取得
void DXGameObjectManager::StoreCollider2D()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		//アクティブでなければ無視する
		if (!game->GetEnable()) continue;
		auto com = game->GetComponent<Collider2D>();
		//コライダーがなければ無視する
		if (com == nullptr) continue;
		auto tag = game->GetTag();
		//キャラクター
		if(tag == Tag::PlayerTag || tag == Tag::EnemyTag)
		{
			mShooterCollider2DList.push_back(com);
		}
		//弾
		else if(tag == Tag::PlayerBullet || tag == Tag::EnemyBullet)
		{
			mBulletCollider2DList.push_back(com);
		}
	}
}

bool DXGameObjectManager::IsCollisionJudge(Tag tag1, Tag tag2)
{
	//同じタグなら判定しない
	if (tag1 == tag2) return false;
	//自機と自機の弾は判定しない
	if (tag1 == Tag::PlayerTag && tag2 == Tag::PlayerBullet) return false;
	if (tag1 == Tag::PlayerBullet && tag2 == Tag::PlayerTag) return false;
	//敵機と敵機の弾は判定しない
	if (tag1 == Tag::EnemyTag && tag2 == Tag::EnemyBullet) return false;
	if (tag1 == Tag::EnemyBullet && tag2 == Tag::EnemyTag) return false;
	//弾同士は判定しない
	if (tag1 == Tag::PlayerBullet && tag2 == Tag::EnemyBullet) return false;
	return true;
}

//ゲームオブジェクトを作り配列に格納、作ったゲームオブジェクトのポインタを返す
DXGameObject * DXGameObjectManager::Instantiate()
{
	mTempGameObjectsList.push_back(std::make_unique<DXGameObject>(mDXManager.get(), this));
	mGameObjectCounter++;
	auto game = mTempGameObjectsList.back().get();
	game->SetID(mGameObjectCounter);
	game->SetEnable(true);
	//テストしやすくするため四角形表示コンポーネントを付けている
	//不要になり次第消す
	//game->AddComponent<DXSquare>();
	return game;
}

BOOL DXGameObjectManager::Update()
{
	//FPSを計算しデバッグウィンドウに出力する
	auto fps = mFPSCountor.get()->GetFPS();
	std::stringstream stream;
	stream << fps << std::endl;
	OutputDebugStringA(stream.str().c_str());
	//背景移動
	mBackGround->UpdateBackGrounds();

	//現在の入力状態を取得
	mDXManager->GetDXInput()->SetInputState();
	mShooterCollider2DList.clear();
	mBulletCollider2DList.clear();
	StoreCollider2D();
	//生成したオブジェクトの更新処理
	for(auto itr = mGameObjectsList.begin();itr != mGameObjectsList.end();++itr)
	{
		auto game = itr->get();
		if(game->GetEnable()) itr->get()->Update();
	}
	if (mDXManager->GetDXInput()->GetInputState(DIK_ESCAPE))return FALSE;
	return TRUE;
}

void DXGameObjectManager::LateUpdate()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (game->GetEnable()) itr->get()->LateUpdate();
	}
	
	//当たり判定
	for(auto shooter:mShooterCollider2DList)
	{
		auto shooterTag = shooter->GetTag();
		//キャラクター同士の当たり判定
		for(auto shooter2:mShooterCollider2DList)
		{
			auto shooter2Tag = shooter2->GetTag();
			if (!IsCollisionJudge(shooterTag, shooter2Tag)) continue;
			shooter->IsCollision(shooter2);
			shooter2->IsCollision(shooter);
		}
		//キャラクターと弾の当たり判定
		for(auto bullet:mBulletCollider2DList)
		{
			auto bulletTag = bullet->GetTag();
			if (!IsCollisionJudge(shooterTag, bulletTag)) continue;
			shooter->IsCollision(bullet);
			bullet->IsCollision(shooter);
		}
	}

	//キャラクターの衝突応答
	for(auto shooter:mShooterCollider2DList)
	{
		//衝突していたら
		if(shooter->IsCollided()) shooter->OnCollision();
	}
	//弾の衝突応答
	for (auto bullet : mBulletCollider2DList)
	{
		//衝突していたら
		if (bullet->IsCollided()) bullet->OnCollision();
	}

}

void DXGameObjectManager::Render()
{
	//バッファクリア
	mDXManager->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);

	//生成したオブジェクトのレンダリング処理
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (game->GetEnable()) itr->get()->Render();
	}

	//画面表示
	mDXManager->EndScene();

	//1フレーム内に追加生成されたものがあれば管理リストに追加する
	for (auto itr = mTempGameObjectsList.begin(); itr != mTempGameObjectsList.end(); ++itr)
	{
		//中身のないものは追加しない
		if (*itr == nullptr) continue;
		mGameObjectsList.push_back(std::move(*itr));
	}

	//次フレーム用に一時配列のクリアと入力状況の取得
	mTempGameObjectsList.clear();
	mDXManager->GetDXInput()->SetPreBuffer();
}

//指定したIDのゲームオブジェクトのアクティブを取得
bool DXGameObjectManager::IsEnable(UINT id)
{
	bool result = false;
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (game->GetID() != id) continue;
		if(game->GetEnable())
		{
			result = true;
			break;
		}
	}
	return result;
}

//IDをキーにゲームオブジェクトを探す
DXGameObject * DXGameObjectManager::GetDXGameObjectWithID(UINT id)
{
	DXGameObject* pGame = nullptr;
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (game->GetID() != id) continue;
		pGame = game;
		break;
	}
	return pGame;
}


