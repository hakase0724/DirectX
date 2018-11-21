#pragma once
#include "Scene.h"
#include "BackGround.h"
#include "BulletPool.h"
#include "DXText.h"

namespace MyDirectX
{
	class PlayScene :public Scene
	{
	public:
		PlayScene() {};
		~PlayScene() {};
		void Init();
		virtual void SceneStart() override;
		virtual void SceneUpdate() override;
		virtual void SceneEnd() override;
	private:
		std::unique_ptr<BackGround> mBackGround;
		std::unique_ptr<BulletPool> mBulletPool;
		int mFrameCount;
		const int FPS_CHEACK_FRAME_COUNT = 60;
		DXText* mFPSText;
	};
}


