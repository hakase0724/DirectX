#pragma once
#include <list>
#include <functional>

namespace MyObservarPattern 
{
	/*
	T�^�������Ƃ���߂�l�����̊֐���o�^�ł���N���X
	*/
	template <class T>
	class Subject
	{
	public:
		Subject() {};
		//�󂯎�����l��o�^����Ă���֐��ɓn���Ď��s
		virtual void OnNext(T value);
		//����I������
		virtual void OnCompleted();
		//�ُ�I������
		virtual void OnError(std::exception& e);
		/*
		�o�^����
		���s�֐��o�^
		����I�������o�^
		�ُ�I�������o�^
		*/
		virtual void Subscribe(std::function<void(T value)> next);
		virtual void Subscribe(std::function<void(T value)> next, std::function<void()> completed);
		virtual void Subscribe(std::function<void(T value)> next, std::function<void()> completed, std::function<void()> error);
	private:
		//���s�֐����X�g
		std::list<std::function<void(T value)>> mOnNextFunctionList;
		//����I���������X�g
		std::list<std::function<void()>> mOnCompletedFunctionList;
		//�ُ�I���������X�g
		std::list<std::function<void()>> mOnErrorFunctionList;
		//�f�X�g���N�^��private�ɂ��ĊO������j���ł��Ȃ�����
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

