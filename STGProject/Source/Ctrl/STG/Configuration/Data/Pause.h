#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "StageSet.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Configuration
{
namespace Data
{
	class Pause
	{
	public:
		typedef StageSet::Id Id;
		Pause( const Id &stageSetId )
			: mStageSetId( stageSetId )
		{}

		const Id &GetId() const
		{
			return mStageSetId;
		}
		void SetId( const Id &id )
		{
			// ‰½‚à‚µ‚È‚¢
		}

		bool operator < ( const Pause &oper ) const
		{
			return this->mStageSetId < oper.mStageSetId;
		}
		bool operator == ( const Pause &oper ) const
		{
			return this->mStageSetId == oper.mStageSetId;
		}

	private:
		Id mStageSetId;
	};

	class PauseParam {};
}
}
}
}
}