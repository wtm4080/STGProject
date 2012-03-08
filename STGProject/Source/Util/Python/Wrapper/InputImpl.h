#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IInput.h"
#include "Util/Input/Manager.h"
#include "Util/Input/STG/Detail/Controller.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Python
{
namespace Wrapper
{
	class InputImpl
		: public IInput
	{
	public:
		// シューティング用のコントローラーの取得
		virtual PController GetController() const
		{
			return Input::Manager::GetController();
		}

		// 利用可能なジョイスティックの数を取得
		virtual Selene::Sint32 GetJoystickCount() const
		{
			return Input::Manager::GetJoystickCount();
		}

		// ゲームパッドのアナログスティックをコントローラーに割り当てる
		// 戻り値は、現在入力されているゲームパッドの仮想キー
		// -1でどれも入力されていない状態
		virtual Selene::Sint32 SetAxis( Input::STG::Detail::AXIS_ID axis )
		{
			return Input::Manager::GetSTGController()->SetAxis( axis );
		}
		// ゲームパッドのボタンをコントローラーに割り当てる
		// Axisに割り当てられている仮想キーは無視される
		virtual Selene::Sint32 SetButton( Input::STG::KEY_ID key )
		{
			return Input::Manager::GetSTGController()->SetButton( key );
		}

		// 割り当てる仮想キーが分かっている場合はこちらを使う
		virtual void SetAxis( Input::STG::Detail::AXIS_ID axis, Selene::Uint32 virtualKey )
		{
			Input::Manager::GetSTGController()->SetAxis( axis, virtualKey );
		}
		virtual void SetButton( Input::STG::KEY_ID key, Selene::Uint32 virtualKey )
		{
			Input::Manager::GetSTGController()->SetButton( key, virtualKey );
		}

		// 割り当てられている仮想キーを取得する
		// 割り当てられていない場合、-1が返される
		virtual Selene::Sint32 GetAxisVirtualKey( Input::STG::Detail::AXIS_ID axis ) const
		{
			return Input::Manager::GetSTGController()->GetAxisVirtualKey( axis );
		}
		virtual Selene::Sint32 GetButtonVirtualKey( Input::STG::KEY_ID key ) const
		{
			return Input::Manager::GetSTGController()->GetButtonVirtualKey( key );
		}
	};
}
}
}
}