#include "stdafx.h"
#include "DXGameObjectManager.h"

using namespace MyDirectX;
using namespace DirectX;
DXGameObjectManager::DXGameObjectManager(HWND hwnd)
{
	CreateResources(hwnd);
	CreateGameObject();
}

void DXGameObjectManager::CreateResources(HWND hwnd)
{
	//DirectXリソース管理
	mDXManager = std::make_unique<DXManager>(hwnd);
}

void DXGameObjectManager::CreateGameObject()
{
	//動けるスフィア生成
	auto sphere = Instantiate();
	sphere->AddComponent<DXSphere>();
	sphere->AddComponent<Mover>();
	//初期位置が違うキューブ生成
	auto cube = Instantiate();
	auto transform = cube->GetTransform();
	transform.Position = XMFLOAT3(1.0f, 0.0f, 0.0f);
	cube->SetTransform(&transform);
	cube->AddComponent<DXCube>();
	cube->AddComponent<Mover>();
}

//ゲームオブジェクトを作り配列に格納、作ったゲームオブジェクトのポインタを返す
DXGameObject * DXGameObjectManager::Instantiate()
{
	mGameObjectsList.push_back(std::make_unique<DXGameObject>(mDXManager.get()));
	return mGameObjectsList.back().get();
}

BOOL DXGameObjectManager::Update()
{
	//現在の入力状態を取得
	mDXManager->GetDXInput()->SetInputState();
	//生成したオブジェクトの更新処理
	for(auto itr = mGameObjectsList.begin();itr != mGameObjectsList.end();++itr)
	{
		itr->get()->Update();
	}
	if (mDXManager->GetDXInput()->GetInputState(DIK_ESCAPE))
		return FALSE;
	return TRUE;
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
}


