#pragma once
#include "Scene.h"
#include "BackGround.h"

namespace MyDirectX
{
	class PlayScene :public Scene
	{
	public:
		PlayScene() {};
		~PlayScene() {};
		void Init();
	private:
		std::unique_ptr<BackGround> mBackGround;
	};
}


