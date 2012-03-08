#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <boost/python.hpp>


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
	class IScene
	{
	public:
		// シーンの切り替え
		virtual void ChangeScene( const boost::python::object &obj ) = 0;

		// ゲームの終了
		virtual void End() = 0;
		// 終了フラグの取得
		virtual bool IsEnd() = 0;

		// STGタイトルシーンへ切り替え
		virtual void ChangeToSTGTitle() = 0;
		// STGシーンへ切り替え
		virtual void ChangeToSTG( int stageSetId, int myShipId ) = 0;

		virtual ~IScene() {}
	};
}
}
}
}