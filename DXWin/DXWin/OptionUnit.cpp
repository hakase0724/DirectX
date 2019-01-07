#include "stdafx.h"
#include "OptionUnit.h"
#include "DXGameObject.h"


using namespace MyDirectX;

void OptionUnit::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mTransform = mGameObject->GetTransform();
	mTransform->Scale.x /= 5;
	mTransform->Scale.y /= 5;
	mTransform->Scale.z /= 5;
}

void OptionUnit::Initialize()
{
	if (mPlayerTransform == nullptr) 
	{
		mPlayerTransform = mPlayerGameObject->GetTransform(); 
	}
}

void OptionUnit::Update()
{
	mTransform->Position = mPlayerTransform->Position;

	//����������Ă��邩
	if(mPlayerCom->IsLongPush())
	{
		//����Ă�����O����
		mTransform->Position.y += mYOffset;
	}
	else
	{
		//����Ă��Ȃ���Ή���
		mTransform->Position.x += mXOffset;
	}

	//�v���C���[���ł��Ă�����ꏏ�ɑł�
	if(mPlayerCom->IsShot())
	{
		BULLET_SETTING_DATA data;
		data.transform = mGameObject->GetTransform();
		data.tag = PlayerBullet;
		data.xVectol = 0.0f;
		data.yVectol = 0.05f;
		data.texturePath = _T("Texture/Bullet3.png");
		data.scaleRatio = 0.3f;
		//�e���o��
		mBulletPool->GetBullet(data);
	}
}

void OptionUnit::SetPlayer(DXGameObject * player)
{
	mPlayerGameObject = player;
	mPlayerCom = player->GetComponent<Player>();
}
