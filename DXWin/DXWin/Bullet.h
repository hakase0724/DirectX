#pragma once
#include "IComponent.h"
#include "DXGameObject.h"

namespace MyDirectX
{
	class Bullet :public Component
	{
	public:
		Bullet() {};
		~Bullet() {};
		//����������
		virtual void Initialize(DXGameObject* gameObject);
		//�܂��Ă΂�Ȃ��@�����������炱�̂܂܎g�킸���������E�E�E
		virtual void Awake() {};
		virtual void Start() {};
		//�X�V����
		virtual void Update();
		virtual void LateUpdate() {};
		virtual void FixedUpdate() {};
		//�`�揈��
		virtual void Render() {};
		//�������
		virtual void Exit() {};
		virtual void OnCollisionEnter(CollisionInfo* info);
		virtual void OnCollisionStay(CollisionInfo* info) {};
		virtual void OnCollisionExit(CollisionInfo* info) {};
	private:
		DXInput* mDXInput;
	};

	struct BulletObject
	{
		DXGameObject* gameObject;
		Bullet* bullet;
	};
}

