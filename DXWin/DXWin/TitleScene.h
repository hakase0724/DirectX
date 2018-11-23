#pragma once
#include "Scene.h"

namespace MyDirectX
{
	class TitleScene :public Scene
	{
	public:
		TitleScene() {};
		virtual void Init() override;
		~TitleScene() {};
		virtual bool IsSceneEnd() override;
	};
}

