#pragma once


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	class RepeatCounter
	{
	public:
		RepeatCounter()
			: mInterval( 1.0f )
			, mIntervalCount( 0 )
			, mRepeatCount( 0 )
		{}
		RepeatCounter( float itv )
			: mInterval( itv )
			, mIntervalCount( 0 )
			, mRepeatCount( 0 )
		{}

		// 1フレーム毎の状態更新
		void UpdateState()
		{
			mRepeatCount = 0;

			mIntervalCount += 1.0f;

			while( mIntervalCount >= mInterval )
			{
				mIntervalCount -= mInterval;

				mRepeatCount++;
			}
		}

		// 繰り返し回数の取得
		// 先にUpdateState()を呼び出しておくこと
		unsigned GetRepeatCount() const
		{
			return mRepeatCount;
		}

		// 状態をリセット
		void Reset()
		{
			mIntervalCount = 0;
			mRepeatCount = 0;
		}

		// 繰り返し間隔の取得
		float GetInterval() const
		{
			return mInterval;
		}
		// 繰り返し間隔の設定
		void SetInterval( float itv )
		{
			mInterval = itv;
		}

	private:
		float mInterval;
		float mIntervalCount;
		unsigned mRepeatCount;
	};
}
}