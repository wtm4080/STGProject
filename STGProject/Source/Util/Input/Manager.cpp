#include "PCH.h"
#include "Manager.h"
#include "STG/Detail/Controller.h"
#include "STG/Detail/ReplayController.h"

using namespace Game;
using namespace Util::Input;
using namespace Selene;

namespace
{
	static Manager::PSTGController mpSTGController;
	static Manager::PSTGReplayController mpReplayController;
}


// 標準コントローラーの取得
Manager::PController Manager::GetController()
{
	return PController( GetSTGController() );
}

// シューティング用のコントローラーの取得
Manager::PSTGController Manager::GetSTGController()
{
	if( !mpSTGController )
	{
		mpSTGController = 
			PSTGController( new STG::Detail::Controller() );
	}

	return mpSTGController;
}

// リプレイ再生用のコントローラーの取得
Manager::PSTGReplayController Manager::GetReplayController()
{
	if( !mpReplayController )
	{
		mpReplayController = 
			PSTGReplayController( new STG::Detail::ReplayController() );
	}

	return mpReplayController;
}


// 利用可能なジョイスティックの数を取得
Sint32 Manager::GetJoystickCount()
{
	return Core::Manager::GetInputManager()->GetJoystickCount();
}


// コントローラーの開放
void Manager::Release()
{
	mpSTGController.reset();
	mpReplayController.reset();
}