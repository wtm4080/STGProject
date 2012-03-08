#include "PCH.h"
#include "Base.h"
#include "Parameter.h"

#include "Ctrl/Scene/STG/STG.h"
#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/Stage/Stage/IStage.h"

using namespace Game;
using namespace Mdl::STG::Stage::StageSet;
namespace py = boost::python;
using namespace Selene;


void Base::Update()
{
	OnUpdate();

	if( mpCurrentStage )
	{
		mpCurrentStage->Update();
	}

	if( !mpCurrentStage || mpCurrentStage->IsEnd() )
	{
		mpCurrentStage = GetMode()->GetNextStage();

		mScoreManager.attr( "write" )();
	}

	mInfArea.attr( "update" )();
	mScoreManager.attr( "update" )();
}

void Base::Draw() const
{
	OnDraw();

	if( mpCurrentStage )
	{
		mpCurrentStage->Draw();
	}

	mInfArea.attr( "draw" )();
}


bool Base::IsEnd() const
{
	return !mpCurrentStage;
}

void Base::OnContinue()
{
	mScoreManager.attr( "reset" )();
}

void Base::OnMyShipDestruction()
{
}

void Base::OnMyShipRevival()
{
	mScoreManager.attr( "addRate" )( -( GetScoreRate() / 2 ) );
}


Base::Base( const Parameter &param )
: mpMode( param.GetMode() )
, mInfArea()
, mScoreManager()
{
	assert( mpMode );

	mScoreManager = 
		py::import( "STG.Stage.BasicScoreManager" )
		.attr( "BasicScoreManager" )( param.GetStageSetId() );
	mScoreManager.attr( "read" )();
	mInfArea = 
		py::import( "STG.Stage.BasicInfArea" )
		.attr( "BasicInfArea" )( mScoreManager );
}


// STG構成オブジェクトの取得
Ctrl::STG::Actors &Base::GetActors() const
{
	return mpMode->GetActors();
}

// プレイモードクラスの取得
Parameter::PMode Base::GetMode() const
{
	return mpMode;
}

// 共通リソースの取得
Base::PCommonResource Base::GetCommonResource() const
{
	return mpMode->GetScene()->GetResource();
}


Uint64 Base::GetScore() const
{
	return py::extract<Uint64>( mScoreManager.attr( "score" ) );
}

Uint64 Base::GetHighScore() const
{
	return py::extract<Uint64>( mScoreManager.attr( "highScore" ) );
}

float Base::GetScoreRate() const
{
	return py::extract<float>( mScoreManager.attr( "rate" ) );
}

void Base::AddScore( Uint64 score, bool applyRate )
{
	mScoreManager.attr( "addScore" )( score, applyRate );
}

void Base::AddRate( float rate, bool resetDecWaitCount )
{
	mScoreManager.attr( "addRate" )( rate, resetDecWaitCount );
}