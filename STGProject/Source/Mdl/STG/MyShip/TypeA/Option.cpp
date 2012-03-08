#include "PCH.h"
#include "Option.h"
#include "Resource.h"
#include "Missile.h"
#include "SpMissile.h"

#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/Enemy/IEnemy.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace MyShip::TypeA;
using namespace Util::STG;
using namespace Selene;
using namespace boost;

namespace
{
	static const Vector2DF DRAW_SIZE( 32, 32 );
	static const Vector2DF LAUNCH_EXPLOSION_SIZE( 96*0.3f, 96*0.3f );
	static const numeric::interval<float> SPMISSILE_ANGLE( -160.0f, -20.0f );
	static const Vector2DF SPLAUNCH_EXPLOSION_SIZE( 96, 96 );
}


Option::Option( PMode pMode, const Vector2DF &pos, Util::Sprite::PTexture pOptionTexture, 
	Util::Sprite::PTexture pMissileTexture, Util::Sprite::PTexture pExplosionTexture, 
	float rotAngle )
: mpMode( pMode )
, mLocator( 180.0f )
, mRotAngle( rotAngle )
, mpMissileTexture( pMissileTexture )
, mpExplosionTexture( pExplosionTexture )
, mAuxs( pMode )
{
	assert( pOptionTexture );
	assert( pMissileTexture );

	mLocator.SetTracing( true );
	mLocator.GetPosition() = pos;
	mLocator.GetSpeed().SetUnitVector( 90.0f ) *= 4.0f;

	mDrawParam.SetTexture( pOptionTexture );
	mDrawParam.SetSrc( Resource::OPTION.GetRect() );
	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( DRAW_SIZE ) );
	mDrawParam.SetPriority( View::STG::PRI_MYSHIP_OPTION );
	mDrawParam.SetRotDegree( mRotAngle );
}


void Option::Update()
{
	mLocator.Update();

	mRotAngle += 1.0f;
	mRotAngle >= 360.0f ? mRotAngle -= 360.0f : void();
	mDrawParam.SetRotDegree( mRotAngle );
	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( DRAW_SIZE ) );

	Draw();
}

void Option::Draw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}


const Vector2DF &Option::GetDrawSize()
{
	return DRAW_SIZE;
}

void Option::SetTargetPosition( const Vector2DF &pos )
{
	mLocator.GetTargetPosition() = pos;
}

float Option::GetRotateAngle() const
{
	return mRotAngle;
}

void Option::SetRotateAngle( float angle )
{
	mRotAngle = angle;
}


void Option::LaunchMissile( float circlingAngle ) const
{
	Vector2DF pos = mLocator.GetPosition() + Vector2DF( 0, -8 );

	mAuxs.CreateExplosion( pos, LAUNCH_EXPLOSION_SIZE );

	MyShot::PMyShot pMissile( 
		new Missile( mpMode, pos, circlingAngle, 
		mpMissileTexture ) );

	mpMode->GetActors().GetMyShots().push_back( pMissile );
}

void Option::LaunchSpMissile( bool aiming )
{
	float angle = -90.0f;

	if( aiming && 
		!mpMode->GetActors().GetEnemies().empty() )
	{
#ifdef max
#undef max
#endif
		std::pair<float, float> 
			targetEnemy( std::numeric_limits<float>::max(), angle );

		typedef Ctrl::STG::Actors::PEnemy PEnemy;
		foreach( PEnemy pEnemy, mpMode->GetActors().GetEnemies() )
		{
			float distance = 
				mLocator.GetPosition().GetDistance( pEnemy->GetPosition() );
			float tmpAngle = 
				mLocator.GetPosition().GetAngle( pEnemy->GetPosition() );

			if( distance < targetEnemy.first && 
				numeric::in( tmpAngle, SPMISSILE_ANGLE ) )
			{
				targetEnemy.first = distance;
				targetEnemy.second = tmpAngle;
			}
		}

		angle = targetEnemy.second;
	}

	assert( numeric::in( angle, SPMISSILE_ANGLE ) );

	{
		Vector2DF pos = mLocator.GetPosition() + Vector2DF( 0, -32 );

		mAuxs.CreateExplosion( pos, SPLAUNCH_EXPLOSION_SIZE );

		MyShot::PMyShot pSpMissile( 
			new SpMissile( mpMode, pos, angle, 
			mpMissileTexture, mpExplosionTexture ) );

		mpMode->GetActors().GetMyShots().push_back( pSpMissile );

		mwpSpMissile = Util::Ptr<MyShot::IMyShot>::Weak( pSpMissile );
	}
}

bool Option::IsExistSpMissile()
{
	return !mwpSpMissile.expired();
}