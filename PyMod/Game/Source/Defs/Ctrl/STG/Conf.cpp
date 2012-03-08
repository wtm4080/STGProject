#include "PCH.h"
#include "Conf.h"

#include "Defs/Ctrl/STG/PyInstantiation.h"
#include "Defs/Ctrl/STG/PyPause.h"
#include "Defs/Mdl/STG/Myship/PyMyShip.h"
#include "Defs/Mdl/STG/PyStageSet.h"
#include "Defs/Mdl/STG/PyStage.h"

#include "Ctrl/STG/Python/IConf.h"

using namespace boost::python;
using namespace Game::Ctrl::STG::Python;
using namespace std;
using namespace Defs::Ctrl::STG;
using namespace Defs::Mdl::STG;

namespace
{
	IConf *pConf = NULL;
}


void Conf::Configurate()
{
	class_<Conf>( "STGConf", no_init )
		.def( "_setInstance", &Conf::_setInstance )
		.def( "registerMyShip", &Conf::registerMyShip )
		.def( "registerStageSet", &Conf::registerStageSet )
		.def( "_registerPauseView", &Conf::_registerPauseView )
		.def( "registerStage", &Conf::registerStage )
		.def( "getStageSetInfoList", &Conf::getStageSetInfoList )
		.def( "getMyShipInfoList", &Conf::getMyShipInfoList )
		.def( "readSetting", &Conf::readSetting )
		.def( "writeSetting", &Conf::writeSetting )
		.def( "getScreenMode", &Conf::getScreenMode )
		.def( "setScreenMode", &Conf::setScreenMode )
		.def( "getBGMVolume", &Conf::getBGMVolume )
		.def( "setBGMVolume", &Conf::setBGMVolume )
		.def( "getSEVolume", &Conf::getSEVolume )
		.def( "setSEVolume", &Conf::setSEVolume )
		.def( "attachControllerAxis", &Conf::attachControllerAxis )
		.def( "getAxisVirtualKey", &Conf::getAxisVirtualKey )
		.def( "attachControllerButton", &Conf::attachControllerButton )
		.def( "getButtonVirtualKey", &Conf::getButtonVirtualKey )
		.def( "getMaxFileCacheSize", &Conf::getMaxFileCacheSize )
		.def( "setMaxFileCacheSize", &Conf::setMaxFileCacheSize )
		.def( "setDefaultSetting", &Conf::setDefaultSetting )
		;
}


void Conf::_setInstance( uintptr_t p )
{
	pConf = reinterpret_cast<IConf *>( p );
}

int Conf::registerMyShip( const wstring &name, const object &obj )
{
	typedef PyInstantiation<IConf::PMyShip, IConf::MyShipParam, MyShip::PyMyShip>
		Instantiation;

	Game::Util::Ptr<Instantiation>::Shared pInst( new Instantiation( obj ) );
	int id = pConf->RegisterMyShip( name, 
		IConf::PMyShipInstantiation( pInst ) );
	pInst->SetId( id );

	return id;
}

int Conf::registerStageSet( const wstring &name, 
	const object &obj, const object &pauseView )
{
	typedef PyInstantiation<IConf::PStageSet, IConf::StageSetParam, PyStageSet> 
		Instantiation;
	typedef PyInstantiation<IConf::PPauseView, IConf::PauseViewParam, PyPause> 
		PauseViewInstantiation;

	Game::Util::Ptr<Instantiation>::Shared pInst( new Instantiation( obj ) );
	Game::Util::Ptr<PauseViewInstantiation>::Shared pPauseViewInst( 
		new PauseViewInstantiation( pauseView ) );
	int id = pConf->RegisterStageSet( name, 
		IConf::PStageSetInstantiation( pInst ), 
		IConf::PPauseViewInstantiation( pPauseViewInst ) );
	pInst->SetId( id );
	pPauseViewInst->SetId( id );

	return id;
}

