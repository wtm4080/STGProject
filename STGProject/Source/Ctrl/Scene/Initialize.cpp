#include "PCH.h"
#include "Initialize.h"
#include "STG/Title.h"

#include "Ctrl/STG/Configuration/Manager.h"
#include "Ctrl/STG/Option/Manager.h"

using namespace Game;
using namespace Game::Ctrl::Scene;
using namespace Selene;

namespace
{
	typedef Util::Ptr<IScene>::Shared PScene;
}


// 1フレーム毎の状態更新
void Initialize::UpdateState()
{
	// STG構成情報の初期化
	Ctrl::STG::Configuration::Manager::Initialize();
	Ctrl::STG::Option::Manager::Read();

	Manager::ChangeScene( PScene( new STG::Title() ) );
}