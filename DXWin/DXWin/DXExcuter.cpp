#include "stdafx.h"
#include "DXExcuter.h"

using namespace MyDirectX;
DXExcuter::DXExcuter()
{
	mCollisionManager = std::make_unique<CollisionManager>();
}

DXExcuter::~DXExcuter()
{
}

void DXExcuter::SetScene(Scene * scene)
{
	mScene = scene;
	mExcuteObjectsList = mScene->GetGameObjects();
}

void DXExcuter::Excute()
{
	//シーンが登録されて無ければ処理しない
	if (!mScene) return;
	//1フレームの処理を行う
	mScene->SceneUpdate();
	mCollisionManager->SetGameObjects(mExcuteObjectsList);
	Update();
	mScene->SceneLateUpdate();
	LateUpdate();
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
