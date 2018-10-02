#pragma once
#include <d3d11.h>
#include <memory>
#include "DXManager.h"
#include <wrl/client.h>
#include <vector>  
#include <DirectXMath.h>
namespace MyDirectX
{
	class DXCube
	{
	public:
		DXCube();
		DXCube(DXManager *dxManager);
		DXCube(TRANSFORM *transform);
		DXCube(TRANSFORM *transform, DXManager *dxManager);
		~DXCube();
		TRANSFORM GetTransform() const { return mTransform; }
		void SetTransform(TRANSFORM transform);
		HRESULT Init(DXManager* dxManager);
		BOOL Update(DXInput* input, DXCamera* camera);
		void Render();
		void Exit();
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
		ID3D11RasterizerState* mRasterizerState;
		DXManager* mDXManager;
		//�f�[�^�X�V�p�o�b�t�@
		CONSTANT_BUFFER cBuffer;
		TRANSFORM mTransform;
		int mDrawNum;
		float xRote;
		float yRote;
	};
}



