#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <string>


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
	class StageSet
	{
	public:
		typedef int Id;

		StageSet( const Id &id )
			: mId( id )
			, mName()
		{}
		StageSet( const std::wstring &name )
			: mId()
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
		const std::wstring &GetName() const
		{
			return mName;
		}

		bool operator < ( const StageSet &oper ) const
		{
			return this->mId < oper.mId;
		}
		bool operator == ( const StageSet &oper ) const
		{
			return this->mId == oper.mId;
		}

	private:
		Id mId;
		std::wstring mName;
	};
}
}
}
}
}