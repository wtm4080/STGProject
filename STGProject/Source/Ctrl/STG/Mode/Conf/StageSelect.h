#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Regular.h"
#include "Ctrl/STG/Configuration/Data/Stage.h"


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
	typedef Configuration::Data::Stage::Id StageId;

	class StageSelect
	{
	public:
		StageSelect( const StageSetId &stageSetId, const MyShipId &myShipId, 
			const StageId &stageId )
			: mStageSetId( stageSetId )
			, mMyShipId( myShipId )
			, mStageId( stageId )
		{}

		const StageSetId &GetStageSetId() const
		{
			return mStageSetId;
		}
		const MyShipId &GetMyShipId() const
		{
			return mMyShipId;
		}
		const StageId &GetStageId() const
		{
			return mStageId;
		}

	private:
		StageSetId mStageSetId;
		MyShipId mMyShipId;
		StageId mStageId;
	};
}
}
}
}
}