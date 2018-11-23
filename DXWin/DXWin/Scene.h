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
		//���g�̃V�[����\���V�[���X�e�[�g��Ԃ�
		SceneState GetSceneState() const { return mSceneState; }
		//�V�[���ɍŏ����瑶�݂���Q�[���I�u�W�F�N�g��n��
		std::vector<DXGameObject*> GetGameObjects() const
		{ 
			std::vector<DXGameObject*> games;
			for(auto& game:mGameObjectsList)
			{
				games.push_back(game.get());
			}
			return games;
		}
		//�Q�[���I�u�W�F�N�g���V�[���ɓo�^���Q�Ƃ�n��
		virtual DXGameObject* Instantiate();
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
		std::vector<std::unique_ptr<DXGameObject>> mGameObjectsList;
		//���g�̃V�[����\��
		SceneState mSceneState;
		//�S�̃��\�[�X�Ǘ��N���X�ւ̎Q��
		DXResourceManager* mDXRescourceManager;
	};
}

