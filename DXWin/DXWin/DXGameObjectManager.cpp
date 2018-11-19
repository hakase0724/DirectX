#include "stdafx.h"
#include "DXGameObjectManager.h"
#include "DXManager.h"
#include <sstream>

using namespace MyDirectX;
using namespace DirectX;
DXGameObjectManager::DXGameObjectManager(HWND hwnd)
{
	CreateResources(hwnd);
	mSceneState = Title;
	CreateTitleSceneObject();
}

void DXGameObjectManager::ShowFPS()
{
	mFrameCount++;
	//FPSを計算しデバッグウィンドウに出力する
	auto fps = mFPSCountor.get()->GetFPS();
	if(mFrameCount % mShowCoolTime == 0)
	{
		mFrameCount = 0;	
		std::wstringstream ws;
		ws.precision(6);
		ws << fps << std::endl;
		auto t = ws.str();
		auto pt = t.c_str();
		mText->UpdateText(pt);
		ws.clear();	
		/*if (mEnemyCom)
		{
			std::wstringstream ws2;
			ws2.precision(6);
			auto hp = mEnemyCom->GetHP();
			ws2 << hp << std::endl;
			auto t2 = ws2.str();
			auto pt2 = t2.c_str();
			mEnemyHPTextCom->UpdateText(pt2);
			ws2.clear();
		}*/
	}
}

void DXGameObjectManager::CreateResources(HWND hwnd)
{
	mDXSound = std::make_unique<DXSound>(hwnd);
	
	//DirectXリソース管理
	mDXManager = std::make_unique<DXManager>(hwnd);
	//FPSカウンターを生成
	mFPSCountor = std::make_unique<FPSCountor>();
	////弾管理クラスを生成
	mBulletManager = std::make_unique<BulletManager>(this);
	mBulletManager->CreatePreBullets(1000);
	mBackGround = std::make_unique<BackGround>();
}

