#pragma once
#include <d3d11.h>
#include <typeinfo>
#include "DXManager.h"
#include "IComponent.h"
#include "DXGameObject.h"
#include "MeshAndShader.h"

namespace MyDirectX
{
	class MeshRenderer :public Component
	{
	public:
		MeshRenderer() {};
		~MeshRenderer();
		//�p�C�v���C���̉��߂̎d����ύX����
		void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Awake() override {};
		virtual void Start() override {};
		virtual void Update() override {};
		virtual void Render() override;
		virtual void Exit() override;
		//���b�V�������
		template <typename T>
		void CreateMesh();
		//�V�F�[�_�[�����
		template <typename T>
		void CreateShader();
	private:
		//�f�[�^�X�V�p�o�b�t�@
		CONSTANT_BUFFER cBuffer;
		//�`�搔
		int mDrawNum;
		//���g���ێ�����f�[�^
		DXManager* mDXManager;
		DXCamera* mDXCamera;
		ID3D11DeviceContext* mDeviceContext;
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
		//�p�C�v���C���̉��߂̎d��
		D3D11_PRIMITIVE_TOPOLOGY mTopology;
	};
	template<typename T>
	inline void MeshRenderer::CreateMesh()
	{
		if (!typeid(T).before(typeid(MeshInfo*))) return;
		auto mesh = new T();
		//�ꕶ��Z�����ĉǐ����グ��
		auto factory = mDXManager->GetDXFactory();
		auto device = mDXManager->GetDevice();
		factory->CreateMesh(mesh, device, &mVertexBuffer, &mIndexBuffer);
		mDrawNum = mesh->indexNum;
	}
	template<typename T>
	inline void MeshRenderer::CreateShader()
	{
		if (!typeid(T).before(typeid(ShaderInfo*))) return;
		auto shader = new T();
		//�ꕶ��Z�����ĉǐ����グ��
		auto factory = mDXManager->GetDXFactory();
		auto device = mDXManager->GetDevice();
		factory->CreateShader(shader, device, &mVertexShader, &mPixelShader, &mVertexLayout, &mRasterizerState, &mConstantBuffer);
	}
}


