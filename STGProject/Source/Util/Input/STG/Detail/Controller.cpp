#include "PCH.h"
#include "Controller.h"

using namespace Game;
using namespace Util::STG;
using namespace Util::Input::STG;
using namespace Detail;
using namespace Selene;
using namespace boost;


// コンストラクタ
Controller::Controller()
: mpController( MakeIntrusivePtr( Core::Manager::GetInputManager()->CreateInputController( 0 ) ) )
, mAxisVKeyMap()
, mKeyVKeyMap()
{
	// 軸1のマイナス（上）へカーソルキーの↑をアタッチ
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_AXIS_01_MINUIS, Engine::Input::KEY_UP );
	// 軸1のプラス（下）へカーソルキーの↓をアタッチ
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_AXIS_01_PLUS, Engine::Input::KEY_DOWN );
	// 軸2のマイナス（左）へカーソルキーの←をアタッチ
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_AXIS_02_MINUIS, Engine::Input::KEY_LEFT );
	// 軸2のプラス（右）へカーソルキーの→をアタッチ
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_AXIS_02_PLUS, Engine::Input::KEY_RIGHT );

	// ボタン1へZキーをアタッチ
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_BUTTON_01, Engine::Input::KEY_Z );
	// ボタン2へXキーをアタッチ
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_BUTTON_02, Engine::Input::KEY_X );
	// ボタン3へCキーをアタッチ
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_BUTTON_03, Engine::Input::KEY_C );
	// ボタン4へLShiftキーをアタッチ
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_BUTTON_04, Engine::Input::KEY_LSHIFT );
	// ボタン5へSpaceキーをアタッチ
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_BUTTON_05, Engine::Input::KEY_SPACE );
}


// フリー状態かを取得
bool Controller::IsFree( KEY_ID key ) const
{
	return mpController->IsFree( static_cast<Engine::Input::eControllerButton>( key ) );
}

// 離した瞬間かを取得
bool Controller::IsPull( KEY_ID key ) const
{
	return mpController->IsPull( static_cast<Engine::Input::eControllerButton>( key ) );
}

// 押した瞬間かを取得
bool Controller::IsPush( KEY_ID key ) const
{
	return mpController->IsPush( static_cast<Engine::Input::eControllerButton>( key ) );
}

// ホールド状態かを取得
bool Controller::IsHold( KEY_ID key ) const
{
	return mpController->IsHold( static_cast<Engine::Input::eControllerButton>( key ) );
}


// 方向の取得
Vector2DF Controller::GetDirection() const
{
	Vector2DF direction;

	direction.y = -mpController->GetPower( Engine::Input::CONTROLLER_AXIS_01_MINUIS );
	direction.y = direction.y + mpController->GetPower( Engine::Input::CONTROLLER_AXIS_01_PLUS );
	direction.x = -mpController->GetPower( Engine::Input::CONTROLLER_AXIS_02_MINUIS );
	direction.x = direction.x + mpController->GetPower( Engine::Input::CONTROLLER_AXIS_02_PLUS );

	if( direction.GetAbs() > 1.0f )
	{
		direction.Normalize();
	}

	return direction;
}


// ゲームパッドのアナログスティックをコントローラーに割り当てる
// 戻り値は、現在入力されているゲームパッドの仮想キー
// -1でどれも入力されていない状態
Sint32 Controller::SetAxis( AXIS_ID axis )
{
	Engine::Input::IJoystick *pJStick = 
		Core::Manager::GetInputManager()->GetJoystick( 0 );

	if( pJStick )
	{
		for( Uint32 vKey = 0; vKey < JOYSTICK_VIRTUAL_BUTTON_MAX; vKey++ )
		{
			if( pJStick->GetVirtualButtonState( vKey ) == Engine::Input::BUTTON_STATE_PUSH )
			{
				SetAxis( axis, vKey );

				return numeric_cast<Sint32>( vKey );
			}
			else if( pJStick->GetVirtualButtonState( vKey ) == Engine::Input::BUTTON_STATE_HOLD )
			{
				return numeric_cast<Sint32>( vKey );
			}
		}
	}

	return -1;
}

