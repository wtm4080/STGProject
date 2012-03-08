#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Idiot01.h"
#include "Mdl/STG/Bullet/Launcher/NWay.h"


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
	class Idiot01b
		: public Idiot01
	{
	public:
		Idiot01b( PStageSet pStageSet, 
			const Util::STG::Vector2DF &initPos, 
			const Util::STG::Vector2DF &targetPos );

	private:
		Bullet::Launcher::NWay mLauncher;

		virtual void Launch();

		void Launch2Way( float angle );
	};
}
}
}
}
}
}
}