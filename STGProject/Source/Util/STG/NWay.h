#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace STG
{
	class NWay
	{
	public:
		static void GetAngleSet( std::set<float> &angleSet, 
			float angle, float intervalAngle, unsigned num );
	};
}
}
}