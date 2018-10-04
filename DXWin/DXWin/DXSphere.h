#pragma once
#include <d3d11.h>
#include <memory>
#include "DXManager.h"
#include <wrl/client.h>
#include <vector>  
#include <DirectXMath.h>
#include "DXGameObject.h"
namespace MyDirectX 
{
	class DXSphere :public DXGameObject
	{
	public:
		DXSphere(DXManager *dxManager, DXInput* input, DXCamera* camera);
		DXSphere(TRANSFORM *transform, DXManager *dxManager, DXInput* input, DXCamera* camera);
		~DXSphere();
		virtual HRESULT Init(DXManager* dxManager, DXInput* input, DXCamera* camera) override;
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
		CONSTANT_BUFFER2 cBuffer;
		int mDrawNum;
	};
}



