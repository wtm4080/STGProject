#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "IEnemy.h"
#include "Mdl/STG/Actor/Base.h"
#include "Util/STG/Hit/Rect.h"


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
#pragma warning( disable:4250 )
	class Base
		: public Actor::Base
		, public IEnemy
	{
	public:
		// 当たり判定
		virtual bool IsHit( const Util::STG::Hit::RectI &hit ) const;
		// 破壊
		virtual void Destruct();
		virtual void Destruct( float hp );

		// HPの取得
		virtual float GetHP() const;
		// 当たり判定の取得
		virtual Util::STG::Hit::RectI GetHitRect() const;

		// 当たり判定用の半径を取得
		virtual float GetHitRadius() const;

		// PrimalArmorが生成されているかを取得
		virtual bool IsPAGenerated() const;
		// PrimalArmorの総量を取得
		virtual float GetMaxPAAmount() const;
		// PrimalArmorの残量を取得
		virtual float GetPAAmount() const;

	protected:
		// コンストラクタ
		Base( Actor::Base::PMode pMode, 
			const Util::STG::Hit::RectI &hit, float hp );
		const float mMaxHP;

		// HPの設定
		void SetHP( float hp );
		// 当たり判定の設定
		void SetHitRect( const Util::STG::Hit::RectI &hit );

	private:
		Util::STG::Hit::RectI mHitRect;
		float mHP;

		// 更新
		virtual void UpdateMiddle();

		virtual void OnDestruct() = 0;
		virtual void OnDamaged( float damage ) = 0;
		virtual void OnDestruct( float hp ) = 0;
	};
}
}
}
}