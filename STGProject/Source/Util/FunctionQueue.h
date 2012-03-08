#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Delegate/Delegate.h"
#include <queue>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	// 最初に追加した関数から実行していく
	// 関数の引数は0個、戻り値はboolでなければならない
	// 戻り値がfalseになると、先頭の関数がpopされる
	class FunctionQueue
	{
	public:
		typedef Delegate::Delegate0<bool> Delegate;

		// コンストラクタ
		FunctionQueue()
			: mFuncQueue()
			, mDefaultFunc()
		{}
		FunctionQueue( const std::queue<Delegate> &queue )
			: mFuncQueue( queue )
			, mDefaultFunc()
		{}

		// 先頭の関数を実行する
		void Call()
		{
			if( !IsEmpty() && 
				!mFuncQueue.front()() )
			{
				mFuncQueue.pop();
			}
			else if( IsEmpty() )
			{
				if( !mDefaultFunc.IsEmpty() && !mDefaultFunc() )
				{
					mDefaultFunc.Reset();
				}
			}
		}
		void operator () ()
		{
			Call();
		}

		// 関数を末尾に追加
		void Push( const Delegate &f )
		{
			mFuncQueue.push( f );
		}

		// 先頭の関数を削除
		void Pop()
		{
			mFuncQueue.pop();
		}

		// 関数を全削除
		void Clear()
		{
			while( !mFuncQueue.empty() )
			{
				mFuncQueue.pop();
			}
		}

		// 関数の有無
		bool IsEmpty() const
		{
			return mFuncQueue.empty();
		}

		// 関数の数
		std::queue<Delegate>::size_type GetSize() const
		{
			return mFuncQueue.size();
		}

		// 空の時に実行する関数の設定
		// 関数がfalseを返すと設定が解除される
		void SetDefaultFunction( const Delegate &func )
		{
			mDefaultFunc = func;
		}

	private:
		std::queue<Delegate> mFuncQueue;
		Delegate mDefaultFunc;
	};
}
}