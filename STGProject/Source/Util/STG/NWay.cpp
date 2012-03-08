#include "PCH.h"
#include "NWay.h"

using namespace Game;
using namespace Util::STG;
using namespace std;


void NWay::GetAngleSet( set<float> &angleSet, float angle, float intervalAngle, unsigned num )
{
	assert( num > 0 );

	angleSet.clear();

	unsigned numCount = num;
	float leftAngle = angle, rightAngle = angle;

	if( num % 2 == 0 )
	{
		leftAngle -= intervalAngle / 2;
		rightAngle += intervalAngle / 2;
	}
	else
	{
		angleSet.insert( angle );
		numCount--;

		leftAngle -= intervalAngle;
		rightAngle += intervalAngle;
	}

	for( unsigned i = num / 2; i > 0; i-- )
	{
		angleSet.insert( leftAngle );
		angleSet.insert( rightAngle );

		leftAngle -= intervalAngle;
		rightAngle += intervalAngle;
	}
}