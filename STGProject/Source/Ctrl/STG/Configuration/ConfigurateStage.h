#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Manager.h"
#include "Detail/Instantiation.h"
#include <boost/python.hpp>


//----------------------------------------------------------------------------------
//	Define
//----------------------------------------------------------------------------------

#define CONFIGURATION_BEGIN \
	void Game::Ctrl::STG::Configuration::Manager::ConfigurateStage()	\
	{

#define STAGESET_BEGIN( Name, Class, PauseViewModuleName ) \
	{																			\
	Data::StageSet::Id stageSetId =												\
	RegisterStageSet(															\
	Data::StageSet( Name ),														\
	Detail::Holder<Data::StageSet, PStageSet, StageSetParam>::PInstantiation(	\
	new Detail::Instantiation<PStageSet, StageSetParam, Class>() ) );			\
	boost::python::import( "Game" ).attr( "STGConf" )							\
	.attr( "_registerPauseView" )( stageSetId, PauseViewModuleName );			\

#define REGISTER( Name, Class ) \
	RegisterStage(														\
	Data::Stage( stageSetId, Name ),									\
	Detail::Holder<Data::Stage, PStage, StageParam>::PInstantiation(	\
	new Detail::Instantiation<PStage, StageParam, Class>() ) )

#define STAGESET_END \
	}

#define CONFIGURATE_PYTHON() ConfiguratePyStage()

#define CONFIGURATION_END \
	}