#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
#include "Mdl/STG/Stage/StageSet/IStageSet.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
	class PyStageSet
		: public Game::Mdl::STG::Stage::StageSet::IStageSet
	{
	public:
		PyStageSet( const boost::python::object &object )
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
		virtual void OnContinue()
		{
			mPyObject.attr( "onContinue" )();
		}
		virtual void OnMyShipDestruction()
		{
			mPyObject.attr( "onMyShipDestruction" )();
		}
		virtual void OnMyShipRevival()
		{
			mPyObject.attr( "onMyShipRevival" )();
		}

	private:
		boost::python::object mPyObject;
	};
}
}
}