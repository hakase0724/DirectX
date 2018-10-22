#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <memory>
#include <vector> 
#include <algorithm>
#include "DXManager.h"
#include "IComponent.h"


namespace MyDirectX
{
	//このプロジェクトの核となるクラス
	//このクラスにComponentクラスを継承したクラスを追加していく
	class DXGameObject
	{
	public:
		DXGameObject(DXManager* dxManager);
		DXGameObject(TRANSFORM* transform, DXManager* dxManager);
		virtual ~DXGameObject();
		//自身のtransform情報を公開
		TRANSFORM GetTransform() const { return mTransform; }
		//自身にコンポーネントを追加する
		template<typename T>
		T* AddComponent();
		//指定したコンポーネントを取得する
		//指定したコンポーネントが複数ついていた場合は最初の一つのみ返す
		template<typename T>
		T* GetComponent();
		//指定したコンポーネントを消す
		template<typename T>
		void RemoveComponent();
		//ゲッター
		DXManager* GetDXManager() { return mDXManager; }
		DXInput* GetDXInput() { return mDXInput; }
		DXCamera* GetDXCamera() { return mDXCamera; }
		//自身のtransform情報を更新
		virtual void SetTransform(TRANSFORM *transform) { mTransform = *transform; }
		//自身の初期化
		virtual HRESULT Init(DXManager* dxManager);
		//自身の情報更新
		virtual void Update();
		virtual void LateUpdate();
		virtual void FixedUpdate();
		//自身の描画
		virtual void Render();
		//自身の解放
		virtual void Exit();
		virtual void OnCollisionEnter(Collisioninfo* info);
		virtual void OnCollisionStay(Collisioninfo* info);
		virtual void OnCollisionExit(Collisioninfo* info);
		std::string GetName() { return mName; }
		void SetName(std::string name) { mName = name; }
	protected:
		//自身の座標回転スケール
		TRANSFORM mTransform;
		//DirectXのリソース管理クラス
		DXManager* mDXManager;
		//DirectInput管理クラス
		DXInput* mDXInput;
		//カメラ情報
		DXCamera* mDXCamera;
		//自身が持つコンポーネントのリスト
		std::vector<Component*> mComponentsList;
		std::string mName;
	};

	template<typename T>
	inline T * DXGameObject::AddComponent()
	{
		T* pReturn = nullptr;
		//Componentの派生クラスでなければnullを返す
		if (!typeid(T).before(typeid(Component*))) return pReturn;
		pReturn = new T();
		pReturn->Initialize(this);
		mComponentsList.push_back(pReturn);
		return pReturn;
	}

	template<typename T>
	inline T * DXGameObject::GetComponent()
	{
		T* pReturn = nullptr;
		//配列を全走査し全てに対してキャストを試みる
		//成功したらその時点で走査を終了し値を返す
		for(auto itr = mComponentsList.begin();itr != mComponentsList.end();++itr)
		{
			pReturn = dynamic_cast<T*>(*itr);	
			if (pReturn != NULL) break;
		}
		return pReturn;
	}

	template<typename T>
	inline void DXGameObject::RemoveComponent()
	{
		//条件式に合致したものを配列の終端に押し込む
		auto remove = std::remove_if(mComponentsList.begin(), mComponentsList.end(), [](Component* com)->bool {return dynamic_cast<T*>(com) != NULL; });
		//消すものは終端に集まってるため後ろから消す
		mComponentsList.erase(remove, mComponentsList.end());
	}

}



