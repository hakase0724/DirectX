#pragma once
#include "Scene.h"
#include "BackGround.h"
#include "BulletPool.h"
#include "BarrageManager.h"
#include "DXText.h"
#include "DXTexture.h"
#include "Player.h"
#include "ReactiveProperty.h"

using namespace MyObservarPattern;

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
		void AddScore(double score){ *mScoreRP + score; }
	private:
		//自機生成
		void CreatePlayer(LOAD_FROM_CSV_DATA data);
		//ボス生成
		void CreateBossEnemy(LOAD_FROM_CSV_DATA data);
		//雑魚敵生成
		void CreateNormalEnemy(LOAD_FROM_CSV_DATA data);
		//背景生成
		void CreateBackGround();
		//CSVデータから生成する
		void CreateFromCSVData();
		//UI要素生成
		void CreateUIItem();
		//アイテム生成
		void CreateItem();
		//弾幕管理クラス生成
		void CreateBulletPool();
		//背景管理クラス　2つの画像を循環移動させる
		std::unique_ptr<BackGround> mBackGround;
		//弾のオブジェクトプール
		std::unique_ptr<BulletPool> mBulletPool;
		//弾幕管理クラス
		std::unique_ptr<BarrageManager> mBarrageManager;
		//フレーム計測用
		int mFrameCount;
		//FPS表示更新フレーム数
		const int FPS_CHEACK_FRAME_COUNT = 60;
		//FPS表示テキスト
		DXText* mFPSText;
		//HP表示テキスト
		DXText* mHPText;
		//Score表示テキスト
		DXText* mScoreText;
		//シーン開始時にアクティブにするオブジェクト
		std::vector<DXGameObject*> mAwakeObject;
		//自機
		DXGameObject* mPlayer;
		Player* mPlayerCom;
		//ボス敵
		DXGameObject* mEnemy;
		//ウェーブを管理する配列
		std::vector<std::vector<DXGameObject*>> mEnemyWaveList;
		//最終ウェーブか
		bool mIsLastWave;
		//今のウェーブ数
		int mWaveCount;
		//エイリアステンプレートを使って名前を短縮
		using Property = ReactiveProperty<double>;
		//HP表示に使う変数
		std::unique_ptr<Property, Deleter> mHpRP;
		//FPS表示に使う変数
		std::unique_ptr<Property, Deleter> mFPSRP;
		//Score表示に使う変数
		std::unique_ptr<Property, Deleter> mScoreRP;
	};
}


