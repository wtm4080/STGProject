#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Ctrl/Scene/IScene.h"
#include <boost/python.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace Scene
{
	class PyScene
		: public IScene
	{
	public:
		PyScene( const boost::python::object &obj )
			: mObj( obj )
		{}

		virtual void UpdateState()
		{
			mObj.attr( "update" )();
		}

	private:
		boost::python::object mObj;
	};
}
}
}