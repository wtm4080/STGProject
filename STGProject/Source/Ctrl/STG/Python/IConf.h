#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <set>
#include "Ctrl/STG/Configuration/Data/MyShip.h"
#include "Ctrl/STG/Configuration/Data/StageSet.h"
#include "Ctrl/STG/Configuration/Data/Pause.h"
#include "Ctrl/STG/Configuration/Detail/IInstantiation.h"
#include "Ctrl/STG/Option/Parameter.h"
#include "Util/Input/STG/Detail/Controller.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Python
{
	class IConf
	{
	public:
		typedef Util::Ptr<Mdl::STG::MyShip::IMyShip>::Shared PMyShip;
		typedef Mdl::STG::MyShip::Parameter MyShipParam;
		typedef Util::Ptr<Configuration::Detail::IInstantiation<PMyShip, MyShipParam>>::Shared 
			PMyShipInstantiation;
		virtual int RegisterMyShip( const std::wstring &name, PMyShipInstantiation pInst ) = 0;

		typedef Util::Ptr<Mdl::STG::Stage::StageSet::IStageSet>::Shared PStageSet;
		typedef Mdl::STG::Stage::StageSet::Parameter StageSetParam;
		typedef Util::Ptr<Configuration::Detail::IInstantiation<PStageSet, StageSetParam>>::Shared 
			PStageSetInstantiation;
		typedef Util::Ptr<View::STG::Pause::IPause>::Shared PPauseView;
		typedef Ctrl::STG::Configuration::Data::PauseParam PauseViewParam;
		typedef Util::Ptr<Configuration::Detail::IInstantiation<PPauseView, PauseViewParam>>::Shared 
			PPauseViewInstantiation;
		virtual int RegisterStageSet( const std::wstring &name, 
			PStageSetInstantiation pInst, PPauseViewInstantiation pInstPauseView ) = 0;
		virtual void RegisterPauseView( int stageSetId, 
			PPauseViewInstantiation pInstPauseView ) = 0;

		typedef Util::Ptr<Mdl::STG::Stage::Stage::IStage>::Shared PStage;
		typedef Mdl::STG::Stage::Stage::Parameter StageParam;
		typedef Util::Ptr<Configuration::Detail::IInstantiation<PStage, StageParam>>::Shared 
			PStageInstantiation;
		virtual int RegisterStage( int stageSetId, const std::wstring &name, PStageInstantiation pInst ) = 0;

		typedef Util::Ptr<std::set<Configuration::Data::StageSet>>::Shared PStageSetInfo;
		virtual PStageSetInfo GetStageSetInfo() = 0;
		typedef Util::Ptr<std::set<Configuration::Data::MyShip>>::Shared PMyShipInfo;
		virtual PMyShipInfo GetMyShipInfo() = 0;

		virtual void ReadSetting() = 0;
		virtual void WriteSetting() = 0;
		virtual void SetScreenMode( bool fullScreen ) = 0;
		virtual void SetBGMVolume( unsigned volume ) = 0;
		virtual void SetSEVolume( unsigned volume ) = 0;
		virtual int AttachControllerAxis( Util::Input::STG::Detail::AXIS_ID axisId ) = 0;
		virtual int AttachControllerButton( Util::Input::STG::KEY_ID keyId ) = 0;
		virtual void SetMaxFileCacheSize( unsigned size ) = 0;
		virtual void SetDefaultSetting() = 0;
		virtual const Option::Parameter &GetOptionParameter() = 0;

		virtual ~IConf() {}
	};
}
}
}
}