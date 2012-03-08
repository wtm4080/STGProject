#include "PCH.h"
#include "Ctrl/STG/Configuration/ConfigurateStage.h"

#include "Test/StageSetCore.h"
#include "Test/TestStage1/StageCore.h"

using namespace Game::Mdl::STG::Stage;


CONFIGURATION_BEGIN

STAGESET_BEGIN( L"Test", Test::StageSetCore, "STG.Pause.Basic.Core" )
	using namespace Test;
	REGISTER( L"TestStage1", TestStage1::StageCore );
STAGESET_END

CONFIGURATE_PYTHON();

CONFIGURATION_END