#pragma once


namespace MyDirectX
{
	class DXGameObject;

	//コンポーネントのインターフェイス
	class IComponent
	{
	public:
		virtual void Initialize(DXGameObject* gameObject) = 0;
		virtual void Awake() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Exit() = 0;
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
		//描画処理
		virtual void Render() {};
		//解放処理
		virtual void Exit() {};
		virtual ~Component() {};
	protected:
		DXGameObject* mGameObject;
	};
}
