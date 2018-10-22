#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <memory>
#include <vector> 
#include <algorithm>
#include "DXManager.h"
#include "IComponent.h"


namespace MyDirectX
{
	//���̃v���W�F�N�g�̊j�ƂȂ�N���X
	//���̃N���X��Component�N���X���p�������N���X��ǉ����Ă���
	class DXGameObject
	{
	public:
		DXGameObject(DXManager* dxManager);
		DXGameObject(TRANSFORM* transform, DXManager* dxManager);
		virtual ~DXGameObject();
		//���g��transform�������J
		TRANSFORM GetTransform() const { return mTransform; }
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
		//�Q�b�^�[
		DXManager* GetDXManager() { return mDXManager; }
		DXInput* GetDXInput() { return mDXInput; }
		DXCamera* GetDXCamera() { return mDXCamera; }
		//���g��transform�����X�V
		virtual void SetTransform(TRANSFORM *transform) { mTransform = *transform; }
		//���g�̏�����
		virtual HRESULT Init(DXManager* dxManager);
		//���g�̏��X�V
		virtual void Update();
		virtual void LateUpdate();
		virtual void FixedUpdate();
		//���g�̕`��
		virtual void Render();
		//���g�̉��
		virtual void Exit();
		virtual void OnCollisionEnter(Collisioninfo* info);
		virtual void OnCollisionStay(Collisioninfo* info);
		virtual void OnCollisionExit(Collisioninfo* info);
		std::string GetName() { return mName; }
		void SetName(std::string name) { mName = name; }
	protected:
		//���g�̍��W��]�X�P�[��
		TRANSFORM mTransform;
		//DirectX�̃��\�[�X�Ǘ��N���X
		DXManager* mDXManager;
		//DirectInput�Ǘ��N���X
		DXInput* mDXInput;
		//�J�������
		DXCamera* mDXCamera;
		//���g�����R���|�[�l���g�̃��X�g
		std::vector<Component*> mComponentsList;
		std::string mName;
	};

	template<typename T>
	inline T * DXGameObject::AddComponent()
	{
		T* pReturn = nullptr;
		//Component�̔h���N���X�łȂ����null��Ԃ�
		if (!typeid(T).before(typeid(Component*))) return pReturn;
		pReturn = new T();
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



