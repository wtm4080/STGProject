#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IConf.h"
#include "Ctrl/STG/Configuration/Manager.h"
#include "Ctrl/STG/Option/Manager.h"
#include "Util/Input/Manager.h"


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
	class ConfImpl
		: public IConf
	{
	public:
		virtual int RegisterMyShip( const std::wstring &name, PMyShipInstantiation pInst )
		{
			return Configuration::Manager::RegisterMyShip( 
				Configuration::Data::MyShip( name ), pInst );
		}
		virtual int RegisterStageSet( const std::wstring &name, 
			PStageSetInstantiation pInst, PPauseViewInstantiation pInstPauseView )
		{
			int stageSetId = Configuration::Manager::RegisterStageSet( 
				Configuration::Data::StageSet( name ), pInst );
			Configuration::Manager::RegisterPauseView( 
				Configuration::Data::Pause( stageSetId ), pInstPauseView );
			return stageSetId;
		}
		virtual int RegisterStage( int stageSetId, const std::wstring &name, PStageInstantiation pInst )
		{
			return Configuration::Manager::RegisterStage( 
				Configuration::Data::Stage( stageSetId, name ), pInst );
		}
		virtual void RegisterPauseView( int stageSetId, PPauseViewInstantiation pInstPauseView )
		{
			Configuration::Manager::RegisterPauseView( 
				Configuration::Data::Pause( stageSetId ), pInstPauseView );
		}

		virtual PStageSetInfo GetStageSetInfo()
		{
			PStageSetInfo pStageSetInfo( 
				new std::set<Configuration::Data::StageSet>() );
			Configuration::Manager::GetStageSetDataSet( *pStageSetInfo );
			return pStageSetInfo;
		}
		virtual PMyShipInfo GetMyShipInfo()
		{
			PMyShipInfo pMyShipInfo( 
				new std::set<Configuration::Data::MyShip>() );
			Configuration::Manager::GetMyShipDataSet( *pMyShipInfo );
			return pMyShipInfo;
		}

		virtual void ReadSetting()
		{
			Option::Manager::Read();
		}
		virtual void WriteSetting()
		{
			Option::Manager::Write();
		}
		virtual void SetScreenMode( bool fullScreen )
		{
			auto param = Option::Manager::GetParameter();
			param.SetFullScreen( fullScreen );
			Option::Manager::SetScreenMode( param );
		}
		virtual void SetBGMVolume( unsigned volume )
		{
			auto param = Option::Manager::GetParameter();
			param.SetBGMVolume( volume );
			Option::Manager::SetBGMVolume( param );
		}
		virtual void SetSEVolume( unsigned volume )
		{
			auto param = Option::Manager::GetParameter();
			param.SetSEVolume( volume );
			Option::Manager::SetSEVolume( param );
		}
		virtual int AttachControllerAxis( Util::Input::STG::Detail::AXIS_ID axisId )
		{
			auto pController = Util::Input::Manager::GetSTGController();
			int vKey = pController->SetAxis( axisId );
			if( vKey != -1 )
			{
				Option::Manager::SetAxis();
			}
			return vKey;
		}
		virtual int AttachControllerButton( Util::Input::STG::KEY_ID keyId )
		{
			auto pController = Util::Input::Manager::GetSTGController();
			int vKey = pController->SetButton( keyId );
			if( vKey != -1 )
			{
				Option::Manager::SetButton();
			}
			return vKey;
		}
		virtual void SetMaxFileCacheSize( unsigned size )
		{
			auto param = Option::Manager::GetParameter();
			param.SetMaxFileCacheSize( size );
			Option::Manager::SetMaxFileCacheSize( param );
		}
		virtual void SetDefaultSetting()
		{
			Option::Manager::SetDefault();
		}

		virtual const Option::Parameter &GetOptionParameter()
		{
			return Option::Manager::GetParameter();
		}
	};
}
}
}
}