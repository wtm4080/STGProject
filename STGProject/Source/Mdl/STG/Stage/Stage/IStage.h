#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <boost/python.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Stage
{
namespace Stage
{
	class IStage
	{
	public:
		virtual void Update() = 0;
		virtual void Draw() const = 0;

		virtual bool IsEnd() const = 0;

		virtual boost::python::object GetInternalPyObject() = 0;

		virtual ~IStage() {}
	};
}
}
}
}
}