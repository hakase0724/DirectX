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
		//����������
		virtual void Initialize(DXGameObject* gameObject);
		//�܂��Ă΂�Ȃ��@�����������炱�̂܂܎g�킸���������E�E�E
		virtual void Awake() {};
		virtual void Start() {};
		//�X�V����
		virtual void Update();
		virtual void LateUpdate() {};
		virtual void FixedUpdate() {};
		//�`�揈��
		virtual void Render() {};
		//�������
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
		//����������
		virtual void Initialize(DXGameObject* gameObject)
		{ 
			mGameObject = gameObject; 
			mId = mGameObject->GetID();
		}
		//�܂��Ă΂�Ȃ��@�����������炱�̂܂܎g�킸���������E�E�E
		virtual void Awake() {};
		virtual void Start() {};
		//�X�V����
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void FixedUpdate() {};
		//�`�揈��
		virtual void Render() {};
		//�������
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
 

