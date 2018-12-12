#pragma once
#include <vector>

namespace MyDirectX
{
	class DirLoder
	{
	public:
		DirLoder() {};
		~DirLoder() {};
		//ディレクトリ内からファイルパスを取得
		//noexcept(false) = 例外を送出する可能性あり
		std::vector<std::wstring> GetFilePathInDir(const std::wstring& dirName, const std::wstring& extension) noexcept(false);
	};
}


