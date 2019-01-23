#pragma once
#include "IComponent.h"
#include "DXGameObject.h"
#include "DXTexture.h"

namespace MyDirectX
{
	class BulletPool;

	class Bullet :public Component
	{
	public:
		Bullet() {};
		~Bullet() { delete mMoveVectol; };
		//����������
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		void SetBulletPool(BulletPool* pool) { mBulletPool = pool; }
		//�x�N�g���ݒ�
		void SetVectol(float x, float y)
		{ 
			if(mMoveVectol == nullptr)
			{
				mMoveVectol = new Vec2(x, y);
			}
			else
			{
				mMoveVectol->x = x;
				mMoveVectol->y = y;
			}
		}
		//�X�V����1
		virtual void Update() override;
		virtual void OnCollisionEnter2D(Collider2D* col) override;
		virtual void OnDisable() override;
		//x���W�Œ�
		void FixedXAxiz(float* axiz) 
		{
			isXFixed = true;
			mFixedXAxiz = axiz;
		}
		//y���W�Œ�
		void FixedYAxiz(float* axiz) 
		{
			isYFixed = true;
			mFixedYAxiz = axiz;
		}
		void SetTextureComponent(DXTexture* renderer) { mRenderer = renderer; }
		void SetTexture(const wchar_t* fileName) { mRenderer->SetTexture(fileName); }
		//�I�u�W�F�N�g�v�[���ɋA��
		void ReturnPool();
	private:
		DXInput* mDXInput;
		DXCamera* mDXCamera;
		TRANSFORM* mTransform;
		Vec2* mMoveVectol;
		BulletPool* mBulletPool;
		DXTexture* mRenderer;
		//�Œ肷����W
		float* mFixedXAxiz;
		float* mFixedYAxiz;
		//���W�Œ�t���O
		bool isXFixed = false;
		bool isYFixed = false;
	};
}

