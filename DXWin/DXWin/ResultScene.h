#pragma once
#include "Scene.h"
#include "DXText.h"


namespace MyDirectX
{
	class ResultScene :public Scene
	{
	public:
		ResultScene() {};
		~ResultScene() {};
		virtual void Init() override;
		virtual void SceneStart() override;
		virtual bool IsSceneEnd() override;
	private:
		DXText* mResultText;
	};

}

