#include "stdafx.h"
#include "DXGameObject.h"

using namespace DirectX;
using namespace MyDirectX;

DXGameObject::DXGameObject(DXResourceManager* manager)
{
	mTransform = std::make_unique<TRANSFORM>();
	mTransform->Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform->Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform->Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	mDXResourceManager = manager;
	mDXManager = mDXResourceManager->GetDXManager();
	mDXInput = mDXManager->GetDXInput();
	mDXCamera = mDXManager->GetDXCamera();
	mName = "GameObject";
}

DXGameObject::~DXGameObject()
{
	Exit();
}

void DXGameObject::RemoveComponent(Component * com)
{
	//�������ɍ��v�������̂�z��̏I�[�ɉ�������
	auto remove = std::remove_if(mComponentsList.begin(), mComponentsList.end(), [&](Component* mCom)->bool {return mCom == com; });
	//�������̂͏I�[�ɏW�܂��Ă邽�ߌ�납�����
	mComponentsList.erase(remove, mComponentsList.end());
}

//���g�̏�����
HRESULT DXGameObject::Init(DXManager * dxManager)
{
	mDXManager = dxManager;
	mDXInput = mDXManager->GetDXInput();
	mDXCamera = mDXManager->GetDXCamera();
	return S_OK;
}

//�����Ă���R���|�[�l���g�̏������������s��
void DXGameObject::InitializeComponent()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->Initialize();
	}
}

//�����Ă���R���|�[�l���g�̍X�V�������s��
void DXGameObject::Update()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		if (!pItr->GetEnable())continue;
		pItr->Update();
	}
}

//�����Ă���R���|�[�l���g�̍X�V�������I�������ł̍X�V����
void DXGameObject::LateUpdate()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		if (!pItr->GetEnable())continue;
		pItr->LateUpdate();
	}
}


//�����Ă���R���|�[�l���g�̕`�揈�����s��
void DXGameObject::Render()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		if (!pItr->GetEnable())continue;
		pItr->Render();
	}
}

//�����Ă���R���|�[�l���g�̉���������s��
void DXGameObject::Exit()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->Exit();
		delete pItr;
	}
}

//�Փ˂������̏���
void DXGameObject::OnCollisionEnter2D(Collider2D* col)
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		if (!pItr->GetEnable())continue;
		pItr->OnCollisionEnter2D(col);
	}
}

//�Փ˂��I��������̏���
void DXGameObject::OnCollisionExit2D(Collider2D* col)
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		if (!pItr->GetEnable())continue;
		pItr->OnCollisionExit2D(col);
	}
}

//�A�N�e�B�u�ɂȂ�����
void DXGameObject::OnEnable()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->OnEnable();
	}
}

//��A�N�e�B�u�ɂȂ�����
void DXGameObject::OnDisable()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->OnDisable();
	}
}
