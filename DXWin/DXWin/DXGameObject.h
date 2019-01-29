#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <memory>
#include <vector> 
#include <algorithm>
#include "DXManager.h"
#include "IComponent.h"
#include "MyEnums.h"
#include "AlignedAllocationPolicy.h"
#include "DXResourceManager.h"

namespace MyDirectX
{
	class Scene;
	//このプロジェクトの核となるクラス
	//このクラスにComponentクラスを継承したクラスを追加していく
	class DXGameObject :public AlignedAllocationPolicy<16>
	{
	public:
		DXGameObject(DXResourceManager* manager);
		virtual ~DXGameObject();
		//自身のtransform情報を公開
		TRANSFORM* GetTransform() const { return mTransform.get(); }
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
		void RemoveComponent(Component* com);
		template<typename T>
		int GetComponentCount();
		//ゲッター
		DXManager* GetDXManager() { return mDXManager; }
		DXInput* GetDXInput() { return mDXInput; }
		DXCamera* GetDXCamera() { return mDXCamera; }
		//自身のtransform情報を更新
		virtual void SetTransform(TRANSFORM *transform) {/* mTransform = transform;*/ }
		//自身の初期化
		virtual HRESULT Init(DXManager* dxManager);
		//自身の持っているコンポーネントの初期化
		virtual void InitializeComponent();
		//自身の情報更新
		virtual void Update();
		//全てのUpdateが終わった後で呼ばれる
		virtual void LateUpdate();
		//自身の描画
		virtual void Render();
		//自身の解放
		virtual void Exit();
		//衝突した時の処理
		virtual void OnCollisionEnter2D(Collider2D* col);
		//衝突が終わった時の処理
		virtual void OnCollisionExit2D(Collider2D* col);
		virtual void OnEnable();
		virtual void OnDisable();
		//初期位置を設定する
		void SetDefaultTransform() { mDefaultTransform = *mTransform; }
		void SetDefaultTransform(TRANSFORM* transform) { mDefaultTransform = *transform; }
		//初期位置に移動する
		void ResetTransform() 
		{
			mTransform->Position = mDefaultTransform.Position;
			mTransform->Rotation = mDefaultTransform.Rotation;
			mTransform->Scale = mDefaultTransform.Scale;
		};
		//ゲッターとセッター
		//名前
		std::string GetName() { return mName; }
		void SetName(std::string name) { mName = name; }
		//ID
		UINT GetID() const { return mId; }
		void SetID(UINT id) { mId = id; }
		//タグ
		Tag GetTag() const { return mTag; }
		void SetTag(Tag tag) { mTag = tag; }
		//アクティブ状態
		bool GetEnable() const { return mEnable; }
		void SetEnable(bool enable) 
		{
			mEnable = enable; 
			//falseからtrueになったら
			if(mEnable == true)
			{
				if (mPreEnable == false)
				{
					mPreEnable = mEnable;
					OnEnable();
				}
			}

			//trueからfalseになったら
			if (mEnable == false)
			{
				if (mPreEnable == true)
				{
					mPreEnable = mEnable;
					OnDisable();
				}
			}
		}
		//シーン情報
		Scene* GetScene() const { return mScene; }
		void SetScene(Scene* scene) { mScene = scene; }
		//機能クラス
		void SetDXResourceManager(DXResourceManager* manager) { mDXResourceManager = manager; }
		DXResourceManager* GetDXResourceManager() const { return mDXResourceManager; }
	protected:
		//自身の座標回転スケール
		std::unique_ptr<TRANSFORM> mTransform;
		//DirectXのリソース管理クラス
		DXManager* mDXManager;
		//DirectInput管理クラス
		DXInput* mDXInput;
		//カメラ情報
		DXCamera* mDXCamera;
		DXResourceManager* mDXResourceManager;
		//自身が持つコンポーネントのリスト
		std::vector<Component*> mComponentsList;
		std::string mName;
		Tag mTag;
		UINT mId;
		bool mEnable;
		Scene* mScene;
		TRANSFORM mDefaultTransform;
	private:
		//1フレーム前のアクティブ状態
		bool mPreEnable = false;
	};

	template<typename T>
	inline T * DXGameObject::AddComponent()
	{
		T* pReturn = nullptr;
		//Componentの派生クラスでなければnullを返す
		if (!typeid(T).before(typeid(Component*))) return pReturn;
		pReturn = new T();
		//追加したコンポーネントの初期化処理を呼び出す
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

	template<typename T>
	inline int DXGameObject::GetComponentCount()
	{
		int count = 0;
		T* component;
		for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
		{
			component = dynamic_cast<T*>(*itr);
			if (component != NULL) count++;
		}
		return count;
	}

}



