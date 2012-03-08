#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Base.h"
#include "Util/Input/STG/Detail/ReplayController.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Mode
{
	class Replay
		: public Base
	{
	public:
		// コンストラクタ
		Replay( PScene pScene, const Conf::Replay &conf );

		// 次のステージを取得する
		virtual PStage GetNextStage();
		// 乱数生成器の取得
		virtual PRandom GetRandom() const;
		// シーンの再起動
		virtual void Restart() const;

	private:
		PRandom mpRandom;
		typedef Util::Ptr<Util::Input::STG::Detail::ReplayController>::Shared 
			PReplayController;
		PReplayController mpReplayController;

		// 更新時の処理
		virtual void OnUpdate();
		// 描画時の処理
		virtual void OnDraw() const;
	};
}
}
}
}