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
		virtual void OnCollisionEnter2D(Collider2D* col) override;
		virtual void OnDisable() override;
		//x座標固定
		void FixedXAxiz(float* axiz) 
		{
			isXFixed = true;
			mFixedXAxiz = axiz;
		}
		//y座標固定
		void FixedYAxiz(float* axiz) 
		{
			isYFixed = true;
			mFixedYAxiz = axiz;
		}
		void SetTextureComponent(DXTexture* renderer) { mRenderer = renderer; }
		void SetTexture(const wchar_t* fileName) { mRenderer->SetTexture(fileName); }
		//オブジェクトプールに帰る
		void ReturnPool();
	private:
		DXInput* mDXInput;
		DXCamera* mDXCamera;
		TRANSFORM* mTransform;
		Vec2* mMoveVectol;
		BulletPool* mBulletPool;
		DXTexture* mRenderer;
		//固定する座標
		float* mFixedXAxiz;
		float* mFixedYAxiz;
		//座標固定フラグ
		bool isXFixed = false;
		bool isYFixed = false;
	};
}

