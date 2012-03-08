#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"


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
	class IStageSet
	{
	public:
		virtual void Update() = 0;
		virtual void Draw() const = 0;

		virtual bool IsEnd() const = 0;
		virtual void OnContinue() = 0;
		virtual void OnMyShipDestruction() = 0;
		virtual void OnMyShipRevival() = 0;

		virtual ~IStageSet() {}
	};
}
}
}
}
}