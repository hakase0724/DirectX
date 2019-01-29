#pragma once
#include "Primitive2D.h"
#include "IComponent.h"
#include "MyEnums.h"
#include "MyStructs.h"
#include <vector> 

namespace MyDirectX
{
	class Collider2D :public Component
	{
	public:
		Collider2D() { OutputDebugString(_T("eƒNƒ‰ƒX‚ª¶¬‚³‚ê‚½‚æ")); };
		virtual ~Collider2D() {};
		virtual bool IsCollision(Collider2D* otherCollider) { return false; }
		bool IsCollided() const { return mIsCollided; }
		virtual void OnCollision() {};
	protected:
		std::vector<Collider2D*> mCollisionList;
		std::vector<Collider2D*> mPreCollisionList;
		//Õ“Ë‚µ‚Ä‚¢‚é‚©
		bool mIsCollided;
	};

}

