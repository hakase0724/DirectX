#include "stdafx.h"
#include "BarrageBase.h"

using namespace MyDirectX;

void BarrageBase::Normalization(float & x, float & y)
{
	auto len = sqrtf(x * x + y * y);
	x /= len;
	y /= len;
}
