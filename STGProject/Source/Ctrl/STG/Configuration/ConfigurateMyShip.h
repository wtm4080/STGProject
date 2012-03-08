#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Manager.h"
#include "Detail/Instantiation.h"


//----------------------------------------------------------------------------------
//	Define
//----------------------------------------------------------------------------------

#define CONFIGURATION_BEGIN \
	void Game::Ctrl::STG::Configuration::Manager::ConfigurateMyShip()	\
	{

#define REGISTER( Name, Class ) \
	RegisterMyShip(														\
	Data::MyShip( Name ),												\
	Detail::Holder<Data::MyShip, PMyShip, MyShipParam>::PInstantiation(	\
	new Detail::Instantiation<PMyShip, MyShipParam, Class>() ) )

#define CONFIGURATE_PYTHON() ConfiguratePyMyShip()

#define CONFIGURATION_END \
	}