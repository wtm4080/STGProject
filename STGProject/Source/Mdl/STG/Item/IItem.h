#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Mdl/STG/Actor/IActor.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Item
{
	class IItem
		: virtual public Actor::IActor
	{
	public:
		// Ž©‹@ƒw‚Ì“–‚½‚è”»’è‚Ì”¼Œa‚ÌŽæ“¾
		virtual float GetHitRadius() const = 0;
		// “–‚½‚è”»’è
		virtual bool IsHit( const Util::STG::Hit::CircleI &hit ) const = 0;

		virtual ~IItem() {}
	};
}
}
}
}