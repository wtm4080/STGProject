#include "PCH.h"
#include "Idiot01a.h"

#include "Ctrl/STG/Actors.h"
#include "Mdl/STG/Bullet/Linear.h"
#include "Mdl/STG/MyShip/IMyShip.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Stage::Test::TestStage1::Enemy;
using namespace Util::STG;


Idiot01a::Idiot01a( PStageSet pStageSet, 
	const Util::STG::Vector2DF &initPos, 
	const Util::STG::Vector2DF &targetPos, 
	float bulletSpeed, float launchItv )
	: Idiot01( pStageSet, initPos, targetPos )
	, mBulletSpeed( bulletSpeed )
{
	mLaunchItv.SetInterval( launchItv );
}


void Idiot01a::Launch()
{
	Util::STG::Locator::LinearF locator( mLocator.GetPosition() );

	static const int hitRadius = 6;

	Util::Sprite::DrawParameter dParam = 
		mAuxs.GetBulletRedDrawParam( 
		locator.GetPosition(), Vector2DF( 16, 16 ) );

	float angle = mLocator.GetPosition().GetAngle( 
		Base::GetActors().GetMyShip()->GetPosition() );
	locator.GetSpeed().SetUnitVector( angle ) *= mBulletSpeed;

	Bullet::PBullet pBullet( 
		new Bullet::Linear( Base::GetMode(), locator, hitRadius, dParam ) );
	Base::GetActors().GetBullets().push_back( pBullet );
}