void Conf::_registerPauseView( int stageSetId, const wstring &module )
{
	typedef PyInstantiation<IConf::PPauseView, IConf::PauseViewParam, PyPause> 
		PauseViewInstantiation;

	object pauseView = import( str( module ) );
	Game::Util::Ptr<PauseViewInstantiation>::Shared 
		pPauseViewInst( new PauseViewInstantiation( pauseView ) );
	pConf->RegisterPauseView( stageSetId, 
		IConf::PPauseViewInstantiation( pPauseViewInst ) );
	pPauseViewInst->SetId( stageSetId );
}

int Conf::registerStage( int stageSetId, const wstring &name, const object &obj )
{
	typedef PyInstantiation<IConf::PStage, IConf::StageParam, PyStage> 
		Instantiation;

	Game::Util::Ptr<Instantiation>::Shared pInst( new Instantiation( obj ) );

	int id = pConf->RegisterStage( stageSetId, name, 
		IConf::PStageInstantiation( pInst ) );
	pInst->SetId( id );

	return id;
}


Conf::pylist Conf::getStageSetInfoList()
{
	IConf::PStageSetInfo pStageSetInfo = pConf->GetStageSetInfo();
	pylist infoList;

	foreach( auto info, *pStageSetInfo )
	{
		infoList.append( 
			make_tuple( info.GetId(), str( info.GetName() ) ) );
	}

	return infoList;
}

Conf::pylist Conf::getMyShipInfoList()
{
	IConf::PMyShipInfo pMyShipInfo = pConf->GetMyShipInfo();
	pylist infoList;

	foreach( auto info, *pMyShipInfo )
	{
		infoList.append( 
			make_tuple( info.GetId(), str( info.GetName() ) ) );
	}

	return infoList;
}


void Conf::readSetting()
{
	pConf->ReadSetting();
}

void Conf::writeSetting()
{
	pConf->WriteSetting();
}

bool Conf::getScreenMode()
{
	return pConf->GetOptionParameter().IsFullScreen();
}

void Conf::setScreenMode( bool fullScreen )
{
	pConf->SetScreenMode( fullScreen );
}

unsigned Conf::getBGMVolume()
{
	return pConf->GetOptionParameter().GetBGMVolume();
}

void Conf::setBGMVolume( unsigned volume )
{
	pConf->SetBGMVolume( volume );
}

unsigned Conf::getSEVolume()
{
	return pConf->GetOptionParameter().GetSEVolume();
}

void Conf::setSEVolume( unsigned volume )
{
	pConf->SetSEVolume( volume );
}

int Conf::attachControllerAxis( Game::Util::Input::STG::Detail::AXIS_ID axisId )
{
	return pConf->AttachControllerAxis( axisId );
}

int Conf::getAxisVirtualKey( Game::Util::Input::STG::Detail::AXIS_ID axisId )
{
	using namespace Game::Util::Input::STG::Detail;
	auto param = pConf->GetOptionParameter();

	switch( axisId )
	{
	case AXIS_X_MINUS:
		return param.GetVKeyXMinus();
	case AXIS_X_PLUS:
		return param.GetVKeyXPlus();
	case AXIS_Y_MINUS:
		return param.GetVKeyYMinus();
	case AXIS_Y_PLUS:
		return param.GetVKeyYPlus();
	default:
		assert( false );
		return -1;
	}
}

int Conf::attachControllerButton( Game::Util::Input::STG::KEY_ID keyId )
{
	return pConf->AttachControllerButton( keyId );
}

int Conf::getButtonVirtualKey( Game::Util::Input::STG::KEY_ID keyId )
{
	using namespace Game::Util::Input::STG;
	auto param = pConf->GetOptionParameter();

	switch( keyId )
	{
	case KEY_Z:
		return param.GetVKeyZ();
	case KEY_X:
		return param.GetVKeyX();
	case KEY_C:
		return param.GetVKeyC();
	case KEY_LSHIFT:
		return param.GetVKeyLShift();
	case KEY_SPACE:
		return param.GetVKeySpace();
	default:
		assert( false );
		return -1;
	}
}

unsigned Conf::getMaxFileCacheSize()
{
	return pConf->GetOptionParameter().GetMaxFileCacheSize();
}

void Conf::setMaxFileCacheSize( unsigned size )
{
	pConf->SetMaxFileCacheSize( size );
}

void Conf::setDefaultSetting()
{
	pConf->SetDefaultSetting();
}