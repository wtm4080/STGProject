#include "PCH.h"
#include "En01.h"

#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/Bullet/Linear.h"
#include "Mdl/STG/MyShip/IMyShip.h"
#include "Mdl/STG/Stage/Test/Resource.h"
#include "Mdl/STG/Stage/Test/StageSetCore.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Stage::Test::TestStage1::Enemy;
using namespace Util::STG;
using namespace Selene;

namespace
{
	static const Vector2DI EN_SIZE( 128, 128 );
	static const Vector2DF EXPLOSION_SIZE( 96*5, 96*5 );
	static const float HP = 8000;
	static const Vector2DF INIT_POS( 220, -100 );

	class AcceledBullet
		: public Bullet::Linear
	{
	public:
		AcceledBullet( PMode pMode, 
			const Locator::LinearF &locator, int hitRadius, 
			const Util::Sprite::DrawParameter &drawParam, float angle )
			: Linear( pMode, locator, hitRadius, drawParam )
			, mAngle( angle )
			, ACCEL( 0.1f )
			, SPEED( 4.0f )
		{}

	private:
		const float ACCEL;
		const float SPEED;
		float mAngle;

		virtual void OnUpdate()
		{
			Linear::OnUpdate();

			if( Linear::GetLocator().GetSpeed().GetAbs() < SPEED )
			{
				Linear::GetLocator().GetAccel().SetUnitVector( mAngle ) *= ACCEL;
			}
			else
			{
				Linear::GetLocator().GetAccel() = 0;
				Linear::GetLocator().GetSpeed().SetUnitVector( mAngle ) *= SPEED;
			}

			{
				Util::Sprite::DrawParameter dParam = 
					Linear::GetDrawParameter();
				dParam.SetRotDegree( 
					Linear::GetLocator().GetSpeed().GetAngle() );
				Linear::SetDrawParameter( dParam );
			}
		}
	};
}


En01::En01( PStageSet pStageSet )
: Base( pStageSet->GetMode(), Hit::RectI( INIT_POS, EN_SIZE ), HP )
, mpStageSet( pStageSet )
, mLocator( INIT_POS )
, mRotDegree( 0 )
, mLaunchAngle( 0 )
, mLaunchItv( 3.0f )
, mCircleLauncher()
, mAimingBulletCount( 0 )
, mAimingLauncher()
, mAcceledItv( 0.5f )
, mRandomWaitCount( 0 )
, mRandomLaunchItv( 15.0f )
, mPhase3Count( 0 )
, mExplosionItv( 3.0f )
, mHPGauge( pStageSet->GetMode(), HP )
, mAuxs( pStageSet->GetMode() )
{
	mLocator.GetSpeed().y = 4.0f;

	mDrawParam.SetTexture( mpStageSet->GetResource()->GetIcon1() );
	mDrawParam.SetSrc( Resource::ICON1.GetRect() );
	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( EN_SIZE ) );
	mDrawParam.SetPriority( View::STG::PRI_ENEMY );
	mDrawParam.SetRotDegree( mRotDegree );

	mHPGauge.Appear();

	mCircleLauncher.SetGenerator( 
		Bullet::Launcher::Circle::Generator( this, &En01::LaunchCircle ) );
	mCircleLauncher.SetNum( 6 );
	mCircleLauncher.SetAngle( mLaunchAngle );

	mAimingTiming.Push( 1, 60.0f, 
		Util::RepeatQueue::RepeatFunc( this, &En01::UpdateTarget ) );
	mAimingTiming.Push( 15, 2.5f, 
		Util::RepeatQueue::RepeatFunc( this, &En01::LaunchAiming ) );
	mAimingLauncher.SetGenerator( 
		Bullet::Launcher::NWay::Generator( this, &En01::GenerateAiming ) );
	mAimingLauncher.SetNum( 3 );
	mAimingLauncher.SetIntervalAngle( 30.0f );

	mRandomLauncher.SetGenerator( 
		Bullet::Launcher::Circle::Generator( this, &En01::LaunchRandom ) );
	mRandomLauncher.SetNum( 5 );

	mPhaseQueue.Push( 
		Util::FunctionQueue::Delegate( this, &En01::Phase1 ) );
	mPhaseQueue.Push( 
		Util::FunctionQueue::Delegate( this, &En01::EraseBullet ) );
	mPhaseQueue.Push( 
		Util::FunctionQueue::Delegate( this, &En01::Phase2 ) );
	mPhaseQueue.Push( 
		Util::FunctionQueue::Delegate( this, &En01::EraseBullet ) );
	mPhaseQueue.Push( 
		Util::FunctionQueue::Delegate( this, &En01::Phase3 ) );
}


Vector2DF En01::GetPosition() const
{
	return mLocator.GetPosition();
}

Vector2DF En01::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


void En01::OnUpdate()
{
	mLocator.Update();

	mRotDegree += 1.0f;
	if( mRotDegree >= 360 )
	{
		mRotDegree -= 360;
	}

	mPhaseQueue();

	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( EN_SIZE ) );
	mDrawParam.SetRotDegree( mRotDegree );

	mHPGauge.SetValue( Base::GetHP() );
	mHPGauge.Update();
}

void En01::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );

	mHPGauge.Draw();
}

void En01::OnErase()
{
	OnDestruct();
}

void En01::OnDestruct()
{
	mpStageSet->AddScore( static_cast<Uint64>( mMaxHP ) );

	Base::SetValid( true );
}

void En01::OnDamaged( float damage )
{
	mpStageSet->AddRate( damage * 0.01f );
}

