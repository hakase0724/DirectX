#include "stdafx.h"
#include "Bullet.h"
#include "CommonValues.h"
#include "BulletPool.h"

using namespace MyDirectX;

void Bullet::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mDXInput = mGameObject->GetDXInput();
	mId = mGameObject->GetID();
	mDXCamera = mGameObject->GetDXCamera();
	mTag = mGameObject->GetTag();
}

void Bullet::Initialize()
{
	mId = mGameObject->GetID();
	mTag = mGameObject->GetTag();
}

void Bullet::Update()
{
	auto transform = mGameObject->GetTransform();
	transform->Position.x += mMoveVectol->x;
	transform->Position.y += mMoveVectol->y;
	//�X�N���[�����W�擾
	auto screenPos = mDXCamera->WorldToScreenPoint(transform);
	//�Ԃ��Ă����s��̒�������W���擾
	auto screenPosX = screenPos.m128_f32[0];
	auto screenPosY = screenPos.m128_f32[1];
	//��ʒ�����cHeight / 2
	//��ʊO�ɏo����
	if(screenPosY < -cHeight / 2)
	{
		mGameObject->SetEnable(false);
	}
	if(screenPosY > cHeight + cHeight / 2)
	{
		mGameObject->SetEnable(false);
	}
	if(screenPosX < -cWidth / 2)
	{
		mGameObject->SetEnable(false);
	}
	if (screenPosX > cWidth + cWidth / 2)
	{
		mGameObject->SetEnable(false);
	}
	
	
}

void Bullet::OnCollisionEnter()
{
	mGameObject->SetEnable(false);
}

void Bullet::OnDisable()
{
	ReturnPool();
}

void Bullet::ReturnPool()
{
	mBulletPool->ReturnBullet(mGameObject);
}
