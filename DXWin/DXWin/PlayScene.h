#pragma once
#include "Scene.h"
#include "BackGround.h"
#include "BulletPool.h"
#include "BarrageManager.h"
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
		std::unique_ptr<BarrageManager> mBarrageManager;
		int mFrameCount;
		const int FPS_CHEACK_FRAME_COUNT = 60;
		DXText* mFPSText;
		//シーン開始時にアクティブにするオブジェクト
		std::vector<DXGameObject*> mAwakeObject;
		DXGameObject* mPlayer;
		DXGameObject* mEnemy;
		//ウェーブを管理する配列
		std::vector<std::vector<DXGameObject*>> mEnemyWaveList;
		//最終ウェーブか
		bool mIsLastWave;
		//今のウェーブ数
		int mWaveCount;
	};
}


