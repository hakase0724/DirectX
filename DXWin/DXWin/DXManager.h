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
		//ウィンドルのハンドル
		HWND GetHwnd() const { return mHwnd; }
		//ドライバーの種類オプション　NULLはデバッグ用らしい
		D3D_DRIVER_TYPE GetDriverType() const { return mDriverType; }
		//DirectXの機能サポートレベルを設定する　今回はDirectX11の勉強だから11を設定した
		D3D_FEATURE_LEVEL GetLevel() const { return mLevel; }
		//DirectXの仮想ドライバー　多分こいつが一番大事なもの
		ID3D11Device* GetDevice() const { return mDevice.Get(); }
		//レンダリングについて色々設定できるものらしい
		ID3D11DeviceContext* GetDeviceContext() const { return mDeviceContext.Get(); }
		//描画処理に必要な情報が入るバッファーらしい
		IDXGISwapChain* GetSwapChain() const { return mSwapChain.Get(); }
		//レンダリング時に使えるサブリソース識別
		ID3D11RenderTargetView* GetRenderTargetView() const { return mRenderTargetView; }
		//入力アセンブラステージの入力データにアクセス　入力してなんかするときに使いそう
		ID3D11InputLayout* GetVertexLayout() const { return mVertexLayout.Get(); }
		//頂点シェーダー管理
		ID3D11VertexShader* GetVertexShader() const { return mVertexShader.Get(); }
		//ピクセルシェーダー管理
		ID3D11PixelShader* GetPixelShader() const { return mPixelShader.Get(); }
		//データバッファ　シェーダーとのデータのやり取りに使っている
		ID3D11Buffer* GetConstantBuffer() const { return mConstantBuffer; }
		//頂点シェーダー用のバッファ
		ID3D11Buffer* GetVertexBuffer() const { return mVertexBuffer; }
		//インデックス要のバッファ
		ID3D11Buffer* GetIndexBuffer() const { return mIndexBuffer; }
		//ラスタライザステージのラスタライザステートへアクセス　面とか出すときラスタ形式で出しているから必要らしい
		ID3D11RasterizerState* GetRasterizerState() const { return mRasterizerState.Get(); }
		//入力管理
		DXInput* GetDXInput() const { return mDXInput.get(); }
		//カメラ
		DXCamera* GetDXCamera() const{ return mDXCamera.get(); }
	private:
		const float mColor[4] = { 0.0f,0.0f,0.0f,1.0f };
		float xRote;
		float yRote;
		int mDrawNum;
		//ウィンドルのハンドル
		HWND mHwnd;
		//ドライバーの種類オプション　NULLはデバッグ用らしい
		D3D_DRIVER_TYPE mDriverType;
		//DirectXの機能サポートレベルを設定する　今回はDirectX11の勉強だから11を設定した
		D3D_FEATURE_LEVEL mLevel;
		//DirectXの仮想ドライバー　多分こいつが一番大事なもの
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		//レンダリングについて色々設定できるものらしい
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDeviceContext;
		//描画処理に必要な情報が入るバッファーらしい
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
		//レンダリング時に使えるサブリソース識別
		ID3D11RenderTargetView* mRenderTargetView;
		//入力アセンブラステージの入力データにアクセス　入力してなんかするときに使いそう
		Microsoft::WRL::ComPtr<ID3D11InputLayout> mVertexLayout;
		//頂点シェーダー管理
		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
		//ピクセルシェーダー管理
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
		//データバッファ　シェーダーとのデータのやり取りに使っている
		ID3D11Buffer* mConstantBuffer;
		//頂点シェーダー用のバッファ
		ID3D11Buffer* mVertexBuffer;
		//インデックス要のバッファ
		ID3D11Buffer* mIndexBuffer;
		//ラスタライザステージのラスタライザステートへアクセス　面とか出すときラスタ形式で出しているから必要らしい
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRasterizerState;
		//入力管理
		std::unique_ptr<DXInput> mDXInput;
		//カメラ
		std::unique_ptr<DXCamera> mDXCamera;

	};
}


