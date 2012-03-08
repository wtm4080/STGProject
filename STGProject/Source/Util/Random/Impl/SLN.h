#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Random/IRandom.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Random
{
namespace Impl
{
	class SLN
		: public IRandom
	{
	public:
		// コンストラクタ
		SLN( int seed = 0 );

		// 乱数生成の種の設定
		void SetSeed( int seed );

		// 指定範囲内の整数乱数の取得
		virtual int GetInt( int min, int max );
		virtual int GetInt( const boost::numeric::interval<int> &itv );
		// 指定範囲内の浮動小数乱数の取得
		virtual float GetFloat( float min, float max );
		virtual float GetFloat( const boost::numeric::interval<float> &itv );
		// bool値の取得
		virtual bool GetBool();

	private:
		Selene::Kernel::Math::Random mRandom;
	};
}
}
}
}