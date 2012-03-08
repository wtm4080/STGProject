#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Detail/Holder.h"
#include "Data/MyShip.h"
#include "Data/Pause.h"
#include "Data/StageSet.h"
#include "Data/Stage.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Configuration
{
	class Manager
	{
	public:
		static void Initialize();
		static void Release();

		typedef Util::Ptr<Mdl::STG::MyShip::IMyShip>::Shared PMyShip;
		typedef Mdl::STG::MyShip::Parameter MyShipParam;
		static PMyShip GetMyShip( const Data::MyShip::Id &id, 
			const MyShipParam &param );
		typedef Util::Ptr<Mdl::STG::Stage::StageSet::IStageSet>::Shared PStageSet;
		typedef Mdl::STG::Stage::StageSet::Parameter StageSetParam;
		static PStageSet GetStageSet( const Data::StageSet::Id &id, 
			const StageSetParam &param );
		typedef Util::Ptr<Mdl::STG::Stage::Stage::IStage>::Shared PStage;
		typedef Mdl::STG::Stage::Stage::Parameter StageParam;
		static PStage GetStage( const Data::Stage::Id &id, 
			const StageParam &param );
		typedef Util::Ptr<View::STG::Pause::IPause>::Shared PPause;
		static PPause GetPauseView( const Data::StageSet::Id &stageSetId );

		typedef std::set<Data::MyShip> MyShipDataSet;
		static void GetMyShipDataSet( MyShipDataSet &dataSet );
		static Data::MyShip GetMyShipData( const Data::MyShip::Id &id );
		typedef std::set<Data::StageSet> StageSetDataSet;
		static void GetStageSetDataSet( StageSetDataSet &dataSet );
		static Data::StageSet GetStageSetData( const Data::StageSet::Id &id );
		typedef std::set<Data::Stage> StageDataSet;
		static void GetStageDataSet( const Data::StageSet::Id &stageSetId, 
			StageDataSet &dataSet );
		static Data::Stage GetStageData( const Data::Stage::Id &id );
		
		typedef Util::Ptr<Detail::IInstantiation<PMyShip, MyShipParam>>::Shared 
			PMyShipInstantiation;
		static Data::MyShip::Id RegisterMyShip( const Data::MyShip &data, 
			PMyShipInstantiation pInst );
		typedef Util::Ptr<Detail::IInstantiation<PStageSet, StageSetParam>>::Shared 
			PStageSetInstantiation;
		static Data::StageSet::Id RegisterStageSet( const Data::StageSet &data, 
			PStageSetInstantiation pInst );
		typedef Util::Ptr<Detail::IInstantiation<PStage, StageParam>>::Shared 
			PStageInstantiation;
		static Data::Stage::Id RegisterStage( const Data::Stage &data, 
			PStageInstantiation pInst );
		typedef Util::Ptr<Detail::IInstantiation<PPause, Data::PauseParam>>::Shared 
			PPauseViewInstantiation;
		static Data::Pause::Id RegisterPauseView( const Data::Pause &data, 
			PPauseViewInstantiation pInst );

	private:
		static Detail::Holder<Data::MyShip, PMyShip, MyShipParam> mMyShipHolder;
		static Detail::Holder<Data::StageSet, PStageSet, StageSetParam> mStageSetHolder;
		static Detail::Holder<Data::Stage, PStage, StageParam> mStageHolder;
		static Detail::Holder<Data::Pause, PPause, Data::PauseParam> mPauseViewHolder;

		static void ConfigurateMyShip();
		static void ConfigurateStage();
		static void ConfiguratePyMyShip();
		static void ConfiguratePyStage();
	};
}
}
}
}