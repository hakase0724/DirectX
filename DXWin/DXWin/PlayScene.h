#pragma once
#include "Scene.h"
#include "BackGround.h"
#include "BulletPool.h"
#include "BarrageManager.h"
#include "DXText.h"
#include "DXTexture.h"

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
		//自機生成
		void CreatePlayer(DATA data);
		//ボス生成
		void CreateBossEnemy(DATA data);
		//雑魚敵生成
		void CreateNormalEnemy(DATA data);
		std::unique_ptr<BackGround> mBackGround;
		std::unique_ptr<BulletPool> mBulletPool;
		std::unique_ptr<BarrageManager> mBarrageManager;
		//フレーム計測用
		int mFrameCount;
		//FPS表示更新フレーム数
		const int FPS_CHEACK_FRAME_COUNT = 60;
		//FPS表示テキスト
		DXText* mFPSText;
		//シーン開始時にアクティブにするオブジェクト
		std::vector<DXGameObject*> mAwakeObject;
		//自機
		DXGameObject* mPlayer;
		//ボス敵
		DXGameObject* mEnemy;
		//ウェーブを管理する配列
		std::vector<std::vector<DXGameObject*>> mEnemyWaveList;
		//最終ウェーブか
		bool mIsLastWave;
		//今のウェーブ数
		int mWaveCount;
	};
}


