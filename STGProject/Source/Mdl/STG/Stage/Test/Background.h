#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Forward.h"
#include "Util/Sprite/DrawParameter.h"


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
	class Background
	{
	public:
		typedef StageSetCore *PStageSet;
		Background( PStageSet pStageSet );

		void Update();
		void Draw() const;

		static const float INIT_SCROLL_AMOUNT;
		float GetScrollAmount() const;
		void SetScrollAmount( float amount = INIT_SCROLL_AMOUNT );

	private:
		PStageSet mpStageSet;
		Util::Sprite::DrawParameter mDrawParam1;
		Util::Sprite::DrawParameter mDrawParam2;
		float mScrollAmount;

		void ScrollV( Util::Sprite::DrawParameter &param1, 
			const Util::Sprite::DrawParameter &param2, bool after = false );
		void ScrollH( Util::Sprite::DrawParameter &param );
	};
}
}
}
}
}