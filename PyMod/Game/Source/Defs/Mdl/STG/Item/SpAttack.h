#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
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
	class SpAttack
		: public Base
	{
	public:
		// コンストラクタ
		SpAttack( const Game::Util::STG::Vector2DF &pos, float angle = -90.0f );

		void SetEffectCallback( const boost::python::object &callback );

	private:
		Game::Util::Sprite::DrawParameter mDrawParam;
		boost::python::object mEffectCallback;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();
		virtual void Effect() const;
	};
}
}
}
}