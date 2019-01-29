#pragma once
#include "Scene.h"
#include "BackGround.h"
#include "BulletPool.h"
#include "BarrageManager.h"
#include "DXText.h"
#include "DXTexture.h"
#include "Player.h"
#include "ReactiveProperty.h"
#include "ScoreItemPool.h"
#include "ExplosionEffectPool.h"
#include "BombPool.h"
#include "PowerUpItemPool.h"

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
		void AddScore(double score)
		{ 
			if(mIsCombo)
			{
				mComboScore += score;
				mComboCountFrame = 0;
			}
			else mIsCombo = true;
			*mScoreRP + score; 
		}
		void CreateBomb(DirectX::XMFLOAT3 pos);
		void CreatePowerUp(DirectX::XMFLOAT3 pos);
		DXGameObject* CreateExplosionEffect(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 scale = { 0.5f,0.5f,0.5f });
		DXGameObject* CreateScoreItem(DirectX::XMFLOAT3 pos);
		void BossDie() { mIsBossDie = true; }
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
		//オブジェクトプール作成
		void CreateBulletPool();
		void CreateScoreItemPool();
		void CreateExplosionEffectPool();
		void CreateBombPool();
		void CreatePowerUpItemPool();
		//コンボ処理
		void ComboAction();
		//背景管理クラス　2つの画像を循環移動させる
		std::unique_ptr<BackGround> mBackGround;
		//オブジェクトプール
		std::unique_ptr<BulletPool> mBulletPool;
		std::unique_ptr<ScoreItemPool> mScoreItemPool;
		std::unique_ptr<ExplosionEffectPool> mExplosionEffectPool;
		std::unique_ptr<BombPool> mBombPool;
		std::unique_ptr<PowerUpItemPool> mPowerUpItemPool;
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
		//コンボ中のスコア
		double mComboScore = 0.0;
		//コンボ中か
		bool mIsCombo = false;
		//コンボ中の経過フレーム数
		int mComboCountFrame = 0;
		bool mIsBossDie = false;
		//コンボ継続フレーム数
		const int COMBO_LIMIT_FRAME = 30;
		//予め作る弾の数
		const int PRE_CREATE_BULLET_NUM = 1000;
	};
}


