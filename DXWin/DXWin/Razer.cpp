#include "stdafx.h"
#include "Razer.h"
#include "DXGameObject.h"

using namespace MyDirectX;

void MyDirectX::Razer::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mTransform = mGameObject->GetTransform();
}

void MyDirectX::Razer::Initialize()
{
	mGameObject->ResetTransform();
	//初期情報記憶
	mDefaultScaleY = mTransform->Scale.y;
	mDefaultPositionY = mTransform->Position.y;
}

void MyDirectX::Razer::Update()
{
	//バーのサイズ変更
	auto scaley = mTransform->Scale.y * 0.01f;
	mTransform->Scale.y += scaley;
	//サイズ変更に合わせて場所を移動
	auto positiony = scaley * 0.5f;
	mTransform->Position.y += positiony;
}
