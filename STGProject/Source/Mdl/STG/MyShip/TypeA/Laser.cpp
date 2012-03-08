#include "PCH.h"
#include "Laser.h"
#include "Resource.h"

#include "Ctrl/STG/Actors.h"
#include "Mdl/STG/Actor/Particle/Creator.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace MyShip::TypeA;
using namespace Util::STG;
using namespace Selene;

namespace
{
	static const int RADIUS = 6;
	static const Vector2DF LASER_SIZE( 12, 32 );
	static const float ANGLE = 270.0f;
	static const float SPEED = 22.0f;
	static const float ALPHA = 0.8f;
	static const float DAMAGE = 10.0f;
}


// コンストラクタ
Laser::Laser( Base::PMode pMode, const Vector2DF &pos, 
			 Util::Sprite::PTexture pLaserTexture, Util::Sprite::PTexture pParticleTexture )
: Base( pMode, pos, RADIUS, DAMAGE )
, mpParticleTexture( pParticleTexture )
, mAuxs( pMode )
{
	assert( pLaserTexture );
	assert( pParticleTexture );

	mLocator.GetPosition() = pos;
	mLocator.GetSpeed().SetUnitVector( ANGLE ) *= SPEED;

	Base::SetDamageRateDec( 0.06f );
	Base::SetDamageRateMin( 0.5f );

	mDrawParam.SetTexture( pLaserTexture );
	mDrawParam.SetSrc( Resource::LASER.GetRect() );
	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( LASER_SIZE ) );
	mDrawParam.SetPriority( View::STG::PRI_MYSHOT );
	mDrawParam.SetRotDegree( ANGLE - 270.0f );
	mDrawParam.SetColor( ColorF( 1.0f, 1.0f, 1.0f, ALPHA ) );
}


// 位置の取得
Vector2DF Laser::GetPosition() const
{
	return mLocator.GetPosition();
}

// 外力の適用
Vector2DF Laser::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


void Laser::OnUpdate()
{
	mLocator.Update();

	mDrawParam.SetDst( mLocator.GetPosition().MakeRect( LASER_SIZE ) );
	mDrawParam.SetRotDegree( mLocator.GetSpeed().GetAngle() - 270.0f );
}

void Laser::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}

void Laser::OnDestruct()
{
	using namespace Mdl::STG::Actor;

	Particle::Parameter param;
	{
		Util::Sprite::DrawParameter dParam;
		dParam.SetTexture( mpParticleTexture );
		dParam.SetSrc( Resource::BLUE_CIRCLE.GetRect() );
		dParam.SetDst( mLocator.GetPosition().MakeRect( 12, 12 ) );
		dParam.SetPriority( View::STG::PRI_MYSHOT );
		dParam.SetAlphaBlend( Util::Sprite::AB_ADD );
		param.SetDrawParameter( dParam );
	}
	param.SetPosition( mLocator.GetPosition() + Vector2DF( 0, -6 ) );
	param.SetAngleDomain( ANGLE+180 - 20, ANGLE+180 + 20 );
	param.SetSpeedDomain( 8.0f, 12.0f );
	param.SetZoomRateDomain( 0.8f, 1.0f );
	param.SetZoomDecRateDomain( 0.06f, 0.08f );

	Particle::Creator creator( Base::GetMode(), param );
	creator.Create( 30 );
}

void Laser::OnDestruct( float hp )
{
	mAuxs.CreateFadeOut( mDrawParam );
}

void Laser::OnErase()
{
	mAuxs.CreateFadeOut( mDrawParam );
}