#pragma once
#include "BarrageBase.h"

namespace MyDirectX
{
	class AllDirectionSync :public BarrageBase
	{
	public:
		AllDirectionSync();
		~AllDirectionSync() {};
		virtual bool IsBarrageEnd();
		virtual void CreateBarrage(BulletManager* manager, DXGameObject* player, DXGameObject* enemy);
	private:
		float mCosAngle;
		float mSinAngle;
	};

}

