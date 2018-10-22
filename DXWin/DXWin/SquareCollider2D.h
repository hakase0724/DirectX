#pragma once
#include <memory>
#include "Collider2D.h"
#include "DXGameObject.h"
#include "MeshAndShader.h"

namespace MyDirectX
{
	class SquareCollider2D :public Collider2D
	{
	public:
		SquareCollider2D() {};
		~SquareCollider2D() {};
		Point2D* RightTop() const { return new Point2D(mPos.x + oneSide / 2,mPos.y + oneSide / 2); }
		Point2D* LeftTop() const { return new Point2D(mPos.x - oneSide / 2, mPos.y + oneSide / 2); }
		Point2D* RightBottom() const { return new Point2D(mPos.x + oneSide / 2, mPos.y - oneSide / 2); }
		Point2D* LeftBottom() const { return new Point2D(mPos.x - oneSide / 2, mPos.y - oneSide / 2); }
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Update() override {};
		virtual void Render() override;
		virtual void LateUpdate() override;
		virtual void Exit() override;
		virtual bool IsCollision(Collider2D* otherCollider) override;
	private:
		float oneSide;
		Point2D mPos;
		Point2D CalcPos();
		bool IsSquareCollision(SquareCollider2D* otherSquareCollider);
	};
}


