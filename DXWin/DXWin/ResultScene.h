#pragma once
#include "Scene.h"

namespace MyDirectX
{
	class ResultScene :public Scene
	{
	public:
		ResultScene();
		~ResultScene();
		void Init();
		virtual bool IsSceneEnd() override;
	};

}

