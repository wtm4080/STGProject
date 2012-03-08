#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Forward.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
	class Auxs;

	namespace Actor
	{
		class IActor;
		class Base;
		class Animation;
		class FadeOut;

		typedef Util::Ptr<IActor>::Shared PActor;
		typedef Util::Ptr<Animation>::Shared PAnimation;
		typedef Util::Ptr<FadeOut>::Shared PFadeOut;

		namespace Particle
		{
			class Particle;
			class Creator;
			class Parameter;

			typedef Util::Ptr<Particle>::Shared PParticle;
		}
	}

	namespace Bullet
	{
		class IBullet;
		class Base;
		class Linear;
		class Rotate;

		namespace BulletML
		{
			class CreateParam;
			class MLActor;

			typedef Util::Ptr<MLActor>::Shared PMLActor;
		}

		namespace Launcher
		{
			class Circle;
			class NWay;
		}

		typedef Util::Ptr<IBullet>::Shared PBullet;
		typedef Util::Ptr<Linear>::Shared PLinear;
		typedef Util::Ptr<Rotate>::Shared PRotate;
	}

	namespace Enemy
	{
		class IEnemy;
		class Base;

		typedef Util::Ptr<IEnemy>::Shared PEnemy;
	}

	namespace Item
	{
		class IItem;
		class Base;
		class Extend;
		class PowerUp;
		class SupplySpAttack;

		typedef Util::Ptr<IItem>::Shared PItem;
		typedef Util::Ptr<Extend>::Shared PExtend;
		typedef Util::Ptr<PowerUp>::Shared PPowerUp;
		typedef Util::Ptr<SupplySpAttack>::Shared PSupplySpAttack;
	}

	namespace MyShip
	{
		class IMyShip;
		class Base;
		class Parameter;

		typedef Util::Ptr<IMyShip>::Shared PMyShip;
	}

	namespace MyShot
	{
		class IMyShot;
		class Base;

		typedef Util::Ptr<IMyShot>::Shared PMyShot;
	}

	namespace Resource
	{
		class Common;
		class Title;
	}

	namespace Stage
	{
		namespace Event
		{
			class IEvent;
			template <class Stage>
			class Base;

			typedef Util::Ptr<IEvent>::Shared PEvent;
		}

		namespace Stage
		{
			class IStage;
			template <class StageSet>
			class Base;
			class Parameter;

			typedef Util::Ptr<IStage>::Shared PStage;
		}

		namespace StageSet
		{
			class IStageSet;
			class Base;
			class Parameter;

			typedef Util::Ptr<IStageSet>::Shared PStageSet;
		}
	}
}
}
}