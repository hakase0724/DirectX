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
		//”­Ë‘Ò‹@’†‚©
		bool IsCoolTime(int time) { return time % mCoolTime == 0; }
		//’e–‹‚ª‘Å‚¿I‚í‚Á‚½‚©
		virtual bool IsBarrageEnd() = 0;
		//’e‚Ì‹O“¹‚ğŒvZ‚·‚é
		virtual void CreateBarrage(BulletManager* manager,DXGameObject* player,DXGameObject* enemy) = 0;
	protected:
		//’e–‹‚Ì–¼‘O‚ğ¦‚·enum
		BarrageName mName;
		//’e‚ğ”­Ë‚·‚éƒtƒŒ[ƒ€ŠÔŠu
		int mCoolTime;
		//’e‚ğ”­Ë‚·‚éÛ‚É“¯‚É‘Å‚Â’e”
		int mBulletNum;
		//’e‘¬
		float mBulletSpeed;
		//’e‚ÌŠp“x‚ğ•Ï‚¦‚é‚Ég‚¤•Ï”
		float mAngle;
		//“x”–@•\‹L‚ÌŠp“x‚ğŒÊ“x–@•\‹L‚ÌŠp“x‚É•ÏŠ·‚·‚é
		float ToRadian(float angle) { return angle * (float)(acos(-1.0f) / 180.0f); }
		//“n‚³‚ê‚½ƒxƒNƒgƒ‹‚ğ³‹K‰»‚·‚é
		void Normalization(float &x, float &y);
		//ŒÄ‚Î‚ê‚½‰ñ”
		int mCount;
	};
}


