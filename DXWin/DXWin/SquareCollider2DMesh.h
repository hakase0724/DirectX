#pragma once
#include "Primitive2D.h"
#include "MeshInfo.h"

namespace MyDirectX
{
	class SquareCollider2DMesh:public MeshInfo
	{
	public:
		SquareCollider2DMesh() {};
		void SetColliderParam(Point2D* leftTop, Point2D* rightTop, Point2D* leftBottom, Point2D* rightBottom);
		void SetColliderParam();
		~SquareCollider2DMesh();
		virtual UINT GetSize() override { return sizeof(VERTEX_DATA); }
	};

}

