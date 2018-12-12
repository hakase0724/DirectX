#include "stdafx.h"
#include "DirLoder.h"
#include <Windows.h>
#include <string>

using namespace MyDirectX;
using namespace std;

vector<wstring> DirLoder::GetFilePathInDir(const wstring & dirName, const wstring & extension) noexcept(false)
{
	HANDLE hFind;
	//defined at Windwos.h
	WIN32_FIND_DATA win32fd;
	//�t�@�C�����̔z��
	std::vector<std::wstring> fileNames;

	//�T���t�@�C�����w��@���C���h�J�[�h���g�p
	std::wstring searchName = dirName + L"\\*." + extension;
	//�t�@�C������
	hFind = FindFirstFile(searchName.c_str(), &win32fd);

	//������Ȃ�������
	if (hFind == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("file not found");
	}

	//���̃t�@�C�����������ǂݍ��ݑ�����
	do
	{
		//�f�B���N�g���Ȃ疳��
		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {}
		//�t�@�C���p�X���擾
		else
		{
			//�t�@�C����
			std::wstring fileName = win32fd.cFileName;
			//�n���ꂽ�f�B���N�g���z��������
			auto dirPath = dirName + _T("/");
			//�t�@�C�����ƍ��킹�ăp�X����
			fileName.insert(0, dirPath);
			fileNames.push_back(fileName);
		}
	} while (FindNextFile(hFind, &win32fd));
	//����
	FindClose(hFind);

	return fileNames;
}
