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
	mGameObject->SetTransform(transform);
	mId = mGameObject->GetID();
	mWaitCount = mCoolCount;
	mBulletManager = mGameObject->GetDXGameObjectManager()->GetBulletManager();
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
			auto game = mBulletManager->GetBullet(mGameObject->GetTransform(), Tag::PlayerBullet);
			auto gameTransform = game->GetTransform();
			//�e�e���m�̊Ԋu
			auto offset = gameTransform->Scale.x/* + gameTransform->Scale.x / 2*/;
			gameTransform->Position.x += offset * (i - (float)bulletNum / 3.0f);
			game->SetTransform(gameTransform);
		}
	}	
	else if(!mDXInput->GetInputState(DIK_Z))
	{
		//���˂��Ȃ������ꍇ�͔��ˉ\��Ԃɂ��Ă���
		mWaitCount = mCoolCount - 1;
	}
	//�f�o�b�O�p
	//�G���^�[�L�[�������ꂽ�Ƃ��������~�߂�
	if (mDXInput->GetInputState(DIK_RETURN))
	{
		//�����Ӗ��̂Ȃ��R�[�h���ƃR���p�C�����̍œK���ɂ���ď�����͗l
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
