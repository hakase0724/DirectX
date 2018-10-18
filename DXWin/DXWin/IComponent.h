#pragma once


namespace MyDirectX
{
	class DXGameObject;

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
		virtual ~Component() {};
	protected:
		DXGameObject* mGameObject;
	};
}
