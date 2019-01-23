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
		//”wŒi‚ÌˆÚ“®‘¬“x
		float mMoveSpeed = 0.01f;
		//”wŒi‚ªã‚É–ß‚éYÀ•W@‚±‚Ì’lˆÈ‰º‚É‚È‚Á‚½‚çã‚É–ß‚é
		const float MOVE_UP_Y_POSITION = -5.0f;
		//”wŒi‚ªã‚É–ß‚éÛ‚ÌˆÚ“®—Ê
		const float MOVE_UP_VALUE = 10.0f;
	};
}


