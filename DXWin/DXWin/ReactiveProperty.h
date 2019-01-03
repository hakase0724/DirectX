#pragma once
#include "Subject.h"
#include "InitPrimitiveDataType.h"
namespace MyObservarPattern
{
	class Deleter
	{
	public:
		template <typename T>
		void operator()(T* value);
	};
	template<typename T>
	inline void Deleter::operator()(T * value)
	{
		value->Dispose();
	}

	template <class T>
	class ReactiveProperty
	{
	public:
		//初期値なし
		ReactiveProperty() 
		{
			mSubject = new Subject<T>();
			MyLib::Init(mValue);
		};
		//初期値あり
		ReactiveProperty(T value) 
		{
			mSubject = new Subject<T>();
			mValue = value;
		};
		//関数登録
		virtual void Subscribe(std::function<void(T value)> next);
		virtual void Subscribe(std::function<void(T value)> next, std::function<void()> completed);
		virtual void Subscribe(std::function<void(T value)> next, std::function<void()> completed, std::function<void()> error);

		//オペレータオーバーロード
		T operator +(T value)
		{
			mValue += value;
			mSubject->OnNext(mValue);
			return mValue;
		}
		T operator -(T value)
		{
			mValue -= value;
			mSubject->OnNext(mValue);
			return mValue;
		}
		T operator *(T value)
		{
			mValue *= value;
			mSubject->OnNext(mValue);
			return mValue;
		}
		T operator /(T value)
		{
			mValue /= value;
			mSubject->OnNext(mValue);
			return mValue;
		}
		T operator %(T value)
		{
			mValue %= value;
			mSubject->OnNext(mValue);
			return mValue;
		}
		T operator =(T value)
		{
			mValue = value;
			mSubject->OnNext(mValue);
			return mValue;
		}
		//値を取得
		T GetValue() const { return mValue; }
		//解放
		void Dispose() 
		{
			mSubject->OnCompleted();
			delete this; 
		};
	private:
		Subject<T>* mSubject;
		T mValue;
		~ReactiveProperty() {};

	};
	template<class T>
	inline void ReactiveProperty<T>::Subscribe(std::function<void(T value)> next)
	{
		mSubject->Subscribe(next);
	}
	template<class T>
	inline void ReactiveProperty<T>::Subscribe(std::function<void(T value)> next, std::function<void()> completed)
	{
		mSubject->Subscribe(next, completed);
	}
	template<class T>
	inline void ReactiveProperty<T>::Subscribe(std::function<void(T value)> next, std::function<void()> completed, std::function<void()> error)
	{
		mSubject->Subscribe(next, completed, error);
	}

}

