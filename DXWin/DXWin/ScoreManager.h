#pragma once
#include "ReactiveProperty.h"
#include "DXText.h"

using namespace MyObservarPattern;
namespace MyDirectX
{
	class ScoreManager
	{
	public:
		ScoreManager();
		~ScoreManager();

	private:
		//エイリアステンプレートを使って名前を短縮
		using Property = ReactiveProperty<double>;
		//Score表示に使う変数
		std::unique_ptr<Property, Deleter> mScoreRP;
	};
}

