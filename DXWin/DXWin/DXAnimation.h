#pragma once
#include "IComponent.h"
#include "DXTexture.h"
#include <vector>

namespace MyDirectX
{
	class DXAnimation :public Component
	{
	public:
		DXAnimation() {};
		~DXAnimation() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		virtual void Update() override;
		//�؂�ւ���e�N�X�`���R���|�[�l���g
		void SetAnimationTexture(DXTexture* texture) { mAnimationTexture = texture; }
		//�e�N�X�`���p�X���Z�b�g����
		void SetAnimationFile(const wchar_t* fileName);
		void SetLoop(bool loop) { mIsLoop = loop; }
		void SetTextureChangeCount(int count) { mTextureChangeCount = count; }
	private:
		DXTexture* mAnimationTexture;
		//�\������e�N�X�`���̃p�X�̔z��
		std::vector<wchar_t*> mFileNameList;
		//���\�����Ă���e�N�X�`���̔ԍ�
		int mFileNumber;
		//�o�߃t���[����
		int mFrameCount;
		//�e�N�X�`����؂�ւ���t���[����
		int mTextureChangeCount = 7;
		bool mIsLoop = true;
	};
}


