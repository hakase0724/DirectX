#pragma once
#include "BarrageBase.h"

namespace MyDirectX
{
	class TargetPlayerBarrage :public BarrageBase
	{
	public:
		TargetPlayerBarrage();
		~TargetPlayerBarrage() {};
		virtual bool IsBarrageEnd();
		virtual void CreateBarrage(BulletManager* manager, DXGameObject* player, DXGameObject* enemy);
	};
}


