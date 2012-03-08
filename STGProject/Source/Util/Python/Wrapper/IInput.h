#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Input/STG/IController.h"


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
	class IInput
	{
	public:
		// シューティング用のコントローラーの取得
		typedef Ptr<Input::STG::IController>::Shared PController;
		virtual PController GetController() const = 0;

		// 利用可能なジョイスティックの数を取得
		virtual Selene::Sint32 GetJoystickCount() const = 0;

		// ゲームパッドのアナログスティックをコントローラーに割り当てる
		// 戻り値は、現在入力されているゲームパッドの仮想キー
		// -1でどれも入力されていない状態
		virtual Selene::Sint32 SetAxis( Input::STG::Detail::AXIS_ID axis ) = 0;
		// ゲームパッドのボタンをコントローラーに割り当てる
		// Axisに割り当てられている仮想キーは無視される
		virtual Selene::Sint32 SetButton( Input::STG::KEY_ID key ) = 0;

		// 割り当てる仮想キーが分かっている場合はこちらを使う
		virtual void SetAxis( Input::STG::Detail::AXIS_ID axis, Selene::Uint32 virtualKey ) = 0;
		virtual void SetButton( Input::STG::KEY_ID key, Selene::Uint32 virtualKey ) = 0;

		// 割り当てられている仮想キーを取得する
		// 割り当てられていない場合、-1が返される
		virtual Selene::Sint32 GetAxisVirtualKey( Input::STG::Detail::AXIS_ID axis ) const = 0;
		virtual Selene::Sint32 GetButtonVirtualKey( Input::STG::KEY_ID key ) const = 0;

		virtual ~IInput() {}
	};
}
}
}
}