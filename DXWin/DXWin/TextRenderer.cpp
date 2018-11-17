#include "stdafx.h"
#include "TextRenderer.h"

using namespace DirectX;
using namespace MyDirectX;
TextRenderer::TextRenderer()
{
}


TextRenderer::~TextRenderer()
{
}

void TextRenderer::Initialize(DXGameObject * gameObject)
{
	mDXManager = gameObject->GetDXManager();
	mDXCamera = gameObject->GetDXCamera();
	mDeviceContext = mDXManager->GetDeviceContext();
	mGameObject = gameObject;
	mDXFactory = mDXManager->GetDXFactory();
	mDevice = mDXManager->GetDevice();
	mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	mDefaultColor.r = 1;
	mDefaultColor.g = 1;
	mDefaultColor.b = 1;
	mDefaultColor.a = 1;
	mColor = mDefaultColor;

	CreateMesh<TextureMesh>();
	CreateShader<TextureShader>();

	// フォントハンドルの生成
	int fontSize = 64;
	int fontWeight = 1000;
	LOGFONT lf =
	{
		fontSize, 0, 0, 0, fontWeight, 0, 0, 0,
		SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN,
		(WCHAR)"ＭＳ Ｐ明朝"
	};
	HFONT hFont = CreateFontIndirectW(&lf);

	// 現在のウィンドウに適用
	// デバイスにフォントを持たせないとGetGlyphOutline関数はエラーとなる
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	// フォントビットマップ取得
	const wchar_t* c = L"S";
	UINT code = (UINT) * c;
	const int gradFlag = GGO_GRAY4_BITMAP;
	// 階調の最大値
	int grad = 0;
	switch (gradFlag)
	{
	case GGO_GRAY2_BITMAP:
		grad = 4;
		break;
	case GGO_GRAY4_BITMAP:
		grad = 16;
		break;
	case GGO_GRAY8_BITMAP:
		grad = 64;
		break;
	}

	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	GLYPHMETRICS gm;
	CONST MAT2 mat = { {0,1},{0,0},{0,0},{0,1} };
	DWORD size = GetGlyphOutlineW(hdc, code, gradFlag, &gm, 0, NULL, &mat);
	BYTE *pMono = new BYTE[size];
	GetGlyphOutlineW(hdc, code, gradFlag, &gm, size, pMono, &mat);

	// 不要なものを解放
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
	ReleaseDC(NULL, hdc);

	//フォントの幅と高さ
	int fontWidth = gm.gmCellIncX;
	int fontHeight = tm.tmHeight;

	//フォントを書き込むテクスチャ作成
	D3D11_TEXTURE2D_DESC fontTextureDesc;
	ZeroMemory(&fontTextureDesc, sizeof(fontTextureDesc));
	fontTextureDesc.Width = fontWidth;
	fontTextureDesc.Height = fontHeight;
	fontTextureDesc.MipLevels = 1;
	fontTextureDesc.ArraySize = 1;
	fontTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	fontTextureDesc.SampleDesc.Count = 1;
	fontTextureDesc.SampleDesc.Quality = 0;
	fontTextureDesc.Usage = D3D11_USAGE_DYNAMIC;
	fontTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	fontTextureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	fontTextureDesc.MiscFlags = 0;
	ID3D11Texture2D* fontTexture = 0;
	auto manager = mGameObject->GetDXManager();
	HRESULT hr = manager->GetDevice()->CreateTexture2D(&fontTextureDesc, NULL, &fontTexture);
	//デバイスコンテキスト
	auto deviceContext = manager->GetDeviceContext();
	// フォント情報をテクスチャに書き込む部分
	D3D11_MAPPED_SUBRESOURCE hMappedResource;
	hr = deviceContext->Map(
		fontTexture,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&hMappedResource);

	// ここで書き込む
	BYTE* pBits = (BYTE*)hMappedResource.pData;
	// フォント情報の書き込み
	// iOfs_x, iOfs_y : 書き出し位置(左上)
	// iBmp_w, iBmp_h : フォントビットマップの幅高
	// Level : α値の段階 (GGO_GRAY4_BITMAPなので17段階)
	int iOfs_x = gm.gmptGlyphOrigin.x;
	int iOfs_y = tm.tmAscent - gm.gmptGlyphOrigin.y;
	int iBmp_w = gm.gmBlackBoxX + (4 - (gm.gmBlackBoxX % 4)) % 4;
	int iBmp_h = gm.gmBlackBoxY;
	int Level = 17;
	int x, y;
	DWORD Alpha, Color;
	memset(pBits, 0, hMappedResource.RowPitch * tm.tmHeight);
	for (y = iOfs_y; y < iOfs_y + iBmp_h; y++)
	{
		for (x = iOfs_x; x < iOfs_x + iBmp_w; x++)
		{
			Alpha =
				(255 * pMono[x - iOfs_x + iBmp_w * (y - iOfs_y)])
				/ (Level - 1);
			Color = 0x00ffffff | (Alpha << 24);

			memcpy(
				(BYTE*)pBits
				+ hMappedResource.RowPitch * y + 4 * x,
				&Color,
				sizeof(DWORD));
		}
	}
	deviceContext->Unmap(fontTexture, 0);
	//不要なので削除
	delete[] pMono;

	// ShaderResourceViewの情報を作成する
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = fontTextureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = fontTextureDesc.MipLevels;

	manager->GetDevice()->CreateShaderResourceView(fontTexture, &srvDesc, &mShaderResorceView);

	// シェーダ用にサンプラを作成する
	D3D11_SAMPLER_DESC samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));
	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samDesc.AddressU = samDesc.AddressV = samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.MaxAnisotropy = 1;
	samDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samDesc.MaxLOD = D3D11_FLOAT32_MAX;

	manager->GetDevice()->CreateSamplerState(&samDesc, &mSampler);
	mTexture = fontTexture;

	
}

