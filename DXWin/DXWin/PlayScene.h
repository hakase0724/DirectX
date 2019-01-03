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
		//���@����
		void CreatePlayer(LOAD_FROM_CSV_DATA data);
		//�{�X����
		void CreateBossEnemy(LOAD_FROM_CSV_DATA data);
		//�G���G����
		void CreateNormalEnemy(LOAD_FROM_CSV_DATA data);
		//�w�i����
		void CreateBackGround();
		//CSV�f�[�^���琶������
		void CreateFromCSVData();
		//UI�v�f����
		void CreateUIItem();
		//�A�C�e������
		void CreateItem();
		//�e���Ǘ��N���X����
		void CreateBulletPool();
		//�w�i�Ǘ��N���X�@2�̉摜���z�ړ�������
		std::unique_ptr<BackGround> mBackGround;
		//�e�̃I�u�W�F�N�g�v�[��
		std::unique_ptr<BulletPool> mBulletPool;
		//�e���Ǘ��N���X
		std::unique_ptr<BarrageManager> mBarrageManager;
		//�t���[���v���p
		int mFrameCount;
		//FPS�\���X�V�t���[����
		const int FPS_CHEACK_FRAME_COUNT = 60;
		//FPS�\���e�L�X�g
		DXText* mFPSText;
		//HP�\���e�L�X�g
		DXText* mHPText;
		//Score�\���e�L�X�g
		DXText* mScoreText;
		//�V�[���J�n���ɃA�N�e�B�u�ɂ���I�u�W�F�N�g
		std::vector<DXGameObject*> mAwakeObject;
		//���@
		DXGameObject* mPlayer;
		Player* mPlayerCom;
		//�{�X�G
		DXGameObject* mEnemy;
		//�E�F�[�u���Ǘ�����z��
		std::vector<std::vector<DXGameObject*>> mEnemyWaveList;
		//�ŏI�E�F�[�u��
		bool mIsLastWave;
		//���̃E�F�[�u��
		int mWaveCount;
		//�G�C���A�X�e���v���[�g���g���Ė��O��Z�k
		using Property = ReactiveProperty<double>;
		//HP�\���Ɏg���ϐ�
		std::unique_ptr<Property, Deleter> mHpRP;
		//FPS�\���Ɏg���ϐ�
		std::unique_ptr<Property, Deleter> mFPSRP;
		//Score�\���Ɏg���ϐ�
		std::unique_ptr<Property, Deleter> mScoreRP;
	};
}


