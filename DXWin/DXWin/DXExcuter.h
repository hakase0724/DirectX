#pragma once
#include "Scene.h"
#include "DXResourceManager.h"
#include "CollisionManager.h"
namespace MyDirectX
{
	class DXExcuter
	{
	public:
		DXExcuter();
		~DXExcuter() {};
		//シーンの登録
		void SetScene(Scene* scene);
		//機能クラスをセットする
		void SetDXResourceManager(DXResourceManager* manager) { mDXRescourceManager = manager; }
		//ゲームループを実行する
		void Excute();
		bool IsSceneEnd() const { return mScene->IsSceneEnd(); }
	private:
		//登録シーン
		Scene* mScene;
		//登録されているゲームオブジェクトのUpdateを呼ぶ
		void Update();
		//登録されているゲームオブジェクトのLateUpdateを呼ぶ
		void LateUpdate();
		//登録されているゲームオブジェクトのRenderを呼ぶ
		void Render();
		//処理を動かすゲームオブジェクトの参照リスト
		std::vector<DXGameObject*> mExcuteObjectsList;
		//衝突管理クラス
		std::unique_ptr<CollisionManager> mCollisionManager;
		//機能クラスの参照
		DXResourceManager* mDXRescourceManager;
	};
}

