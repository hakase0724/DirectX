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
		//�V�[���J�n���ɃA�N�e�B�u�ɂ���I�u�W�F�N�g
		std::vector<DXGameObject*> mAwakeObject;
		DXGameObject* mPlayer;
		DXGameObject* mEnemy;
		//�E�F�[�u���Ǘ�����z��
		std::vector<std::vector<DXGameObject*>> mEnemyWaveList;
		//�ŏI�E�F�[�u��
		bool mIsLastWave;
		//���̃E�F�[�u��
		int mWaveCount;
	};
}


