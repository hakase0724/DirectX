#include "stdafx.h"
#include "DXGameObjectManager.h"

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
	auto test = Create<DXSquare>();
	test->SetName("MoveObject");
	test->AddComponent<Mover>();
	test->AddComponent<SquareCollider2D>();
	auto player = test->AddComponent<Player>();
	player->SetManager(this);


	//auto test2 = Create<DXSquare>();
	//test2->SetName("NotMoveObject");
	//auto transfrom = test2->GetTransform();
	//transfrom.Position = XMFLOAT3(-2.0f, 0.0f, 0.0f);
	//test2->SetTransform(&transfrom);
	//test2->AddComponent<SquareCollider2D>();

	//auto test3 = Create<DXSquare>();
	//test3->SetName("NotMoveObject2");
	//auto transfrom2 = test3->GetTransform();
	//transfrom2.Position = XMFLOAT3(-1.0f, 1.5f, 0.0f);
	//test3->SetTransform(&transfrom2);
	//test3->AddComponent<SquareCollider2D>();
}

void DXGameObjectManager::StoreCollider2D()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto com = itr->get()->GetComponent<Collider2D>();
		if (com != nullptr) mCollider2DList.push_back(com);
	}
}

//ゲームオブジェクトを作り配列に格納、作ったゲームオブジェクトのポインタを返す
DXGameObject * DXGameObjectManager::Instantiate()
{
	mGameObjectsList.push_back(std::make_unique<DXGameObject>(mDXManager.get()));
	mGameObjectCounter++;
	mGameObjectsList.back().get()->SetID(mGameObjectCounter);
	return mGameObjectsList.back().get();
}
//ゲーム内で生成する
DXGameObject * DXGameObjectManager::InstantiateTemp()
{
	mTempGameObjectsList.push_back(std::make_unique<DXGameObject>(mDXManager.get()));
	mGameObjectCounter++;
	mTempGameObjectsList.back().get()->SetID(mGameObjectCounter);
	mTempGameObjectsList.back().get()->AddComponent<DXSquare>();
	return mTempGameObjectsList.back().get();
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
		itr->get()->Update();
	}
	if (mDXManager->GetDXInput()->GetInputState(DIK_ESCAPE))return FALSE;
	return TRUE;
}

void DXGameObjectManager::LateUpdate()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		itr->get()->LateUpdate();
	}
	//総当たり衝突判定
	for(auto col:mCollider2DList)
	{
		auto col1ID = col->GetID();
		for(auto col2:mCollider2DList)
		{
			if (col1ID != col2->GetID())
				col->IsCollision(col2);
		}
	}
}

void DXGameObjectManager::FixedUpdate()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		itr->get()->FixedUpdate();
	}
}

void DXGameObjectManager::Render()
{
	//バッファクリア
	mDXManager->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);
	//生成したオブジェクトのレンダリング処理
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		itr->get()->Render();
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


