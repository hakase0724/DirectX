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
		//初期化処理
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		void SetBulletPool(BulletPool* pool) { mBulletPool = pool; }
		//ベクトル設定
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
		//更新処理1
		virtual void Update() override;
		virtual void OnCollisionEnter() override;
		virtual void OnDisable() override;
		void SetTextureComponent(DXTexture* renderer) { mRenderer = renderer; }
		void SetTexture(const wchar_t* fileName) { mRenderer->SetTexture(fileName); }
		void ReturnPool();
	private:
		DXInput* mDXInput;
		DXCamera* mDXCamera;
		TRANSFORM* mTransform;
		Vec2* mMoveVectol;
		BulletPool* mBulletPool;
		DXTexture* mRenderer;
	};
}

