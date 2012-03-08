#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Delegate/Delegate.h"
#include <list>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	// 追加した関数をすべて実行する
	// 関数の引数は0個、戻り値はboolでなければならない
	// 戻り値がfalseになると、その関数はpopされる
	class FunctionList
	{
	public:
		typedef Delegate::Delegate0<bool> Delegate;

		// コンストラクタ
		FunctionList()
			: mFuncList()
			, mDefaultFunc()
		{}
		FunctionList( const std::list<Delegate> &list )
			: mFuncList( list )
			, mDefaultFunc()
		{}

		// 関数を実行する
		void Call()
		{
			if( !IsEmpty() )
			{
				for( std::list<Delegate>::iterator itr = mFuncList.begin(); 
					itr != mFuncList.end(); )
				{
					if( !itr->Call() )
					{
						mFuncList.erase( itr++ );
					}
					else
					{
						itr++;
					}
				}

				if( !mOnlyEmptyFlag )
				{
					if( !mDefaultFunc.IsEmpty() && !mDefaultFunc() )
					{
						mDefaultFunc.Reset();
					}
				}
			}
			else
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

		// 関数を追加
		void Add( const Delegate &func )
		{
			mFuncList.push_back( func );
		}

		// 関数を全削除
		void Clear()
		{
			mFuncList.clear();
		}

		// 関数の有無を調べる
		bool IsEmpty() const
		{
			return mFuncList.empty();
		}

		// 関数の数を調べる
		std::list<Delegate>::size_type GetSize() const
		{
			return mFuncList.size();
		}

		// 空の時に実行する関数の設定
		// onlyEmptyをfalseにすると、空でない時も実行される
		// 関数がfalseを返すと設定が解除される
		void SetDefaultFunction( const Delegate &func, bool onlyEmpty = true )
		{
			mDefaultFunc = func;
			mOnlyEmptyFlag = onlyEmpty;
		}

	private:
		std::list<Delegate> mFuncList;
		Delegate mDefaultFunc;
		// mDefaultFuncをmFuncListが空の時しか実行しないフラグ
		bool mOnlyEmptyFlag;
	};
}
}