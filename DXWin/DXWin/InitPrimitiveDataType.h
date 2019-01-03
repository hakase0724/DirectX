#pragma once

//今後便利クラスとか作ったらここに追加していこう
namespace MyLib
{
	/*
	Init
	各組み込み型を初期化する
	c++は組み込み型を初期化してくれないみたいだから自前実装
	*/
	void Init(int & value);
	void Init(double & value);
	void Init(float & value);
	
}

