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
		~DXGameManager();
		//ゲームループを実行
		//終了時にfalseを返す
		bool Update();
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

