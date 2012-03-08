#include "PCH.h"
#include "SLN.h"

using namespace Game;
using namespace Util;
using namespace Random::Impl;
using namespace Selene;
using namespace boost::numeric;


// コンストラクタ
SLN::SLN( int seed )
: mRandom( seed )
{
}


// 乱数生成の種の設定
void SLN::SetSeed( int seed )
{
	mRandom.Seed( seed );
}


// 指定範囲内の整数乱数の取得
int SLN::GetInt( int min, int max )
{
	return mRandom.GetInt( min, max );
}

int SLN::GetInt( const interval<int> &itv )
{
	return mRandom.GetInt( itv.lower(), itv.upper() );
}

// 指定範囲内の浮動小数乱数の取得
float SLN::GetFloat( float min, float max )
{
	return mRandom.GetFloat( min, max );
}

float SLN::GetFloat( const interval<float> &itv )
{
	return mRandom.GetFloat( itv.lower(), itv.upper() );
}

// bool値の取得
bool SLN::GetBool()
{
	return GetInt( 0, 1 ) != 0;
}