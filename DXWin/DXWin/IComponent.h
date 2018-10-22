#pragma once
#include<string>


namespace MyDirectX
{
	class DXGameObject;

	struct Collisioninfo
	{
		std::string name;
		UINT id;
		Collisioninfo() {};
	};

	//�R���|�[�l���g�̃C���^�[�t�F�C�X
	class IComponent
	{
	public:
		virtual void Initialize(DXGameObject* gameObject) = 0;
		virtual void Awake() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;
		virtual void Exit() = 0;
		virtual void OnCollisionEnter(Collisioninfo* info) = 0;
		virtual void OnCollisionStay(Collisioninfo* info) = 0;
		virtual void OnCollisionExit(Collisioninfo* info) = 0;
		virtual std::string GetName() = 0;
		virtual UINT GetID() = 0;
		virtual ~IComponent() = 0 {};
	};

	//�R���|�[�l���g�N���X
	//���̃N���X���p�������N���X��DXGameObject�ɒǉ����Ă���
	//C++�ł͒��ۃN���X��template�ɓn�����Ƃ��ł��Ȃ��炵���̂ł��̃N���X��n��
	class Component:public IComponent
	{
	public:
		//����������
		virtual void Initialize(DXGameObject* gameObject) {};
		//�܂��Ă΂�Ȃ��@�����������炱�̂܂܎g�킸���������E�E�E
		virtual void Awake() {};
		virtual void Start() {};
		//�X�V����
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void FixedUpdate() {};
		//�`�揈��
		virtual void Render() {};
		//�������
		virtual void Exit() {};
		virtual void OnCollisionEnter(Collisioninfo* info) {};
		virtual void OnCollisionStay(Collisioninfo* info) {};
		virtual void OnCollisionExit(Collisioninfo* info) {};
		virtual std::string GetName() { return mName; }
		virtual UINT GetID() { return mId; }
		virtual ~Component() {};
	protected:
		DXGameObject* mGameObject;
		std::string mName;
		UINT mId;
	};
}
