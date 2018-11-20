#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <memory>
#include <vector> 
#include <algorithm>
#include "DXManager.h"
#include "IComponent.h"
#include "MyEnums.h"

namespace MyDirectX
{
	class DXGameObjectManager;
	class Scene;
	//���̃v���W�F�N�g�̊j�ƂȂ�N���X
	//���̃N���X��Component�N���X���p�������N���X��ǉ����Ă���
	class DXGameObject
	{
	public:
		DXGameObject(DXManager* dxManager);
		DXGameObject(DXManager* dxManager, DXGameObjectManager* dxGameObjectManager);
		DXGameObject(TRANSFORM* transform, DXManager* dxManager, DXGameObjectManager* dxGameObjectManager);
		virtual ~DXGameObject();
		//���g��transform�������J
		TRANSFORM* GetTransform() const { return mTransform.get(); }
		//���g�ɃR���|�[�l���g��ǉ�����
		template<typename T>
		T* AddComponent();
		//�w�肵���R���|�[�l���g���擾����
		//�w�肵���R���|�[�l���g���������Ă����ꍇ�͍ŏ��̈�̂ݕԂ�
		template<typename T>
		T* GetComponent();
		//�w�肵���R���|�[�l���g������
		template<typename T>
		void RemoveComponent();
		void RemoveComponent(Component* com);
		//�Q�b�^�[
		DXManager* GetDXManager() { return mDXManager; }
		DXInput* GetDXInput() { return mDXInput; }
		DXCamera* GetDXCamera() { return mDXCamera; }
		//���g��transform�����X�V
		virtual void SetTransform(TRANSFORM *transform) {/* mTransform = transform;*/ }
		//���g�̏�����
		virtual HRESULT Init(DXManager* dxManager);
		//���g�̎����Ă���R���|�[�l���g�̏�����
		virtual void InitializeComponent();
		//���g�̏��X�V
		virtual void Update();
		//�S�Ă�Update���I�������ŌĂ΂��
		virtual void LateUpdate();
		//���g�̕`��
		virtual void Render();
		//���g�̉��
		virtual void Exit();
		//�Փ˂������̏���
		virtual void OnCollisionEnter();
		//�Փ˂��I��������̏���
		virtual void OnCollisionExit();
		//�Q�b�^�[�ƃZ�b�^�[
		//���O
		std::string GetName() { return mName; }
		void SetName(std::string name) { mName = name; }
		//ID
		UINT GetID() const { return mId; }
		void SetID(UINT id) { mId = id; }
		//�^�O
		Tag GetTag() const { return mTag; }
		void SetTag(Tag tag) { mTag = tag; }
		//�A�N�e�B�u���
		bool GetEnable() const { return mEnable; }
		void SetEnable(bool enable) { mEnable = enable; }
		//�V�[�����
		Scene* GetScene() const { return mScene; }
		void SetScene(Scene* scene) { mScene = scene; }
		DXGameObjectManager* GetDXGameObjectManager() const { return mDXGameObjectManager; }
	protected:
		//���g�̍��W��]�X�P�[��
		std::unique_ptr<TRANSFORM> mTransform;
		//TRANSFORM* mTransform;
		//DirectX�̃��\�[�X�Ǘ��N���X
		DXManager* mDXManager;
		//DirectInput�Ǘ��N���X
		DXInput* mDXInput;
		//�J�������
		DXCamera* mDXCamera;
		DXGameObjectManager* mDXGameObjectManager;
		//���g�����R���|�[�l���g�̃��X�g
		std::vector<Component*> mComponentsList;
		std::string mName;
		Tag mTag;
		UINT mId;
		bool mEnable;
		Scene* mScene;
	};

	template<typename T>
	inline T * DXGameObject::AddComponent()
	{
		T* pReturn = nullptr;
		//Component�̔h���N���X�łȂ����null��Ԃ�
		if (!typeid(T).before(typeid(Component*))) return pReturn;
		pReturn = new T();
		//�ǉ������R���|�[�l���g�̏������������Ăяo��
		pReturn->Initialize(this);
		mComponentsList.push_back(pReturn);
		return pReturn;
	}

	template<typename T>
	inline T * DXGameObject::GetComponent()
	{
		T* pReturn = nullptr;
		//�z���S�������S�Ăɑ΂��ăL���X�g�����݂�
		//���������炻�̎��_�ő������I�����l��Ԃ�
		for(auto itr = mComponentsList.begin();itr != mComponentsList.end();++itr)
		{
			pReturn = dynamic_cast<T*>(*itr);	
			if (pReturn != NULL) break;
		}
		return pReturn;
	}

	template<typename T>
	inline void DXGameObject::RemoveComponent()
	{
		//�������ɍ��v�������̂�z��̏I�[�ɉ�������
		auto remove = std::remove_if(mComponentsList.begin(), mComponentsList.end(), [](Component* com)->bool {return dynamic_cast<T*>(com) != NULL; });
		//�������̂͏I�[�ɏW�܂��Ă邽�ߌ�납�����
		mComponentsList.erase(remove, mComponentsList.end());
	}

}



