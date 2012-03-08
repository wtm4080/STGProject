#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IScene.h"
#include "Ctrl/Scene/Manager.h"
#include "Ctrl/Scene/STG/Title.h"
#include "Ctrl/Scene/STG/STG.h"


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
	class SceneImpl
		: public IScene
	{
	public:
		// シーンの切り替え
		virtual void ChangeScene( const boost::python::object &obj )
		{
			Ctrl::Scene::Manager::ChangeScene( obj );
		}

		// ゲームの終了
		virtual void End()
		{
			Ctrl::Scene::Manager::End();
		}
		// 終了フラグの取得
		virtual bool IsEnd()
		{
			return Ctrl::Scene::Manager::IsEnd();
		}

		typedef Util::Ptr<Ctrl::Scene::IScene>::Shared PScene;
		// STGタイトルシーンへ切り替え
		virtual void ChangeToSTGTitle()
		{
			Ctrl::Scene::Manager::ChangeScene( 
				PScene( new Ctrl::Scene::STG::Title() ) );
		}
		// STGシーンへ切り替え
		virtual void ChangeToSTG( int stageSetId, int myShipId )
		{
			Ctrl::STG::Mode::Conf::Regular conf( stageSetId, myShipId );
			Ctrl::Scene::Manager::ChangeScene( 
				PScene( new Ctrl::Scene::STG::STG( conf ) ) );
		}
	};
}
}
}
}