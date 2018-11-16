#pragma once
#include "BarrageBase.h"

namespace MyDirectX
{
	class SixWayRazerBarrage :public BarrageBase
	{
	public:
		SixWayRazerBarrage();
		~SixWayRazerBarrage() {};
		virtual bool IsBarrageEnd();
		virtual void CreateBarrage(BulletManager* manager, DXGameObject* player, DXGameObject* enemy);
	private:
		float mCosAngle;
		float mSinAngle;
		float mRazerNum;
	};
}


