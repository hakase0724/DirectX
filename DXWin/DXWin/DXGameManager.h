#pragma once
#include "DXResourceManager.h"
#include "DXExcuter.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "BulletPool.h"

namespace MyDirectX
{
	class DXGameManager
	{
	public:
		DXGameManager(HWND hwnd);
		~DXGameManager() {};
		void Initialize();
		//ゲームループを実行
		//終了時にfalseを返す
		bool Update();
		void SetVsyncIntarval(int intarval) { mDXResourceManager->SetVsyncIntarval(intarval); }
	private:
		//シーン切り替え
		void SceneChange();
		//総シーン数
		int mSceneCount;
		//現在登録しているシーンの番号
		int mSceneIndex;
		//シーンのリスト
		std::vector<std::unique_ptr<Scene>> mSceneList;
		//機能クラスをまとめたクラス
		std::unique_ptr<DXResourceManager> mDXResourceManager;
		//ゲームループを実行するクラス
		std::unique_ptr<DXExcuter> mDXExcuter;
	};

}

