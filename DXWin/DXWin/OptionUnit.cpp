#include "stdafx.h"
#include "OptionUnit.h"
#include "DXGameObject.h"


using namespace MyDirectX;

void OptionUnit::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mOffset = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void OptionUnit::Initialize()
{
	auto transform = mGameObject->GetTransform();
	transform->Scale.x /= 5;
	transform->Scale.y /= 5;
	transform->Scale.z /= 5;
}

void OptionUnit::Update()
{
	auto playerTransform = mPlayerGameObject->GetTransform();
	auto transform = mGameObject->GetTransform();
	transform->Position.x = playerTransform->Position.x + mOffset.x;
	transform->Position.y = playerTransform->Position.y + mOffset.y;
	transform->Position.z = playerTransform->Position.z + mOffset.z;
	if(mPlayerCom->IsShot())
	{
		BULLET_SETTING_DATA data;
		data.transform = mGameObject->GetTransform();
		data.tag = PlayerBullet;
		data.xVectol = 0.0f;
		data.yVectol = 0.05f;
		data.texturePath = _T("Texture/Bullet3.png");
		data.scaleRatio = 0.3f;
		//’e‚ðo‚·
		auto game = mBulletPool->GetBullet(data);
	}
}

void OptionUnit::SetPlayer(DXGameObject * player)
{
	mPlayerGameObject = player;
	mPlayerCom = player->GetComponent<Player>();
}
