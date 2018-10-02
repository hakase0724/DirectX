#include "stdafx.h"
#include "DXGameObjectManager.h"
#include "dinput.h"

using namespace MyDirectX;
using namespace DirectX;
DXGameObjectManager::DXGameObjectManager(HWND hwnd)
{
	//DirectXリソース管理
	mDXManager = std::unique_ptr<DXManager>(new DXManager(hwnd));

	//入力管理
	mDXInput = std::unique_ptr<DXInput>(new DXInput(hwnd));

	//カメラを生成
	auto cParam = new CameraParam
	(
		DirectX::XMVectorSet(0.0f, 1.0f, -2.3f, 1.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f),
		cWidth / cHeight
	);
	mDXCamera = std::unique_ptr<DXCamera>(new DXCamera(cParam));

	//キューブを生成
	mDXCube = std::unique_ptr<DXCube>(new DXCube(mDXManager.get()));
	//キューブの初期transform
	auto transform = new TRANSFORM(XMFLOAT3(-1.0f,0.0f,0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.5f, 1.5f, 1.5f));
	mDXCube2 = std::unique_ptr<DXCube>(new DXCube(transform, mDXManager.get()));
	transform = new TRANSFORM(XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.5f, 0.5f));
	mDXCube3 = std::unique_ptr<DXCube>(new DXCube(transform, mDXManager.get()));

	//生成したものを破棄
	delete cParam;
	delete transform;
}


DXGameObjectManager::~DXGameObjectManager()
{

}

HRESULT DXGameObjectManager::Init(HWND hwnd)
{
	return S_OK;
}

BOOL DXGameObjectManager::Update()
{
	//現在の入力状態を取得
	mDXInput->SetInputState();	
	auto cube = mDXCube2->GetTransform();
	if (mDXInput->GetInputState(DIK_W)) cube.Position.y += 0.01f;
	if (mDXInput->GetInputState(DIK_A)) cube.Position.x -= 0.01f;
	if (mDXInput->GetInputState(DIK_S)) cube.Position.y -= 0.01f;
	if (mDXInput->GetInputState(DIK_D)) cube.Position.x += 0.01f;
	mDXCube2->SetTransform(cube);
	mDXCube->Update(mDXInput.get(), mDXCamera.get());
	mDXCube2->Update(mDXInput.get(), mDXCamera.get());
	mDXCube3->Update(mDXInput.get(), mDXCamera.get());
	if (mDXInput->GetInputState(DIK_ESCAPE))return FALSE;
	return TRUE;
}

void DXGameObjectManager::Render()
{
	//バッファクリア
	mDXManager->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	//生成したオブジェクトのレンダリング処理
	mDXCube->Render();
	mDXCube2->Render();
	mDXCube3->Render();
	//画面表示
	mDXManager->EndScene();
}
