#include "PCH.h"
#include "Manager.h"

using namespace Game;
using namespace Ctrl::STG::Configuration;

Detail::Holder<Data::MyShip, Manager::PMyShip, Manager::MyShipParam> Manager::mMyShipHolder;
Detail::Holder<Data::StageSet, Manager::PStageSet, Manager::StageSetParam> Manager::mStageSetHolder;
Detail::Holder<Data::Stage, Manager::PStage, Manager::StageParam> Manager::mStageHolder;
Detail::Holder<Data::Pause, Manager::PPause, Data::PauseParam> Manager::mPauseViewHolder;


void Manager::Initialize()
{
	ConfigurateMyShip();
	ConfigurateStage();
}

void Manager::Release()
{
	mMyShipHolder.Clear();
	mStageSetHolder.Clear();
	mStageHolder.Clear();
	mPauseViewHolder.Clear();
}


Manager::PMyShip Manager::GetMyShip( const Data::MyShip::Id &id, 
									const MyShipParam &param )
{
	return mMyShipHolder.Get( id, param );
}

Manager::PStageSet Manager::GetStageSet( const Data::StageSet::Id &id, 
										const StageSetParam &param )
{
	return mStageSetHolder.Get( id, param );
}

Manager::PStage Manager::GetStage( const Data::Stage::Id &id, 
								  const StageParam &param )
{
	return mStageHolder.Get( id, param );
}

Manager::PPause Manager::GetPauseView( const Data::StageSet::Id &stageSetId )
{
	return mPauseViewHolder.Get( stageSetId, Data::PauseParam() );
}


void Manager::GetMyShipDataSet( MyShipDataSet &dataSet )
{
	mMyShipHolder.GetDataSet( dataSet );
}

void Manager::GetStageSetDataSet( StageSetDataSet &dataSet )
{
	mStageSetHolder.GetDataSet( dataSet );
}

void Manager::GetStageDataSet( const Data::StageSet::Id &stageSetId, 
							  StageDataSet &dataSet )
{
	mStageHolder.GetDataSet( dataSet );

	for( auto itr = dataSet.begin(); itr != dataSet.end(); )
	{
		if( itr->GetStageSetId() != stageSetId )
		{
			dataSet.erase( itr++ );
		}
		else
		{
			itr++;
		}
	}
}

Data::MyShip Manager::GetMyShipData( const Data::MyShip::Id &id )
{
	return mMyShipHolder.GetData( id );
}

Data::StageSet Manager::GetStageSetData( const Data::StageSet::Id &id )
{
	return mStageSetHolder.GetData( id );
}

Data::Stage Manager::GetStageData( const Data::Stage::Id &id )
{
	return mStageHolder.GetData( id );
}


Data::MyShip::Id Manager::RegisterMyShip( const Data::MyShip &data, 
	PMyShipInstantiation pInst )
{
	return mMyShipHolder.Add( data, pInst );
}

Data::StageSet::Id Manager::RegisterStageSet( const Data::StageSet &data, 
	PStageSetInstantiation pInst )
{
	return mStageSetHolder.Add( data, pInst );
}

Data::Stage::Id Manager::RegisterStage( const Data::Stage &data, 
	PStageInstantiation pInst )
{
	return mStageHolder.Add( data, pInst );
}

Data::Pause::Id Manager::RegisterPauseView( const Data::Pause &data, 
	PPauseViewInstantiation pInst )
{
	return mPauseViewHolder.Add( data, pInst );
}


void Manager::ConfiguratePyMyShip()
{
	using namespace boost::python;

	import( "STG.MyShip.Conf" ).attr( "configurate" )();
}

void Manager::ConfiguratePyStage()
{
	using namespace boost::python;

	import( "STG.Stage.Conf" ).attr( "configurate" )();
}