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
		//�G�C���A�X�e���v���[�g���g���Ė��O��Z�k
		using Property = ReactiveProperty<double>;
		//Score�\���Ɏg���ϐ�
		std::unique_ptr<Property, Deleter> mScoreRP;
	};
}

