#include "stdafx.h"
#include "DXExcuter.h"

using namespace MyDirectX;
DXExcuter::DXExcuter()
{
	mCollisionManager = std::make_unique<CollisionManager>();
	mScene = nullptr;
}

DXExcuter::~DXExcuter()
{
}

void DXExcuter::SetScene(Scene * scene)
{
	if (mScene != nullptr) mScene->SceneEnd();
	mScene = scene;
	mScene->SceneStart();
	mExcuteObjectsList.clear();
	mExcuteObjectsList = mScene->GetGameObjects();
}

void DXExcuter::Excute()
{
	//シーンが登録されて無ければ処理しない
	if (!mScene) return;
	//1フレームの処理を行う
	mScene->SceneUpdate();
	//コライダーを格納
	mCollisionManager->SetGameObjects(mExcuteObjectsList);
	Update();
	mScene->SceneLateUpdate();
	LateUpdate();
	//衝突処理
	mCollisionManager->Collision();
	Render();
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
