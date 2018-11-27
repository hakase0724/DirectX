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
	//�������L��
	mDefaultScaleX = mTransform->Scale.x;
	mDefaultPositionX = mTransform->Position.x;
	mMaxHitPoint = mHPViewObject->GetMaxHP();
}

void HPGauge::Update()
{
	//�̗͔䗦�v�Z
	auto hpRate = mHPViewObject->GetHP() / mMaxHitPoint;
	//�o�[�̃T�C�Y�ύX
	auto scalex = mDefaultScaleX * hpRate;
	mTransform->Scale.x = scalex;
	//�T�C�Y�ύX�ɍ��킹�ďꏊ���ړ�
	auto positionx = mDefaultPositionX - mDefaultScaleX * (1 - hpRate) * 0.5;
	mTransform->Position.x = positionx;
}
