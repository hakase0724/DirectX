#pragma once
#include "DXManager.h"
#include "DXCube.h"
#include "DXSphere.h"
#include <vector> 
#include "DXGameObject.h"
#include "Mover.h"
#include "Collider.h"
#include "DXSquare.h"
#include "Roller.h"
#include "Colliders.h"
#include "Player.h"
#include "FPSCountor.h"
#include "BulletManager.h"
#include "MyStructs.h"
#include "DXTexture.h"
#include "Enemy.h"
#include "BackGround.h"
#include "DXSound.h"
#include "DXText.h"

namespace MyDirectX 
{
	class DXGameObjectManager
	{
	public:
		DXGameObjectManager(HWND hwnd);
		~DXGameObjectManager() {};
		DXManager* GetDXManager() const { return mDXManager.get(); }
		//�I�u�W�F�N�g�𐶐�
		DXGameObject* Instantiate();
		BOOL Update();
		void LateUpdate();
		void Render();
		//�w�肵��ID�̃I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�Ԃ�
		bool IsEnable(UINT id);
		//�w�肵��ID�̃I�u�W�F�N�g��Ԃ�
		DXGameObject* GetDXGameObjectWithID(UINT id);
		BulletManager* GetBulletManager() const { return mBulletManager.get(); }
	private:
		void ShowFPS();
		//�Q�[�����ɕK�v�ȃN���X���C���X�^���X������
		void CreateResources(HWND hwnd);
		//�Q�[���ɍŏ����瑶�݂���Q�[���I�u�W�F�N�g�𐶐�����
		void CreateGameObject();
		//�Q�[�����̃R���C�_�[���Փ˔���Ɏg�p���邽�ߐU�蕪�����ꂼ��̔z��ɓ����
		void StoreCollider2D();
		bool IsCollisionJudge(Tag shooter,Tag bullet);
		//���������I�u�W�F�N�g�̐��@���̒l���e�Q�[���I�u�W�F�N�g��ID�Ƃ��Ċ��蓖�Ă�
		UINT mGameObjectCounter;
		std::unique_ptr<BackGround> mBackGround;
		std::unique_ptr<FPSCountor> mFPSCountor;
		std::unique_ptr<DXManager> mDXManager;
		std::unique_ptr<BulletManager> mBulletManager;
		std::unique_ptr<DXSound> mDXSound;
		//�Q�[���I�u�W�F�N�g�Ǘ��z��
		std::vector<std::unique_ptr<DXGameObject>> mGameObjectsList;
		//�Q�[�����ɒǉ��������ꂽ���̂��ꎞ�I�ɓ���Ă���
		std::vector<std::unique_ptr<DXGameObject>> mTempGameObjectsList;
		//�e��łL�����N�^�[�̃R���C�_�[�̔z��
		std::vector<Collider2D*> mShooterCollider2DList;
		//�e�̃R���C�_�[�̔z��
		std::vector<Collider2D*> mBulletCollider2DList;
		DXGameObject* testObj;
		TextRenderer* textRenderer;
		DXText* mText;
		int mFrameCount;
		int mShowCoolTime = 60;
	};
}



