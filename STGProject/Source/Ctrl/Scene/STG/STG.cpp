#include "PCH.h"
#include "STG.h"

#include "Ctrl/STG/Configuration/Manager.h"
#include "Ctrl/STG/Mode/Regular.h"
#include "Ctrl/STG/Mode/Replay.h"
#include "Ctrl/STG/Mode/StageSelect.h"
#include "Ctrl/STG/Pause.h"
#include "Ctrl/STG/Python/STGImpl.h"
#include "Mdl/STG/Resource/Common.h"
#include "Util/Input/STG/IController.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Ctrl::Scene::STG;
using namespace Ctrl::STG::Mode;


// コンストラクタ
STG::STG( const Conf::Regular &conf )
: mFadeFlag( false )
, mConf( conf )
, mStageSetId( conf.GetStageSetId() )
{
	mpMode = PMode( new Regular( this, conf ) );

	Init();
}

STG::STG( const Conf::Replay &conf )
: mFadeFlag( false )
, mConf( conf )
, mStageSetId( conf.GetStageSetId() )
{
	mpMode = PMode( new Replay( this, conf ) );

	Init();
}

STG::STG( const Conf::StageSelect &conf )
: mFadeFlag( false )
, mConf( conf )
, mStageSetId( conf.GetStageSetId() )
{
	mpMode = PMode( new StageSelect( this, conf ) );

	Init();
}

void STG::Init()
{
	assert( mpMode );

	mpResource = PResource( new Mdl::STG::Resource::Common() );

	{
		mpPyInterface = PPyInterface( new Ctrl::STG::Python::STGImpl( mpMode ) );

		namespace py = boost::python;
		py::object gameModule = py::import( "Game" );
		gameModule.attr( "STG" ).attr( "_setInstance" )( 
			reinterpret_cast<uintptr_t>( 
			mpPyInterface.get() ) );

		py::object commonResource = py::import( "STG.Resource.Common" );
		commonResource.attr( "_initialize" )();
	}
}

STG::~STG()
{
	namespace py = boost::python;
	py::object gameModule = py::import( "Game" );
	gameModule.attr( "STG" ).attr( "_setInstance" )( NULL );
}


// 1フレーム毎の状態更新
void STG::UpdateState()
{
	if( !mFadeFlag )
	{
		View::FadeIn::Begin( 30, View::STG::PRI_FADE_EFFECT, 
			View::FadeIn::Delegate( this, &STG::UpdateState ) );

		mFadeFlag = true;
	}
	else
	{
		mpMode->Update();

		if( Util::Input::Manager::GetController()->IsPush( Util::Input::STG::KEY_SPACE ) )
		{
			Pause();
		}

		Draw();
	}
}


// 描画
void STG::Draw()
{
	mpMode->Draw();
}


// 共通リソースの取得
STG::PResource STG::GetResource() const
{
	return mpResource;
}


// 構成情報の取得
const STG::STGConf STG::GetConf() const
{
	assert( mConf.which() != CONF_EMPTY );

	return mConf;
}


// コンティニュー用ポーズ画面の起動
void STG::PauseForContinue()
{
	Pause( true );
}


Util::Delegate::Delegate0<> STG::GetDrawDelegate()
{
	return Util::Delegate::Delegate0<>( this, &STG::Draw );
}


void STG::Pause( bool continuing )
{
	Util::Sprite::Manager::StopShake();

	{
		typedef Util::Ptr<View::STG::Pause::IPause>::Shared PPauseView;
		PPauseView pPauseView( 
			Ctrl::STG::Configuration::Manager::GetPauseView( mStageSetId ) );
		if( !pPauseView )
		{
			Util::Exception e;
			e.SetErrorMessageBoxInfo( L"ポーズ画面の起動に失敗しました" );
			e.AddErrorInfo( 
				L"StageSetId: " + boost::lexical_cast<std::wstring>( mStageSetId ) );
			THROW( e );
		}

		typedef Util::Ptr<Ctrl::STG::Pause>::Shared PPauseCtrl;
		PPauseCtrl pPauseCtrl = PPauseCtrl( 
			new Ctrl::STG::Pause( 
			Util::Delegate::Delegate0<>( this, &STG::Draw ), pPauseView ) );

		if( continuing )
		{
			Scene::Manager::Interrupt( 
				Scene::Manager::Delegate( pPauseCtrl, &Ctrl::STG::Pause::Update_Continue ) );
		}
		else
		{
			Scene::Manager::Interrupt( 
				Scene::Manager::Delegate( pPauseCtrl, &Ctrl::STG::Pause::Update ) );
		}
	}
}