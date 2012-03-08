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
namespace Input
{
namespace STG
{
namespace Detail
{
	// リプレイ再生時にリプレイ情報から入力情報を取得する
	class ReplayController
		: public IController
	{
	public:
		// フリー状態かを取得
		virtual bool IsFree( KEY_ID key ) const;
		// 離した瞬間かを取得
		virtual bool IsPull( KEY_ID key ) const;
		// 押した瞬間かを取得
		virtual bool IsPush( KEY_ID key ) const;
		// ホールド状態かを取得
		virtual bool IsHold( KEY_ID key ) const;

		// 方向の取得
		virtual Util::STG::Vector2DF GetDirection() const;

	private:
	};
}
}
}
}
}