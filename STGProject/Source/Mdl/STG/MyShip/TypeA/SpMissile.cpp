#include "PCH.h"
#include "SpMissile.h"
#include "Resource.h"

#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/Actor/Animation.h"
#include "Mdl/STG/Bullet/IBullet.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace MyShip::TypeA;
using namespace Util::STG;
using namespace Selene;

namespace
{
	static const int RADIUS = 16;
	static const Vector2DF MISSILE_SIZE( 64, 64 );
	static const float INIT_SPEED = 0.1f;
	static const float MAX_SPEED = 25.0f;
	static const float INIT_ACCEL = 2.0f;
	static const float DAMAGE = 2.0f;

	static const Vector2DF EXPLODE_SIZE( 96*3.0f, 96*3.0f );
	static const unsigned EXPLODE_FRAMENUM = 90;
	static const int EXPLODE_RADIUS = static_cast<int>( 96 );

	static const Hit::RectI VALID_AREA( 
		0, 0, 
		Util::Consts::SCREEN_SIZE.x - Util::Consts::STG_INFAREA_SIZE.x, 
		Util::Consts::SCREEN_SIZE.y, false );
}


// コンストラクタ
SpMissile::SpMissile( Actor::Base::PMode pMode, 
	const Vector2DF &pos, float angle, 
	Util::Sprite::PTexture pMissileTexture, 
	Util::Sprite::PTexture pExplosionTexture )
	: Base( pMode, pos, RADIUS, DAMAGE )
	, mLocator( pos )
	, mExplodeFlag( false )
{
	assert( pMissileTexture );
	assert( pExplosionTexture );

	mLocator.GetSpeed().SetUnitVector( angle ) *= INIT_SPEED;
	mLocator.GetAccel().SetUnitVector( angle ) *= INIT_ACCEL;

	Base::SetNoDamage( true );

	mDrawParam.SetTexture( pMissileTexture );
	mDrawParam.SetSrc( Resource::MISSILE.GetRect() );
	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( MISSILE_SIZE ) );
	mDrawParam.SetPriority( View::STG::PRI_MYSHOT );
	mDrawParam.SetRotDegree( mLocator.GetSpeed().GetAngle() + 90.0f );

	{
		Util::Sprite::DrawParameter drawParam;
		drawParam.SetTexture( pExplosionTexture );
		drawParam.SetDst( mLocator.GetPosition().MakeRect( EXPLODE_SIZE ) );
		drawParam.SetPriority( View::STG::PRI_EXPLOSION );
		drawParam.SetAlphaBlend( Util::Sprite::AB_ADD );
		drawParam.SetFiltering( false );
		drawParam.SetRotDegree( pMode->GetRandom()->GetFloat( -180.0f, 180.0f ) );

		mExplodeAnimation = 
			Util::Sprite::Animation( Point2DI( 96, 96 ), 16, 1.5f, drawParam );
		mExplodeAnimation.SetFramePos( 4 );
	}

	mInValidArea = Base::IsHit( VALID_AREA );
}


// 位置の取得
Vector2DF SpMissile::GetPosition() const
{
	return mLocator.GetPosition();
}

// 外力の適用
Vector2DF SpMissile::ApplyExternalForce( const Vector2DF &vec )
{
	if( mExplodeFlag )
	{
		return Vector2DF();
	}
	else
	{
		return mLocator.ApplyExternalForce( vec );
	}
}


void SpMissile::OnUpdate()
{
	if( !mExplodeFlag )
	{
		mLocator.Update();
		if( mLocator.GetSpeed().GetAbs() > MAX_SPEED )
		{
			mLocator.GetSpeed().Normalize() *= MAX_SPEED;
		}

		bool inValidAreaNow = Base::IsHit( VALID_AREA );

		if( mInValidArea && !inValidAreaNow )
		{
			Base::Destruct();
		}
		else
		{
			mInValidArea = inValidAreaNow;
		}
	}

	if( !mExplodeFlag )
	{
		mDrawParam.SetDst( mLocator.GetPosition().MakeRect( MISSILE_SIZE ) );
		mDrawParam.SetRotDegree( mLocator.GetSpeed().GetAngle() + 90.0f );
	}
	else
	{
		if( mExplodeFrameCount > 0 )
		{
			mExplodeAnimation.SetDst( 
				mLocator.GetPosition().MakeRect( EXPLODE_SIZE ) );
			mExplodeAnimation.SetRotDegree( 
				Base::GetMode()->GetRandom()->GetFloat( -180.0f, 180.0f ) );

			mExplodeFrameCount--;

			Util::Sprite::Manager::SetShake( 10 );
		}
		else
		{
			Actor::Base::Erase();
		}

		std::set<Bullet::PBullet> bullets;
		GetActors().DetectBulletHitAll( GetHitCircle(), bullets );
		foreach( Bullet::PBullet pBullet, bullets )
		{
			pBullet->Erase();
		}
	}
}

void SpMissile::OnDraw() const
{
	if( !mExplodeFlag )
	{
		Util::Sprite::Manager::Draw( mDrawParam );
	}
	else if( mExplodeFrameCount > 0 )
	{
		mExplodeAnimation.Draw();
	}
}

void SpMissile::OnDestruct()
{
	Actor::Base::SetValid( true );

	if( !mExplodeFlag )
	{
		mExplodeFlag = true;
		mExplodeFrameCount = EXPLODE_FRAMENUM;

		mLocator.GetSpeed() = 0;
		mLocator.GetAccel() = 0;

		Base::SetHitRadius( EXPLODE_RADIUS );
	}
}

void SpMissile::OnDestruct( float hp )
{
	Base::Destruct();
}

void SpMissile::OnErase()
{
	Actor::PAnimation pAnimeObject(
		new Actor::Animation( 
		Base::GetMode(), 
		Hit::RectI( mExplodeAnimation.GetDrawParameter().GetDst() ), 
		mExplodeAnimation ) );

	Base::GetActors().GetActors().push_back( Actor::PActor( pAnimeObject ) );
}