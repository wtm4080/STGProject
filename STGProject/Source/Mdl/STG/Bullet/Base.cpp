#include "PCH.h"
#include "Base.h"

#include "Ctrl/Scene/STG/STG.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/Resource/Common.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Bullet;
using namespace Util::STG;
using namespace Selene;

namespace
{
	// 初期HP
	static const float INIT_HP = 100.0f;
}


// コンストラクタ
Base::Base( Actor::Base::PMode pMode, const Vector2DF &pos, int radius )
: Actor::Base( pMode, Util::STG::Hit::RectI( pos, radius * 2, radius * 2 ) )
, mHitCircle( pos, radius )
, mHitRect( pos, radius * 2, radius * 2 )
, mHP( INIT_HP )
{
	mDamagedDrawParam.SetTexture( 
		Actor::Base::GetMode()->GetScene()->GetResource()->GetBulletDamagedEffect() );
	mDamagedDrawParam.SetSrc( Resource::Common::BULLET_DAMAGED_EFFECT.GetRect() );
	mDamagedDrawParam.SetDst( pos.MakeRect( GetHitRadius()*4, GetHitRadius()*4 ) );
	mDamagedDrawParam.SetPriority( View::STG::PRI_ENEMYBULLET_DAMAGED );
	mDamagedDrawParam.SetColor( ColorF( 1.0f, 1.0f, 1.0f, 0 ) );
	mDamagedDrawParam.SetAlphaBlend( Util::Sprite::AB_ADD );
}


// 更新
void Base::Update()
{
	Actor::Base::Update();
	UpdateDamagedDraw();
}

void Base::UpdateMiddle()
{
	UpdateHitPos();

	if( mHP <= 0 )
	{
		Destruct();
	}
}

void Base::UpdateDamagedDraw()
{
	mDamagedDrawParam.SetDst( 
		GetPosition().MakeRect( GetHitRadius()*4, GetHitRadius()*4 ) );
	{
		ColorF color = mDamagedDrawParam.GetColor();
		if( color.a > 0 )
		{
			color.a -= 0.01f;
		}
		else
		{
			color.a = 0;
		}
		mDamagedDrawParam.SetColor( color );
	}
}

void Base::DrawMiddle() const
{
	if( mDamagedDrawParam.GetColor().a > 0 )
	{
		Util::Sprite::Manager::Draw( mDamagedDrawParam );
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
	if( mHP > 0 )
	{
		Actor::Base::SetValid( false );

		OnDestruct();
	}
}

void Base::Destruct( float hp )
{
	if( mHP > 0 )
	{
		mHP -= hp;
		OnDamaged( hp );
		{
			static const float MAX_ALPHA = 0.4f;
			auto color = mDamagedDrawParam.GetColor();
			if( color.a < MAX_ALPHA )
			{
				color.a += 0.1f;
			}
			else
			{
				color.a = MAX_ALPHA;
			}
			mDamagedDrawParam.SetColor( color );
		}

		if( mHP <= 0 )
		{
			Actor::Base::SetValid( false );

			OnDestruct( hp );
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


// 当たり判定の位置の更新
void Base::UpdateHitPos()
{
	mHitCircle.SetCenter( GetPosition() );
	mHitRect.SetPosition( GetPosition() );
}