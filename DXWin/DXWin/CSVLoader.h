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
		std::vector<LOAD_FROM_CSV_DATA> LoadData(const char* filePath);
	};
}


