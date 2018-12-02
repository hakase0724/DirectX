#pragma once
#include<memory>
#include "DXManager.h"
#include "DXSound.h"
#include "FPSCountor.h"
#include "CSVLoader.h"

namespace MyDirectX
{
	class DXGameObject;

	class DXResourceManager
	{
	public:
		DXResourceManager(HWND hwnd);
		~DXResourceManager() {};
		//�I�u�W�F�N�g�𐶐�����
		DXGameObject* Instantiate();
		//DirectX���\�[�X�Ǘ��N���X��Ԃ�
		DXManager* GetDXManager() const { return mDXManager.get(); }
		//�w�肵���L�[�����͂��ꂽ�^�C�~���O��
		bool GetKeyDown(int key) { return mDXManager->GetDXInput()->GetKeyDown(key); }
		//�w�肵���L�[�����͂���Ă��邩
		bool GetKey(int key) { return mDXManager->GetDXInput()->GetInputState(key); }
		//���Ǘ��N���X��Ԃ�
		DXSound* GetBGMDXSound() const { return mBGMDXSound.get(); }
		DXSound* GetSEDXSound() const { return mSEDXSound.get(); }
		//FPS��Ԃ�
		double GetFPS() const { return mFPS; }
		//���݂̓��͏󋵂��擾
		void SetInputState() { mDXManager->GetDXInput()->SetInputState(); }
		//���̃t���[���֍s���O�Ɍ��݂̓��͏󋵂��L�^����
		void SetPreBuffer() { mDXManager->GetDXInput()->SetPreBuffer(); }
		//FPS���v�Z����
		void UpdateFPS() { mFPS = mFPSCountor->GetFPS(); }
		std::vector<DATA> LoadData(const char* filePath) { return mCSVLoader->LoadData(filePath); }
	private:
		//FPS�v�Z���ʂ�ێ�
		double mFPS;
		//���������I�u�W�F�N�g��
		UINT mGameObjectCount;
		//�e��@�\�N���X
		std::unique_ptr<FPSCountor> mFPSCountor;
		std::unique_ptr<DXManager> mDXManager;
		std::unique_ptr<DXSound> mBGMDXSound;
		std::unique_ptr<DXSound> mSEDXSound;
		std::unique_ptr<CSVLoader> mCSVLoader;
	};
}


