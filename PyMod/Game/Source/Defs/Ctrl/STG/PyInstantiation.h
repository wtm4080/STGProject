#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
#include "Ctrl/STG/Configuration/Detail/IInstantiation.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Ctrl
{
namespace STG
{
	template <class Target, class Parameter, class Type>
	class PyInstantiation
		: public Game::Ctrl::STG::Configuration::Detail::IInstantiation<Target, Parameter>
	{
	public:
		PyInstantiation( const boost::python::object &moduleObject )
			: mModuleObject( moduleObject )
		{}

		virtual Target GetInstance( const Parameter &param ) const
		{
			return Target( new Type( mModuleObject.attr( "Core" )( mId ) ) );
		}

		int GetId() const { return mId; }
		void SetId( int id ) { mId = id; }

	private:
		boost::python::object mModuleObject;
		int mId;
	};
}
}
}