#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "IStageSet.h"
#include <boost/python.hpp>
#include <selene.h>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Stage
{
namespace StageSet
{
	class Base
		: public IStageSet
	{
	public:
		virtual void Update();
		virtual void Draw() const;

		virtual bool IsEnd() const;
		virtual void OnContinue();
		virtual void OnMyShipDestruction();
		virtual void OnMyShipRevival();

		// プレイモードクラスの取得
		typedef Ctrl::STG::Mode::IMode *PMode;
		PMode GetMode() const;
		// 共通リソースの取得
		typedef Util::Ptr<Mdl::STG::Resource::Common>::Shared PCommonResource;
		PCommonResource GetCommonResource() const;
		// STG構成オブジェクトの取得
		Ctrl::STG::Actors &GetActors() const;

		Selene::Uint64 GetScore() const;
		Selene::Uint64 GetHighScore() const;
		float GetScoreRate() const;
		void AddScore( Selene::Uint64 score, bool applyRate = true );
		void AddRate( float rate, bool resetDecWaitCount = true );

	protected:
		Base( const Parameter &param );

		virtual void OnUpdate() = 0;
		virtual void OnDraw() const = 0;

	private:
		PMode mpMode;
		typedef Util::Ptr<Stage::IStage>::Shared PStage;
		PStage mpCurrentStage;
		boost::python::object mInfArea;
		boost::python::object mScoreManager;
	};
}
}
}
}
}