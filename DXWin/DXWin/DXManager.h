#pragma once
#include <d3d11.h>
#include <memory>
#include "DXInput.h"
#include "DXCamera.h"
#include <wrl/client.h>

namespace MyDirectX
{
	class DXManager
	{
	public:
		DXManager();
		HRESULT InitDX11(HWND hwnd);
		BOOL UpdateDX11();
		void RenderDX11();
		void ExitDX11();
		const float cWidth = 1280;
		const float cHeight = 960;
		//�E�B���h���̃n���h��
		HWND GetHwnd() const { return mHwnd; }
		//�h���C�o�[�̎�ރI�v�V�����@NULL�̓f�o�b�O�p�炵��
		D3D_DRIVER_TYPE GetDriverType() const { return mDriverType; }
		//DirectX�̋@�\�T�|�[�g���x����ݒ肷��@�����DirectX11�̕׋�������11��ݒ肵��
		D3D_FEATURE_LEVEL GetLevel() const { return mLevel; }
		//DirectX�̉��z�h���C�o�[�@������������ԑ厖�Ȃ���
		ID3D11Device* GetDevice() const { return mDevice.Get(); }
		//�����_�����O�ɂ��ĐF�X�ݒ�ł�����̂炵��
		ID3D11DeviceContext* GetDeviceContext() const { return mDeviceContext.Get(); }
		//�`�揈���ɕK�v�ȏ�񂪓���o�b�t�@�[�炵��
		IDXGISwapChain* GetSwapChain() const { return mSwapChain.Get(); }
		//�����_�����O���Ɏg����T�u���\�[�X����
		ID3D11RenderTargetView* GetRenderTargetView() const { return mRenderTargetView; }
		//���̓A�Z���u���X�e�[�W�̓��̓f�[�^�ɃA�N�Z�X�@���͂��ĂȂ񂩂���Ƃ��Ɏg������
		ID3D11InputLayout* GetVertexLayout() const { return mVertexLayout.Get(); }
		//���_�V�F�[�_�[�Ǘ�
		ID3D11VertexShader* GetVertexShader() const { return mVertexShader.Get(); }
		//�s�N�Z���V�F�[�_�[�Ǘ�
		ID3D11PixelShader* GetPixelShader() const { return mPixelShader.Get(); }
		//�f�[�^�o�b�t�@�@�V�F�[�_�[�Ƃ̃f�[�^�̂����Ɏg���Ă���
		ID3D11Buffer* GetConstantBuffer() const { return mConstantBuffer; }
		//���_�V�F�[�_�[�p�̃o�b�t�@
		ID3D11Buffer* GetVertexBuffer() const { return mVertexBuffer; }
		//�C���f�b�N�X�v�̃o�b�t�@
		ID3D11Buffer* GetIndexBuffer() const { return mIndexBuffer; }
		//���X�^���C�U�X�e�[�W�̃��X�^���C�U�X�e�[�g�փA�N�Z�X�@�ʂƂ��o���Ƃ����X�^�`���ŏo���Ă��邩��K�v�炵��
		ID3D11RasterizerState* GetRasterizerState() const { return mRasterizerState.Get(); }
		//���͊Ǘ�
		DXInput* GetDXInput() const { return mDXInput.get(); }
		//�J����
		DXCamera* GetDXCamera() const{ return mDXCamera.get(); }
	private:
		const float mColor[4] = { 0.0f,0.0f,0.0f,1.0f };
		float xRote;
		float yRote;
		int mDrawNum;
		//�E�B���h���̃n���h��
		HWND mHwnd;
		//�h���C�o�[�̎�ރI�v�V�����@NULL�̓f�o�b�O�p�炵��
		D3D_DRIVER_TYPE mDriverType;
		//DirectX�̋@�\�T�|�[�g���x����ݒ肷��@�����DirectX11�̕׋�������11��ݒ肵��
		D3D_FEATURE_LEVEL mLevel;
		//DirectX�̉��z�h���C�o�[�@������������ԑ厖�Ȃ���
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		//�����_�����O�ɂ��ĐF�X�ݒ�ł�����̂炵��
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDeviceContext;
		//�`�揈���ɕK�v�ȏ�񂪓���o�b�t�@�[�炵��
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
		//�����_�����O���Ɏg����T�u���\�[�X����
		ID3D11RenderTargetView* mRenderTargetView;
		//���̓A�Z���u���X�e�[�W�̓��̓f�[�^�ɃA�N�Z�X�@���͂��ĂȂ񂩂���Ƃ��Ɏg������
		Microsoft::WRL::ComPtr<ID3D11InputLayout> mVertexLayout;
		//���_�V�F�[�_�[�Ǘ�
		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
		//�s�N�Z���V�F�[�_�[�Ǘ�
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
		//�f�[�^�o�b�t�@�@�V�F�[�_�[�Ƃ̃f�[�^�̂����Ɏg���Ă���
		ID3D11Buffer* mConstantBuffer;
		//���_�V�F�[�_�[�p�̃o�b�t�@
		ID3D11Buffer* mVertexBuffer;
		//�C���f�b�N�X�v�̃o�b�t�@
		ID3D11Buffer* mIndexBuffer;
		//���X�^���C�U�X�e�[�W�̃��X�^���C�U�X�e�[�g�փA�N�Z�X�@�ʂƂ��o���Ƃ����X�^�`���ŏo���Ă��邩��K�v�炵��
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRasterizerState;
		//���͊Ǘ�
		std::unique_ptr<DXInput> mDXInput;
		//�J����
		std::unique_ptr<DXCamera> mDXCamera;

	};
}


