#include "PCH.h"
#include "Missile.h"
#include "Resource.h"

#include "Ctrl/STG/Actors.h"
#include "Mdl/STG/Enemy/IEnemy.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace MyShip::TypeA;
using namespace Util::STG;
using namespace Selene;

namespace
{
	static const int RADIUS = 6;
	static const Vector2DF MISSILE_SIZE( 32, 32 );
	static const float LAUNCH_ANGLE = -90.0f;
	static const float CIRCLING_ANGLE = 2.0f;
	static const float INIT_SPEED = 0.1f;
	static const float MAX_SPEED = 10.0f;
	static const float INIT_ACCEL = 0.6f;
	static const float DAMAGE = 8.0f;
	static const Vector2DF EXPLOSION_SIZE( 96*0.8f, 96*0.8f );
	static const Hit::RectI TRACE_AREA( 0, 0, 440, 480, false );
}


// コンストラクタ
Missile::Missile( Base::PMode pMode, const Vector2DF &pos, float circlingAngle, 
				 Util::Sprite::PTexture pMissileTexture )
: Base( pMode, pos, RADIUS, DAMAGE )
, mLocator( circlingAngle )
, mAuxs( pMode )
{
	assert( pMissileTexture );

	mLocator.GetPosition() = pos;
	mLocator.GetSpeed().SetUnitVector( LAUNCH_ANGLE ) *= INIT_SPEED;
	mLocator.GetAccel().SetUnitVector( LAUNCH_ANGLE ) *= INIT_ACCEL;
	mLocator.SetTracing( false );

	mDrawParam.SetTexture( pMissileTexture );
	mDrawParam.SetSrc( Resource::MISSILE.GetRect() );
	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( MISSILE_SIZE ) );
	mDrawParam.SetPriority( View::STG::PRI_MYSHOT );
	mDrawParam.SetRotDegree( mLocator.GetSpeed().GetAngle() + 90.0f );
}


// 位置の取得
Vector2DF Missile::GetPosition() const
{
	return mLocator.GetPosition();
}

// 外力の適用
Vector2DF Missile::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


void Missile::OnUpdate()
{
	mLocator.Update();

	if( mLocator.GetSpeed().GetAbs() >= MAX_SPEED )
	{
		mLocator.GetSpeed().SetUnitVector( mLocator.GetSpeed().GetAngle() ) *= MAX_SPEED;
		mLocator.GetAccel() = 0;
	}
	else
	{
		mLocator.GetAccel().SetUnitVector( mLocator.GetSpeed().GetAngle() ) *= INIT_ACCEL;
	}

	{
		using namespace std;
		typedef Ctrl::STG::Actors::PEnemy PEnemy;

#ifdef max
#undef max
#endif
		pair<float, Vector2DF> targetEnemy( numeric_limits<float>::max(), Vector2DF() );

		foreach( PEnemy pEnemy, Base::GetActors().GetEnemies() )
		{
			if( pEnemy->IsHit( TRACE_AREA ) )
			{
				float distance = 
					mLocator.GetPosition().GetDistance( pEnemy->GetPosition() );

				if( distance < targetEnemy.first )
				{
					targetEnemy.first = distance;
					targetEnemy.second = pEnemy->GetPosition();
				}
			}
		}

		if( targetEnemy.first < numeric_limits<float>::max() )
		{
			mLocator.GetTargetPosition() = targetEnemy.second;
			mLocator.SetTracing( true );
		}
		else
		{
			mLocator.SetTracing( false );
		}
	}

	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( MISSILE_SIZE ) );
	mDrawParam.SetRotDegree( mLocator.GetSpeed().GetAngle() + 90.0f );
}

void Missile::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}

void Missile::OnDestruct()
{
	mAuxs.CreateExplosion( mLocator.GetPosition(), EXPLOSION_SIZE );
}

void Missile::OnDestruct( float hp )
{
	mAuxs.CreateExplosion( mLocator.GetPosition(), EXPLOSION_SIZE );
}

void Missile::OnErase()
{
	mAuxs.CreateExplosion( mLocator.GetPosition(), EXPLOSION_SIZE );
}