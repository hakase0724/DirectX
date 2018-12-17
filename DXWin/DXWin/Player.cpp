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
	mMaxBombNum = 3;
	mPower = 1;
	mMaxPower = 4;
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
		for(int i = 0;i < mPower;i++)
		{
			BULLET_SETTING_DATA data;
			data.transform = mGameObject->GetTransform();
			data.tag = PlayerBullet;
			data.xVectol = 0.0f;
			data.yVectol = 0.05f;
			data.texturePath = _T("Texture/Bullet3.png");
			data.scaleRatio = 0.3f;
			//�e���o��
			auto game = mBulletPool->GetBullet(data);
			auto gameTransform = game->GetTransform();
			//�e�e���m�̊Ԋu
			auto offset = gameTransform->Scale.x;
			//�e���m�̃I�t�Z�b�g�v�Z
			gameTransform->Position.x += offset * (i - (float)mPower / 3.0f);
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

	if(mDXInput->GetKeyDown(DIK_X))
	{
		Bomb();
	}

#if _DEBUG
	//�G���^�[�L�[�Ńu���[�N�|�C���g
	if(mDXInput->GetKeyDown(DIK_RETURN))
	{
		mWaitCount = mCoolCount - 1;
	}
#endif

}

void Player::OnCollisionEnter2D(Collider2D* col)
{
	auto game = col->GetGameObject();
	//�A�C�e���Ƃ̏Փ˂ł̓_���[�W���󂯂Ȃ�
	if (game->GetTag() == Item) return;
	Damage(1.0);
}

void Player::Damage(double damage)
{
	mHitPoint -= damage;
	//�̗͂��Ȃ��Ȃ����玩�g�̃A�N�e�B�u��؂�
	if (mHitPoint <= 0)
	{
		mGameObject->SetEnable(false);
	}
}

void Player::Bomb()
{
	//�{���������Ă��Ȃ���Ή������Ȃ�
	if (mBombNum <= 0) return;
	//�V�[���ɓo�^����Ă���I�u�W�F�N�g���擾
	auto gameObjects = mGameObject->GetScene()->GetGameObjects();
	for (auto game : gameObjects)
	{
		//��A�N�e�B�u�Ȃ疳��
		if (!game->GetEnable()) continue;
		auto tag = game->GetTag();
		//���@�������͎��e�Ȃ疳��
		if (tag == PlayerTag) continue;
		if (tag == PlayerBullet) continue;
		//HP�������Ă���R���|�[�l���g���擾
		auto gameHaveHP = game->GetComponent<IHP>();
		//HP������Ȃ�_���[�W��^����
		if (gameHaveHP != nullptr)
		{
			gameHaveHP->Damage(10.0);
		}
		//�Ȃ���΃A�N�e�B�u��؂�
		else
		{
			game->SetEnable(false);
		}
	}
	mUsedBombNum++;
	//�g�p�񐔂��ő及�L���𒴂�����ő及�L�����X�V
	if(mUsedBombNum >= mMaxBombNum)
	{
		mUsedBombNum = 0;
		mMaxBombNum++;
	}
	mBombNum--;
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
