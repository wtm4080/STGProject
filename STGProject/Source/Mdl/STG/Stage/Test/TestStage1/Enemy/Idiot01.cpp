#include "PCH.h"
#include "Idiot01.h"

#include "Ctrl/STG/Actors.h"
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
	static const Vector2DI EN_SIZE( 48, 48 );
	static const Vector2DF EXPLOSION_SIZE( 96, 96 );
	static const float HP = 5;
	static const unsigned WAIT_FRAME_NUM = 10;
	static const Hit::RectI LAUNCH_AREA( 0, 0, 440, 360, false );
}


Idiot01::Idiot01( PStageSet pStageSet, const Util::STG::Vector2DF &initPos, 
	const Util::STG::Vector2DF &targetPos, float speed )
	: Base( pStageSet->GetMode(), Hit::RectI( initPos, EN_SIZE ), HP )
	, mpStageSet( pStageSet )
	, mLocator( initPos )
	, mInitPos( initPos )
	, mTargetPos( targetPos )
	, mArrivalTargetPos( false )
	, mWaitCount( 0 )
	, mSpeed( speed )
	, mAuxs( pStageSet->GetMode() )
{
	mLocator.GetSpeed().SetUnitVector( 
		mLocator.GetPosition().GetAngle( mTargetPos ) ) *= mSpeed;

	mDrawParam.SetTexture( mpStageSet->GetResource()->GetIcon2() );
	mDrawParam.SetSrc( Resource::ICON2.GetRect() );
	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( EN_SIZE ) );
	mDrawParam.SetPriority( View::STG::PRI_ENEMY );
}


Vector2DF Idiot01::GetPosition() const
{
	return mLocator.GetPosition();
}

Vector2DF Idiot01::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


void Idiot01::OnUpdate()
{
	mLocator.Update();

	if( !mArrivalTargetPos )
	{
		if( mLocator.GetPosition().GetDistance( mTargetPos ) <= 
			mLocator.GetSpeed().GetAbs() )
		{
			mLocator.GetAccel() = 0;
			mLocator.GetSpeed() = 0;
			mLocator.GetPosition() = mTargetPos;

			mArrivalTargetPos = true;
		}
		else if( mLocator.GetPosition().GetDistance( mTargetPos ) <= 50.0f )
		{
			if( mLocator.GetSpeed().GetAbs() > 1.0f )
			{
				mLocator.GetAccel().SetUnitVector( 
					mLocator.GetSpeed().GetAngle() + 180.0f ) *= mSpeed / 20.0f;
			}
			else
			{
				mLocator.GetAccel() = 0;
				mLocator.GetSpeed().Normalize();
			}
		}
	}
	else
	{
		if( mWaitCount == WAIT_FRAME_NUM )
		{
			if( mLocator.GetSpeed().GetAbs() < mSpeed )
			{
				mLocator.GetAccel().SetUnitVector( 
					mInitPos.GetAngle( mTargetPos ) ) *= mSpeed / 50.0f;
			}
			else
			{
				mLocator.GetAccel() = 0;
				mLocator.GetSpeed().SetUnitVector( 
					mInitPos.GetAngle( mTargetPos ) ) *= mSpeed;
			}
		}
		else
		{
			mWaitCount++;
		}
	}

	mLaunchItv.UpdateState();
	if( Base::IsHit( LAUNCH_AREA ) )
	{
		for( unsigned i = 0; i < mLaunchItv.GetRepeatCount(); i++ )
		{
			Launch();
		}
	}

	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( EN_SIZE ) );
}

void Idiot01::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}

void Idiot01::OnErase()
{
	OnDestruct();
}

void Idiot01::OnDestruct()
{
	mpStageSet->AddScore( static_cast<Uint64>( mMaxHP ) );

	mAuxs.CreateExplosion( mLocator.GetPosition(), EXPLOSION_SIZE );
}

void Idiot01::OnDamaged( float damage )
{
	mpStageSet->AddRate( damage * 0.01f );
}

void Idiot01::OnDestruct( float hp )
{
	OnDestruct();
}