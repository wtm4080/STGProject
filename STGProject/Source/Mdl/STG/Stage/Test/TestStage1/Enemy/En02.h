#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Mdl/STG/Auxs.h"
#include "Mdl/STG/Enemy/Base.h"
#include "Mdl/STG/Enemy/HPGauge.h"
#include "Mdl/STG/Stage/Test/Forward.h"
#include "Util/FunctionQueue.h"
#include "Util/RepeatCounter.h"
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
	class En02
		: public Mdl::STG::Enemy::Base
	{
	public:
		typedef StageCore *PStage;
		En02( PStage pStage );

		virtual Util::STG::Vector2DF GetPosition() const;
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

	private:
		PStage mpStage;
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		Mdl::STG::Enemy::HPGauge mHPGauge;
		Auxs mAuxs;
		Util::FunctionQueue mPhaseQueue;

		// Phase1
		Bullet::BulletML::PMLActor mpMLActor;
		Util::RepeatCounter mMLBulletItv;

		// LastPhase
		unsigned mLastPhaseCount;
		Util::RepeatCounter mExplosionItv;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();
		virtual void OnDestruct();
		virtual void OnDamaged( float damage );
		virtual void OnDestruct( float hp );

		bool Phase1();
		bool EraseBullet();
		bool LastPhase();
	};
}
}
}
}
}
}
}