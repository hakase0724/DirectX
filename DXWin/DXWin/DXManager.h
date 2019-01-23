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
		//初期化
		HRESULT InitDX11(HWND hwnd);
		//終了
		void ExitDX11();
		//描画開始前のバッファクリア
		void BeginScene(float r,float g, float b,float a);
		//描画処理が終了した後の画面をユーザーに見せる
		void EndScene();
		//VSyncの有無を切り替える
		void SetVsyncEnable(bool isEnable);
		//ウィンドルのハンドル
		HWND GetHwnd() const { return mHwnd; }
		//ドライバーの種類オプション　NULLはデバッグ用らしい
		D3D_DRIVER_TYPE GetDriverType() const { return mDriverType; }
		//DirectXの機能サポートレベルを設定する　今回はDirectX11の勉強だから11を設定した
		D3D_FEATURE_LEVEL GetLevel() const { return mLevel; }
		//DirectXの仮想ドライバー　多分こいつが一番大事なもの
		ID3D11Device* GetDevice() const { return mDevice; }
		//レンダリングについて色々設定できるものらしい
		ID3D11DeviceContext* GetDeviceContext() const { return mDeviceContext; }
		//描画処理に必要な情報が入るバッファーらしい
		IDXGISwapChain* GetSwapChain() const { return mSwapChain; }
		//レンダリング時に使えるサブリソース識別
		ID3D11RenderTargetView* GetRenderTargetView() const { return mRenderTargetView; }		
		//ビューポート設定
		D3D11_VIEWPORT GetView() const { return mView; }	
		//深度バッファのビュー情報
		ID3D11DepthStencilView* GetDepthStencilView() const { return mDepthStencilView; }
		//深度バッファの状態
		ID3D11DepthStencilState* GetDepthStencilState() const { return mDepthStencilState; }
		void OMSetBlendState(bool blendFlg);
		//保持している機能のポインタを返す
		DXInput* GetDXInput() const { return mDXInput.get(); }
		DXCamera* GetDXCamera() const { return mDXCamera.get(); }
		DXFactory* GetDXFactory() const { return mDXFactory.get(); }
		DXRenderDataPool* GetDXRenderDataPool() const { return mDXRenderDataPool.get(); }
		void SetVsyncIntarval(int intarval) { mVsyncIntarval = intarval; }
	private:
		ID3D11Debug* mD3dDebug;
		//ウィンドルのハンドル
		HWND mHwnd;
		//ドライバーの種類オプション　NULLはデバッグ用らしい
		D3D_DRIVER_TYPE mDriverType;
		//DirectXの機能サポートレベルを設定する　今回はDirectX11の勉強だから11を設定した
		D3D_FEATURE_LEVEL mLevel;
		//DirectXの仮想ドライバー　多分こいつが一番大事なもの
		ID3D11Device* mDevice;
		//レンダリングについて色々設定できるものらしい
		ID3D11DeviceContext* mDeviceContext;
		//描画処理に必要な情報が入るバッファーらしい
		IDXGISwapChain* mSwapChain;
		//レンダリング時に使えるサブリソース識別
		ID3D11RenderTargetView* mRenderTargetView;
		//深度バッファのビュー情報
		ID3D11DepthStencilView* mDepthStencilView;
		//深度バッファの状態
		ID3D11DepthStencilState* mDepthStencilState;
		//ビューポート設定
		D3D11_VIEWPORT mView;
		ID3D11BlendState* mBlendState;
		//VSyncの有無　
		BOOL mIsVsyncEnable;
		//保持している機能
		std::unique_ptr<DXInput> mDXInput;
		std::unique_ptr<DXCamera> mDXCamera;
		std::unique_ptr<DXFactory> mDXFactory;
		std::unique_ptr<DXRenderDataPool> mDXRenderDataPool;
		int mVsyncIntarval = 1;
		
	};
}


