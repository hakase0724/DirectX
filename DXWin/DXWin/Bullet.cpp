#include "stdafx.h"
#include "Bullet.h"
#include "CommonValues.h"
#include "BulletManager.h"
#include "DXGameObjectManager.h"

using namespace MyDirectX;

void Bullet::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mDXInput = mGameObject->GetDXInput();
	mId = mGameObject->GetID();
	mDXCamera = mGameObject->GetDXCamera();
	auto manager = mGameObject->GetDXGameObjectManager();
	mBulletManager = mGameObject->GetDXGameObjectManager()->GetBulletManager();
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
	transform->Position.y += 0.01f;
	//�X�N���[�����W�擾
	auto screenPos = mDXCamera->WorldToScreenPoint(transform);
	//�Ԃ��Ă����s��̒�����y���W���擾
	auto screenPosY = screenPos.m128_f32[1];
	//��ʊO�ɏo����
	if(screenPosY < -cHeight / 2)
	{
		mBulletManager->ReturnBullet(mGameObject);
	}
	
}

void Bullet::OnCollisionEnter()
{
	mBulletManager->ReturnBullet(mGameObject);
}
