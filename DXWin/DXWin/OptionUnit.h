#pragma once
#include "IComponent.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "Player.h"

namespace MyDirectX
{
	//class Player {};

	class OptionUnit :public Component
	{
	public:
		OptionUnit() {};
		~OptionUnit() {};
		//èâä˙âªèàóù
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		virtual void Update() override;
		void SetPlayer(DXGameObject* player);
		void SetBulletPool(BulletPool* bulletPool) { mBulletPool = bulletPool; };
		void SetXOffset(float xoffset) { mXOffset = xoffset; };
		void SetYOffset(float yoffset) { mYOffset = yoffset; };
	private:
		DXGameObject* mPlayerGameObject;
		BulletPool* mBulletPool;
		Player* mPlayerCom;
		TRANSFORM* mTransform;
		TRANSFORM* mPlayerTransform;
		float mXOffset;
		float mYOffset;
	};
}


