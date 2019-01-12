#pragma once
#include <memory>
#include <vector>
#include "DXGameObject.h"
#include "MyEnums.h"
#include "DXResourceManager.h"
namespace MyDirectX
{
	class DXGameObject;

	class Scene
	{
	public:
		Scene() {};
		virtual ~Scene() {};
		void SetDXResourceManager(DXResourceManager* manager) { mDXRescourceManager = manager; }
		//�V�[���ɍŏ����瑶�݂���Q�[���I�u�W�F�N�g��n��
		std::list<std::unique_ptr<DXGameObject>>* GetGameObjects() 
		{ 
			return &mGameObjectsList;
		}
		//�Q�[���I�u�W�F�N�g���V�[���ɓo�^���Q�Ƃ�n��
		virtual DXGameObject* Instantiate();
		//�V�[���̏����ݒ�@�V�[����̃I�u�W�F�N�g�̐����Ȃǂ��s��
		virtual void Init() {};
		//�V�[�����n�܂������ɌĂ΂��
		virtual void SceneStart() {};
		//Update�O�ɌĂ΂��@�Q�[���I�u�W�F�N�g�Ɉˑ����Ȃ�Update
		virtual void SceneUpdate() {};
		//LateUpdate�O�ɌĂ΂��@�Q�[���I�u�W�F�N�g�Ɉˑ����Ȃ�LateUpdate
		virtual void SceneLateUpdate() {};
		//�`�揈�����I�������ɌĂ΂��@1�t���[���̍Ō�ɍs������
		virtual void SceneEndFrame() {};
		//�V�[���̏I���ɌĂ΂��
		virtual void SceneEnd() {};
		//�V�[���̏I������
		virtual bool IsSceneEnd() { return false; }
	protected:
		//���̃V�[���ɍŏ����瑶�݂���Q�[���I�u�W�F�N�g�̃��X�g
		std::list<std::unique_ptr<DXGameObject>> mGameObjectsList;
		//�S�̃��\�[�X�Ǘ��N���X�ւ̎Q��
		DXResourceManager* mDXRescourceManager;
	};
}


