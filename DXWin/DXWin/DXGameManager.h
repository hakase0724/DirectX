#pragma once
#include "DXResourceManager.h"
#include "DXExcuter.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "BulletPool.h"

namespace MyDirectX
{
	class DXGameManager
	{
	public:
		DXGameManager(HWND hwnd);
		~DXGameManager() {};
		void Initialize();
		//�Q�[�����[�v�����s
		//�I������false��Ԃ�
		bool Update();
		void SetVsyncIntarval(int intarval) { mDXResourceManager->SetVsyncIntarval(intarval); }
	private:
		//�V�[���؂�ւ�
		void SceneChange();
		//���V�[����
		int mSceneCount;
		//���ݓo�^���Ă���V�[���̔ԍ�
		int mSceneIndex;
		//�V�[���̃��X�g
		std::vector<std::unique_ptr<Scene>> mSceneList;
		//�@�\�N���X���܂Ƃ߂��N���X
		std::unique_ptr<DXResourceManager> mDXResourceManager;
		//�Q�[�����[�v�����s����N���X
		std::unique_ptr<DXExcuter> mDXExcuter;
	};

}

