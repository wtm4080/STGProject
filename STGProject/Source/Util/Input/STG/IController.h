#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/STG/Vector2D.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Input
{
namespace STG
{
	enum KEY_ID
	{
		KEY_Z		= Selene::Engine::Input::CONTROLLER_BUTTON_01, 
		KEY_X		= Selene::Engine::Input::CONTROLLER_BUTTON_02, 
		KEY_C		= Selene::Engine::Input::CONTROLLER_BUTTON_03, 
		KEY_LSHIFT	= Selene::Engine::Input::CONTROLLER_BUTTON_04, 
		KEY_SPACE	= Selene::Engine::Input::CONTROLLER_BUTTON_05, 
	};

	// シューティング用のコントローラーのインターフェース
	class IController
	{
	public:
		// フリー状態かを取得
		virtual bool IsFree( KEY_ID key ) const = 0;
		// 離した瞬間かを取得
		virtual bool IsPull( KEY_ID key ) const = 0;
		// 押した瞬間かを取得
		virtual bool IsPush( KEY_ID key ) const = 0;
		// ホールド状態かを取得
		virtual bool IsHold( KEY_ID key ) const = 0;

		// 方向の取得
		virtual Util::STG::Vector2DF GetDirection() const = 0;

		// デストラクタ
		virtual ~IController() {}
	};
}
}
}
}