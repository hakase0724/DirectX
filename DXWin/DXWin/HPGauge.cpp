#include "stdafx.h"
#include "HPGauge.h"

using namespace MyDirectX;

void HPGauge::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
	mTransform = mGameObject->GetTransform();
}

void HPGauge::Initialize()
{
	mGameObject->ResetTransform();
	//初期情報記憶
	mDefaultScaleX = mTransform->Scale.x;
	mDefaultPositionX = mTransform->Position.x;
	mMaxHitPoint = mHPViewObject->GetMaxHP();
}

void HPGauge::Update()
{
	//体力比率計算
	auto hpRate = mHPViewObject->GetHP() / mMaxHitPoint;
	//バーのサイズ変更
	auto scalex = mDefaultScaleX * hpRate;
	mTransform->Scale.x = (float)scalex;
	//サイズ変更に合わせて場所を移動
	//ゲージ増加量の半分だけ移動させる
	auto positionx = mDefaultPositionX - mDefaultScaleX * (1 - hpRate) * 0.5;
	mTransform->Position.x = (float)positionx;
}
