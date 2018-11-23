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
		virtual void Init() override;
		virtual void SceneStart() override;
		virtual void SceneUpdate() override;
		virtual void SceneEnd() override;
		virtual bool IsSceneEnd() override;
	private:
		std::unique_ptr<BackGround> mBackGround;
		std::unique_ptr<BulletPool> mBulletPool;
		int mFrameCount;
		const int FPS_CHEACK_FRAME_COUNT = 60;
		DXText* mFPSText;
		//シーン開始時にアクティブにするオブジェクト
		std::vector<DXGameObject*> mAwakeObject;
		DXGameObject* mPlayer;
		DXGameObject* mEnemy;
	};
}


