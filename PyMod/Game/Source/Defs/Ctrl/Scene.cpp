#include "PCH.h"
#include "Scene.h"

#include "Util/Python/Wrapper/IScene.h"

using namespace boost::python;
using namespace Game;
using namespace Util::Python::Wrapper;
using namespace Defs::Ctrl;

namespace
{
	IScene *pScene;
}


void Scene::Configurate()
{
	class_<Scene>( "Scene", no_init )
		.def( "_setInstance", &Scene::_setInstance )
		.def( "changeScene", &Scene::changeScene )
		.def( "end", &Scene::end )
		.def( "isEnd", &Scene::isEnd )
		.def( "changeToSTGTitle", &Scene::changeToSTGTitle )
		.def( "changeToSTG", &Scene::changeToSTG )
		;
}


void Scene::_setInstance( uintptr_t p )
{
	pScene = reinterpret_cast<IScene *>( p );
}

void Scene::changeScene( const object &obj )
{
	pScene->ChangeScene( obj );
}

void Scene::end()
{
	pScene->End();
}

bool Scene::isEnd()
{
	return pScene->IsEnd();
}


void Scene::changeToSTGTitle()
{
	pScene->ChangeToSTGTitle();
}

void Scene::changeToSTG( int stageSetId, int myShipId )
{
	pScene->ChangeToSTG( stageSetId, myShipId );
}