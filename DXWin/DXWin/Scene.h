#pragma once
#include <memory>
#include <vector>
#include "DXGameObject.h"
#include "MyEnums.h"
#include "DXResourceManager.h"
namespace MyDirectX
{
	class DXGameObject;

	class Scene
	{
	public:
		Scene() {};
		virtual ~Scene() {};
		void SetDXResourceManager(DXResourceManager* manager) { mDXRescourceManager = manager; }
		//シーンに最初から存在するゲームオブジェクトを渡す
		std::list<std::unique_ptr<DXGameObject>>* GetGameObjects() 
		{ 
			return &mGameObjectsList;
		}
		//ゲームオブジェクトをシーンに登録し参照を渡す
		virtual DXGameObject* Instantiate();
		//シーンの初期設定　シーン上のオブジェクトの生成などを行う
		virtual void Init() {};
		//シーンが始まった時に呼ばれる
		virtual void SceneStart() {};
		//Update前に呼ばれる　ゲームオブジェクトに依存しないUpdate
		virtual void SceneUpdate() {};
		//LateUpdate前に呼ばれる　ゲームオブジェクトに依存しないLateUpdate
		virtual void SceneLateUpdate() {};
		//描画処理が終わった後に呼ばれる　1フレームの最後に行う処理
		virtual void SceneEndFrame() {};
		//シーンの終わりに呼ばれる
		virtual void SceneEnd() {};
		//シーンの終了条件
		virtual bool IsSceneEnd() { return false; }
	protected:
		//このシーンに最初から存在するゲームオブジェクトのリスト
		std::list<std::unique_ptr<DXGameObject>> mGameObjectsList;
		//全体リソース管理クラスへの参照
		DXResourceManager* mDXRescourceManager;
	};
}