//ゲームに始めからいるオブジェクトを生成
void DXGameObjectManager::CreateGameObject()
{
	//自機
	mPlayer = Instantiate();
	auto playerTex = mPlayer->AddComponent<DXTexture>();
	playerTex->SetTexture();
	mPlayer->SetTag(Tag::PlayerTag);
	mPlayer->AddComponent<Mover>();
	auto player = mPlayer->AddComponent<Player>();
	auto playerCol = mPlayer->AddComponent<SquareCollider2D>();
	playerCol->SetOneSide(playerCol->GetOneSide() / 30.0f);

	//敵
	mEnemy = Instantiate();
	mEnemy->SetTag(Tag::EnemyTag);
	auto enemyTex = mEnemy->AddComponent<DXTexture>();
	enemyTex->SetTexture(_T("Texture/Enemy.png"));
	auto texPos = mEnemy->GetTransform();
	texPos->Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	auto enemyCol = mEnemy->AddComponent<SquareCollider2D>();
	enemyCol->SetOneSide(enemyCol->GetOneSide() / 2.0f);
	mEnemyCom = mEnemy->AddComponent<Enemy>();
	mEnemyCom->SetPlayer(mPlayer);

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

	testObj = Instantiate();
	testObj->GetTransform()->Position.x = 1.2f;
	testObj->GetTransform()->Position.y = -0.8f;
	testObj->GetTransform()->Position.z = -1.1f;
	testObj->GetTransform()->Scale.x = 0.07f;
	testObj->GetTransform()->Scale.y = 0.07f;
	mText = testObj->AddComponent<DXText>();

	//mEnemyHPText = Instantiate();
	//mEnemyHPText->GetTransform()->Position.x = 1.2f;
	//mEnemyHPText->GetTransform()->Position.y = 0.8f;
	//mEnemyHPText->GetTransform()->Position.z = -1.1f;
	//mEnemyHPText->GetTransform()->Scale.x = 0.07f;
	//mEnemyHPText->GetTransform()->Scale.y = 0.07f;
	//mEnemyHPTextCom = mEnemyHPText->AddComponent<DXText>();
	////mEnemyHPView = std::make_unique<HPView>(mEnemyCom, mEnemyHPTextCom);

	//mPlayerHPText = Instantiate();
	//mPlayerHPText->GetTransform()->Position.x = -1.7f;
	//mPlayerHPText->GetTransform()->Position.y = 0.8f;
	//mPlayerHPText->GetTransform()->Position.z = -1.1f;
	//mPlayerHPText->GetTransform()->Scale.x = 0.07f;
	//mPlayerHPText->GetTransform()->Scale.y = 0.07f;
	//mPlayerHPTextCom = mPlayerHPText->AddComponent<DXText>();
	//mPlayerHPView = std::make_unique<HPView>(player, mPlayerHPTextCom);

	mDXSound->Play();
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

void DXGameObjectManager::Reset()
{
	//全ての弾を一時配列に逃がす
	for (auto &bullet : mGameObjectsList)
	{
		auto tag = bullet->GetTag();
		if (tag == PlayerBullet || tag == EnemyBullet)
		{
			mBulletManager->ReturnBullet(bullet.get());
			mTempGameObjectsList.push_back(std::move(bullet));
		}
	}
	//管理配列をクリアしオブジェクトを再生成
	mGameObjectsList.clear();
	switch (mSceneState)
	{
	case Title:
		CreateTitleSceneObject();
		break;
	case Play:
		CreateGameSceneObject();
		break;
	default:
		break;
	}
	//逃がした弾をもとに戻す
	for (auto itr = mTempGameObjectsList.begin(); itr != mTempGameObjectsList.end(); ++itr)
	{
		//中身のないものは追加しない
		if (*itr == nullptr) continue;
		mGameObjectsList.push_back(std::move(*itr));
	}
	mTempGameObjectsList.clear();
	isReset = false;
}

//ゲームオブジェクトを作り配列に格納、作ったゲームオブジェクトのポインタを返す
DXGameObject * DXGameObjectManager::Instantiate()
{
	mTempGameObjectsList.push_back(std::make_unique<DXGameObject>(mDXManager.get(), this));
	mGameObjectCounter++;
	auto game = mTempGameObjectsList.back().get();
	game->SetID(mGameObjectCounter);
	game->SetEnable(true);
	return game;
}

BOOL DXGameObjectManager::Update()
{
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
	
	if (mDXManager->GetDXInput()->GetKeyDown(DIK_T)) ChangeScene(SceneState::Title);	
	if (mDXManager->GetDXInput()->GetKeyDown(DIK_P)) ChangeScene(SceneState::Play);
	if (mSceneState == Play)
	{
		ShowFPS();
		//背景移動
		mBackGround->UpdateBackGrounds();
		//自機もしくは敵が死んだらタイトルへ
		if (mPlayer) if (!mPlayer->GetEnable()) 
			ChangeScene(SceneState::Title);
		if (mEnemy) if (!mEnemy->GetEnable()) 
			ChangeScene(SceneState::Title);
		/*if(mPlayerHPView) mPlayerHPView->Update();
		if(mEnemyHPView) mEnemyHPView->Update();*/
		
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

	//次フレーム用の準備
	mTempGameObjectsList.clear();
	//リセットするなら
	if (isReset) Reset();
	//現フレームの入力情報を記憶
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

void DXGameObjectManager::CreateTitleSceneObject()
{
	mPlayer = nullptr;
	mEnemy = nullptr;
	mDXSound->Stop();
	auto title = Instantiate();
	auto text = title->AddComponent<DXText>();
	auto transform = title->GetTransform();
	transform->Scale = XMFLOAT3(0.5f,0.5f,0.5f);
	transform->Position.x -= 1.0f;
	text->UpdateText(L"TITLE");
	mBackGround->ClearBackGrounds();
}

void DXGameObjectManager::CreateGameSceneObject()
{
	CreateGameObject();
}

void DXGameObjectManager::CreateResultSceneObject()
{
}

void DXGameObjectManager::ChangeScene(SceneState state)
{
	mSceneState = state;
	isReset = true;
}


