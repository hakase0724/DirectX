#pragma once
#include "IComponent.h"
#include "AlignedAllocationPolicy.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "Player.h"

namespace MyDirectX
{
	//class Player {};

	class OptionUnit :public Component,public AlignedAllocationPolicy<16>
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
		void SetXOffset(float xoffset) { mOffset.x = xoffset; };
		void SetYOffset(float yoffset) { mOffset.y = yoffset; };
	private:
		DXGameObject* mPlayerGameObject;
		BulletPool* mBulletPool;
		Player* mPlayerCom;
		DirectX::XMFLOAT3 mOffset;
	};
}


