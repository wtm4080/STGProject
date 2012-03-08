#include "PCH.h"
#include "Input.h"

#include "Util/Python/Wrapper/IInput.h"

using namespace Game;
using namespace Util::Python::Wrapper;
using namespace boost::python;
using namespace Selene;
using namespace Util::Input::STG;
using namespace Defs::Util::Input;

namespace
{
	IInput *pInput;

	typedef Game::Util::Input::STG::Detail::AXIS_ID AXIS_ID;
}


void Input::Configurate()
{
	class_<Input>( "Input", no_init )
		.def( "_setInstance", &Input::_setInstance )
		.def( "getController", &Input::getController )
		.def( "getJoystickCount", &Input::getJoystickCount )
		.def( "setAxis", static_cast<Sint32 (*)( AXIS_ID )>( &Input::setAxis ) )
		.def( "setAxis", static_cast<void (*)( AXIS_ID, Uint32 )>( &Input::setAxis ) )
		.def( "setButton", static_cast<Sint32 (*)( KEY_ID )>( &Input::setButton ) )
		.def( "setButton", static_cast<void (*)( KEY_ID, Uint32 )>( &Input::setButton ) )
		.def( "getAxisVirtualKey", &Input::getAxisVirtualKey )
		.def( "getButtonVirtualKey", &Input::getButtonVirtualKey )
		;

	enum_<KEY_ID>( "KeyId" )
		.value( "Z", KEY_Z )
		.value( "X", KEY_X )
		.value( "C", KEY_C )
		.value( "LShift", KEY_LSHIFT )
		.value( "Space", KEY_SPACE )
		;
	{
		namespace InputDetail = Game::Util::Input::STG::Detail;
		enum_<AXIS_ID>( "AxisId" )
			.value( "XMinus", InputDetail::AXIS_X_MINUS )
			.value( "XPlus", InputDetail::AXIS_X_PLUS )
			.value( "YMinus", InputDetail::AXIS_Y_MINUS )
			.value( "YPlus", InputDetail::AXIS_Y_PLUS )
			;
	}

	class_<Controller>( "InputController", no_init )
		.def( "isFree", &Controller::IsFree )
		.def( "isPull", &Controller::IsPull )
		.def( "isPush", &Controller::IsPush )
		.def( "isHold", &Controller::IsHold )
		.add_property( "direction", &Controller::GetDirection )
		;
}


void Input::_setInstance( uintptr_t p )
{
	pInput = reinterpret_cast<IInput *>( p );
}

Controller Input::getController()
{
	return Controller( pInput->GetController() );
}

Sint32 Input::getJoystickCount()
{
	return pInput->GetJoystickCount();
}

Sint32 Input::setAxis( AXIS_ID axis )
{
	return pInput->SetAxis( axis );
}

void Input::setAxis( AXIS_ID axis, Uint32 vKey )
{
	pInput->SetAxis( axis, vKey );
}

Sint32 Input::setButton( KEY_ID key )
{
	return pInput->SetButton( key );
}

void Input::setButton( KEY_ID key, Uint32 vKey )
{
	pInput->SetButton( key, vKey );
}

Sint32 Input::getAxisVirtualKey( AXIS_ID axis )
{
	return pInput->GetAxisVirtualKey( axis );
}

Sint32 Input::getButtonVirtualKey( KEY_ID key )
{
	return pInput->GetButtonVirtualKey( key );
}