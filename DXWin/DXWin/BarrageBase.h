#pragma once
#include "MyEnums.h"
#include <math.h>
#include <tuple>
namespace MyDirectX
{
	class BulletManager;
	class DXGameObject;
	class BarrageBase
	{
	public:
		BarrageBase() {};
		~BarrageBase() {};
		BarrageName GetName() const { return mName; }
		int GetBulletNum() const { return mBulletNum; }
		//���ˑҋ@����
		bool IsCoolTime(int time) { return time % mCoolTime == 0; }
		//�e�����ł��I�������
		virtual bool IsBarrageEnd() = 0;
		//�e�̋O�����v�Z����
		virtual void CreateBarrage(BulletManager* manager,DXGameObject* player,DXGameObject* enemy) = 0;
	protected:
		//�e���̖��O������enum
		BarrageName mName;
		//�e�𔭎˂���t���[���Ԋu
		int mCoolTime;
		//�e�𔭎˂���ۂɓ����ɑłe��
		int mBulletNum;
		//�e��
		float mBulletSpeed;
		//�e�̊p�x��ς��鎞�Ɏg���ϐ�
		float mAngle;
		//�x���@�\�L�̊p�x���ʓx�@�\�L�̊p�x�ɕϊ�����
		float ToRadian(float angle) { return angle * (float)(acos(-1.0f) / 180.0f); }
		//�n���ꂽ�x�N�g���𐳋K������
		void Normalization(float &x, float &y);
		//�Ă΂ꂽ��
		int mCount;
	};
}


