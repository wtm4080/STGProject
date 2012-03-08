#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Ctrl
{
	class Scene
	{
	public:
		static void Configurate();

		static void _setInstance( uintptr_t p );
		static void changeScene( const boost::python::object &obj );
		static void end();
		static bool isEnd();
		static void changeToSTGTitle();
		static void changeToSTG( int stageSetId, int myShipId );
	};
}
}