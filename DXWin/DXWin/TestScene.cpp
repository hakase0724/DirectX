#include "stdafx.h"
#include "TestScene.h"
#include "DXTexture.h"

using namespace MyDirectX;

void TestScene::Init()
{
	mGauge = Instantiate();
	auto renderer = mGauge->AddComponent<TextureRenderer>();
	auto gaugeTex = mGauge->AddComponent<DXTexture>();
	renderer->SetDefaultColor(1.0f, 0.8f, 0.0f, 0.0f);
	gaugeTex->SetTexture(_T("Texture/Square.png"));
	mTransform = mGauge->GetTransform();
	mTransform->Scale.y = 0.1f;
	mTransform->Scale.x = 3.0f;
	mGauge->SetEnable(true);
	mDefaultScaleX = mTransform->Scale.x;
	mDefaultPositionX = mTransform->Position.x;

	//”wŒi—p‰æ‘œ1
	auto back = Instantiate();
	auto texBack = back->AddComponent<DXTexture>();
	texBack->SetTexture(_T("Texture/background.png"));
	auto backTransform = back->GetTransform();
	backTransform->Position.z = 2.0f;
	backTransform->Scale.x = 5.0f;
	backTransform->Scale.y = 5.0f;
	back->SetEnable(true);

	//”wŒi—p‰æ‘œ2
	auto back2 = Instantiate();
	auto texBack2 = back2->AddComponent<DXTexture>();
	texBack2->SetTexture(_T("Texture/background.png"));
	auto backTransform2 = back2->GetTransform();
	backTransform2->Position.y = 5.0f;
	backTransform2->Position.z = 2.0f;
	backTransform2->Scale.x = 5.0f;
	backTransform2->Scale.y = 5.0f;
	back2->SetEnable(true);
}

void TestScene::SceneStart()
{
	mHitPoint = mMaxHitPoint;
}

void TestScene::SceneUpdate()
{
	if(mDXRescourceManager->GetKey(DIK_D))
	{
		mHitPoint -= 10;
	}
	if(mDXRescourceManager->GetKey(DIK_H))
	{
		mHitPoint += 10;
	}
	auto hpRate = mHitPoint / mMaxHitPoint;
	if (hpRate < 0.0) hpRate = 0.0;
	if (hpRate > 1.0) hpRate = 1.0;
	auto scalex = mDefaultScaleX * hpRate;
	mTransform->Scale.x = scalex;
	auto positionx = mDefaultPositionX - mDefaultScaleX * (1 - hpRate) * 0.5;
	mTransform->Position.x = positionx;
}

void TestScene::SceneEnd()
{
}

bool TestScene::IsSceneEnd()
{
	return false;
}
