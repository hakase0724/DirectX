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
	mDXManager = std::unique_ptr<DXManager>(new DXManager(hwnd));
	//入力管理
	mDXInput = std::unique_ptr<DXInput>(new DXInput(hwnd));
}

void DXGameObjectManager::CreateGameObject()
{
	//カメラを生成
	auto cParam = new CameraParam
	(
		DirectX::XMVectorSet(0.0f, 0.0f, -3.5f, 1.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f),
		cWidth / cHeight
	);
	mDXCamera = std::unique_ptr<DXCamera>(new DXCamera(cParam));

	//キューブを生成
	//キューブの初期transform
	auto transform = new TRANSFORM(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.5f));
	auto transform2 = new TRANSFORM(XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.5f));
	mDXCube = std::make_unique<DXCube>(transform, mDXManager.get(), mDXInput.get(), mDXCamera.get());
	mDXCube->Init(transform, mDXManager.get(), mDXInput.get(), mDXCamera.get());
	//生成したものを破棄
	auto game = InstantiateGameObjcet();
	game->AddComponent<DXCube>();
	delete cParam;
	delete transform;
	delete transform2;
}

DXGameObject * DXGameObjectManager::InstantiateGameObjcet()
{
	mDXGameObjectArray.emplace_back(std::make_unique<DXGameObject>(mDXManager.get(), mDXInput.get(), mDXCamera.get()));
	return mDXGameObjectArray.back().get();
}

template<typename T>
void DXGameObjectManager::Instantiate()
{
	mDXGameObjectArray.emplace_back(std::make_unique<T>(mDXManager.get(), mDXInput.get(), mDXCamera.get()));
}

template<typename T>
void DXGameObjectManager::Instantiate(TRANSFORM *transform)
{
	mDXGameObjectArray.emplace_back(std::make_unique<T>(transform,mDXManager.get(), mDXInput.get(), mDXCamera.get()));
}

DXGameObjectManager::~DXGameObjectManager(){}

HRESULT DXGameObjectManager::Init(HWND hwnd)
{
	return S_OK;
}

BOOL DXGameObjectManager::Update()
{
	//現在の入力状態を取得
	mDXInput->SetInputState();	
	mDXCube->Update();
	for(int i = 0;i < mDXGameObjectArray.size();i++)
	{
		mDXGameObjectArray[i]->Update();
	}
	if (mDXInput->GetInputState(DIK_ESCAPE))return FALSE;
	return TRUE;
}

void DXGameObjectManager::Render()
{
	//バッファクリア
	mDXManager->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);
	mDXCube->Render();
	//生成したオブジェクトのレンダリング処理
	for (int i = 0; i < mDXGameObjectArray.size(); i++)
	{
		mDXGameObjectArray[i]->Render();
	}
	//画面表示
	mDXManager->EndScene();
}


