#include "PCH.h"
#include "Holder.h"

#include "Ctrl/STG/Configuration/Manager.h"

using namespace Game;
using namespace Ctrl::STG;
using namespace Mode::Conf;


// コンストラクタ
Holder::Holder()
	: mActors( Selene::RectF( 
	0, 0, 
	static_cast<float>( Util::Consts::SCREEN_SIZE.x - Util::Consts::STG_INFAREA_SIZE.x ), 
	static_cast<float>( Util::Consts::SCREEN_SIZE.y ) ) )
	, mCurrentStageData( 0 )
{
}


// STG構成オブジェクトの取得
Actors &Holder::GetActors()
{
	return mActors;
}

const Actors &Holder::GetActors() const
{
	return mActors;
}


// ステージセットの取得
PStageSet Holder::GetStageSet() const
{
	return mpStageSet;
}

// ステージセットの設定
void Holder::SetStageSet( PStageSet pStageSet )
{
	mpStageSet = pStageSet;
}

// ステージセットの初期化
void Holder::InitStageSet( const StageSetParam &param, 
						  const Configuration::Data::StageSet::Id &stageSetId )
{
	mpStageSet = Configuration::Manager::GetStageSet( stageSetId, param );

	assert( mpStageSet );
}


// ステージ情報キューの取得
StageDataQueue &Holder::GetStageDataQueue()
{
	return mStageDataQueue;
}

// 次のステージを取得する
PStage Holder::GetNextStage( const StageParam &param )
{
	if( !mStageDataQueue.empty() )
	{
		PStage pStage = Configuration::Manager::GetStage( 
			mStageDataQueue.front().GetId(), param );
		assert( pStage );

		mCurrentStageData = mStageDataQueue.front();

		mStageDataQueue.pop();

		return pStage;
	}
	else
	{
		return PStage();
	}
}

// ステージ情報キューの初期化
void Holder::InitStageDataQueue( const Configuration::Data::StageSet::Id &stageSetId )
{
	while( !mStageDataQueue.empty() )
	{
		mStageDataQueue.pop();
	}

	Configuration::Manager::StageDataSet dataSet;
	Configuration::Manager::GetStageDataSet( stageSetId, dataSet );
	assert( !dataSet.empty() );

	foreach( const Configuration::Data::Stage &data, dataSet )
	{
		mStageDataQueue.push( data );
	}
}

// 現在のステージデータの取得
const StageData &Holder::GetCurrentStageData() const
{
	return mCurrentStageData;
}


// 自機の初期化
void Holder::InitMyShip( const MyShipParam &param, 
						const Configuration::Data::MyShip::Id &myShipId )
{
	mActors.SetMyShip( 
		Configuration::Manager::GetMyShip( myShipId, param ) );

	assert( mActors.GetMyShip() );
}