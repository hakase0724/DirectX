#include "stdafx.h"
#include "Player.h"

using namespace MyDirectX;

void Player::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mDXInput = mGameObject->GetDXInput();
	auto transform = mGameObject->GetTransform();
	transform->Scale.x /= 3.0f;
	transform->Scale.y /= 3.0f;
	transform->Scale.z /= 3.0f;
	mId = mGameObject->GetID();
	mGameObject->SetDefaultTransform(transform);
	mWaitCount = mCoolCount;
	mHitPoint = 1.0;
}

void Player::Initialize()
{
	mGameObject->ResetTransform();
	mWaitCount = mCoolCount;
	mHitPoint = mDefaultHitPoint;
}

void Player::Update()
{
	//���t���[���J�E���g���s��
	mWaitCount++;
	
	if(!isCoolTime())
	{
		//���˂��Ȃ�
	}
	else if (mDXInput->GetInputState(DIK_Z))
	{
		//�������˂���p�e�X�g�R�[�h
		auto bulletNum = 4;
		for(int i = 0;i < bulletNum;i++)
		{
			BULLET_SETTING_DATA data;
			data.transform = mGameObject->GetTransform();
			data.tag = PlayerBullet;
			data.xVectol = 0.0f;
			data.yVectol = 0.05f;
			data.texturePath = _T("Texture/Bullet3.png");
			//�e���o��
			auto game = mBulletPool->GetBullet(data);
			auto gameTransform = game->GetTransform();
			//�e�e���m�̊Ԋu
			auto offset = gameTransform->Scale.x;
			gameTransform->Position.x += offset * (i - (float)bulletNum / 3.0f);
		}
		mGameObject->GetDXResourceManager()->GetSEDXSound()->ResetSound();
		mGameObject->GetDXResourceManager()->GetSEDXSound()->Play();
	}	
	else if(!mDXInput->GetInputState(DIK_Z))
	{
		//���˂��Ȃ������ꍇ�͔��ˉ\��Ԃɂ��Ă���
		//-1���Ă���͎̂��̔���ł�+1���Ĕ��肷�邩��
		mWaitCount = mCoolCount - 1;
		//SE�����Z�b�g���Ă���
		mGameObject->GetDXResourceManager()->GetSEDXSound()->Stop();
	}

#if _DEBUG
	if(mDXInput->GetKeyDown(DIK_RETURN))
	{
		mWaitCount = mCoolCount - 1;
	}
#endif

}

void Player::OnCollisionEnter()
{
	mHitPoint -= 1.0;
	//�̗͂��Ȃ��Ȃ����玩�g�̃A�N�e�B�u��؂�
	if(mHitPoint <= 0)
	{
		mGameObject->SetEnable(false);
	}
}

bool Player::isCoolTime()
{
	if(mWaitCount % mCoolCount == 0)
	{
		mWaitCount = 0;
		return true;
	}
	else
	{
		return false;
	}
}
