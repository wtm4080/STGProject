#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IActors.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Python
{
	class ISTG
	{
	public:
		typedef Util::Ptr<IActors>::Shared PActors;
		virtual PActors GetActors() const = 0;
		typedef Util::Ptr<Util::Input::STG::IController>::Shared PController;
		virtual PController GetController() const = 0;
		typedef Util::Random::PRandom PRandom;
		virtual PRandom GetRandom() const = 0;
		typedef Util::Ptr<Mdl::STG::Stage::Stage::IStage>::Shared PStage;
		virtual PStage GetNextStage() = 0;
		virtual bool GetDebugStrFlag() const = 0;
		virtual void SetDebugStrFlag( bool flag ) = 0;
		virtual void Restart() const = 0;
		virtual Selene::Uint64 GenObjectId() = 0;

		virtual ~ISTG() {}
	};
}
}
}
}