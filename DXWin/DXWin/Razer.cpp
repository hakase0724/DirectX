#include "stdafx.h"
#include "Razer.h"
#include "DXGameObject.h"

using namespace MyDirectX;

void MyDirectX::Razer::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mTransform = mGameObject->GetTransform();
}

void MyDirectX::Razer::Initialize()
{
	mGameObject->ResetTransform();
	//�������L��
	mDefaultScaleY = mTransform->Scale.y;
	mDefaultPositionY = mTransform->Position.y;
}

void MyDirectX::Razer::Update()
{
	//�o�[�̃T�C�Y�ύX
	auto scaley = mTransform->Scale.y * 0.01f;
	mTransform->Scale.y += scaley;
	//�T�C�Y�ύX�ɍ��킹�ďꏊ���ړ�
	auto positiony = scaley * 0.5f;
	mTransform->Position.y += positiony;
}
