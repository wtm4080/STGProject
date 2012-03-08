#include "PCH.h"
#include "Idiot01b.h"

#include "Ctrl/STG/Actors.h"
#include "Mdl/STG/Bullet/Linear.h"
#include "Mdl/STG/MyShip/IMyShip.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Stage::Test::TestStage1::Enemy;
using namespace Util::STG;


Idiot01b::Idiot01b( PStageSet pStageSet, const Util::STG::Vector2DF &initPos, 
	const Util::STG::Vector2DF &targetPos )
	: Idiot01( pStageSet, initPos, targetPos )
{
	mLaunchItv.SetInterval( 15.0f );

	mLauncher.SetGenerator( 
		Bullet::Launcher::NWay::Generator( this, &Idiot01b::Launch2Way ) );
	mLauncher.SetNum( 2 );
	mLauncher.SetAngle( 90.0f );
	mLauncher.SetIntervalAngle( 45.0f );
}


void Idiot01b::Launch()
{
	mLauncher.Launch();
}


void Idiot01b::Launch2Way( float angle )
{
	Util::STG::Locator::LinearF locator( mLocator.GetPosition() );

	static const int hitRadius = 6;

	Util::Sprite::DrawParameter dParam = 
		mAuxs.GetBulletBlueDrawParam( 
		locator.GetPosition(), Vector2DF( 16, 16 ) );

	locator.GetAccel().SetUnitVector( 90.0f ) *= 0.04f;
	locator.GetSpeed().SetUnitVector( angle ) *= 1.0f;

	Bullet::PBullet pBullet( 
		new Bullet::Linear( Base::GetMode(), locator, hitRadius, dParam ) );

	Base::GetActors().GetBullets().push_back( pBullet );
}