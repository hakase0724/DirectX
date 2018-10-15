#pragma once
#include <d3d11.h>
#include <memory>
#include "DXManager.h"
#include "MeshAndShader.h"
#include "IComponent.h"
#include "DXGameObject.h"
namespace MyDirectX 
{
	class DXSphere :public Component
	{
	public:
		DXSphere(){};
		~DXSphere();
		//���g��transform�������J
		TRANSFORM GetTransform() const { return mTransform; }
		//���g��transform�����X�V
		void SetTransform(TRANSFORM *transform) { mTransform = *transform; }
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Awake() override {};
		virtual void Start() override {};
		bool Init();
		virtual void Update() override {};
		virtual void Render() override;
		virtual void Exit() override;
	private:
		//�f�[�^�X�V�p�o�b�t�@
		CONSTANT_BUFFER cBuffer;
		int mDrawNum;
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
		TRANSFORM mTransform;
		DXManager* mDXManager;
		DXInput* mDXInput;
		DXCamera* mDXCamera;
		ID3D11DeviceContext* mDeviceContext;
		std::unique_ptr<SphereMesh> mMesh;
		std::unique_ptr<LightingShader> mShader;
	};
}



