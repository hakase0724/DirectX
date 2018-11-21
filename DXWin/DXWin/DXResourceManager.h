#pragma once
#include<memory>
#include "DXManager.h"
#include "DXSound.h"
#include "FPSCountor.h"
#include "DXGameObject.h"

namespace MyDirectX
{
	class DXResourceManager
	{
	public:
		DXResourceManager(HWND hwnd);
		~DXResourceManager();
		DXGameObject* Instantiate();
		DXManager* GetDXManager() const { return mDXManager.get(); }
		bool GetKeyDown(int key) { return mDXManager->GetDXInput()->GetKeyDown(key); }
		bool GetKey(int key) { return mDXManager->GetDXInput()->GetInputState(key); }
		DXSound* GetDXSound() const { return mDXSound.get(); }
		double GetFPS() const { return mFPSCountor->GetFPS(); }
		void SetInputState() { mDXManager->GetDXInput()->SetInputState(); }
		void SetPreBuffer() { mDXManager->GetDXInput()->SetPreBuffer(); }
		bool IsEnd();
	private:
		UINT mGameObjectCount;
		std::unique_ptr<FPSCountor> mFPSCountor;
		std::unique_ptr<DXManager> mDXManager;
		std::unique_ptr<DXSound> mDXSound;
	};
}


