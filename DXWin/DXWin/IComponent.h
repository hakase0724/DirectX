#pragma once
#include<string>


namespace MyDirectX
{
	class DXGameObject;

	struct Collisioninfo
	{
		std::string name;
		UINT id;
		Collisioninfo() {};
	};

	//コンポーネントのインターフェイス
	class IComponent
	{
	public:
		virtual void Initialize(DXGameObject* gameObject) = 0;
		virtual void Awake() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;
		virtual void Exit() = 0;
		virtual void OnCollisionEnter(Collisioninfo* info) = 0;
		virtual void OnCollisionStay(Collisioninfo* info) = 0;
		virtual void OnCollisionExit(Collisioninfo* info) = 0;
		virtual std::string GetName() = 0;
		virtual UINT GetID() = 0;
		virtual ~IComponent() = 0 {};
	};

	//コンポーネントクラス
	//このクラスを継承したクラスをDXGameObjectに追加していく
	//C++では抽象クラスをtemplateに渡すことができないらしいのでこのクラスを渡す
	class Component:public IComponent
	{
	public:
		//初期化処理
		virtual void Initialize(DXGameObject* gameObject) {};
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
		virtual void OnCollisionStay(Collisioninfo* info) {};
		virtual void OnCollisionExit(Collisioninfo* info) {};
		virtual std::string GetName() { return mName; }
		virtual UINT GetID() { return mId; }
		virtual ~Component() {};
	protected:
		DXGameObject* mGameObject;
		std::string mName;
		UINT mId;
	};
}
