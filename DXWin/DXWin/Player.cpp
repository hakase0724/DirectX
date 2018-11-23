#include "stdafx.h"
#include "Player.h"
#include "DXGameObjectManager.h"

using namespace MyDirectX;

void Player::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mDXInput = mGameObject->GetDXInput();
	auto transform = mGameObject->GetTransform();
	transform->Scale.x /= 2.0f;
	transform->Scale.y /= 2.0f;
	transform->Scale.z /= 2.0f;
	mId = mGameObject->GetID();
	mGameObject->SetDefaultTransform(transform);
	mWaitCount = mCoolCount;
	HitPoint = 4.0;
}

void Player::Initialize()
{
	mGameObject->ResetTransform();
	mWaitCount = mCoolCount;
	HitPoint = 4.0f;
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
			auto game = mBulletPool->GetBullet(mGameObject->GetTransform(), Tag::PlayerBullet);
			auto gameTransform = game->GetTransform();
			//�e�e���m�̊Ԋu
			auto offset = gameTransform->Scale.x;
			gameTransform->Position.x += offset * (i - (float)bulletNum / 3.0f);
		}
	}	
	else if(!mDXInput->GetInputState(DIK_Z))
	{
		//���˂��Ȃ������ꍇ�͔��ˉ\��Ԃɂ��Ă���
		mWaitCount = mCoolCount - 1;
	}
}

void Player::OnCollisionEnter()
{
	HitPoint -= 1.0;
	//�̗͂��Ȃ��Ȃ����玩�g�̃A�N�e�B�u��؂�
	if(HitPoint <= 0)
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
