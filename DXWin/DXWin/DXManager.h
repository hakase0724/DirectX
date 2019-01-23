#pragma once
#include <d3d11.h>
#include <memory>
#include "DXInput.h"
#include "DXCamera.h"
#include <DirectXMath.h>
#include "DXFactory.h"
#include "MyStructs.h"
#include "DXRenderDataPool.h"
#include "CommonValues.h"
#include <dxgidebug.h>
#include "AlignedAllocationPolicy.h"


namespace MyDirectX
{
	class DXManager:public AlignedAllocationPolicy<16>
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
		void OMSetBlendState(bool blendFlg);
		//�ێ����Ă���@�\�̃|�C���^��Ԃ�
		DXInput* GetDXInput() const { return mDXInput.get(); }
		DXCamera* GetDXCamera() const { return mDXCamera.get(); }
		DXFactory* GetDXFactory() const { return mDXFactory.get(); }
		DXRenderDataPool* GetDXRenderDataPool() const { return mDXRenderDataPool.get(); }
		void SetVsyncIntarval(int intarval) { mVsyncIntarval = intarval; }
	private:
		ID3D11Debug* mD3dDebug;
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
		ID3D11BlendState* mBlendState;
		//VSync�̗L���@
		BOOL mIsVsyncEnable;
		//�ێ����Ă���@�\
		std::unique_ptr<DXInput> mDXInput;
		std::unique_ptr<DXCamera> mDXCamera;
		std::unique_ptr<DXFactory> mDXFactory;
		std::unique_ptr<DXRenderDataPool> mDXRenderDataPool;
		int mVsyncIntarval = 1;
		
	};
}


