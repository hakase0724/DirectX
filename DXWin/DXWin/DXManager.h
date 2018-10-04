#pragma once
#include <d3d11.h>
#include <memory>
#include "DXInput.h"
#include "DXCamera.h"
#include <DirectXMath.h>
#include <wrl/client.h>


namespace MyDirectX
{
	//��ʉ𑜓x
	const float cWidth = 1280;
	const float cHeight = 960;
	//���_����ێ�����\����
	struct VERTEX
	{
		DirectX::XMFLOAT3 V;
		DirectX::XMFLOAT4 C;
	};
	//�V�F�[�_�ɏ��𑗂�萔�o�b�t�@�\����
	struct CONSTANT_BUFFER
	{
		DirectX::XMFLOAT4X4 gWVP;
	};

	struct VERTEX2 {
		DirectX::XMFLOAT3 V;
		DirectX::XMFLOAT3 N;
	};

	struct CONSTANT_BUFFER2 {
		DirectX::XMMATRIX mW;
		DirectX::XMMATRIX mWVP;
		DirectX::XMVECTOR vLightPos;
		DirectX::XMVECTOR vEyePos;
		DirectX::XMVECTOR vColor;
	};
	class DXManager
	{
	public:
		DXManager(HWND hwnd);
		~DXManager();
		//������
		HRESULT InitDX11(HWND hwnd);
		//�I��
		void ExitDX11();
		//�`��J�n�O�̃o�b�t�@�N���A
		void BeginScene(float r,float g, float b,float a);
		//�`�揈�����I��������̉�ʂ����[�U�[�Ɍ�����
		void EndScene();
		//VSync�̗L����؂�ւ���
		void SetVsyncEnable(bool isEnable);
		//�E�B���h���̃n���h��
		HWND GetHwnd() const { return mHwnd; }
		//�h���C�o�[�̎�ރI�v�V�����@NULL�̓f�o�b�O�p�炵��
		D3D_DRIVER_TYPE GetDriverType() const { return mDriverType; }
		//DirectX�̋@�\�T�|�[�g���x����ݒ肷��@�����DirectX11�̕׋�������11��ݒ肵��
		D3D_FEATURE_LEVEL GetLevel() const { return mLevel; }
		//DirectX�̉��z�h���C�o�[�@������������ԑ厖�Ȃ���
		ID3D11Device* GetDevice() const { return mDevice; }
		//�����_�����O�ɂ��ĐF�X�ݒ�ł�����̂炵��
		ID3D11DeviceContext* GetDeviceContext() const { return mDeviceContext; }
		//�`�揈���ɕK�v�ȏ�񂪓���o�b�t�@�[�炵��
		IDXGISwapChain* GetSwapChain() const { return mSwapChain; }
		//�����_�����O���Ɏg����T�u���\�[�X����
		ID3D11RenderTargetView* GetRenderTargetView() const { return mRenderTargetView; }		
		//�r���[�|�[�g�ݒ�
		D3D11_VIEWPORT GetView() const { return mView; }	
		//�[�x�o�b�t�@�̃r���[���
		ID3D11DepthStencilView* GetDepthStencilView() const { return mDepthStencilView; }
		//�[�x�o�b�t�@�̏��
		ID3D11DepthStencilState* GetDepthStencilState() const { return mDepthStencilState; }
	private:
		//�E�B���h���̃n���h��
		HWND mHwnd;
		//�h���C�o�[�̎�ރI�v�V�����@NULL�̓f�o�b�O�p�炵��
		D3D_DRIVER_TYPE mDriverType;
		//DirectX�̋@�\�T�|�[�g���x����ݒ肷��@�����DirectX11�̕׋�������11��ݒ肵��
		D3D_FEATURE_LEVEL mLevel;
		//DirectX�̉��z�h���C�o�[�@������������ԑ厖�Ȃ���
		ID3D11Device* mDevice;
		//�����_�����O�ɂ��ĐF�X�ݒ�ł�����̂炵��
		ID3D11DeviceContext* mDeviceContext;
		//�`�揈���ɕK�v�ȏ�񂪓���o�b�t�@�[�炵��
		IDXGISwapChain* mSwapChain;
		//�����_�����O���Ɏg����T�u���\�[�X����
		ID3D11RenderTargetView* mRenderTargetView;
		//�[�x�o�b�t�@�̃r���[���
		ID3D11DepthStencilView* mDepthStencilView;
		//�[�x�o�b�t�@�̏��
		ID3D11DepthStencilState* mDepthStencilState;
		//�r���[�|�[�g�ݒ�
		D3D11_VIEWPORT mView;
		//VSync�̗L���@
		BOOL mIsVsyncEnable;
		
	};
}


