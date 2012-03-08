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
namespace Stage
{
	class Parameter
	{
	public:
		typedef StageSet::IStageSet *PStageSet;
		PStageSet GetStageSet() const { return mpStageSet; }
		void SetStageSet( PStageSet pStageSet ) { mpStageSet = pStageSet; }

	private:
		PStageSet mpStageSet;
	};
}
}
}
}
}