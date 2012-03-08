#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Mdl/STG/Actor/IActor.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace MyShot
{
	class IMyShot
		: virtual public Actor::IActor
	{
	public:
		// 当たり判定
		virtual bool IsHit( const Util::STG::Hit::CircleI &hit ) const = 0;
		virtual bool IsHit( const Util::STG::Hit::RectI &hit ) const = 0;
		// 破壊
		virtual void Destruct() = 0;
		virtual void Destruct( float hp ) = 0;

		// HPの取得
		virtual float GetHP() const = 0;
		// 当たり判定の半径の取得
		virtual float GetHitRadius() const = 0;

		// PrimalArmorへのダメージを取得
		virtual float GetPADamage() const = 0;
		// PrimalArmorが展開されていない時でも強制的にダメージを与えるかどうかを取得
		virtual bool IsForcibleForPA() const = 0;

		virtual ~IMyShot() {}
	};
}
}
}
}