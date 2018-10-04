#pragma once
#include <d3d11.h>
#include <memory>
#include <vector>  
#include <DirectXMath.h>
#include "DXManager.h"
#include "IComponent.h"


namespace MyDirectX
{
	class DXGameObject
	{
	public:
		DXGameObject(DXManager* dxManager, DXInput* input, DXCamera* camera);
		DXGameObject(TRANSFORM* transform, DXManager* dxManager, DXInput* input, DXCamera* camera);
		~DXGameObject();
		//���g��transform�������J
		TRANSFORM GetTransform() const { return mTransform; }
		DXManager* GetDXManager() const { return mDXManager; }
		DXInput* GetDXInput() const { return mDXInput; }
		DXCamera* GetDXCamera() const { return mDXCamera; }
		//���g��transform�����X�V
		virtual void SetTransform(TRANSFORM *transform);
		template <typename T>
		void AddComponent();
		//���g�̏�����
		virtual HRESULT Init(DXManager* dxManager, DXInput* input, DXCamera* camera);
		//���g�̏��X�V
		virtual void Update();
		//���g�̕`��
		virtual void Render();
		//���g�̉��
		virtual void Exit();
	protected:
		TRANSFORM mTransform;
		DXManager* mDXManager;
		DXInput* mDXInput;
		DXCamera* mDXCamera;
		//���̓A�Z���u���X�e�[�W�̓��̓f�[�^�ɃA�N�Z�X�@���͂��ĂȂ񂩂���Ƃ��Ɏg������
		ID3D11InputLayout* mVertexLayout;
		//���_�V�F�[�_�[�Ǘ�
		ID3D11VertexShader* mVertexShader;
		//�s�N�Z���V�F�[�_�[�Ǘ�
		ID3D11PixelShader* mPixelShader;
		//�f�[�^�o�b�t�@�@�V�F�[�_�[�Ƃ̃f�[�^�̂����Ɏg���Ă���
		ID3D11Buffer* mConstantBuffer;
		//���_�V�F�[�_�[�p�̃o�b�t�@
		ID3D11Buffer* mVertexBuffer;
		//�C���f�b�N�X�v�̃o�b�t�@
		ID3D11Buffer* mIndexBuffer;
		//���X�^���C�Y�X�e�[�g
		ID3D11RasterizerState* mRasterizerState;
		std::vector<std::unique_ptr<IComponent>> mComponentList;
	};
	
}



