#pragma once
#include <memory>
#include <vector> 
#include "BarrageBase.h"
namespace MyDirectX
{
	class BarrageManager
	{
	public:
		BarrageManager();
		~BarrageManager() {};
		template<typename T>
		BarrageBase* SetBarrage();
		BarrageBase* GetBarrage(BarrageName name);
	private:
		std::vector<std::unique_ptr<BarrageBase>> mBarrageList;
	};

	template<typename T>
	inline BarrageBase* BarrageManager::SetBarrage()
	{
		if (!typeid(T).before(typeid(BarrageBase*))) return nullptr;
		mBarrageList.push_back(std::make_unique<T>());
		return mBarrageList.back().get();
	}

}

