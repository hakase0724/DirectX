#pragma once
#include "DXManager.h"
#include "IComponent.h"
#include "DXGameObject.h"
#include "Colliders.h"
#include <string>

namespace MyDirectX
{
	class DXGameObjectManager;

	class Player :public Component
	{
	public:
		Player() {};
		~Player() {};
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
		virtual void OnCollisionEnter(Collisioninfo* info) {};
		virtual void OnCollisionStay(Collisioninfo* info) {};
		virtual void OnCollisionExit(Collisioninfo* info) {};
		void SetManager(DXGameObjectManager* manager);
	private:
		DXGameObjectManager* mManager;
		DXInput* mDXInput;
	};

	class TestComponent:public Component
	{
	public:
		//初期化処理
		virtual void Initialize(DXGameObject* gameObject)
		{ 
			mGameObject = gameObject; 
			mId = mGameObject->GetID();
		}
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
		virtual void OnCollisionEnter(Collisioninfo* info) {};
		virtual void OnCollisionStay(Collisioninfo* info) 
		{
			auto transform = mGameObject->GetTransform();
			transform.Position.y += 0.01f;
			mGameObject->SetTransform(&transform);
			auto id = std::to_string(mId);
			auto colId = std::to_string(info->id);
			OutputDebugStringA(info->name.c_str());
			OutputDebugStringA(id.c_str());
			OutputDebugStringA("\n");
			OutputDebugStringA(colId.c_str());
			OutputDebugStringA("\n");
		};
		virtual void OnCollisionExit(Collisioninfo* info) {};
	};
}
 

