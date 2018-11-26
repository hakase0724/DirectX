#pragma once
#include "Scene.h"

namespace MyDirectX
{
	class ResultScene :public Scene
	{
	public:
		ResultScene() {};
		~ResultScene() {};
		virtual void Init() override;
		virtual bool IsSceneEnd() override;
	};

}

