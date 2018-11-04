#pragma once
#include "IComponent.h"
#include "DXGameObject.h"

namespace MyDirectX
{
	class Bullet :public Component
	{
	public:
		Bullet() {};
		~Bullet() {};
		//初期化処理
		virtual void Initialize(DXGameObject* gameObject);
		//まだ呼ばれない　もしかしたらこのまま使わず消すかも・・・
		virtual void Awake() {};
		virtual void Start() {};
		//更新処理
		virtual void Update();
		virtual void LateUpdate() {};
		virtual void FixedUpdate() {};
		//描画処理
		virtual void Render() {};
		//解放処理
		virtual void Exit() {};
		virtual void OnCollisionEnter(CollisionInfo* info);
		virtual void OnCollisionStay(CollisionInfo* info) {};
		virtual void OnCollisionExit(CollisionInfo* info) {};
	private:
		DXInput* mDXInput;
	};

	struct BulletObject
	{
		DXGameObject* gameObject;
		Bullet* bullet;
	};
}

