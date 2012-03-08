#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Stage/Event/Base.h"
#include "../StageCore.h"
#include "Util/RepeatCounter.h"


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
namespace Event
{
	class Ev01
		: public STG::Stage::Event::Base<StageCore>
	{
	public:
		Ev01( StageCore *pStage );

	private:
		virtual void OnUpdate();
		virtual void OnDraw() const;

		unsigned mFrameCount;

		Util::RepeatCounter mIdiot01aItv;
		bool mIdiot01aLeftAppear;

		Util::RepeatCounter mIdiot01bItv;
	};
}
}
}
}
}
}
}