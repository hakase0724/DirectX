#include "stdafx.h"
#include "DXGameManager.h"

using namespace MyDirectX;
DXGameManager::DXGameManager(HWND hwnd)
{
	//シーン情報登録用ポインタ
	std::unique_ptr<Scene> scene;
	//機能クラスをまとめたもの
	mDXResourceManager = std::make_unique<DXResourceManager>(hwnd);
	//ゲームループを実行するクラス
	mDXExcuter = std::make_unique<DXExcuter>();
	mDXExcuter->SetDXResourceManager(mDXResourceManager.get());
	
	//タイトルシーン生成
	auto title = new TitleScene();
	title->SetDXResourceManager(mDXResourceManager.get());
	title->Init();
	scene.reset(title);
	mSceneList.push_back(std::move(scene));
	//プレイシーン生成
	auto play = new PlayScene();
	play->SetDXResourceManager(mDXResourceManager.get());
	play->Init();
	scene.reset(play);
	mSceneList.push_back(std::move(scene));
	//リザルトシーン生成
	auto result = new ResultScene();
	result->SetDXResourceManager(mDXResourceManager.get());
	result->Init();
	scene.reset(result);
	mSceneList.push_back(std::move(scene));
	//リフレッシュレートに応じて垂直同期間隔を設定する
	auto hdc = GetDC(hwnd);
	auto rate = GetDeviceCaps(hdc, VREFRESH);
	int intarval = 0;
	if (rate <= 60) intarval = 1;
	if (rate >= 120) intarval = 2;
	SetVsyncIntarval(intarval);
}

void DXGameManager::Initialize()
{
	mSceneIndex = 0;
	mSceneCount = mSceneList.size();
	mDXExcuter->SetScene(mSceneList[mSceneIndex].get());
}

bool DXGameManager::Update()
{
	//現在の入力を取得
	mDXResourceManager->SetInputState();
	//FPS計算
	mDXResourceManager->UpdateFPS();
	//処理を実行
	mDXExcuter->Excute();
	//エスケープが押されていたら終了する
	if (mDXResourceManager->GetKey(DIK_ESCAPE))return false;
	//シーンが終了していたら切り替える
	if (mDXExcuter->IsSceneEnd()) SceneChange();
	//次フレームのために現在の入力状況を保存
	mDXResourceManager->SetPreBuffer();
	return true;
}

void DXGameManager::SceneChange()
{
	mSceneIndex = (++mSceneIndex) % mSceneCount;
	mDXExcuter->SetScene(mSceneList[mSceneIndex].get());
}
