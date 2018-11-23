#pragma once
#include "Scene.h"
#include "DXResourceManager.h"
#include "CollisionManager.h"
namespace MyDirectX
{
	class DXExcuter
	{
	public:
		DXExcuter();
		~DXExcuter() {};
		//�V�[���̓o�^
		void SetScene(Scene* scene);
		//�@�\�N���X���Z�b�g����
		void SetDXResourceManager(DXResourceManager* manager) { mDXRescourceManager = manager; }
		//�Q�[�����[�v�����s����
		void Excute();
		bool IsSceneEnd() const { return mScene->IsSceneEnd(); }
	private:
		//�o�^�V�[��
		Scene* mScene;
		//�o�^����Ă���Q�[���I�u�W�F�N�g��Update���Ă�
		void Update();
		//�o�^����Ă���Q�[���I�u�W�F�N�g��LateUpdate���Ă�
		void LateUpdate();
		//�o�^����Ă���Q�[���I�u�W�F�N�g��Render���Ă�
		void Render();
		//�����𓮂����Q�[���I�u�W�F�N�g�̎Q�ƃ��X�g
		std::vector<DXGameObject*> mExcuteObjectsList;
		//�ՓˊǗ��N���X
		std::unique_ptr<CollisionManager> mCollisionManager;
		//�@�\�N���X�̎Q��
		DXResourceManager* mDXRescourceManager;
	};
}

