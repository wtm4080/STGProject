#include "PCH.h"
#include "Idiot02.h"

#include "Ctrl/STG/Actors.h"
#include "Mdl/STG/Bullet/Linear.h"
#include "Mdl/STG/Item/PowerUp.h"
#include "Mdl/STG/MyShip/IMyShip.h"
#include "Mdl/STG/Stage/Test/Background.h"
#include "Mdl/STG/Stage/Test/Resource.h"
#include "Mdl/STG/Stage/Test/StageSetCore.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Stage::Test::TestStage1::Enemy;
using namespace Util::STG;

namespace
{
	static const Vector2DI EN_SIZE( 64, 64 );
	static const Vector2DF EXPLOSION_SIZE( 96*2, 96*2 );
	static const float HP = 200;
	static const Hit::RectI LAUNCH_AREA( 0, 0, 440, 360, false );
}


Idiot02::Idiot02( PStageSet pStageSet, const Util::STG::Vector2DF &initPos, bool dropPowerUp )
	: Base( pStageSet->GetMode(), Hit::RectI( initPos, EN_SIZE ), HP )
	, mpStageSet( pStageSet )
	, mLocator( initPos )
	, mLaunchTiming()
	, mAuxs( pStageSet->GetMode() )
	, mDropPowerUp( dropPowerUp )
{
	mDrawParam.SetTexture( mpStageSet->GetResource()->GetIcon3() );
	mDrawParam.SetSrc( Resource::ICON3.GetRect() );
	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( EN_SIZE ) );
	mDrawParam.SetPriority( View::STG::PRI_ENEMY );

	mLaunchTiming.Push( 1, 20.0f, 
		Util::RepeatQueue::RepeatFunc( this, &Idiot02::UpdateTarget ) );
	mLaunchTiming.Push( 5, 5.0f, 
		Util::RepeatQueue::RepeatFunc( this, &Idiot02::LaunchAiming ) );
}


Vector2DF Idiot02::GetPosition() const
{
	return mLocator.GetPosition();
}

Vector2DF Idiot02::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


void Idiot02::OnUpdate()
{
	mLocator.Update();
	mLocator.GetPosition() += 
		Vector2DF( 0, mpStageSet->GetBackground()->GetScrollAmount() );

	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( EN_SIZE ) );

	if( Base::IsHit( LAUNCH_AREA ) )
	{
		mLaunchTiming.Update();
	}
}

void Idiot02::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}

void Idiot02::OnErase()
{
	OnDestruct();
}

void Idiot02::OnDestruct()
{
	mpStageSet->AddScore( static_cast<Selene::Uint64>( mMaxHP ) );

	mAuxs.CreateExplosion( mLocator.GetPosition(), EXPLOSION_SIZE );
}

void Idiot02::OnDamaged( float damage )
{
	mpStageSet->AddRate( damage * 0.01f );
}

void Idiot02::OnDestruct( float hp )
{
	OnDestruct();

	if( mDropPowerUp )
	{
		Item::PItem pItem( 
			new Item::PowerUp( Base::GetMode(), mLocator.GetPosition() ) );

		Base::GetActors().GetItems().push_back( pItem );
	}
}

void Idiot02::UpdateTarget()
{
	mTargetAngle = mLocator.GetPosition().GetAngle( 
		Base::GetActors().GetMyShip()->GetPosition() );
}

void Idiot02::LaunchAiming()
{
	Util::STG::Locator::LinearF locator( mLocator.GetPosition() );

	static const int hitRadius = 4;

	Util::Sprite::DrawParameter dParam = 
		mAuxs.GetBulletRedDrawParam( 
		locator.GetPosition(), Vector2DF( 12, 12 ) );

	locator.GetSpeed().SetUnitVector( mTargetAngle ) *= 3.0f;

	Bullet::PBullet pBullet( 
		new Bullet::Linear( Base::GetMode(), locator, hitRadius, dParam ) );

	Base::GetActors().GetBullets().push_back( pBullet );
}