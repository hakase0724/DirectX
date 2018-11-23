#include "stdafx.h"
#include "ResultScene.h"
#include "DXText.h"

using namespace DirectX;
using namespace MyDirectX;
ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
	auto result = Instantiate();
	auto text = result->AddComponent<DXText>();
	auto transform = result->GetTransform();
	transform->Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);
	transform->Position.x -= 1.0f;
	text->UpdateText(L"RESULT");
	result->SetEnable(true);
}

bool ResultScene::IsSceneEnd()
{
	if (mDXRescourceManager->GetKeyDown(DIK_RETURN))return true;
	return false;
}
