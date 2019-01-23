#include "stdafx.h"
#include "DXRenderDataPool.h"
#include "WICTextureLoader.h"
#include "WICTextureLoader.cpp"

using namespace MyDirectX;

DXRenderDataPool::DXRenderDataPool(ID3D11Device * device, ID3D11DeviceContext * deviceContext)
{
	mDevice = device;
	mDeviceContext = deviceContext;
	//���P�[����ݒ肵�Ȃ���Ε�����������\��������炵��
	setlocale(LC_ALL, "Japanese");
	//�f�B���N�g������t�@�C������ǂݍ��ރN���X
	mDirLoder = std::make_unique<DirLoder>();
	//�f�B���N�g������e�N�X�`����ǂݍ���
	LoadTextureInDir();

	//�󔒂̃e�N�X�`�������
	auto pData = std::make_unique<TEXTURE_DATA>();
	//�t�H���g���������ރe�N�X�`���쐬
	D3D11_TEXTURE2D_DESC fontTextureDesc;
	ZeroMemory(&fontTextureDesc, sizeof(fontTextureDesc));
	fontTextureDesc.Width = 1;
	fontTextureDesc.Height = 1;
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
	mDevice->CreateTexture2D(&fontTextureDesc, NULL, &fontTexture);

	// ShaderResourceView�̏����쐬����
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = fontTextureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = fontTextureDesc.MipLevels;

	mDevice->CreateShaderResourceView(fontTexture, &srvDesc, &pData->shaderView);
	//�f�[�^���\���̂Ɋi�[
	pData->texture = fontTexture;
	pData->fileName = *const_cast<wchar_t*>(L" ");
	mTextureList.push_back(std::move(pData));
}

TEXTURE_DATA * DXRenderDataPool::GetTexture(wchar_t * fileName)
{
	TEXTURE_DATA* pReturn = FindTextureData(fileName);
	if (pReturn != nullptr) return pReturn;
	//�L���b�V����������΍��
	return CreateTexture(fileName);
}

TEXTURE_DATA * DXRenderDataPool::GetFontTexture(wchar_t * text, WCHAR* fontName)
{
	TEXTURE_DATA* pReturn = FindTextureData(*text);
	if (pReturn != nullptr) return pReturn;

	auto pData = std::make_unique<TEXTURE_DATA>();
	// �t�H���g�n���h���̐���
	int fontSize = 64;
	int fontWeight = 1000;
	LOGFONT lf =
	{
		fontSize, 0, 0, 0, fontWeight, 0, 0, 0,
		SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN,
		*fontName
	};
	HFONT hFont = CreateFontIndirectW(&lf);

	// ���݂̃E�B���h�E�ɓK�p
	// �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	wchar_t* c = const_cast<wchar_t*>(text);
	// �t�H���g�r�b�g�}�b�v�擾
	UINT code = (UINT)* c;
	const int gradFlag = GGO_GRAY4_BITMAP;
	// �K���̍ő�l
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

	// �s�v�Ȃ��̂����
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
	ReleaseDC(NULL, hdc);

	//�t�H���g�̕��ƍ���
	int fontWidth = gm.gmCellIncX;
	int fontHeight = tm.tmHeight;

	//�t�H���g���������ރe�N�X�`���쐬
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
	mDevice->CreateTexture2D(&fontTextureDesc, NULL, &fontTexture);
	//�f�o�C�X�R���e�L�X�g
	// �t�H���g�����e�N�X�`���ɏ������ޕ���
	D3D11_MAPPED_SUBRESOURCE hMappedResource;
	mDeviceContext->Map(
		fontTexture,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&hMappedResource);

	// �����ŏ�������
	BYTE* pBits = (BYTE*)hMappedResource.pData;
	// �t�H���g���̏�������
	// iOfs_x, iOfs_y : �����o���ʒu(����)
	// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
	// Level : ���l�̒i�K (GGO_GRAY4_BITMAP�Ȃ̂�17�i�K)
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
	mDeviceContext->Unmap(fontTexture, 0);
	//�s�v�Ȃ̂ō폜
	delete[] pMono;

	// ShaderResourceView�̏����쐬����
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = fontTextureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = fontTextureDesc.MipLevels;

	mDevice->CreateShaderResourceView(fontTexture, &srvDesc, &pData->shaderView);
	//�f�[�^���\���̂Ɋi�[
	pData->texture = fontTexture;
	pData->fileName = *text;
	pReturn = pData.get();
	mTextureList.push_back(std::move(pData));
	return pReturn;
}

TEXTURE_DATA * DXRenderDataPool::FindTextureData(wchar_t * text)
{
	TEXTURE_DATA* pReturn = nullptr;
	//�e�N�X�`�����̃L���b�V�������邩
	for (auto &tex : mTextureList)
	{
		if (text == tex.get()->fileName)
		{
			pReturn = tex.get();
			break;
		}
	}
	return pReturn;
}

TEXTURE_DATA * DXRenderDataPool::FindTextureData(wchar_t text)
{
	std::wstring str = &text;
	TEXTURE_DATA* pReturn = nullptr;
	//�e�N�X�`�����̃L���b�V�������邩
	for (auto &tex : mTextureList)
	{
		if (str == tex.get()->fileName)
		{
			pReturn = tex.get();
			break;
		}
	}
	return pReturn;
}

TEXTURE_DATA * DXRenderDataPool::CreateTexture(std::wstring filePath)
{
	auto pData = std::make_unique<TEXTURE_DATA>();
	pData->fileName = filePath;
	CreateWICTextureFromFile(mDevice, filePath.c_str(), &pData.get()->texture, &pData.get()->shaderView);
	mTextureList.push_back(std::move(pData));
	return mTextureList.back().get();
}

void DXRenderDataPool::LoadTextureInDir()
{
	auto dir = _T("Texture");
	auto exetension = _T("png");
	auto filePaths = mDirLoder->GetFilePathInDir(dir,exetension);
	for(auto file:filePaths)
	{
		CreateTexture(file);
	}
}
