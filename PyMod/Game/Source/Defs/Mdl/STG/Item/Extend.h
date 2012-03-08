#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Item
{
	class Extend
		: public Base
	{
	public:
		// コンストラクタ
		Extend( const Game::Util::STG::Vector2DF &pos, float angle = -90.0f );

	private:
		Game::Util::Sprite::DrawParameter mDrawParam;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();
		virtual void Effect() const;
	};
}
}
}
}