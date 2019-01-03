#pragma once
#include <future>
#include <iostream>
#include <thread>
#include <experimental/coroutine>  // CoroutinesTS
#include <experimental/generator>

namespace MyDirectX
{
	template <typename T>
	struct CoroutineAsync
	{
		struct promise_type
		{
			std::promise<T> mValue;
			//最初から実行状態にしておく
			std::experimental::suspend_never initial_suspend() { return {}; }
			std::experimental::suspend_always final_suspend() { return {}; }

			auto get_return_object()
			{
				return CoroutineAsync(mValue.get_future(), HandleType::from_promise(*this));
			}
			//ハンドリングされていないエラーが出たら
			void unhandled_exception()
			{
				//プログラムを異常終了させる
				std::terminate();
			}

			std::experimental::suspend_never return_value(T value)
			{
				mValue.set_value(value);
				return {};
			}

			template<typename T>
			auto await_transform(std::future<T> f)
			{
				struct Awaiter
				{
					std::future<T> mFuture;

					bool await_ready() const
					{
						return mFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
					}

					void await_suspend(HandleType h)
					{
						std::thread([this, h]()
						{
							mFuture.wait();
							h.resume();
						}).detach();
					}

					T await_resume()
					{
						return mFuture.get();
					}
				};

				return Awaiter{ std::move(f) };
			}
		};

	private:
		using HandleType = std::experimental::coroutine_handle<promise_type>;
		std::future<T> mFuture;
		HandleType mCoroutineHandle;

	public:
		explicit CoroutineAsync(std::future<T>&& future, HandleType h) :mFuture(std::move(future)), mCoroutineHandle(h) {}

		CoroutineAsync(const CoroutineAsync&) = delete;
		CoroutineAsync(CoroutineAsync&& coroutine) :mFuture(std::move(coroutine.mFuture)), mCoroutineHandle(coroutine.mCoroutineHandle)
		{
			coroutine.mCoroutineHandle = nullptr;
		}

		~CoroutineAsync()
		{
			if (mCoroutineHandle != nullptr)
			{
				mCoroutineHandle.destroy();
			}
			mCoroutineHandle = nullptr;
		}

		T GetReturnValue()
		{
			return mFuture.get();
		}

		bool IsCompleted() const
		{
			return mFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
		}
	};
}

