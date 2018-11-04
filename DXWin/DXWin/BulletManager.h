#pragma once
#include "IComponent.h"
#include "Bullet.h"
#include <vector>
#include <memory>
#include "MeshAndShader.h"
#include "DXGameObject.h"

namespace MyDirectX
{
	class BulletManager :public Component
	{
	public:
		BulletManager();
		~BulletManager();
		//初期化処理
		virtual void Initialize(DXGameObject* gameObject);
		//まだ呼ばれない　もしかしたらこのまま使わず消すかも・・・
		virtual void Awake() {};
		virtual void Start() {};
		//更新処理
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void FixedUpdate() {};
		//描画処理
		virtual void Render() {};
		//解放処理
		virtual void Exit() {};
		virtual void OnCollisionEnter(CollisionInfo* info) {};
		virtual void OnCollisionStay(CollisionInfo* info) {};
		virtual void OnCollisionExit(CollisionInfo* info) {};
		DXGameObject* GetBullet();
	private:
		std::vector<std::unique_ptr<DXGameObject>> bulletList;
		MeshInfo* mMeshInfo;
		ShaderInfo* mShaderInfo;
	};

}

