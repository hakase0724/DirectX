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
	mMoveVectol = new Vec2(0, 0);
}

void Bullet::Initialize()
{
	mId = mGameObject->GetID();
	mTag = mGameObject->GetTag();
	mFixedXAxiz = nullptr;
	mFixedYAxiz = nullptr;
	isXFixed = false;
	isYFixed = false;
}

void Bullet::Update()
{
	auto transform = mGameObject->GetTransform();
	transform->Position.x += mMoveVectol->x;
	transform->Position.y += mMoveVectol->y;
	//���W�Œ�t���O�������Ă���΍��W���㏑������
	if(isXFixed)
	{
		transform->Position.x = *mFixedXAxiz;
	}
	if(isYFixed)
	{
		transform->Position.y = *mFixedYAxiz;
	}
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

void Bullet::OnCollisionEnter2D(Collider2D* col)
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
