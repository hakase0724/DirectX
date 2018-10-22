#pragma once
#include "Primitive2D.h"
#include "IComponent.h"
#include <vector> 

namespace MyDirectX
{
	class Collider2D :public Component
	{
	public:
		Collider2D() {};
		virtual ~Collider2D() {};
		virtual bool IsCollision(Collider2D* otherCollider) { return false; }
		//����������
		virtual void Initialize(DXGameObject* gameObject)override {};
		//�܂��Ă΂�Ȃ��@�����������炱�̂܂܎g�킸���������E�E�E
		virtual void Awake()override {};
		virtual void Start()override {};
		//�X�V����
		virtual void Update()override {};
		virtual void LateUpdate()override {};
		virtual void FixedUpdate()override {};
		//�`�揈��
		virtual void Render()override {};
		//�������
		virtual void Exit()override {};
	protected:
		//�Փˏ��
		Collisioninfo info;
		//1�t���[���O�ɏՓ˂��Ă�����
		bool isCollided = false;
		std::vector<UINT> mCollisionList;
	};

}

