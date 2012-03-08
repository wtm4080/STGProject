#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "StageSelect.h"


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
	typedef int ReplayId;

	class Replay
	{
	public:
		Replay( const ReplayId &replayId, const MyShipId &myShipId, 
			const StageSetId &stageSetId )
			: mReplayId( replayId )
			, mMyShipId( myShipId )
			, mStageSetId( stageSetId )
			, mStageId()
			, mPlayAllFlag( true )
		{}
		Replay( const ReplayId &replayId, const MyShipId &myShipId, 
			const StageSetId &stageSetId, const StageId &stageId )
			: mReplayId( replayId )
			, mMyShipId( myShipId )
			, mStageSetId( stageSetId )
			, mStageId( stageId )
			, mPlayAllFlag( false )
		{}

		const ReplayId &GetReplayId() const
		{
			return mReplayId;
		}
		const MyShipId &GetMyShipId() const
		{
			return mMyShipId;
		}
		const StageSetId &GetStageSetId() const
		{
			return mStageSetId;
		}
		const StageId &GetStageId() const
		{
			return mStageId;
		}
		bool GetPlayAllFlag() const
		{
			return mPlayAllFlag;
		}

	private:
		ReplayId mReplayId;
		MyShipId mMyShipId;
		StageSetId mStageSetId;
		StageId mStageId;
		bool mPlayAllFlag;
	};
}
}
}
}
}