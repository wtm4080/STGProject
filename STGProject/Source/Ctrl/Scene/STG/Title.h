#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Ctrl/Scene/IScene.h"
#include <boost/noncopyable.hpp>
#include <boost/python.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace Scene
{
namespace STG
{
	class Title
		: public IScene
		, public boost::noncopyable
	{
	public:
		// 1フレーム毎の状態更新
		virtual void UpdateState();

		// コンストラクタ
		Title();
	private:
		// 現在のタイトル画面
		boost::python::object currentView;
	};
}
}
}
}