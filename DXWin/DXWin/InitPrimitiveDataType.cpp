#include "stdafx.h"
#include "InitPrimitiveDataType.h"

void MyLib::Init(int & value)
{
	value = 0;
}

void MyLib::Init(double & value)
{
	value = 0.0;
}

void MyLib::Init(float & value)
{
	value = 0.0f;
}
