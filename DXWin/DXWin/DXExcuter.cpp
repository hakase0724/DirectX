#include "stdafx.h"
#include "DXExcuter.h"

using namespace MyDirectX;
DXExcuter::DXExcuter()
{
	//衝突管理クラスを生成
	mCollisionManager = std::make_unique<CollisionManager>();
	//シーンの登録を解除する
	mScene = nullptr;
}

void DXExcuter::SetScene(Scene * scene)
{
	//シーンが登録されていたらシーンの終了メソッドを呼び出す
	if (mScene != nullptr) mScene->SceneEnd();
	//シーンを登録する
	mScene = scene;
	//登録シーンの開始メソッドを呼ぶ
	mScene->SceneStart();
	//実行ゲームオブジェクト管理配列をクリアする
	mExcuteObjectsList.clear();
	//実行ゲームオブジェクト管理配列にシーン上のゲームオブジェクトを追加する
	mExcuteObjectsList = mScene->GetGameObjects();
}

void DXExcuter::Excute()
{
	//シーンが登録されて無ければ処理しない
	if (!mScene) return;

	/*毎フレームの処理を行う*/
	//シーンの更新処理
	mScene->SceneUpdate();
	//コライダーを格納
	mCollisionManager->SetGameObjects(mExcuteObjectsList);
	//ゲームオブジェクトの更新処理
	Update();
	//全ての更新処理が終わった後の更新処理
	mScene->SceneLateUpdate();
	//ゲームオブジェクトの後更新処理
	LateUpdate();
	//衝突処理
	mCollisionManager->Collision();
	//描画処理
	Render();
	//1フレーム終了時の処理
	mScene->SceneEndFrame();
}

void DXExcuter::Update()
{
	for(auto game:mExcuteObjectsList)
	{
		if (!game->GetEnable()) continue;
		game->Update();
	}
}

void DXExcuter::LateUpdate()
{
	for (auto game : mExcuteObjectsList)
	{
		if (!game->GetEnable()) continue;
		game->LateUpdate();
	}
}

void DXExcuter::Render()
{
	mDXRescourceManager->GetDXManager()->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);
	for (auto game : mExcuteObjectsList)
	{
		if (!game->GetEnable()) continue;
		game->Render();
	}
	mDXRescourceManager->GetDXManager()->EndScene();
}
