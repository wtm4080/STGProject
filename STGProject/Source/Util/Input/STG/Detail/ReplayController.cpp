#include "PCH.h"
#include "ReplayController.h"

using namespace Game;
using namespace Util::Input::STG;
using namespace Detail;
using namespace Selene;


// フリー状態かを取得
bool ReplayController::IsFree( KEY_ID key ) const
{
	return false;
}

// 離した瞬間かを取得
bool ReplayController::IsPull( KEY_ID key ) const
{
	return false;
}

// 押した瞬間かを取得
bool ReplayController::IsPush( KEY_ID key ) const
{
	return false;
}

// ホールド状態かを取得
bool ReplayController::IsHold( KEY_ID key ) const
{
	return false;
}


// 方向の取得
Util::STG::Vector2DF ReplayController::GetDirection() const
{
	return Util::STG::Vector2DF();
}