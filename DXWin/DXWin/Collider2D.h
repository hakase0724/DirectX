#pragma once
#include "Primitive2D.h"
#include "IComponent.h"

namespace MyDirectX
{
	class Collider2D :public Component
	{
	public:
		Collider2D() {};
		virtual ~Collider2D() {};
		virtual bool isCollision(Collider2D* otherCollider) { return false; }
		//初期化処理
		virtual void Initialize(DXGameObject* gameObject)override {};
		//まだ呼ばれない　もしかしたらこのまま使わず消すかも・・・
		virtual void Awake()override {};
		virtual void Start()override {};
		//更新処理
		virtual void Update()override {};
		virtual void LateUpdate()override {};
		virtual void FixedUpdate()override {};
		//描画処理
		virtual void Render()override {};
		//解放処理
		virtual void Exit()override {};
	};

}

