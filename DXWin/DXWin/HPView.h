#pragma once
#include "IComponent.h"
#include "DXText.h"
#include <sstream>

namespace MyDirectX
{
	class HPView
	{
	public:
		HPView(IHP* hp, DXText* text);
		~HPView();
		void Update();
	private:
		IHP* mHPObject;
		DXText* mViewText;
	};
}


