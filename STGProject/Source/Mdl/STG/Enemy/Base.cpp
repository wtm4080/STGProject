#include "PCH.h"
#include "Base.h"

#include "Ctrl/STG/Mode/IMode.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Enemy;
using namespace Util::STG;

namespace
{
	// 有効領域の余白
	static const int VALIDAREA_MARGIN = 300;
	// ダメージを受ける領域
	static const Hit::RectI DAMAGED_AREA( 0, 0, 
		Util::Consts::SCREEN_SIZE.x - Util::Consts::STG_INFAREA_SIZE.x, 
		Util::Consts::SCREEN_SIZE.y, false );
}


// コンストラクタ
Base::Base( PMode pMode, const Hit::RectI &hit, float hp )
: Actor::Base( pMode, hit )
, mHP( hp )
, mMaxHP( hp )
, mHitRect( hit )
{
	assert( mHP > 0 );

	Actor::Base::SetFrameCounting( false );
	Actor::Base::SetValidAreaMargin( VALIDAREA_MARGIN );
}


// 更新
void Base::UpdateMiddle()
{
	mHitRect.SetPosition( GetPosition() );

	if( mHP <= 0 )
	{
		Destruct();
	}
}


// 当たり判定
bool Base::IsHit( const Hit::RectI &hit ) const
{
	return mHitRect.IsHit( hit );
}

// 破壊
void Base::Destruct()
{
	if( mHP > 0 )
	{
		Actor::Base::SetValid( false );

		OnDestruct();
	}
}

void Base::Destruct( float hp )
{
	if( mHP > 0 && mHitRect.IsHit( DAMAGED_AREA ) )
	{
		mHP -= hp;
		OnDamaged( hp );

		if( mHP <= 0 )
		{
			Actor::Base::SetValid( false );

			OnDestruct( hp );
		}
		else if( mHP > mMaxHP )
		{
			mHP = mMaxHP;
		}
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


// 当たり判定の取得
Hit::RectI Base::GetHitRect() const
{
	return mHitRect;
}

// 当たり判定の設定
void Base::SetHitRect( const Hit::RectI &hit )
{
	mHitRect = hit;
	Actor::Base::SetValidRect( hit );
}


// 当たり判定用の半径の取得
float Base::GetHitRadius() const
{
	Vector2DF widthHeight( mHitRect.GetWidthHeight() );
	return sqrt( Util::Pow( widthHeight.x ) + Util::Pow( widthHeight.y ) ) / 2;
}


// PrimalArmorが生成されているかを取得
bool Base::IsPAGenerated() const
{
	return false;
}

// PrimalArmorの総量を取得
float Base::GetMaxPAAmount() const
{
	return 0;
}

// PrimalArmorの残量を取得
float Base::GetPAAmount() const
{
	return 0;
}