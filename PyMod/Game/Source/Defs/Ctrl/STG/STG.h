#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Ctrl/STG/Python/ISTG.h"
#include "Defs/Util/Input/Controller.h"
#include "Actors.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Ctrl
{
namespace STG
{
	class STG
	{
	public:
		static void Configurate();

		static void _setInstance( uintptr_t p );
		typedef Game::Util::Ptr<Actors>::Shared PActors;
		static PActors getActors();
		static Util::Input::Controller getController();
		typedef Game::Ctrl::STG::Python::ISTG::PRandom PRandom;
		static PRandom getRandom();
		typedef Game::Ctrl::STG::Python::ISTG::PStage PStage;
		static PStage getNextStage();
		static bool getDebugStrFlag();
		static void setDebugStrFlag( bool flag );
		static void restart();
		static Selene::Uint64 genObjectId();
	};
}
}
}