#include "PCH.h"
#include "Base.h"

#include "Defs/Ctrl/STG/STG.h"

using namespace Defs::Mdl::STG;
using namespace Enemy;
using namespace Game::Util::STG;
using namespace Game::Util::Consts;

namespace
{
	// 有効領域の余白
	static const int VALIDAREA_MARGIN = 300;
	// ダメージを受ける領域
	static const Hit::RectI DAMAGED_AREA( 0, 0, 
		SCREEN_SIZE.x - STG_INFAREA_SIZE.x, 
		SCREEN_SIZE.y, false );

	typedef Defs::Ctrl::STG::STG STGControl;
}


// コンストラクタ
Base::Base( const Hit::RectI &hit, float hp )
: Actor::Base( hit )
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
	return sqrt( Game::Util::Pow( widthHeight.x ) + Game::Util::Pow( widthHeight.y ) ) / 2;
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