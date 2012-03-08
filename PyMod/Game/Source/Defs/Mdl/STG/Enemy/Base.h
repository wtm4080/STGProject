#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Enemy/IEnemy.h"
#include "Defs/Mdl/STG/Actor/Base.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------
namespace Defs
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
		, public Game::Mdl::STG::Enemy::IEnemy
	{
	public:
		// 当たり判定
		virtual bool IsHit( const Game::Util::STG::Hit::RectI &hit ) const;
		// 破壊
		virtual void Destruct();
		virtual void Destruct( float hp );

		// HPの取得
		virtual float GetHP() const;
		// HPの設定
		void SetHP( float hp );
		// 当たり判定の取得
		virtual Game::Util::STG::Hit::RectI GetHitRect() const;
		// 当たり判定の設定
		void SetHitRect( const Game::Util::STG::Hit::RectI &hit );

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
		Base( const Game::Util::STG::Hit::RectI &hit, float hp );

	private:
		Game::Util::STG::Hit::RectI mHitRect;
		float mHP;
		const float mMaxHP;

		// 更新
		virtual void UpdateMiddle();

		virtual void OnDestruct() = 0;
		virtual void OnDamaged( float damage ) {}
		virtual void OnDestruct( float hp ) = 0;
	};
}
}
}
}