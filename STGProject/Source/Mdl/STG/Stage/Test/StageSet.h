#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Stage/StageSet/Base.h"


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
namespace Test
{
	class StageSet
		: public StageSet::Base
	{
	public:
		Test( const StageSet::Parameter &param );

	private:
		virtual void OnUpdate();
		virtual void OnDraw() const;
	};
}
}
}
}
}