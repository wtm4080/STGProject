#include "PCH.h"
#include "NWay.h"

#include "Util/STG/NWay.h"

using namespace Game;
using namespace Mdl::STG::Bullet::Launcher;
using namespace std;


NWay::NWay()
: mGenerator()
, mAngle( 90.0f )
, mIntervalAngle( 20.0f )
, mNum( 1 )
{
}

NWay::NWay( const Generator &generator )
: mGenerator( generator )
, mAngle( 90.0f )
, mIntervalAngle( 20.0f )
, mNum( 1 )
{
}


void NWay::Launch()
{
	assert( !mGenerator.IsEmpty() );

	set<float> angleSet;
	Util::STG::NWay::GetAngleSet( 
		angleSet, mAngle, mIntervalAngle, mNum );

	foreach( float angle, angleSet )
	{
		mGenerator( angle );
	}
}


float NWay::GetAngle() const
{
	return mAngle;
}

void NWay::SetAngle( float angle )
{
	mAngle = angle;
}

float NWay::GetIntervalAngle() const
{
	return mIntervalAngle;
}

void NWay::SetIntervalAngle( float interval )
{
	mIntervalAngle = interval;
}

unsigned NWay::GetNum() const
{
	return mNum;
}

void NWay::SetNum( unsigned num )
{
	mNum = num;
}


NWay::Generator NWay::GetGenerator() const
{
	return mGenerator;
}

void NWay::SetGenerator( const Generator &generator )
{
	mGenerator = generator;
}