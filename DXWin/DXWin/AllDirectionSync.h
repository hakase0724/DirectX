#pragma once
#include "BarrageBase.h"

namespace MyDirectX
{
	class AllDirectionSync :public BarrageBase
	{
	public:
		AllDirectionSync();
		~AllDirectionSync() {};
		virtual void CreateBarrage(BulletPool* pool, DXGameObject* player, DXGameObject* enemy);
	private:
		float mCosAngle;
		float mSinAngle;
	};

}

