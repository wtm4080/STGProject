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
namespace StageSet
{
	class Parameter
	{
	public:
		typedef Ctrl::STG::Mode::IMode *PMode;
		PMode GetMode() const { return mpMode; }
		void SetMode( PMode pMode ) { mpMode = pMode; }
		int GetStageSetId() const { return mStageSetId; }
		void SetStageSetId( int id ) { mStageSetId = id; }

	private:
		PMode mpMode;
		int mStageSetId;
	};
}
}
}
}
}