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
namespace Ctrl
{
namespace STG
{
	class Pause
	{
	public:
		typedef Util::Ptr<View::STG::Pause::IPause>::Shared PView;
		typedef Util::Delegate::Delegate0<> UpdateFunc;

		// コンストラクタ
		Pause( const UpdateFunc &func, PView pView );
		// 更新関数
		bool Update();
		bool Update_Continue();

	private:
		// 現在のポーズ画面
		PView mpView;
		// ポーズ中も実行する関数(主に描画)
		UpdateFunc mUpdateFunc;
	};
}
}
}