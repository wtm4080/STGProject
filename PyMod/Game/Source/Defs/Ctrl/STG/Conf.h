#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
#include "Util/Input/STG/Detail/Controller.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Ctrl
{
namespace STG
{
	class Conf
	{
	public:
		static void Configurate();

		static void _setInstance( uintptr_t p );
		static int registerMyShip( const std::wstring &name, 
			const boost::python::object &obj );
		static int registerStageSet( const std::wstring &name, 
			const boost::python::object &obj, const boost::python::object &pauseView );
		static void _registerPauseView( int stageSetId, const std::wstring &module );
		static int registerStage( int stageSetId, const std::wstring &name, 
			const boost::python::object &obj );

		typedef boost::python::list pylist;
		static pylist getStageSetInfoList();
		static pylist getMyShipInfoList();

		static void readSetting();
		static void writeSetting();
		static bool getScreenMode();
		static void setScreenMode( bool fullScreen );
		static unsigned getBGMVolume();
		static void setBGMVolume( unsigned volume );
		static unsigned getSEVolume();
		static void setSEVolume( unsigned volume );
		static int attachControllerAxis( Game::Util::Input::STG::Detail::AXIS_ID axisId );
		static int getAxisVirtualKey( Game::Util::Input::STG::Detail::AXIS_ID axisId );
		static int attachControllerButton( Game::Util::Input::STG::KEY_ID keyId );
		static int getButtonVirtualKey( Game::Util::Input::STG::KEY_ID keyId );
		static unsigned getMaxFileCacheSize();
		static void setMaxFileCacheSize( unsigned size );
		static void setDefaultSetting();
	};
}
}
}