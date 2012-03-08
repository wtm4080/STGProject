#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
#include "View/STG/Pause/IPause.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Ctrl
{
namespace STG
{
	class PyPause
		: public Game::View::STG::Pause::IPause
	{
	public:
		PyPause( const boost::python::object &pauseView )
			: mPauseView( pauseView )
		{}

		virtual bool Update()
		{
			return boost::python::extract<bool>( 
				mPauseView.attr( "update" )() );
		}
		virtual void Draw() const
		{
			mPauseView.attr( "draw" )();
		}

		virtual bool Update_Continue()
		{
			return boost::python::extract<bool>( 
				mPauseView.attr( "update_Continue" )() );
		}
		virtual void Draw_Continue() const
		{
			mPauseView.attr( "draw_Continue" )();
		}

	private:
		boost::python::object mPauseView;
	};
}
}
}