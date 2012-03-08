#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <string>
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
	class Stage
	{
	public:
		typedef int Id;

		Stage( const Id &id )
			: mId( id )
			, mStageSetId()
			, mName()
		{}
		Stage( const StageSet::Id &stageSetId, const std::wstring &name )
			: mId()
			, mStageSetId( stageSetId )
			, mName( name )
		{}

		const Id &GetId() const
		{
			return mId;
		}
		void SetId( const Id &id )
		{
			mId = id;
		}
		const StageSet::Id &GetStageSetId() const
		{
			return mStageSetId;
		}
		const std::wstring &GetName() const
		{
			return mName;
		}

		bool operator < ( const Stage &oper ) const
		{
			return this->mId < oper.mId;
		}
		bool operator == ( const Stage &oper ) const
		{
			return this->mId == oper.mId;
		}

	private:
		Id mId;
		StageSet::Id mStageSetId;
		std::wstring mName;
	};
}
}
}
}
}