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
	//ファイル名の配列
	std::vector<std::wstring> fileNames;

	//探すファイル名指定　ワイルドカードを使用
	std::wstring searchName = dirName + L"\\*." + extension;
	//ファイル検索
	hFind = FindFirstFile(searchName.c_str(), &win32fd);

	//見つからなかったか
	if (hFind == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("file not found");
	}

	//次のファイルがある限り読み込み続ける
	do
	{
		//ディレクトリなら無視
		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {}
		//ファイルパスを取得
		else
		{
			//ファイル名
			std::wstring fileName = win32fd.cFileName;
			//渡されたディレクトリ配下を示す
			auto dirPath = dirName + _T("/");
			//ファイル名と合わせてパス生成
			fileName.insert(0, dirPath);
			fileNames.push_back(fileName);
		}
	} while (FindNextFile(hFind, &win32fd));
	//閉じる
	FindClose(hFind);

	return fileNames;
}
