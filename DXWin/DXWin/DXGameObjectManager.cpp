#include "stdafx.h"
#include "DXGameObjectManager.h"
#include "dinput.h"

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
	//キューブを生成
	//キューブの初期transform
	//auto transform = new TRANSFORM(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.5f));
	mDXCube = std::make_unique<DXCube>(mDXManager.get());
	mDXCube->Init();
	//delete transform;
}

DXGameObjectManager::~DXGameObjectManager(){}

HRESULT DXGameObjectManager::Init(HWND hwnd)
{
	return S_OK;
}

BOOL DXGameObjectManager::Update()
{
	//現在の入力状態を取得
	mDXManager->GetDXInput()->SetInputState();
	//生成したオブジェクトの更新処理
	mDXCube->Update();
	if (mDXManager->GetDXInput()->GetInputState(DIK_ESCAPE))
		return FALSE;
	return TRUE;
}

void DXGameObjectManager::Render()
{
	//バッファクリア
	mDXManager->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);
	//生成したオブジェクトのレンダリング処理
	mDXCube->Render();
	//画面表示
	mDXManager->EndScene();
}


