#include "stdafx.h"
#include "BarrageManager.h"
#include "AllDirectionSync.h"
#include "TargetPlayerBarrage.h"
#include "SixWayRazerBarrage.h"

using namespace MyDirectX;
BarrageManager::BarrageManager()
{
	SetBarrage<AllDirectionSync>();
	SetBarrage<TargetPlayerBarrage>();
	SetBarrage<SixWayRazerBarrage>();
}

BarrageBase * BarrageManager::GetBarrage(BarrageName name)
{
	BarrageBase* pReturn = nullptr;
	for(auto &barrage : mBarrageList)
	{
		if(barrage->GetName() == name)
		{
			pReturn = barrage.get();
			break;
		}
	}
	return pReturn;
}
