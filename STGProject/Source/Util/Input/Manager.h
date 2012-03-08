#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Input
{
	// 入力に関する処理
	class Manager
	{
	public:
		// 標準コントローラーの取得
		typedef Util::Ptr<STG::IController>::Shared 
			PController;
		static PController GetController();
		// シューティング用のコントローラーの取得
		typedef Util::Ptr<STG::Detail::Controller>::Shared 
			PSTGController;
		static PSTGController GetSTGController();
		// リプレイ再生用のコントローラーの取得
		typedef Util::Ptr<STG::Detail::ReplayController>::Shared 
			PSTGReplayController;
		static PSTGReplayController GetReplayController();

		// 利用可能なジョイスティックの数を取得
		static Selene::Sint32 GetJoystickCount();

		// コントローラーの開放
		// 後始末用
		static void Release();
	};
}
}
}