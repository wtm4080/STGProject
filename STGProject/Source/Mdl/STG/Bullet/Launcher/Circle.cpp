#include "PCH.h"
#include "Circle.h"

#include "Util/STG/NWay.h"

using namespace Game;
using namespace Mdl::STG::Bullet::Launcher;
using namespace std;


Circle::Circle()
: mGenerator()
, mAngle( 90.0f )
, mNum( 1 )
{
}

Circle::Circle( const Generator &generator )
: mGenerator( generator )
, mAngle( 90.0f )
, mNum( 1 )
{
}


void Circle::Launch()
{
	assert( !mGenerator.IsEmpty() );

	float interval = 360.0f / mNum;

	set<float> angleSet;
	Util::STG::NWay::GetAngleSet( 
		angleSet, mAngle, interval, mNum );

	foreach( float angle, angleSet )
	{
		mGenerator( angle );
	}
}


float Circle::GetAngle() const
{
	return mAngle;
}

void Circle::SetAngle( float angle )
{
	mAngle = angle;
}

unsigned Circle::GetNum() const
{
	return mNum;
}

void Circle::SetNum( unsigned num )
{
	assert( num != 0 );

	mNum = num;
}


Circle::Generator Circle::GetGenerator() const
{
	return mGenerator;
}

void Circle::SetGenerator( const Generator &generator )
{
	mGenerator = generator;
}