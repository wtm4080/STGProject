#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Configuration/Data/MyShip.h"
#include "Ctrl/STG/Configuration/Data/StageSet.h"
#include "Ctrl/STG/Configuration/Data/Stage.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Mode
{
namespace Conf
{
	typedef Util::Ptr<Mdl::STG::Stage::StageSet::IStageSet>::Shared PStageSet;
	typedef Mdl::STG::Stage::StageSet::Parameter StageSetParam;
	typedef Configuration::Data::Stage StageData;
	typedef std::queue<StageData> StageDataQueue;
	typedef Mdl::STG::Stage::Stage::Parameter StageParam;
	typedef Util::Ptr<Mdl::STG::Stage::Stage::IStage>::Shared PStage;
	typedef Mdl::STG::MyShip::Parameter MyShipParam;

	class Holder
	{
	public:
		// コンストラクタ
		Holder();

		// STG構成オブジェクトの取得
		Actors &GetActors();
		const Actors &GetActors() const;

		// ステージセットの取得
		PStageSet GetStageSet() const;
		// ステージセットの設定
		void SetStageSet( PStageSet pStageSet );
		// ステージセットの初期化
		void InitStageSet( const StageSetParam &param, 
			const Configuration::Data::StageSet::Id &stageSetId );

		// ステージ情報キューの取得
		StageDataQueue &GetStageDataQueue();
		// 次のステージを取得する
		PStage GetNextStage( const StageParam &param );
		// ステージ情報キューの初期化
		void InitStageDataQueue( const Configuration::Data::StageSet::Id &stageSetId );
		// 現在のステージデータの取得
		const StageData &GetCurrentStageData() const;

		// 自機の初期化
		void InitMyShip( const MyShipParam &param, 
			const Configuration::Data::MyShip::Id &myShipId );

	private:
		Actors mActors;
		PStageSet mpStageSet;
		StageDataQueue mStageDataQueue;
		StageData mCurrentStageData;
	};
}
}
}
}
}