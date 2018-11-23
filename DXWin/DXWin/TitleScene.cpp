#include "stdafx.h"
#include "TitleScene.h"
#include "DXText.h"

using namespace DirectX;
using namespace MyDirectX;

void TitleScene::Init()
{
	auto title = Instantiate();
	auto text = title->AddComponent<DXText>();
	auto transform = title->GetTransform();
	transform->Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);
	transform->Position.x -= 1.0f;
	text->UpdateText(L"TITLE");
	title->SetEnable(true);
}

bool TitleScene::IsSceneEnd()
{
	if (mDXRescourceManager->GetKeyDown(DIK_RETURN))return true;
	return false;
}
