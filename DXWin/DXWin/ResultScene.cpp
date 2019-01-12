#include "stdafx.h"
#include "ResultScene.h"
#include <sstream>

using namespace DirectX;
using namespace MyDirectX;

void ResultScene::Init()
{
	//���U���g
	auto result = Instantiate();
	mResultText = result->AddComponent<DXText>();
	auto transform = result->GetTransform();
	transform->Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);
	transform->Position.x -= 1.0f;
	result->SetEnable(true);

	//�����e�L�X�g
	auto resultMessage = Instantiate();
	auto message = resultMessage->AddComponent<DXText>();
	auto transform2 = resultMessage->GetTransform();
	transform2->Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	transform2->Position.x -= 1.1f;
	transform2->Position.y -= 0.4f;
	message->UpdateText(L"PRESS ENTER: GO TO TITLE");
	resultMessage->SetEnable(true);

	auto endMessage = Instantiate();
	auto message2 = endMessage->AddComponent<DXText>();
	auto transform3 = endMessage->GetTransform();
	transform3->Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	transform3->Position.x -= 0.9f;
	transform3->Position.y -= 0.6f;
	message2->UpdateText(L"PRESS ESC: GAME END");
	endMessage->SetEnable(true);
}

void ResultScene::SceneStart()
{
	//�����~�߂�
	mDXRescourceManager->GetBGMDXSound()->Stop();
	mDXRescourceManager->GetSEDXSound()->Stop();
	//���U���g�X�R�A��\��
	std::wstringstream resultScore;
	resultScore.precision(6);
	resultScore << mDXRescourceManager->GetScore();
	auto resultScoret = resultScore.str();
	auto resultScoreptr = resultScoret.c_str();
	mResultText->UpdateText(resultScoreptr);
	resultScore.clear();
}

bool ResultScene::IsSceneEnd()
{
	//�G���^�[�����ꂽ��
	if (mDXRescourceManager->GetKeyDown(DIK_RETURN))return true;
	return false;
}