void En01::OnDestruct( float hp )
{
	OnDestruct();
}


bool En01::Phase1()
{
	if( mLocator.GetPosition().y >= 100 )
	{
		mLocator.GetSpeed() = 0;

		mLaunchItv.UpdateState();
		if( mLaunchItv.GetRepeatCount() >= 1 )
		{
			mCircleLauncher.SetAngle( mLaunchAngle );
			mCircleLauncher.Launch();

			mLaunchAngle += 9.0f;
			if( mLaunchAngle >= 360 )
			{
				mLaunchAngle -= 360.0f;
			}
		}

		mAimingTiming.Update();
	}

	return Base::GetHP() > HP / 2;
}

bool En01::EraseBullet()
{
	foreach( Bullet::PBullet pBullet, Base::GetActors().GetBullets() )
	{
		pBullet->Erase();
	}

	return false;
}

bool En01::Phase2()
{
	auto random = Base::GetMode()->GetRandom();

	mAcceledItv.UpdateState();
	for( unsigned i = 0; i < mAcceledItv.GetRepeatCount(); i++ )
	{
		Util::STG::Locator::LinearF locator( mLocator.GetPosition() );

		static const int hitRadius = 3;
		float angle = random->GetFloat( -180.0f, 180.0f );

		Util::Sprite::DrawParameter dParam = 
			mAuxs.GetBulletBlueDrawParam( 
			locator.GetPosition(), Vector2DF( 16, 6 ) );
		dParam.SetRotDegree( angle );

		Bullet::PBullet pBullet( 
			new AcceledBullet( 
			Base::GetMode(), locator, hitRadius, dParam, angle ) );

		Base::GetActors().GetBullets().push_back( pBullet );
	}

	if( mRandomWaitCount++ < 90 );
	else
	{
		mRandomLaunchItv.UpdateState();
		for( unsigned i = 0; i < mRandomLaunchItv.GetRepeatCount(); i++ )
		{
			mRandomLauncher.SetAngle( random->GetFloat( -180.0f, 180.0f ) );
			mRandomLauncher.Launch();
		}
	}

	return Base::GetHP() > 0;
}

bool En01::Phase3()
{
	if( mPhase3Count++ < 60 )
	{
		mLocator.GetAccel().SetUnitVector( 90.0f ) *= 0.08f;

		mExplosionItv.UpdateState();

		for( unsigned i = 0; i < mExplosionItv.GetRepeatCount(); i++ )
		{
			auto random = Base::GetMode()->GetRandom();
			Vector2DF offset( 
				random->GetFloat( -EN_SIZE.x/2.0f, EN_SIZE.x/2.0f ), 
				random->GetFloat( -EN_SIZE.y/2.0f, EN_SIZE.y/2.0f ) );

			mAuxs.CreateExplosion( mLocator.GetPosition() + offset, 
				EXPLOSION_SIZE / 2 );
		}
	}
	else
	{
		Util::Sprite::Manager::SetShake( 20.0f, 0.3f );
		mAuxs.CreateExplosion( 
			mLocator.GetPosition(), EXPLOSION_SIZE, 2.0f );

		Base::SetValid( false );
	}

	return true;
}


void En01::LaunchCircle( float angle )
{
	Util::STG::Locator::LinearF locator( mLocator.GetPosition() );

	static const int hitRadius = 6;

	Util::Sprite::DrawParameter dParam = 
		mAuxs.GetBulletGreenDrawParam( 
		locator.GetPosition(), Vector2DF( 16, 16 ) );

	locator.GetSpeed().SetUnitVector( angle ) *= 1.0f;
	locator.GetAccel().SetUnitVector( angle ) *= 0.02f;

	Bullet::PBullet pBullet( 
		new Bullet::Linear( Base::GetMode(), locator, hitRadius, dParam ) );

	Base::GetActors().GetBullets().push_back( pBullet );
}

void En01::UpdateTarget()
{
	mTargetAngle = mLocator.GetPosition().GetAngle( 
		Base::GetActors().GetMyShip()->GetPosition() );

	mAimingBulletCount = 0;
}

void En01::LaunchAiming()
{
	mAimingLauncher.SetAngle( mTargetAngle );
	mAimingLauncher.Launch();

	mAimingBulletCount++;
}

void En01::GenerateAiming( float angle )
{
	Util::STG::Locator::LinearF locator( mLocator.GetPosition() );

	static const int hitRadius = 6;

	Util::Sprite::DrawParameter dParam = 
		mAuxs.GetBulletRedDrawParam( 
		locator.GetPosition(), Vector2DF( 16, 16 ) );

	locator.GetSpeed().SetUnitVector( angle ) *= 3.0f + 0.5f*mAimingBulletCount;

	Bullet::PBullet pBullet( 
		new Bullet::Linear( Base::GetMode(), locator, hitRadius, dParam ) );

	Base::GetActors().GetBullets().push_back( pBullet );
}


void En01::LaunchRandom( float angle )
{
	Util::STG::Locator::LinearF locator( mLocator.GetPosition() );

	static const int hitRadius = 12;

	Util::Sprite::DrawParameter dParam = 
		mAuxs.GetBulletRedDrawParam( 
		locator.GetPosition(), Vector2DF( 48, 48 ) );

	locator.GetSpeed().SetUnitVector( angle ) *= 5.0f;

	Bullet::PBullet pBullet( 
		new Bullet::Linear( Base::GetMode(), locator, hitRadius, dParam ) );

	Base::GetActors().GetBullets().push_back( pBullet );
}