#pragma once
#include<malloc.h>
//メモリアラインメントを行うクラス
template <size_t T>
class AlignedAllocationPolicy
{
public:
	static void* operator new(size_t i)
	{
		return _mm_malloc(i, T);
	}
	static void operator delete(void* p) 
	{
		_mm_free(p);
	}
};
