#pragma once
#include <vector>

namespace MyDirectX
{
	class DirLoder
	{
	public:
		DirLoder() {};
		~DirLoder() {};
		//�f�B���N�g��������t�@�C���p�X���擾
		//noexcept(false) = ��O�𑗏o����\������
		std::vector<std::wstring> GetFilePathInDir(const std::wstring& dirName, const std::wstring& extension) noexcept(false);
	};
}