// ゲームパッドのボタンをコントローラーに割り当てる
// Axisに割り当てられている仮想キーは無視される
Sint32 Controller::SetButton( KEY_ID key )
{
	Engine::Input::IJoystick *pJStick = 
		Core::Manager::GetInputManager()->GetJoystick( 0 );

	if( pJStick )
	{
		for( Uint32 vKey = 0; vKey < JOYSTICK_VIRTUAL_BUTTON_MAX; vKey++ )
		{
			if( mAxisVKeyMap.right.find( vKey ) != mAxisVKeyMap.right.end() )
			{
				continue;
			}
			else if( pJStick->GetVirtualButtonState( vKey ) == Engine::Input::BUTTON_STATE_PUSH )
			{
				SetButton( key, vKey );

				return numeric_cast<Sint32>( vKey );
			}
			else if( pJStick->GetVirtualButtonState( vKey ) == Engine::Input::BUTTON_STATE_HOLD )
			{
				return numeric_cast<Sint32>( vKey );
			}
		}
	}

	return -1;
}


// 割り当てる仮想キーが分かっている場合はこちらを使う
void Controller::SetAxis( AXIS_ID axis, Uint32 virtualKey )
{
	{
		Uint32 prevVKey;

		{
			auto itr = mAxisVKeyMap.left.find( axis );
			if( itr != mAxisVKeyMap.left.end() )
			{
				prevVKey = itr->second;

				mpController->DetachGamepadVirtualButton( 
					static_cast<Engine::Input::eControllerButton>( itr->first ), 
					itr->second );
				mAxisVKeyMap.left.erase( itr );
			}
		}

		{
			auto itr = mAxisVKeyMap.right.find( virtualKey );
			if( itr != mAxisVKeyMap.right.end() )
			{
				AXIS_ID axisId = itr->second;
				mpController->DetachGamepadVirtualButton( 
					static_cast<Engine::Input::eControllerButton>( itr->second ), 
					itr->first );
				mAxisVKeyMap.right.erase( itr );

				mAxisVKeyMap.insert( AVKMapValueType( axisId, prevVKey ) );

				mpController->AttachGamepadVirtualButton( 
					static_cast<Engine::Input::eControllerButton>( axisId ), 
					prevVKey );
			}
		}
	}

	mpController->AttachGamepadVirtualButton( 
		static_cast<Engine::Input::eControllerButton>( axis ), 
		virtualKey );

	mAxisVKeyMap.insert( AVKMapValueType( axis, virtualKey ) );
}

void Controller::SetButton( KEY_ID key, Uint32 virtualKey )
{
	{
		Uint32 prevVKey;

		{
			auto itr = mKeyVKeyMap.left.find( key );
			if( itr != mKeyVKeyMap.left.end() )
			{
				prevVKey = itr->second;

				mpController->DetachGamepadVirtualButton( 
					static_cast<Engine::Input::eControllerButton>( itr->first ), 
					itr->second );
				mKeyVKeyMap.left.erase( itr );
			}
		}

		{
			auto itr = mKeyVKeyMap.right.find( virtualKey );
			if( itr != mKeyVKeyMap.right.end() )
			{
				KEY_ID keyId = itr->second;
				mpController->DetachGamepadVirtualButton( 
					static_cast<Engine::Input::eControllerButton>( itr->second ), 
					itr->first );
				mKeyVKeyMap.right.erase( itr );

				mKeyVKeyMap.insert( KVKMapValueType( keyId, prevVKey ) );

				mpController->AttachGamepadVirtualButton( 
					static_cast<Engine::Input::eControllerButton>( keyId ), 
					prevVKey );
			}
		}
	}

	mpController->AttachGamepadVirtualButton( 
		static_cast<Engine::Input::eControllerButton>( key ), 
		virtualKey );

	mKeyVKeyMap.insert( KVKMapValueType( key, virtualKey ) );
}


// 割り当てられている仮想キーを取得する
// 割り当てられていない場合、-1が返される
Sint32 Controller::GetAxisVirtualKey( AXIS_ID axis ) const
{
	auto aItr = mAxisVKeyMap.left.find( axis );
	if( aItr != mAxisVKeyMap.left.end() )
	{
		return numeric_cast<Sint32>( aItr->second );
	}

	return -1;
}

Sint32 Controller::GetButtonVirtualKey( KEY_ID key ) const
{
	auto kItr = mKeyVKeyMap.left.find( key );
	if( kItr != mKeyVKeyMap.left.end() )
	{
		return numeric_cast<Sint32>( kItr->second );
	}

	return -1;
}