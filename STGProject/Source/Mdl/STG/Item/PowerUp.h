#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"
#include "Mdl/STG/Auxs.h"
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
namespace Item
{
	class PowerUp
		: public Base
	{
	public:
		// コンストラクタ
		PowerUp( Actor::Base::PMode pMode, 
			const Util::STG::Vector2DF &pos, float angle = 270.0f );

	private:
		Util::Sprite::DrawParameter mDrawParam;
		Auxs mAuxs;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();
		virtual void Effect() const;
	};
}
}
}
}