#pragma once
#include "BarrageBase.h"

namespace MyDirectX
{
	class SixWayRazerBarrage :public BarrageBase
	{
	public:
		SixWayRazerBarrage();
		~SixWayRazerBarrage() {};
		virtual void CreateBarrage(BulletPool* pool, DXGameObject* player, DXGameObject* enemy);
	private:
		float mCosAngle;
		float mSinAngle;
	};
}


