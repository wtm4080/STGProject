#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IInstantiation.h"
#include <boost/noncopyable.hpp>


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
	template <class Target, class Parameter, class Type>
	class Instantiation
		: public IInstantiation<Target, Parameter>
		, public boost::noncopyable
	{
	public:
		Target GetInstance( const Parameter &param ) const
		{
			return Target( new Type( param ) );
		}
	};
}
}
}
}
}