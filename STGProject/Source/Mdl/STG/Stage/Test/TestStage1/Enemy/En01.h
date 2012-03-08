#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Mdl/STG/Auxs.h"
#include "Mdl/STG/Bullet/Launcher/Circle.h"
#include "Mdl/STG/Bullet/Launcher/NWay.h"
#include "Mdl/STG/Enemy/Base.h"
#include "Mdl/STG/Enemy/HPGauge.h"
#include "Mdl/STG/Stage/Test/Forward.h"
#include "Util/FunctionQueue.h"
#include "Util/RepeatCounter.h"
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
	class En01
		: public Mdl::STG::Enemy::Base
	{
	public:
		typedef StageSetCore *PStageSet;
		En01( PStageSet pStageSet );

		virtual Util::STG::Vector2DF GetPosition() const;
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

	private:
		PStageSet mpStageSet;
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		float mRotDegree;

		// Phase1
		float mLaunchAngle;
		Util::RepeatCounter mLaunchItv;
		Bullet::Launcher::Circle mCircleLauncher;

		Util::RepeatQueue mAimingTiming;
		float mTargetAngle;
		unsigned mAimingBulletCount;
		Bullet::Launcher::NWay mAimingLauncher;

		// Phase2
		Util::RepeatCounter mAcceledItv;
		unsigned mRandomWaitCount;
		Bullet::Launcher::Circle mRandomLauncher;
		Util::RepeatCounter mRandomLaunchItv;

		// Phase3
		unsigned mPhase3Count;
		Util::RepeatCounter mExplosionItv;

		Mdl::STG::Enemy::HPGauge mHPGauge;
		Auxs mAuxs;
		Util::FunctionQueue mPhaseQueue;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();
		virtual void OnDestruct();
		virtual void OnDamaged( float damage );
		virtual void OnDestruct( float hp );

		bool Phase1();
		bool EraseBullet();
		bool Phase2();
		bool Phase3();

		// Phase1
		void LaunchCircle( float angle );
		void UpdateTarget();
		void LaunchAiming();
		void GenerateAiming( float angle );

		// Phase2
		void LaunchRandom( float angle );
	};
}
}
}
}
}
}
}