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
		//�w�i�̈ړ����x
		float mMoveSpeed = 0.01f;
		//�w�i����ɖ߂�Y���W�@���̒l�ȉ��ɂȂ������ɖ߂�
		const float MOVE_UP_Y_POSITION = -5.0f;
		//�w�i����ɖ߂�ۂ̈ړ���
		const float MOVE_UP_VALUE = 10.0f;
	};
}