void TextRenderer::Render()
{
	auto transform = mGameObject->GetTransform();
	auto cameraParam = mDXCamera->GetCameraParam();
	cTextureBuffer.mWVP = mDXCamera->GetDXCameraParam(transform);
	cTextureBuffer.mColor = XMVectorSet(mColor.r, mColor.g, mColor.b, mColor.a);
	//データを渡す
	mDeviceContext->UpdateSubresource(mConstantBuffer, 0, NULL, &cTextureBuffer, 0, 0);
	//パイプライン構築
	UINT stride = sizeof(TEXTURE_VERTEX_DATA);
	UINT offset = 0;
	//頂点バッファを設定
	mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	//インデックスバッファーの設定
	mDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	//入力レイアウト設定
	mDeviceContext->IASetInputLayout(mVertexLayout);
	//頂点情報の解釈の仕方を設定
	mDeviceContext->IASetPrimitiveTopology(mTopology);
	//頂点シェーダーを設定
	mDeviceContext->VSSetShader(mVertexShader, NULL, 0);
	//ピクセルシェーダーを設定
	mDeviceContext->PSSetShader(mPixelShader, NULL, 0);
	//定数バッファを設定
	mDeviceContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	mDeviceContext->PSSetConstantBuffers(0, 1, &mConstantBuffer);
	//テクスチャ描画に必要なリソースの設定
	mDeviceContext->PSSetShaderResources(0, 1, &mShaderResorceView);
	mDeviceContext->PSSetSamplers(0, 1, &mSampler);
	//ラスタライズステートを設定
	mDeviceContext->RSSetState(mRasterizerState);
	//深度バッファ状態を設定
	auto depth = mDXManager->GetDepthStencilState();
	mDeviceContext->OMSetDepthStencilState(depth, 0);
	//描画
	mDeviceContext->DrawIndexed(mDrawNum, 0, 0);
}

void TextRenderer::Exit()
{
	if (mVertexBuffer)mVertexBuffer->Release();
	if (mVertexLayout)mVertexLayout->Release();
	if (mVertexShader)mVertexShader->Release();
	if (mPixelShader)mPixelShader->Release();
	if (mIndexBuffer)mIndexBuffer->Release();
	if (mConstantBuffer)mConstantBuffer->Release();
	if (mRasterizerState)mRasterizerState->Release();
	if (mSampler)mSampler->Release();
}
