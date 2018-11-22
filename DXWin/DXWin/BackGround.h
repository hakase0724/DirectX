#pragma once
#include "DXGameObject.h"

namespace MyDirectX
{
	class BackGround 
	{
	public:
		BackGround() {};
		~BackGround() {};
		void SetBackGrounds(DXGameObject* back1, DXGameObject* back2) 
		{
			mBackFirst = back1;
			mBackSecond = back2;
		}
		void ClearBackGrounds()
		{
			mBackFirst = nullptr;
			mBackSecond = nullptr;
		}
		void UpdateBackGrounds();
		void ChangeBackGroundEnable(bool enable)
		{
			mBackFirst->SetEnable(enable);
			mBackSecond->SetEnable(enable);
		}
	private:
		DXGameObject* mBackFirst;
		DXGameObject* mBackSecond;
	};
}


