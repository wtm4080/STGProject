#include "PCH.h"
#include "Base.h"

#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/Enemy/IEnemy.h"

using namespace Game;
using namespace Mdl::STG;
using namespace MyShot;
using namespace Util::STG;

namespace
{
	// 初期HP
	static const float INIT_HP = 100.0f;
}


// コンストラクタ
Base::Base( Actor::Base::PMode pMode, const Vector2DF &pos, int radius, float baseDamage )
: Actor::Base( pMode, Hit::RectI( pos, radius * 2, radius * 2 ) )
, mHitCircle( pos, radius )
, mHitRect( pos, radius * 2, radius * 2 )
, mMaxHP( INIT_HP )
, mHP( INIT_HP )
, mNoDamage( false )
, mBaseDamage( baseDamage )
, mDamageRate( 1.0f )
, mDamageRateDec( 0.0f )
, mDamageRateMin( 1.0f )
, mPABaseDamage( baseDamage )
, mForcibleForPA( false )
{
}


// 更新
void Base::UpdateMiddle()
{
	UpdateHitPos();

	if( mHP <= 0 )
	{
		Destruct();
	}
	else
	{
		if( mDamageRate > mDamageRateMin )
		{
			mDamageRate -= mDamageRateDec;
		}
		else
		{
			mDamageRate = mDamageRateMin;
		}

		ApplyDamageToEnemy();
	}
}

// 敵にダメージを与える処理
void Base::ApplyDamageToEnemy()
{
	std::set<Enemy::PEnemy> enemies;
	GetActors().DetectEnemyHitAll( mHitRect, enemies );
	if( !enemies.empty() )
	{
		foreach( Enemy::PEnemy pEnemy, enemies )
		{
			pEnemy->Destruct( GetDamage() );
		}

		Destruct();
	}
}


// 当たり判定
bool Base::IsHit( const Hit::CircleI &hit ) const
{
	return mHitCircle.IsHit( hit );
}

bool Base::IsHit( const Hit::RectI &hit ) const
{
	return mHitRect.IsHit( hit );
}

// 破壊
void Base::Destruct()
{
	if( Actor::Base::IsValid() )
	{
		Actor::Base::SetValid( false );

		OnDestruct();
	}
}

void Base::Destruct( float hp )
{
	if( Actor::Base::IsValid() )
	{
		if( !mNoDamage )
		{
			mHP -= hp;
		}
		OnDamaged( hp );

		if( mHP <= 0 )
		{
			Actor::Base::SetValid( false );

			OnDestruct( hp );
		}
	}
}


// 最大HPの取得
float Base::GetMaxHP() const
{
	return mMaxHP;
}

// 最大HPの設定
void Base::SetMaxHP( float hp )
{
	mMaxHP = hp;
	if( mHP > mMaxHP )
	{
		mHP = mMaxHP;
	}
}

// HPの取得
float Base::GetHP() const
{
	return mHP;
}

// HPの設定
void Base::SetHP( float hp )
{
	mHP = hp;
}

// 当たり判定の半径の取得
float Base::GetHitRadius() const
{
	return static_cast<float>( mHitCircle.GetRadius() );
}

// 当たり判定の半径の設定
void Base::SetHitRadius( int radius )
{
	mHitCircle.SetRadius( radius );
	mHitRect.SetWidthHeight( radius * 2, radius * 2 );
	Actor::Base::SetValidRect( mHitRect );
}


const Hit::CircleI &Base::GetHitCircle() const
{
	return mHitCircle;
}

const Hit::RectI &Base::GetHitRect() const
{
	return mHitRect;
}


// 当たり判定の位置の更新
void Base::UpdateHitPos()
{
	mHitCircle.SetCenter( GetPosition() );
	mHitRect.SetPosition( GetPosition() );
}


// 敵へのダメージの取得
float Base::GetDamage() const
{
	return mBaseDamage * mHP/mMaxHP * mDamageRate;
}

// PrimalArmorへのダメージを取得
float Base::GetPADamage() const
{
	return mPABaseDamage * mDamageRate;
}

// PrimalArmorが展開されていない時でも強制的にダメージを与えるかどうかを取得
bool Base::IsForcibleForPA() const
{
	return mForcibleForPA;
}

// PrimalArmorが展開されていない時でも強制的にダメージを与えるかどうかを設定
void Base::SetForcibleForPA( bool forcible )
{
	mForcibleForPA = forcible;
}

// ダメージを受けないかどうかを取得
bool Base::IsNoDamage() const
{
	return mNoDamage;
}

// ダメージを受けないかどうかを設定
void Base::SetNoDamage( bool noDamage )
{
	mNoDamage = noDamage;
}

// 基本ダメージの取得
float Base::GetBaseDamage() const
{
	return mBaseDamage;
}

// 基本ダメージの設定
void Base::SetBaseDamage( float damage )
{
	mBaseDamage = damage;
}

// PrimalArmorへの基本ダメージを取得
float Base::GetPABaseDamage() const
{
	return mPABaseDamage;
}

// PrimalArmorへの基本ダメージを設定
void Base::SetPABaseDamage( float damage )
{
	mPABaseDamage = damage;
}

// ダメージ有効率の取得
float Base::GetDamageRate() const
{
	return mDamageRate;
}

// ダメージ有効率の設定
void Base::SetDamageRate( float rate )
{
	if( rate < mDamageRateMin )
	{
		mDamageRate = mDamageRateMin;
	}
	else
	{
		mDamageRate = rate;
	}
}

// ダメージ有効率の減少率の取得
float Base::GetDamageRateDec() const
{
	return mDamageRateDec;
}

// ダメージ有効率の減少率の設定
void Base::SetDamageRateDec( float dec )
{
	mDamageRateDec = dec;
}

// ダメージ有効率の最小値の取得
float Base::GetDamageRateMin() const
{
	return mDamageRateMin;
}

// ダメージ有効率の最小値の設定
void Base::SetDamageRateMin( float min )
{
	mDamageRateMin = min;

	if( mDamageRate < min )
	{
		mDamageRate = min;
	}
}