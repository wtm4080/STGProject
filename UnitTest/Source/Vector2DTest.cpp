#include "PCH.h"
#include "TestCommon.h"
#include "Util/STG/Vector2D.h"

using namespace Game::Util::STG;
using namespace Game::Util;
using namespace Selene;


TestSuite( Vector2DTest )


TestCase( ConstructTest )
{
	Vector2DI v;
	CheckEqual( 0, v.x );
	CheckEqual( 0, v.y );

	Vector2DF v2( 10.5f, 10.6f );
	Vector2DI v3( v2 );
	CheckEqual( 10, v3.x );
	CheckEqual( 10, v3.y );
}


TestCase( OperatorsTest )
{
	Vector2DI v1( 4, 8 ), v2( 2, 4 );

	Check( Vector2DI( 6, 12 ) == v1 + v2 );
	Check( Vector2DI( 2, 4 ) == v1 - v2 );
	Check( Vector2DI( 8, 32 ) == v1 * v2 );
	Check( Vector2DI( 2, 2 ) == v1 / v2 );

	Vector2DI assigned;
	assigned = v1;
	Check( Vector2DI( 4, 8 ) == assigned );
	assigned += v1;
	Check( Vector2DI( 8, 16 ) == assigned );
	assigned -= v2;
	Check( Vector2DI( 6, 12 ) == assigned );
	assigned *= v2;
	Check( Vector2DI( 12, 48 ) == assigned );
	assigned /= v1;
	Check( Vector2DI( 3, 6 ) == assigned );

	Check( Vector2DI( 6, 10 ) == v1 + 2 );
	Check( Vector2DI( 2, 6 ) == v1 - 2 );
	Check( Vector2DI( 8, 16 ) == v1 * 2 );
	Check( Vector2DI( 2, 4 ) == v1 / 2 );

	assigned = 0;
	Check( Vector2DI() == assigned );
	assigned += 4;
	Check( Vector2DI( 4, 4 ) == assigned );
	assigned -= 2;
	Check( Vector2DI( 2, 2 ) == assigned );
	assigned *= 4;
	Check( Vector2DI( 8, 8 ) == assigned );
	assigned /= 8;
	Check( Vector2DI( 1, 1 ) == assigned );

	Check( Vector2DI( -4, -8 ) == -v1 );

	Check( v1 != v2 );
}


TestCase( GetAbsTest )
{
	CheckEqual( 5, Vector2DI( 3, 4 ).GetAbs() );
}


TestCase( NormalizeTest )
{
	Vector2D<long double> v( 1, 1 );
	v.Normalize();

	CheckEqual( cos( PI/4 ), static_cast<float>( v.x ) );
	CheckEqual( sin( PI/4 ), static_cast<float>( v.y ) );
}


TestCase( SetUnitVectorTest )
{
	Vector2DF v;
	v.SetUnitVector( 45.0f );
	CheckEqual( Cos( 45.0f ), v.x );
	CheckEqual( Sin( 45.0f ), v.y );
}


TestCase( GetAngleTest )
{
	Vector2DI v0( 0, 1 );
	CheckEqual( 90, v0.GetAngle() );

	Vector2DI v1( 1, 0 ), v2( 0, 1 );
	CheckEqual( 135, v1.GetAngle( v2 ) );
}


TestCase( GetDistanceTest )
{
	Vector2DI v0, v1( 3, 4 );
	CheckEqual( 5, v0.GetDistance( v1 ) );
}


TestSuiteEnd()