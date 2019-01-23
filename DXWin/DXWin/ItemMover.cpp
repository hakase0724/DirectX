#include "stdafx.h"
#include "ItemMover.h"
#include "CommonValues.h"
#include "DXGameObject.h"

using namespace MyDirectX;

void ItemMover::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mDXCamera = mGameObject->GetDXCamera();
	mId = mGameObject->GetID();
	mTag = mGameObject->GetTag();
	//�����ݒ肵�Ȃ������ꍇ�̈ړ����x
	mMoveSpeed = 0.02f;
}

void ItemMover::Update()
{
	auto transform = mGameObject->GetTransform();
	transform->Position.y -= mMoveSpeed;
	//�X�N���[�����W�擾
	auto screenPos = mDXCamera->WorldToScreenPoint(transform);
	//�Ԃ��Ă����s��̒�������W���擾
	auto screenPosX = screenPos.m128_f32[0];
	auto screenPosY = screenPos.m128_f32[1];
	//��ʒ�����cHeight / 2
	//��ʊO�ɏo����
	if (screenPosY < -cHeight / 2)
	{
		mGameObject->SetEnable(false);
	}
	if (screenPosY > cHeight + cHeight / 2)
	{
		mGameObject->SetEnable(false);
	}
	if (screenPosX < -cWidth / 2)
	{
		mGameObject->SetEnable(false);
	}
	if (screenPosX > cWidth + cWidth / 2)
	{
		mGameObject->SetEnable(false);
	}
}
