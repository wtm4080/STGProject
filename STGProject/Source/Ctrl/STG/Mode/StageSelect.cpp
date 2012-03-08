#include "PCH.h"
#include "StageSelect.h"

#include "Ctrl/Scene/STG/STG.h"
#include "Ctrl/STG/Configuration/Manager.h"
#include "Mdl/STG/MyShip/Parameter.h"
#include "Mdl/STG/Stage/Stage/Parameter.h"
#include "Mdl/STG/Stage/StageSet/Parameter.h"

using namespace Game;
using namespace Ctrl::STG::Mode;


// コンストラクタ
StageSelect::StageSelect( PScene pScene, const Conf::StageSelect &conf )
	: Base( pScene, conf.GetStageSetId() )
	, mpRandom( new Util::Random::Impl::SLN( static_cast<int>( ::time( NULL ) ) ) )
{
	{
		Conf::MyShipParam param;
		param.SetMode( this );
		param.SetController( Util::Input::Manager::GetController() );
		Base::SetController( param.GetController() );

		Base::GetConfHolder().InitMyShip( param, conf.GetMyShipId() );
	}

	{
		Conf::StageSetParam param;
		param.SetMode( this );
		param.SetStageSetId( conf.GetStageSetId() );

		Base::GetConfHolder().InitStageSet( param, conf.GetStageSetId() );
	}

	{
		while( !Base::GetConfHolder().GetStageDataQueue().empty() )
		{
			Base::GetConfHolder().GetStageDataQueue().pop();
		}

		Base::GetConfHolder().GetStageDataQueue().push( 
			Configuration::Manager::GetStageData( conf.GetStageId() ) );
	}
}


// 次のステージを取得する
IMode::PStage StageSelect::GetNextStage()
{
	assert( Base::GetConfHolder().GetStageSet() );

	Conf::StageParam param;
	param.SetStageSet( Base::GetConfHolder().GetStageSet().get() );

	return Base::GetConfHolder().GetNextStage( param );
}

// 乱数生成器の取得
IMode::PRandom StageSelect::GetRandom() const
{
	return mpRandom;
}

// シーンの再起動
void StageSelect::Restart() const
{
	auto conf = boost::get<Conf::StageSelect>( Base::GetScene()->GetConf() );
	Scene::Manager::ChangeScene( 
		Util::Ptr<Scene::IScene>::Shared( new Scene::STG::STG( conf ) ) );
}


// 更新時の処理
void StageSelect::OnUpdate()
{
}

// 描画時の処理
void StageSelect::OnDraw() const
{
}