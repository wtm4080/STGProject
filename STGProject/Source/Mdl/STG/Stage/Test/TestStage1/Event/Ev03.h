#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Stage/Event/Base.h"
#include "../StageCore.h"


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
	class Ev03
		: public STG::Stage::Event::Base<StageCore>
	{
	public:
		Ev03( StageCore *pStage );

	private:
		bool mEnemyCreated;
		Util::Ptr<STG::Enemy::IEnemy>::Weak mwpEnemy;
		unsigned mAfterDestroyedCount;

		virtual void OnUpdate();
		virtual void OnDraw() const;
	};
}
}
}
}
}
}
}