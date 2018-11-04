#include "stdafx.h"
#include "DXGameObjectManager.h"
#include "DXManager.h"

using namespace MyDirectX;
using namespace DirectX;
DXGameObjectManager::DXGameObjectManager(HWND hwnd)
{
	CreateResources(hwnd);
	CreateGameObject();
	StoreCollider2D();
}

DXGameObjectManager::~DXGameObjectManager()
{
	for(auto col:mCollider2DList)
	{
		col->Exit();
		delete col;
	}
}

void DXGameObjectManager::CreateResources(HWND hwnd)
{
	//DirectXリソース管理
	mDXManager = std::make_unique<DXManager>(hwnd);
}

void DXGameObjectManager::CreateGameObject()
{
	auto test = InstantiateTemp();
	test->SetName("MoveObject");
	test->SetTag(Tag::PlayerTag);
	test->AddComponent<Mover>();
	auto col = test->AddComponent<SquareCollider2D>();
	auto player = test->AddComponent<Player>();
	player->SetManager(this);
	col->SetOneSide(col->GetOneSide() / 10.0f);

	/*auto test3 = InstantiateTemp();
	test3->SetName("NotMoveObject2");
	auto transfrom2 = test3->GetTransform();
	transfrom2.Position = XMFLOAT3(0.0f,1.0f, 0.0f);
	test3->SetTransform(&transfrom2);
	test3->SetTag(Tag::EnemyTag);
	test3->AddComponent<SquareCollider2D>();*/
}

void DXGameObjectManager::StoreCollider2D()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (!game->GetEnable()) continue;
		auto com = game->GetComponent<Collider2D>();
		
		if (com != nullptr) mCollider2DList.push_back(com);

	}
}

bool DXGameObjectManager::IsCollisionJudge(Tag shooter, Tag bullet)
{
	//同じタグなら判定しない
	if (shooter == bullet) return false;
	//自機と自機の弾は判定しない
	if (shooter == Tag::PlayerTag && bullet == Tag::PlayerBullet) return false;
	//敵機と敵機の弾は判定しない
	if (shooter == Tag::EnemyTag && bullet == Tag::EnemyBullet) return false;
	return true;
}

//ゲームオブジェクトを作り配列に格納、作ったゲームオブジェクトのポインタを返す
DXGameObject * DXGameObjectManager::Instantiate()
{
	mGameObjectsList.push_back(std::make_unique<DXGameObject>(mDXManager.get()));
	mGameObjectCounter++;
	auto game = mGameObjectsList.back().get();
	game->SetID(mGameObjectCounter);
	game->SetEnable(true);
	return game;
}
//ゲーム内で生成する
DXGameObject * DXGameObjectManager::InstantiateTemp()
{
	mTempGameObjectsList.push_back(std::make_unique<DXGameObject>(mDXManager.get(),this));
	mGameObjectCounter++;
	auto game = mTempGameObjectsList.back().get();
	game->SetID(mGameObjectCounter);
	game->AddComponent<DXSquare>();
	game->SetEnable(true);
	return game;
}
//キューブ生成
DXGameObject * DXGameObjectManager::CreateCube()
{
	auto cube = Instantiate();
	cube->AddComponent<DXCube>();
	return cube;
}
//スフィア生成
DXGameObject * DXGameObjectManager::CreateSphere()
{
	auto sphere = Instantiate();
	sphere->AddComponent<DXSphere>();
	return sphere;
}
//四角形生成
DXGameObject * DXGameObjectManager::CreateSquare()
{
	auto square = Instantiate();
	square->AddComponent<DXSquare>();
	return square;
}

BOOL DXGameObjectManager::Update()
{
	//現在の入力状態を取得
	mDXManager->GetDXInput()->SetInputState();
	mCollider2DList.clear();
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
	for(auto col:mCollider2DList)
	{
		auto col1Tag = col->GetTag();
		//自機または敵機のコライダーのみ抽出
		if (col1Tag == Tag::PlayerBullet) continue;
		if (col1Tag == Tag::EnemyBullet) continue;
		for(auto col2:mCollider2DList)
		{
			if (!IsCollisionJudge(col1Tag, col2->GetTag())) continue;
			col->IsCollision(col2);
		}
	}
}

void DXGameObjectManager::FixedUpdate()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (game->GetEnable()) itr->get()->FixedUpdate();
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
	mTempGameObjectsList.clear();
	mDXManager->GetDXInput()->SetPreBuffer();
}

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


