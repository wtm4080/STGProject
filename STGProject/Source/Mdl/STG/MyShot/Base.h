#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "IMyShot.h"
#include "Mdl/STG/Actor/Base.h"
#include "Util/STG/Hit/Circle.h"
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
namespace MyShot
{
#pragma warning( disable:4250 )
	class Base
		: public Actor::Base
		, public IMyShot
	{
	public:
		// 当たり判定
		virtual bool IsHit( const Util::STG::Hit::CircleI &hit ) const;
		virtual bool IsHit( const Util::STG::Hit::RectI &hit ) const;
		// 破壊
		virtual void Destruct();
		virtual void Destruct( float hp );

		// 最大HPの取得
		float GetMaxHP() const;
		// HPの取得
		virtual float GetHP() const;
		// 当たり判定の半径の取得
		virtual float GetHitRadius() const;

		// 敵へのダメージの取得
		virtual float GetDamage() const;
		// PrimalArmorへのダメージを取得
		virtual float GetPADamage() const;
		// PrimalArmorが展開されていない時でも強制的にダメージを与えるかどうかを取得
		virtual bool IsForcibleForPA() const;

	protected:
		// コンストラクタ
		Base( Actor::Base::PMode pMode, 
			const Util::STG::Vector2DF &pos, int radius, float baseDamage );

		// 最大HPの設定
		void SetMaxHP( float hp );
		// HPの設定
		void SetHP( float hp );

		// 当たり判定の位置の更新
		void UpdateHitPos();
		// 当たり判定の半径の設定
		void SetHitRadius( int radius );

		const Util::STG::Hit::CircleI &GetHitCircle() const;
		const Util::STG::Hit::RectI &GetHitRect() const;

		// PrimalArmorが展開されていない時でも強制的にダメージを与えるかどうかを設定
		void SetForcibleForPA( bool forcible );
		// ダメージを受けないかどうかを取得
		bool IsNoDamage() const;
		// ダメージを受けないかどうかを設定
		void SetNoDamage( bool noDamage );
		// 基本ダメージの取得
		float GetBaseDamage() const;
		// 基本ダメージの設定
		void SetBaseDamage( float damage );
		// PrimalArmorへの基本ダメージを取得
		float GetPABaseDamage() const;
		// PrimalArmorへの基本ダメージを設定
		void SetPABaseDamage( float damage );
		// ダメージ有効率の取得
		float GetDamageRate() const;
		// ダメージ有効率の設定
		void SetDamageRate( float rate );
		// ダメージ有効率の減少率の取得
		float GetDamageRateDec() const;
		// ダメージ有効率の減少率の設定
		void SetDamageRateDec( float dec );
		// ダメージ有効率の最小値の取得
		float GetDamageRateMin() const;
		// ダメージ有効率の最小値の設定
		void SetDamageRateMin( float min );

	private:
		Util::STG::Hit::CircleI mHitCircle;
		Util::STG::Hit::RectI mHitRect;
		float mMaxHP, mHP;
		bool mNoDamage;
		float mBaseDamage, mDamageRate, mDamageRateDec, mDamageRateMin;
		float mPABaseDamage;
		bool mForcibleForPA;

		// 更新
		virtual void UpdateMiddle();
		// 敵にダメージを与える処理
		virtual void ApplyDamageToEnemy();

		virtual void OnDestruct() = 0;
		virtual void OnDamaged( float damage ) {}
		virtual void OnDestruct( float hp ) = 0;
	};
}
}
}
}