#pragma once
#include "MyStructs.h"
#include <vector>

namespace MyDirectX
{
	class CSVLoader
	{
	public:
		CSVLoader() {};
		~CSVLoader() {};
		std::vector<DATA> LoadData(const char* filePath);
	};
}


