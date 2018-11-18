#pragma once
#include "DXManager.h"
#include "DXCube.h"
#include "DXSphere.h"
#include <vector> 
#include "DXGameObject.h"
#include "Mover.h"
#include "Collider.h"
#include "DXSquare.h"
#include "Roller.h"
#include "Colliders.h"
#include "Player.h"
#include "FPSCountor.h"
#include "BulletManager.h"
#include "MyStructs.h"
#include "DXTexture.h"
#include "Enemy.h"
#include "BackGround.h"
#include "DXSound.h"
#include "DXText.h"

namespace MyDirectX 
{
	class DXGameObjectManager
	{
	public:
		DXGameObjectManager(HWND hwnd);
		~DXGameObjectManager() {};
		DXManager* GetDXManager() const { return mDXManager.get(); }
		//オブジェクトを生成
		DXGameObject* Instantiate();
		BOOL Update();
		void LateUpdate();
		void Render();
		//指定したIDのオブジェクトのアクティブ状態を返す
		bool IsEnable(UINT id);
		//指定したIDのオブジェクトを返す
		DXGameObject* GetDXGameObjectWithID(UINT id);
		BulletManager* GetBulletManager() const { return mBulletManager.get(); }
	private:
		void ShowFPS();
		//ゲーム内に必要なクラスをインスタンス化する
		void CreateResources(HWND hwnd);
		//ゲームに最初から存在するゲームオブジェクトを生成する
		void CreateGameObject();
		//ゲーム中のコライダーを衝突判定に使用するため振り分けそれぞれの配列に入れる
		void StoreCollider2D();
		bool IsCollisionJudge(Tag shooter,Tag bullet);
		//生成したオブジェクトの数　この値を各ゲームオブジェクトのIDとして割り当てる
		UINT mGameObjectCounter;
		std::unique_ptr<BackGround> mBackGround;
		std::unique_ptr<FPSCountor> mFPSCountor;
		std::unique_ptr<DXManager> mDXManager;
		std::unique_ptr<BulletManager> mBulletManager;
		std::unique_ptr<DXSound> mDXSound;
		//ゲームオブジェクト管理配列
		std::vector<std::unique_ptr<DXGameObject>> mGameObjectsList;
		//ゲーム中に追加生成されたものを一時的に入れておく
		std::vector<std::unique_ptr<DXGameObject>> mTempGameObjectsList;
		//弾を打つキャラクターのコライダーの配列
		std::vector<Collider2D*> mShooterCollider2DList;
		//弾のコライダーの配列
		std::vector<Collider2D*> mBulletCollider2DList;
		DXGameObject* testObj;
		TextRenderer* textRenderer;
		DXText* mText;
		int mFrameCount;
		int mShowCoolTime = 60;
	};
}



