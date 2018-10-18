#pragma once
//誤差　epsilonは誤差を表すギリシャ文字だそう
#define EPSILON  0.000001f
#include<math.h>

// 3成分float
struct Float3 {
	float x, y, z;

	Float3() {}
	Float3(float x, float y, float z) : x(x), y(y), z(z) {}
	~Float3() {}

	Float3 operator +(const Float3 &r) const {
		return Float3(x + r.x, y + r.y, z + r.z);
	}

	Float3 operator -(const Float3 &r) const {
		return Float3(x - r.x, y - r.y, z - r.z);
	}

	Float3 operator -() const {
		return Float3(x * -1.0f, y * -1.0f, z * -1.0f);
	}

	Float3 operator *(const Float3 &r) const {
		return Float3(x * r.x, y * r.y, z * r.z);
	}

	Float3 operator /(const Float3 &r) const {
		return Float3(x / r.x, y / r.y, z / r.z);
	}

	Float3 operator *(float r) const {
		return Float3(x * r, y * r, z * r);
	}

	Float3 operator /(float r) const {
		return Float3(x / r, y / r, z / r);
	}

	friend Float3 operator *(float l, const Float3 &r) {
		return Float3(r.x * l, r.y * l, r.z * l);
	}

	friend Float3 operator /(float l, const Float3 &r) {
		return Float3(r.x / l, r.y / l, r.z / l);
	}

	float dot(const Float3 &r) const {
		return x * r.x + y * r.y + z * r.z;
	}

	Float3 cross(const Float3 &r) const {
		return Float3(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
	}

	float length() const {
		return sqrtf(lengthSq());
	}

	float lengthSq() const {
		return x * x + y * y + z * z;
	}

	void norm() {
		const float len = length();
		if (len > 0.0f) {
			x /= len;
			y /= len;
			z /= len;
		}
	}

	Float3 getNorm() const {
		const float len = length();
		if (len > 0.0f) {
			return Float3(x / len, y / len, z / len);
		}
		return Float3(0.0f, 0.0f, 0.0f);
	}
};


// 点
typedef Float3 Point;


// ベクトル
struct Vec3 : public Float3 {
	Vec3() {}
	Vec3(float x, float y, float z) : Float3(x, y, z) {}
	Vec3(const Float3 &r) : Float3(r) {}
	~Vec3() {}

	Vec3& operator =(const Float3 &r) {
		x = r.x;
		y = r.y;
		z = r.z;
		return *this;
	}

	// 標準化
	void norm() {
		const float len = length();
		if (len > 0.0f) {
			x /= len;
			y /= len;
			z /= len;
		}
	}

	// 垂直関係にある？
	bool isVertical(const Vec3 &r) const {
		float d = dot(r);
		return (-EPSILON < d && d < EPSILON);	// 誤差範囲内なら垂直と判定
	}

	// 平行関係にある？
	bool isParallel(const Vec3 &r) const {
		float d = cross(r).lengthSq();
		return (-EPSILON < d && d < EPSILON);	// 誤差範囲内なら平行と判定
	}

	// 鋭角関係？
	bool isSharpAngle(const Vec3 &r) const {
		return (dot(r) >= 0.0f);
	}
};


// 直線
struct Line {
	Point p;
	Vec3 v;		// 方向ベクトル
	Line() : p(0.0f, 0.0f, 0.0f), v(1.0f, 0.0f, 0.0f) {}
	Line(const Point &p, const Vec3 &v) : p(p), v(v) {}
	~Line() {}

	// 点上の座標を取得
	//  ベクトルに掛け算する係数
	Point getPoint(float t) const {
		return p + t * v;
	}
};


// 線分
struct Segment : public Line {

	Segment() {}
	Segment(const Point &p, const Vec3 &v) : Line(p, v) {}
	Segment(const Point &p1, const Point &p2) : Line(p1, p2 - p1) {}

	// 終点を取得
	Float3 getEndPoint() const {
		return p + v;
	}
};


// 球
struct Sphere {
	Point p;
	float r;	// 半径
	Sphere() : p(0.0f, 0.0f, 0.0f), r(0.5f) {}
	Sphere(const Point &p, float r) : p(p), r(r) {}
	~Sphere() {}
};

// カプセル
struct Capsule {
	Segment s;
	float r;	// 半径
	Capsule() : r(0.5f) {}
	Capsule(const Segment &s, float r) : s(s), r(r) {}
	Capsule(const Point &p1, const Point &p2, float r) : s(p1, p2), r(r) {}
	~Capsule() {}
};

// AABB Boxのこと
struct AABB {
	Point p;	// 中心点
	Float3 hl;	// 各軸の辺の長さの半分
	AABB() {}
	AABB(const Point &p, const Float3 &hl) : p(p), hl(hl) {}

	// 辺の長さを取得
	float lenX() const { return hl.x * 2.0f; };
	float lenY() const { return hl.y * 2.0f; };
	float lenZ() const { return hl.z * 2.0f; };
	float len(int i) {
		return *((&hl.x) + i) * 2.0f;
	}
};

