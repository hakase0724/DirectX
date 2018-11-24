#pragma once
#include "BarrageBase.h"

namespace MyDirectX
{
	class TargetPlayerBarrage :public BarrageBase
	{
	public:
		TargetPlayerBarrage();
		~TargetPlayerBarrage() {};
		virtual void CreateBarrage(BulletPool* pool, DXGameObject* player, DXGameObject* enemy);
	};
}


