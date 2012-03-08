#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Ctrl/Scene/IScene.h"
#include <boost/noncopyable.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace Scene
{
	// 最初に実行されるシーン
	// 各種初期化と次のシーンへの移行を行う
	class Initialize
		: public IScene
		, public boost::noncopyable
	{
	public:
		// 1フレーム毎の状態更新
		virtual void UpdateState();

	private:
	};
}
}
}