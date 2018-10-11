#pragma once
#include <d3d11.h>
#include <memory>
#include "DXManager.h"
#include <DirectXMath.h>
#include "CubeMesh.h"
#include "NormalShader.h"
#include "DXFactory.h"
namespace MyDirectX
{
	class DXCube
	{
	public:
		DXCube(){};
		DXCube(DXManager *dxManager);
		DXCube(TRANSFORM *transform, DXManager *dxManager);
		~DXCube();
		//���g��transform�������J
		TRANSFORM GetTransform() const { return mTransform; }
		//���g��transform�����X�V
		void SetTransform(TRANSFORM *transform);
		bool Init();
		void Update();
		void Render();
		void Exit();
	private:
		//�f�[�^�X�V�p�o�b�t�@
		CONSTANT_BUFFER3 cBuffer;
		//�`�搔
		int mDrawNum;
		//�L���[�u�`��ɕK�v�ȃp�����[�^
		std::unique_ptr<DXFactory> mFactory;
		std::unique_ptr<CubeMesh> mMesh;
		std::unique_ptr<NormalShader> mShader;
		//���g���ێ�����f�[�^
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



