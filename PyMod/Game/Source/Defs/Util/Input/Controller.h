#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Input/STG/IController.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Input
{
	class Controller
	{
	public:
		typedef Game::Util::Ptr<Game::Util::Input::STG::IController>::Shared 
			PController;
		Controller( PController p )
			: mpCtrl( p )
		{}

		// フリー状態かを取得
		bool IsFree( Game::Util::Input::STG::KEY_ID key ) const
		{
			return mpCtrl->IsFree( key );
		}
		// 離した瞬間かを取得
		bool IsPull( Game::Util::Input::STG::KEY_ID key ) const
		{
			return mpCtrl->IsPull( key );
		}
		// 押した瞬間かを取得
		bool IsPush( Game::Util::Input::STG::KEY_ID key ) const
		{
			return mpCtrl->IsPush( key );
		}
		// ホールド状態かを取得
		bool IsHold( Game::Util::Input::STG::KEY_ID key ) const
		{
			return mpCtrl->IsHold( key );
		}

		// 方向の取得
		Game::Util::STG::Vector2DF GetDirection() const
		{
			return mpCtrl->GetDirection();
		}

		PController GetPtr() const
		{
			return mpCtrl;
		}

	private:
		PController mpCtrl;
	};
}
}
}