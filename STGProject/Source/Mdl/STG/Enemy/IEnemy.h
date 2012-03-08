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
namespace Enemy
{
	class IEnemy
		: virtual public Actor::IActor
	{
	public:
		// 当たり判定
		virtual bool IsHit( const Util::STG::Hit::RectI &hit ) const = 0;
		// 破壊(エフェクトあり)
		virtual void Destruct() = 0;
		virtual void Destruct( float hp ) = 0;

		// HPの取得
		virtual float GetHP() const = 0;
		// 当たり判定の取得
		virtual Util::STG::Hit::RectI GetHitRect() const = 0;

		// 当たり判定用の半径を取得
		virtual float GetHitRadius() const = 0;

		// PrimalArmorが生成されているかを取得
		virtual bool IsPAGenerated() const = 0;
		// PrimalArmorの総量を取得
		virtual float GetMaxPAAmount() const = 0;
		// PrimalArmorの残量を取得
		virtual float GetPAAmount() const = 0;

		virtual ~IEnemy() {}
	};
}
}
}
}