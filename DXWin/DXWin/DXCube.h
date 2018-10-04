#pragma once
#include <d3d11.h>
#include <memory>
#include "DXManager.h"
#include <wrl/client.h>
#include <vector>  
#include <DirectXMath.h>
#include "DXGameObject.h"
#include "IComponent.h"
namespace MyDirectX
{
	class DXCube:public IComponent
	{
	public:
		DXCube(){};
		DXCube(DXManager *dxManager, DXInput* input, DXCamera* camera);
		DXCube(TRANSFORM *transform, DXManager *dxManager, DXInput* input, DXCamera* camera);
		~DXCube();
		//���g��transform�������J
		TRANSFORM GetTransform() const { return mTransform; }
		//���g��transform�����X�V
		virtual void SetTransform(TRANSFORM *transform);
		virtual bool Init(TRANSFORM* transform, DXManager* dxManager, DXInput* input, DXCamera* camera) override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Exit() override;
	private:
		//�V�F�[�_�𐶐�
		HRESULT CreateShader();
		//�萔�o�b�t�@�𐶐�
		HRESULT CreateConstantBuffer();
		//���_���ƒ��_�o�b�t�@����
		HRESULT CreateVertex();
		//���_�C���f�b�N�X�ƃC���f�b�N�X�o�b�t�@����
		HRESULT CreateIndex();
		//���X�^���C�Y�X�e�[�g����
		HRESULT CreateRasterizeState();
		//�f�[�^�X�V�p�o�b�t�@
		CONSTANT_BUFFER cBuffer;
		int mDrawNum;

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
	};
}



