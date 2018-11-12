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
		Collider2D() {};
		virtual ~Collider2D() {};
		virtual bool IsCollision(Collider2D* otherCollider) { return false; }
		virtual bool IsCollided() const { return mIsCollided; }
		virtual void OnCollision() {};
	protected:
		//è’ìÀÇµÇƒÇ¢ÇÈÇ©
		bool mIsCollided;
	};

}

