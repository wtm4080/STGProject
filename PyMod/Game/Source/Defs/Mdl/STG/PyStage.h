#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
#include "Mdl/STG/Stage/Stage/IStage.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
	class PyStage
		: public Game::Mdl::STG::Stage::Stage::IStage
	{
	public:
		PyStage( const boost::python::object &object )
			: mPyObject( object )
		{}

		virtual void Update()
		{
			mPyObject.attr( "update" )();
		}
		virtual void Draw() const
		{
			mPyObject.attr( "draw" )();
		}

		virtual bool IsEnd() const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "end" ) );
		}

		virtual boost::python::object GetInternalPyObject()
		{
			return mPyObject;
		}

	private:
		boost::python::object mPyObject;
	};
}
}
}