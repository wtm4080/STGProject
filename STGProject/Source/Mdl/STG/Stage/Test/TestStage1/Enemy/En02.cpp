#include "PCH.h"
#include "En02.h"

#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/Bullet/BulletML/MLActor.h"
#include "Mdl/STG/Bullet/IBullet.h"
#include "Mdl/STG/Stage/Test/Resource.h"
#include "Mdl/STG/Stage/Test/StageSetCore.h"
#include "Mdl/STG/Stage/Test/TestStage1/StageCore.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Stage::Test::TestStage1::Enemy;
using namespace Util::STG;

namespace
{
	static const Vector2DI EN_SIZE( 128, 128 );
	static const Vector2DF EXPLOSION_SIZE( 96*5, 96*5 );
	static const float HP = 8000;
	static const Vector2DF INIT_POS( 220, -100 );
}


En02::En02( PStage pStage )
	: Base( pStage->GetMode(), Hit::RectI( INIT_POS, EN_SIZE ), HP )
	, mpStage( pStage )
	, mLocator( INIT_POS )
	, mHPGauge( pStage->GetMode(), HP )
	, mAuxs( pStage->GetMode() )
	// Phase1
	, mMLBulletItv( 1.0f )
	// LastPhase
	, mLastPhaseCount( 0 )
	, mExplosionItv( 3.0f )
{
	mLocator.GetSpeed().y = 4.0f;

	mDrawParam.SetTexture( mpStage->GetStageSet()->GetResource()->GetIcon4() );
	mDrawParam.SetSrc( Resource::ICON4.GetRect() );
	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( EN_SIZE ) );
	mDrawParam.SetPriority( View::STG::PRI_ENEMY );

	mHPGauge.Appear();

	mPhaseQueue.Push( 
		Util::FunctionQueue::Delegate( this, &En02::Phase1 ) );
	mPhaseQueue.Push( 
		Util::FunctionQueue::Delegate( this, &En02::EraseBullet ) );
	mPhaseQueue.Push( 
		Util::FunctionQueue::Delegate( this, &En02::LastPhase ) );
}


Vector2DF En02::GetPosition() const
{
	return mLocator.GetPosition();
}

Vector2DF En02::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


void En02::OnUpdate()
{
	mLocator.Update();

	mPhaseQueue();

	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( EN_SIZE ) );

	mHPGauge.SetValue( Base::GetHP() );
	mHPGauge.Update();
}

void En02::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );

	mHPGauge.Draw();
}

void En02::OnErase()
{
	OnDestruct();
}

void En02::OnDestruct()
{
	mpStage->GetStageSet()->AddScore( 
		static_cast<Selene::Uint64>( mMaxHP ) );

	Base::SetValid( true );
}

void En02::OnDamaged( float damage )
{
	mpStage->GetStageSet()->AddRate( damage * 0.01f );
}

void En02::OnDestruct( float hp )
{
	OnDestruct();
}


bool En02::Phase1()
{
	if( mLocator.GetPosition().y >= 100 )
	{
		mLocator.GetSpeed() = 0;

		mMLBulletItv.UpdateState();
		for( unsigned i = 0; i <mMLBulletItv.GetRepeatCount(); i++ )
		{
			if( !mpMLActor || !mpMLActor->IsValid() )
			{
				mpMLActor = Bullet::BulletML::PMLActor( 
					new Bullet::BulletML::MLActor( Actor::Base::GetMode(), 
					mpStage->GetBMLParsers().GetParser( 
					BML_TEST ), 
					mLocator.GetPosition() ) );

				Bullet::BulletML::CreateParam createParam;
				createParam.SetHitRadius( 2 );
				createParam.SetDrawParam( 
					mAuxs.GetBulletBlueDrawParam( 
					mLocator.GetPosition(), Vector2DF( 14, 14 ) ) );
				createParam.SetPopped( false );
				mpMLActor->GetCreateParamList().push_back( createParam );

				//mpMLActor->SetRank( 1.0 );

				mpMLActor->Update();
			}
			else
			{
				mpMLActor->Update();
			}
		}
	}

	return Base::GetHP() > 0;
}

bool En02::EraseBullet()
{
	foreach( Bullet::PBullet pBullet, Base::GetActors().GetBullets() )
	{
		pBullet->Erase();
	}

	return false;
}

bool En02::LastPhase()
{
	if( mLastPhaseCount++ < 60 )
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