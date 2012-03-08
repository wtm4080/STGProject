#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Auxs.h"
#include "Mdl/STG/Enemy/Base.h"
#include "Mdl/STG/Stage/Test/Forward.h"
#include "Util/RepeatQueue.h"
#include "Util/Sprite/DrawParameter.h"
#include "Util/STG/Locator/Linear.h"


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
namespace Test
{
namespace TestStage1
{
namespace Enemy
{
	class Idiot02
		: public Mdl::STG::Enemy::Base
	{
	public:
		typedef StageSetCore *PStageSet;
		Idiot02( PStageSet pStageSet, 
			const Util::STG::Vector2DF &initPos, 
			bool dropPowerUp = false );

		virtual Util::STG::Vector2DF GetPosition() const;
		virtual Util::STG::Vector2DF ApplyExternalForce( 
			const Util::STG::Vector2DF &vec );

	private:
		PStageSet mpStageSet;
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		Util::RepeatQueue mLaunchTiming;
		float mTargetAngle;
		Auxs mAuxs;
		bool mDropPowerUp;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();
		virtual void OnDestruct();
		virtual void OnDamaged( float damage );
		virtual void OnDestruct( float hp );

		void UpdateTarget();
		void LaunchAiming();
	};
}
}
}
}
}
}
}