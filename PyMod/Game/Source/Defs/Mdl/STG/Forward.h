#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Forward.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
	namespace Actor
	{
		class Animation;
		typedef Game::Util::Ptr<Animation>::Shared PAnimation;
		class FadeOut;
		typedef Game::Util::Ptr<FadeOut>::Shared PFadeOut;

		namespace Particle
		{
			class Particle;
			typedef Game::Util::Ptr<Particle>::Shared PParticle;
		}
	}

	namespace Bullet
	{
		namespace BulletML
		{
			class MLActor;
			typedef Game::Util::Ptr<MLActor>::Shared PMLActor;
		}

		template <class Locator>
		class Simple;
		typedef Simple<Game::Util::STG::Locator::LinearF> Linear;
		typedef Game::Util::Ptr<Linear>::Shared PLinear;
		typedef Simple<Game::Util::STG::Locator::RotateF> Rotate;
		typedef Game::Util::Ptr<Rotate>::Shared PRotate;
	}

	namespace Enemy
	{
	}

	namespace Item
	{
		class Extend;
		typedef Game::Util::Ptr<Extend>::Shared PExtend;
		class PowerUp;
		typedef Game::Util::Ptr<PowerUp>::Shared PPowerUp;
		class SpAttack;
		typedef Game::Util::Ptr<SpAttack>::Shared PSpAttack;
	}

	namespace MyShip
	{
	}

	namespace MyShot
	{
		class Linear;
		typedef Game::Util::Ptr<Linear>::Shared PLinear;
	}
}
}
}