#include "stdafx.h"
#include "TitleScene.h"
#include "DXText.h"

using namespace DirectX;
using namespace MyDirectX;

void TitleScene::Init()
{
	//タイトル
	auto title = Instantiate();
	auto text = title->AddComponent<DXText>();
	auto transform = title->GetTransform();
	transform->Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);
	transform->Position.x -= 1.0f;
	text->UpdateText(L"TITLE");
	title->SetEnable(true);

	//説明テキスト
	auto titleMessage = Instantiate();
	auto message = titleMessage->AddComponent<DXText>();
	auto transform2 = titleMessage->GetTransform();
	transform2->Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	transform2->Position.x -= 1.1f;
	transform2->Position.y -= 0.4f;
	message->UpdateText(L"PRESS ENTER: GAME START");
	titleMessage->SetEnable(true);

	auto endMessage = Instantiate();
	auto message2 = endMessage->AddComponent<DXText>();
	auto transform3 = endMessage->GetTransform();
	transform3->Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	transform3->Position.x -= 0.9f;
	transform3->Position.y -= 0.6f;
	message2->UpdateText(L"PRESS ESC: GAME END");
	endMessage->SetEnable(true);
}

bool TitleScene::IsSceneEnd()
{
	//エンター押されたら
	if (mDXRescourceManager->GetKeyDown(DIK_RETURN))return true;
	return false;
}
