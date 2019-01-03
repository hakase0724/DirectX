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
		//�����l�Ȃ�
		ReactiveProperty() 
		{
			mSubject = new Subject<T>();
			MyLib::Init(mValue);
		};
		//�����l����
		ReactiveProperty(T value) 
		{
			mSubject = new Subject<T>();
			mValue = value;
		};
		//�֐��o�^
		virtual void Subscribe(std::function<void(T value)> next);
		virtual void Subscribe(std::function<void(T value)> next, std::function<void()> completed);
		virtual void Subscribe(std::function<void(T value)> next, std::function<void()> completed, std::function<void()> error);

		//�I�y���[�^�I�[�o�[���[�h
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
		//�l���擾
		T GetValue() const { return mValue; }
		//���
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

