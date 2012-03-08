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
namespace Mdl
{
namespace STG
{
namespace Stage
{
namespace Event
{
	class IEvent
	{
	public:
		virtual void Update() = 0;
		virtual void Draw() const = 0;

		virtual bool IsEnd() const = 0;

		virtual ~IEvent() {}
	};
}
}
}
}
}