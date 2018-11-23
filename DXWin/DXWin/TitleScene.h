#pragma once
#include "Scene.h"

namespace MyDirectX
{
	class TitleScene :public Scene
	{
	public:
		TitleScene() {};
		void Init();
		~TitleScene() {};
		virtual bool IsSceneEnd() override;
	};
}

