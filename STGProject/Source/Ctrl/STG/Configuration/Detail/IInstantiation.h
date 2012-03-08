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
namespace Ctrl
{
namespace STG
{
namespace Configuration
{
namespace Detail
{
	template <class Target, class Parameter>
	class IInstantiation
	{
	public:
		virtual Target GetInstance( const Parameter &param ) const = 0;

		virtual ~IInstantiation() {}
	};
}
}
}
}
}