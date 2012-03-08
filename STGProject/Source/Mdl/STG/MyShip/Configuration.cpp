#include "PCH.h"
#include "Ctrl/STG/Configuration/ConfigurateMyShip.h"

#include "TypeA/Core.h"
#include "TestShip/Core.h"

using namespace Game::Mdl::STG::MyShip;


CONFIGURATION_BEGIN

REGISTER( L"TypeA", TypeA::Core );
REGISTER( L"TestShip", TestShip::Core );

CONFIGURATE_PYTHON();

CONFIGURATION_END