#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Delegate/Delegate.h"
#include "RepeatCounter.h"
#include <list>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	class RepeatQueue
	{
	public:
		RepeatQueue( bool repeatAll = true )
			: mRepeatAll( repeatAll )
			, mList()
			, mItr( mList.begin() )
		{}

		typedef Delegate::Delegate0<> RepeatFunc;
		void Push( unsigned repeatNum, float interval, 
			const RepeatFunc &func = RepeatFunc() )
		{
			mList.push_back( Elem( repeatNum, func, interval ) );

			mItr = mList.begin();
		}

		void Clear()
		{
			mList.clear();

			mItr = mList.begin();
		}

		void Update()
		{
			if( mItr == mList.end() && mRepeatAll )
			{
				for( auto itr = mList.begin(); itr != mList.end(); itr++ )
				{
					itr->Reset();
				}

				mItr = mList.begin();
			}

			if( mItr != mList.end() )
			{
				mItr->Update();

				if( mItr->IsEnd() )
				{
					mItr++;
				}
			}
		}

		bool GetRepeatAll() const { return mRepeatAll; }
		void SetRepeatAll( bool repeatAll ) { mRepeatAll = repeatAll; }

	private:
		class Elem
		{
		public:
			Elem( unsigned repeatNum, const RepeatFunc &func, 
				float interval )
				: mRepeatNum( repeatNum )
				, mRepeatCount( 0 )
				, mFunc( func )
				, mCounter( interval )
			{}

			void Update()
			{
				mCounter.UpdateState();

				for( unsigned i = 0; 
					i < mCounter.GetRepeatCount() && mRepeatCount < mRepeatNum; 
					i++, mRepeatCount++ )
				{
					mFunc();
				}
			}

			bool IsEnd() const
			{
				return mRepeatCount >= mRepeatNum;
			}

			void Reset()
			{
				mRepeatCount = 0;
				mCounter.Reset();
			}

		private:
			const unsigned mRepeatNum;
			unsigned mRepeatCount;
			RepeatFunc mFunc;
			RepeatCounter mCounter;
		};

		std::list<Elem> mList;
		std::list<Elem>::iterator mItr;
		bool mRepeatAll;
	};
}
}