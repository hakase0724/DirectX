#pragma once
#include <d3d11.h>
#include <typeinfo>
#include "DXManager.h"
#include "IComponent.h"
#include "DXGameObject.h"
#include "MeshAndShader.h"
#include "DXRenderDataPool.h"

namespace MyDirectX
{
	class MeshRenderer :public Component
	{
	public:
		MeshRenderer() {};
		~MeshRenderer();
		//�p�C�v���C���̉��߂̎d����ύX����
		void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { mTopology = topology; }
		void SetColor(float r, float g, float b, float a);
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Awake() override {};
		virtual void Start() override {};
		virtual void Update() override {};
		virtual void Render() override;
		virtual void Exit() override;
		virtual void OnCollisionEnter(CollisionInfo* info) override;
		virtual void OnCollisionStay(CollisionInfo* info) override;
		virtual void OnCollisionExit(CollisionInfo* info) override;
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
		//�`��F
		//��
		float r;
		//��
		float g;
		//��
		float b;
		//�����x
		float a;
		//���g���ێ�����f�[�^
		DXManager* mDXManager;
		DXCamera* mDXCamera;
		DXFactory* mDXFactory;
		ID3D11Device* mDevice;
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
		//�C���f�b�N�X�p�̃o�b�t�@
		ID3D11Buffer* mIndexBuffer;
		//���X�^���C�Y�X�e�[�g
		ID3D11RasterizerState* mRasterizerState;
		//�p�C�v���C���̉��߂̎d��
		D3D11_PRIMITIVE_TOPOLOGY mTopology;
	};

	//���b�V�������
	template<typename T>
	inline void MeshRenderer::CreateMesh()
	{
		//�󂯎���^�łȂ����return
		if (!typeid(T).before(typeid(MeshInfo*))) return;
		//���b�V�����擾
		T* pInfo = mGameObject->GetDXManager()->GetDXRenderDataPool()->GetMesh<T>();	
		//���b�V���������ƂɃ����_�����O�ɕK�v�ȃ��b�V�����쐬
		mDXFactory->CreateMesh(pInfo, mDevice, &mVertexBuffer, &mIndexBuffer);
		//�`�悷�钸�_�����Z�b�g
		mDrawNum = pInfo->indexNum;
	}
	//�V�F�[�_�[�����
	template<typename T>
	inline void MeshRenderer::CreateShader()
	{
		//�󂯎���^�łȂ����return
		if (!typeid(T).before(typeid(ShaderInfo*))) return;
		//�V�F�[�_�[���擾
		T* pInfo = mGameObject->GetDXManager()->GetDXRenderDataPool()->GetShader<T>();
		//�V�F�[�_�[�������ƂɃV�F�[�_�[���쐬
		mDXFactory->CreateShader(pInfo, mDevice, &mVertexShader, &mPixelShader, &mVertexLayout, &mRasterizerState, &mConstantBuffer);
	}
}


