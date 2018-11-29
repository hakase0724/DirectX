#pragma once
#include <string>
#include "MyStructs.h"
#include "MyEnums.h"


namespace MyDirectX
{
	class DXGameObject;

	//�R���|�[�l���g�̃C���^�[�t�F�C�X
	class IComponent
	{
	public:
		virtual void Initialize(DXGameObject* gameObject) = 0;
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void Render() = 0;
		virtual void Exit() = 0;
		virtual void OnCollisionEnter() = 0;
		virtual void OnCollisionExit() = 0;
		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		virtual std::string GetName() = 0;
		virtual UINT GetID() = 0;
		virtual ~IComponent() = 0 {};
	};

	class IHP
	{
	public:
		virtual void SetHP(double hp) = 0;
		virtual double GetHP() = 0;
		virtual double GetMaxHP() = 0;
	};

	//�R���|�[�l���g�N���X
	//���̃N���X���p�������N���X��DXGameObject�ɒǉ����Ă���
	//C++�ł͒��ۃN���X��template�ɓn�����Ƃ��ł��Ȃ��炵���̂ł��̃N���X��n��
	class Component:public IComponent
	{
	public:
		//����������
		virtual void Initialize(DXGameObject* gameObject) {};
		virtual void Initialize() {};
		//�X�V����
		virtual void Update() {};
		virtual void LateUpdate() {};
		//�`�揈��
		virtual void Render() {};
		//�������
		virtual void Exit() {};
		//�Փ˂̏���
		virtual void OnCollisionEnter() {};
		virtual void OnCollisionExit() {};
		virtual void OnEnable() {};
		virtual void OnDisable() {};
		std::string GetName() { return mName; }
		UINT GetID() { return mId; }
		Tag GetTag() const { return mTag; }
		void SetTag(Tag tag) { mTag = tag; }
		DXGameObject* GetGameObject() const { return mGameObject; }
		void SetEnable(bool enable) { mEnable = enable; }
		bool GetEnable() const { return mEnable; }
		virtual ~Component() {};
	protected:
		DXGameObject* mGameObject;
		std::string mName;
		UINT mId;
		Tag mTag;
		bool mEnable = true;
	};
}
