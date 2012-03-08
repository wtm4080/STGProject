#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Auxs.h"
#include "Mdl/STG/Enemy/Base.h"
#include "Mdl/STG/Stage/Test/Forward.h"
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
	class Idiot01
		: public Mdl::STG::Enemy::Base
	{
	public:
		virtual Util::STG::Vector2DF GetPosition() const;
		virtual Util::STG::Vector2DF ApplyExternalForce( 
			const Util::STG::Vector2DF &vec );

	protected:
		typedef StageSetCore *PStageSet;
		Idiot01( PStageSet pStageSet, 
			const Util::STG::Vector2DF &initPos, 
			const Util::STG::Vector2DF &targetPos, 
			float speed = 6.0f );

		PStageSet mpStageSet;
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		Util::RepeatCounter mLaunchItv;
		Auxs mAuxs;

	private:
		Util::STG::Vector2DF mInitPos;
		Util::STG::Vector2DF mTargetPos;
		bool mArrivalTargetPos;
		unsigned mWaitCount;
		const float mSpeed;

		virtual void Launch() = 0;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();
		virtual void OnDestruct();
		virtual void OnDamaged( float damage );
		virtual void OnDestruct( float hp );
	};
}
}
}
}
}
}
}