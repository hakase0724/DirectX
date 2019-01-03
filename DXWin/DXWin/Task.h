#pragma once
#include <functional>
#include "ReturnCoroutineValues.h"

namespace MyDirectX
{
	class Task
	{
	public:
		Task() {};
		~Task() {};
		//デリゲート登録
		void SetAction(std::function<void()> action) { mAction = action; }
		//デリゲート実行
		void Run() { if(mAction != nullptr) mAction(); }
		//デリゲート実行　一度実行したらデリゲートを解除する
		void RunOnce()
		{
			Run();
			Reset();
		}
		//デリゲート解除
		void Reset() { mAction = nullptr; }
		//デリゲートがあるか
		bool HasAction() { return mAction != nullptr; }
	private:
		std::function<void()> mAction;
	};
}
