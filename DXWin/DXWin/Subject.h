#pragma once
#include <list>
#include <functional>

namespace MyObservarPattern 
{
	/*
	T型を引数とする戻り値無しの関数を登録できるクラス
	*/
	template <class T>
	class Subject
	{
	public:
		Subject() {};
		//受け取った値を登録されている関数に渡して実行
		virtual void OnNext(T value);
		//正常終了処理
		virtual void OnCompleted();
		//異常終了処理
		virtual void OnError(std::exception& e);
		/*
		登録処理
		実行関数登録
		正常終了処理登録
		異常終了処理登録
		*/
		virtual void Subscribe(std::function<void(T value)> next);
		virtual void Subscribe(std::function<void(T value)> next, std::function<void()> completed);
		virtual void Subscribe(std::function<void(T value)> next, std::function<void()> completed, std::function<void()> error);
	private:
		//実行関数リスト
		std::list<std::function<void(T value)>> mOnNextFunctionList;
		//正常終了処理リスト
		std::list<std::function<void()>> mOnCompletedFunctionList;
		//異常終了処理リスト
		std::list<std::function<void()>> mOnErrorFunctionList;
		//デストラクタをprivateにして外部から破棄できなくする
		~Subject()
		{
			mOnNextFunctionList.clear();
			mOnCompletedFunctionList.clear();
			mOnErrorFunctionList.clear();
		};
	};
	template<class T>
	inline void Subject<T>::OnNext(T value)
	{
		try
		{
			for (auto function : mOnNextFunctionList)
			{
				function(value);
			}
		}
		catch(std::exception& e)
		{
			OnError(e);
		}
		
	}
	template<class T>
	inline void Subject<T>::OnCompleted()
	{
		for(auto function:mOnCompletedFunctionList)
		{
			function();
		}
		delete this;
	}
	template<class T>
	inline void Subject<T>::OnError(std::exception & e)
	{
		for (auto function : mOnErrorFunctionList)
		{
			function();
		}
		delete this;
	}
	template<class T>
	inline void Subject<T>::Subscribe(std::function<void(T value)> next)
	{
		mOnNextFunctionList.push_back(next);
	}
	template<class T>
	inline void Subject<T>::Subscribe(std::function<void(T value)> next, std::function<void()> completed)
	{
		mOnNextFunctionList.push_back(next);
		mOnCompletedFunctionList.push_back(completed);
	}
	template<class T>
	inline void Subject<T>::Subscribe(std::function<void(T value)> next, std::function<void()> completed, std::function<void()> error)
	{
		mOnNextFunctionList.push_back(next);
		mOnCompletedFunctionList.push_back(completed);
		mOnErrorFunctionList.push_back(error);
	}
}

