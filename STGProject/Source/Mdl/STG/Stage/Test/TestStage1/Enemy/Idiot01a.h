#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Idiot01.h"


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
	class Idiot01a
		: public Idiot01
	{
	public:
		Idiot01a( PStageSet pStageSet, 
			const Util::STG::Vector2DF &initPos, 
			const Util::STG::Vector2DF &targetPos, 
			float bulletSpeed = 4.0f, 
			float launchItv = 10.0f );

	private:
		float mBulletSpeed;

		virtual void Launch();
	};
}
}
}
}
}
}
}