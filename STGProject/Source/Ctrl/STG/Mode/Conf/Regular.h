#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Ctrl/STG/Configuration/Data/MyShip.h"
#include "Ctrl/STG/Configuration/Data/StageSet.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Mode
{
namespace Conf
{
	typedef Configuration::Data::MyShip::Id StageSetId;
	typedef Configuration::Data::StageSet::Id MyShipId;

	class Regular
	{
	public:
		Regular( const StageSetId &stageSetId, const MyShipId &myShipId )
			: mStageSetId( stageSetId )
			, mMyShipId( myShipId )
		{}

		const StageSetId &GetStageSetId() const
		{
			return mStageSetId;
		}
		const MyShipId &GetMyShipId() const
		{
			return mMyShipId;
		}

	private:
		StageSetId mStageSetId;
		MyShipId mMyShipId;
	};
}
}
}
}
}