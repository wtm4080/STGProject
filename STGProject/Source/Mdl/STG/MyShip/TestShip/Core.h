#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/MyShip/Base.h"
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
namespace MyShip
{
namespace TestShip
{
	class Core
		: public Base
	{
	public:
		Core( const Parameter &param );

		virtual void DrawInfArea( const Util::STG::Vector2DF &basePos ) const;

		virtual int GetPower() const;
		virtual bool SupplyPower();
		virtual int GetSpAttack() const;
		virtual bool SupplySpAttack();

	private:
		Util::Sprite::DrawParameter mShipDrawParam;
		Util::Sprite::PTexture mpLaserTexture;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnDestruction();
		virtual void OnRevival();
		virtual void OnContinue();

		virtual Util::STG::Vector2DI GetShipSize() const;

		virtual int GetBarrierRadius() const;
		virtual int GetItemRetrieveRadius() const;

		virtual float GetMoveSpeed() const;

		virtual void Shot();
		virtual void SpecialAttack();
	};
}
}
}
}
}