#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Controller.h"
#include "Util/Input/STG/Detail/Controller.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Input
{
	class Input
	{
	public:
		static void Configurate();

		static void _setInstance( uintptr_t p );
		static Controller getController();
		static Selene::Sint32 getJoystickCount();
		static Selene::Sint32 setAxis( Game::Util::Input::STG::Detail::AXIS_ID axis );
		static void setAxis( Game::Util::Input::STG::Detail::AXIS_ID axis, Selene::Uint32 vKey );
		static Selene::Sint32 setButton( Game::Util::Input::STG::KEY_ID key );
		static void setButton( Game::Util::Input::STG::KEY_ID key, Selene::Uint32 vKey );
		static Selene::Sint32 getAxisVirtualKey( Game::Util::Input::STG::Detail::AXIS_ID axis );
		static Selene::Sint32 getButtonVirtualKey( Game::Util::Input::STG::KEY_ID key );
	};
}
}
}