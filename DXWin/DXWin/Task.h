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
		//�f���Q�[�g�o�^
		void SetAction(std::function<void()> action) { mAction = action; }
		//�f���Q�[�g���s
		void Run() { if(mAction != nullptr) mAction(); }
		//�f���Q�[�g���s�@��x���s������f���Q�[�g����������
		void RunOnce()
		{
			Run();
			Reset();
		}
		//�f���Q�[�g����
		void Reset() { mAction = nullptr; }
		//�f���Q�[�g�����邩
		bool HasAction() { return mAction != nullptr; }
	private:
		std::function<void()> mAction;
	};
}
