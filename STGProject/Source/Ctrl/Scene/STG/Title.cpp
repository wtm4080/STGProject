#include "PCH.h"
#include "Title.h"

using namespace Game;
using namespace Ctrl::Scene::STG;
namespace py = boost::python;


// 1フレーム毎の状態更新
void Title::UpdateState()
{
	currentView.attr( "update" )();

	currentView.attr( "draw" )();
}


// コンストラクタ
Title::Title()
: currentView()
{
	py::object pyConf = py::import( "STG.Title.Conf" );
	currentView = pyConf.attr( "getTitleInstance" )();
}