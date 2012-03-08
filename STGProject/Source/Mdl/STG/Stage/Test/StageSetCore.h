#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Forward.h"
#include "Background.h"
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
	class StageSetCore
		: public StageSet::Base
	{
	public:
		StageSetCore( const StageSet::Parameter &param );

		PBackground GetBackground() const;
		PResource GetResource() const;

	private:
		virtual void OnUpdate();
		virtual void OnDraw() const;

		PBackground mpBack;
		PResource mpResource;
	};
}
}
}
}
}