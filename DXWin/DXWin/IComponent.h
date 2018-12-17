#pragma once
#include <string>
#include "MyStructs.h"
#include "MyEnums.h"


namespace MyDirectX
{
	class DXGameObject;
	class Collider2D;
	//コンポーネントのインターフェイス
	class IComponent
	{
	public:
		virtual void Initialize(DXGameObject* gameObject) = 0;
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void Render() = 0;
		virtual void Exit() = 0;
		virtual void OnCollisionEnter2D(Collider2D* col) = 0;
		virtual void OnCollisionExit2D(Collider2D* col) = 0;
		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		virtual std::string GetName() = 0;
		virtual UINT GetID() = 0;
		virtual ~IComponent() = 0 {};
	};

	class IHP
	{
	public:
		virtual void SetHP(double hp) = 0;
		virtual double GetHP() = 0;
		virtual double GetMaxHP() = 0;
		virtual void Damage(double damage) = 0;
	};

	//コンポーネントクラス
	//このクラスを継承したクラスをDXGameObjectに追加していく
	//C++では抽象クラスをtemplateに渡すことができないらしいのでこのクラスを渡す
	class Component:public IComponent
	{
	public:
		//初期化処理
		virtual void Initialize(DXGameObject* gameObject) {};
		virtual void Initialize() {};
		//更新処理
		virtual void Update() {};
		virtual void LateUpdate() {};
		//描画処理
		virtual void Render() {};
		//解放処理
		virtual void Exit() {};
		//衝突の処理
		virtual void OnCollisionEnter2D(Collider2D* col) {};
		virtual void OnCollisionExit2D(Collider2D* col) {};
		virtual void OnEnable() {};
		virtual void OnDisable() {};
		std::string GetName() { return mName; }
		UINT GetID() { return mId; }
		Tag GetTag() const { return mTag; }
		void SetTag(Tag tag) { mTag = tag; }
		DXGameObject* GetGameObject() const { return mGameObject; }
		void SetEnable(bool enable) { mEnable = enable; }
		bool GetEnable() const { return mEnable; }
		virtual ~Component() {};
	protected:
		DXGameObject* mGameObject;
		std::string mName;
		UINT mId;
		Tag mTag;
		bool mEnable = true;
	};
}
