#include "PCH.h"
#include "Auxs.h"

#include "View/STG/DrawPriority.h"

#include "Defs/Ctrl/STG/STG.h"
#include "Defs/Mdl/STG/Actor/Animation.h"
#include "Defs/Mdl/STG/Actor/FadeOut.h"
#include "Defs/Mdl/STG/Actor/Particle/Creator.h"
#include "Defs/Mdl/STG/Actor/Particle/Particle.h"
#include "Defs/Mdl/STG/Bullet/BulletML/MLActor.h"
#include "Defs/Mdl/STG/Bullet/Simple.h"
#include "Defs/Mdl/STG/Item/Extend.h"
#include "Defs/Mdl/STG/Item/PowerUp.h"
#include "Defs/Mdl/STG/Item/SpAttack.h"
#include "Defs/Util/Sprite/Animation/FrameHolder/Sequence.h"
#include "Defs/Util/Sprite/Animation/FrameHolder/Texture.h"

using namespace std;
using namespace Defs::Mdl::STG;
namespace py = boost::python;
namespace View = Game::View::STG;
using namespace Game::Util::STG;
using namespace Selene;

namespace
{
	typedef Defs::Ctrl::STG::STG STGControl;
	typedef Game::Mdl::STG::Actor::PActor PActor;
	typedef Game::Mdl::STG::Bullet::PBullet PBullet;
	typedef Game::Mdl::STG::Enemy::PEnemy PEnemy;
	typedef Game::Mdl::STG::Item::PItem PItem;
	typedef Game::Mdl::STG::MyShot::PMyShot PMyShot;
}


Auxs::Auxs()
	: mCommonResource( py::import( "STG.Resource.Common" ) )
{
}


Actor::PFadeOut Auxs::CreateFadeOut( const DrawParameter &drawParam, unsigned frameNum ) const
{
	Actor::PFadeOut pFadeOut( 
		new Actor::FadeOut( 
		Hit::RectI( drawParam.GetDst().x, drawParam.GetDst().y, 
		drawParam.GetDst().w, drawParam.GetDst().h, false ) ) );
	pFadeOut->SetFrameNum( frameNum );
	pFadeOut->SetDrawParameter( drawParam );

	STGControl::getActors()->GetActorList().push_back( 
		PActor( pFadeOut ) );

	return pFadeOut;
}


void Auxs::CreateParticle( const DrawParameter &drawParam, 
	unsigned num ) const
{
	using namespace Actor::Particle;

	Parameter param;
	{
		DrawParameter dParam = drawParam;
		dParam.SetAlphaBlend( Game::Util::Sprite::AB_ADD );
		param.SetDrawParameter( dParam );
	}
	param.SetPosition( 
		Vector2DF( 
		drawParam.GetDst().x + drawParam.GetDst().w/2, 
		drawParam.GetDst().y + drawParam.GetDst().h/2 ) );
	param.SetSpeedRange( 8.0f, 14.0f );
	param.SetZoomRateRange( 0.6f, 1.0f );
	param.SetZoomDecRateRange( 0.04f, 0.06f );

	Creator creator( param );
	creator.Create( num );
}


Actor::PAnimation Auxs::CreateExplosion( const Vector2DF &pos, const Vector2DF &size, 
	float frameItv ) const
{
	using namespace Util::Sprite::Animation;

	DrawParameter drawParam;
	drawParam.SetTexture( 
		py::extract<Game::Util::Sprite::PTexture>( 
		mCommonResource.attr( "get" )( "explosion" ) ) );
	drawParam.SetDst( pos.MakeRect( size ) );
	drawParam.SetPriority( Game::View::STG::PRI_EXPLOSION );
	drawParam.SetAlphaBlend( Game::Util::Sprite::AB_ADD );
	drawParam.SetFiltering( false );
	drawParam.SetRotDegree( STGControl::getRandom()->GetFloat( -180.0f, 180.0f ) );

	PFrameHolder pTextureHolder( 
		new FrameHolder::Texture( Point2DI( 96, 96 ), 16, drawParam ) );

	Manager animationManager( pTextureHolder, frameItv );

	Actor::PAnimation pAnimeObject( 
		new Actor::Animation( 
		Hit::RectI( drawParam.GetDst() ), animationManager ) );

	STGControl::getActors()->GetActorList().push_back( 
		PActor( pAnimeObject ) );

	return pAnimeObject;
}


Actor::PAnimation Auxs::CreateExplosion2( const Vector2DF &pos, 
	const Vector2DF &size, float frameItv ) const
{
	return CreateExplosion2( pos, size, frameItv, 
		Game::View::STG::PRI_EXPLOSION );
}

Actor::PAnimation Auxs::CreateExplosion2( const Vector2DF &pos, 
	const Vector2DF &size, float frameItv, Sint32 priority ) const
{
	using namespace Util::Sprite::Animation;

	DrawParameter drawParam;
	drawParam.SetSrc( RectF( 0, 0, 480, 480 ) );
	drawParam.SetDst( pos.MakeRect( size ) );
	drawParam.SetPriority( priority );
	drawParam.SetRotDegree( 
		STGControl::getRandom()->GetFloat( -180.0f, 180.0f ) );

	auto texList = mCommonResource.attr( "get" )( "explosion2TexList" );
	PFrameHolder pTextureHolder( 
		new FrameHolder::Sequence( texList, drawParam ) );

	Manager animationManager( pTextureHolder, frameItv );

	Actor::PAnimation pAnimeObject( 
		new Actor::Animation( 
		Hit::RectI( drawParam.GetDst() ), animationManager ) );

	STGControl::getActors()->GetActorList().push_back( 
		PActor( pAnimeObject ) );

	return pAnimeObject;
}


Actor::PAnimation Auxs::CreateSmoke( const Vector2DF &pos, 
	const Vector2DF &size, float frameItv, 
	Sint32 priority, float alpha ) const
{
	using namespace Util::Sprite::Animation;

	DrawParameter drawParam;
	drawParam.SetSrc( RectF( 0, 0, 480, 480 ) );
	drawParam.SetDst( pos.MakeRect( size ) );
	drawParam.SetPriority( priority );
	drawParam.SetRotDegree( 
		STGControl::getRandom()->GetFloat( -180.0f, 180.0f ) );
	ColorF color;
	color.a = alpha;
	drawParam.SetColor( color );

	auto texList = mCommonResource.attr( "get" )( "smokeTexList" );
	PFrameHolder pTextureHolder( 
		new FrameHolder::Sequence( texList, drawParam ) );

	Manager animationManager( pTextureHolder, frameItv );

	Actor::PAnimation pAnimeObject( 
		new Actor::Animation( 
		Hit::RectI( drawParam.GetDst() ), animationManager ) );

	STGControl::getActors()->GetActorList().push_back( 
		PActor( pAnimeObject ) );

	return pAnimeObject;
}


unsigned Auxs::EraseActors() const
{
	unsigned count = 0;

	foreach( PActor pActor, STGControl::getActors()->GetActorList() )
	{
		pActor->Erase();
		count++;
	}

	return count;
}

unsigned Auxs::EraseBullets() const
{
	unsigned count = 0;

	foreach( PBullet pBullet, STGControl::getActors()->GetBulletList() )
	{
		pBullet->Erase();
		count++;
	}

	return count;
}

unsigned Auxs::EraseBullets( const Hit::CircleI &hit ) const
{
	unsigned count = 0;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		pBullet->Erase();
		count++;
	}

	return count;
}

unsigned Auxs::EraseBullets( const Hit::RectI &hit ) const
{
	unsigned count = 0;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		pBullet->Erase();
		count++;
	}

	return count;
}

unsigned Auxs::EraseEnemies() const
{
	unsigned count = 0;

	foreach( PEnemy pEnemy, STGControl::getActors()->GetEnemyList() )
	{
		pEnemy->Erase();
		count++;
	}

	return count;
}

unsigned Auxs::EraseEnemies( const Hit::RectI &hit ) const
{
	unsigned count = 0;

	auto pEnemies = STGControl::getActors()->DetectEnemyHitAll( hit );
	foreach( PEnemy pEnemy, *pEnemies )
	{
		pEnemy->Erase();
		count++;
	}

	return count;
}

unsigned Auxs::EraseItems() const
{
	unsigned count = 0;

	foreach( PItem pItem, STGControl::getActors()->GetItemList() )
	{
		pItem->Erase();
		count++;
	}

	return count;
}

unsigned Auxs::EraseItems( const CircleI &hit ) const
{
	unsigned count = 0;

	auto pItems = STGControl::getActors()->DetectItemHitAll( hit );
	foreach( PItem pItem, *pItems )
	{
		pItem->Erase();
		count++;
	}

	return count;
}

unsigned Auxs::EraseMyShots() const
{
	unsigned count = 0;

	foreach( PMyShot pMyShot, STGControl::getActors()->GetMyShotList() )
	{
		pMyShot->Erase();
		count++;
	}

	return count;
}

unsigned Auxs::EraseMyShots( const Hit::CircleI &hit ) const
{
	unsigned count = 0;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		pMyShot->Erase();
		count++;
	}

	return count;
}

unsigned Auxs::EraseMyShots( const Hit::RectI &hit ) const
{
	unsigned count = 0;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		pMyShot->Erase();
		count++;
	}

	return count;
}


namespace
{
	inline float GetAttenuation( const Vector2DF &position, const Vector2DF &center, 
		float linearAttenuation, float quadraticAttenuation )
	{
		float k1 = ( linearAttenuation < 0 ) ? 0 : linearAttenuation;
		float k2 = ( quadraticAttenuation < 0 ) ? 0 : quadraticAttenuation;

		float d = center.GetDistance( position );
		return 1 / ( 1 + k1*d + k2*d*d );
	}

	inline Vector2DF GetRadialVector( 
		const Vector2DF &center, const Vector2DF &target, 
		float force )
	{
		float dir = center.GetAngle( target );

		Vector2DF forceVector;
		forceVector.SetUnitVector( dir );
		forceVector *= force;
		
		return forceVector;
	}
}

Vector2DF Auxs::ApplyExRadialForceToMyShip( float force, const Vector2DF &center ) const
{
	auto pMyShip = STGControl::getActors()->GetMyShip();
	return pMyShip->ApplyExternalForce( 
		GetRadialVector( center, pMyShip->GetPosition(), force ) );
}

Vector2DF Auxs::ApplyExRadialForceToMyShip( float force, const Vector2DF &center, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	auto pMyShip = STGControl::getActors()->GetMyShip();
	return pMyShip->ApplyExternalForce( 
		GetRadialVector( center, pMyShip->GetPosition(), force ) * 
		GetAttenuation( pMyShip->GetPosition(), center, 
		linearAttenuation, quadraticAttenuation ) );
}

Vector2DF Auxs::ApplyExRadialForceToMyShip( const CircleI &hit, float force ) const
{
	auto pMyShip = STGControl::getActors()->GetMyShip();
	if( pMyShip->IsHit( hit ) )
	{
		return pMyShip->ApplyExternalForce( 
			GetRadialVector( hit.GetCenter(), pMyShip->GetPosition(), force ) );
	}
	else
	{
		return Vector2DF();
	}
}

Vector2DF Auxs::ApplyExRadialForceToMyShip( const CircleI &hit, float force, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	auto pMyShip = STGControl::getActors()->GetMyShip();
	if( pMyShip->IsHit( hit ) )
	{
		return pMyShip->ApplyExternalForce( 
			GetRadialVector( hit.GetCenter(), pMyShip->GetPosition(), force ) * 
			GetAttenuation( pMyShip->GetPosition(), hit.GetCenter(), 
			linearAttenuation, quadraticAttenuation ) );
	}
	else
	{
		return Vector2DF();
	}
}


Vector2DF Auxs::ApplyExForceToActors( const Vector2DF &force ) const
{
	Vector2DF rebound;

	foreach( PActor pActor, STGControl::getActors()->GetActorList() )
	{
		rebound += pActor->ApplyExternalForce( force );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToActors( const Vector2DF &force, const Vector2DF &center, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	Vector2DF rebound;

	foreach( PActor pActor, STGControl::getActors()->GetActorList() )
	{
		rebound += pActor->ApplyExternalForce( force * 
			GetAttenuation( pActor->GetPosition(), center, 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToActors( float force, const Vector2DF &center ) const
{
	Vector2DF rebound;

	foreach( PActor pActor, STGControl::getActors()->GetActorList() )
	{
		rebound += pActor->ApplyExternalForce( 
			GetRadialVector( center, pActor->GetPosition(), force ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToActors( float force, const Vector2DF &center, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	Vector2DF rebound;

	foreach( PActor pActor, STGControl::getActors()->GetActorList() )
	{
		rebound += pActor->ApplyExternalForce( 
			GetRadialVector( center, pActor->GetPosition(), force ) * 
			GetAttenuation( pActor->GetPosition(), center, 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}


Vector2DF Auxs::ApplyExForceToBullets( const Vector2DF &force ) const
{
	Vector2DF rebound;

	foreach( PBullet pBullet, STGControl::getActors()->GetBulletList() )
	{
		rebound += pBullet->ApplyExternalForce( force );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToBullets( const Vector2DF &force, const Vector2DF &center, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	Vector2DF rebound;

	foreach( PBullet pBullet, STGControl::getActors()->GetBulletList() )
	{
		rebound += pBullet->ApplyExternalForce( force * 
			GetAttenuation( pBullet->GetPosition(), center, 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToBullets( const Hit::CircleI &hit, const Vector2DF &force ) const
{
	Vector2DF rebound;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		rebound += pBullet->ApplyExternalForce( force );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToBullets( const Hit::CircleI &hit, const Vector2DF &force, 
	float linearAttenuation ,float quadraticAttenuation ) const
{
	Vector2DF rebound;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		rebound += pBullet->ApplyExternalForce( force * 
			GetAttenuation( pBullet->GetPosition(), hit.GetCenter(), 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToBullets( const Hit::RectI &hit, const Vector2DF &force ) const
{
	Vector2DF rebound;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		rebound += pBullet->ApplyExternalForce( force );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToBullets( const Hit::RectI &hit, const Vector2DF &force, 
	float linearAttenuation ,float quadraticAttenuation ) const
{
	Vector2DF rebound;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		rebound += pBullet->ApplyExternalForce( force * 
			GetAttenuation( pBullet->GetPosition(), hit.GetPosition(), 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToBullets( float force, const Vector2DF &center ) const
{
	Vector2DF rebound;

	foreach( PBullet pBullet, STGControl::getActors()->GetBulletList() )
	{
		rebound += pBullet->ApplyExternalForce( 
			GetRadialVector( center, pBullet->GetPosition(), force ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToBullets( float force, const Vector2DF &center, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	Vector2DF rebound;

	foreach( PBullet pBullet, STGControl::getActors()->GetBulletList() )
	{
		rebound += pBullet->ApplyExternalForce( 
			GetRadialVector( center, pBullet->GetPosition(), force ) * 
			GetAttenuation( pBullet->GetPosition(), center, 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToBullets( const CircleI &hit, float force ) const
{
	Vector2DF rebound;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		rebound += pBullet->ApplyExternalForce( 
			GetRadialVector( hit.GetCenter(), pBullet->GetPosition(), force ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToBullets( const CircleI &hit, float force, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	Vector2DF rebound;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		rebound += pBullet->ApplyExternalForce( 
			GetRadialVector( hit.GetCenter(), pBullet->GetPosition(), force ) * 
			GetAttenuation( pBullet->GetPosition(), hit.GetCenter(), 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}


Vector2DF Auxs::ApplyExForceToEnemies( const Vector2DF &force ) const
{
	Vector2DF rebound;

	foreach( PEnemy pEnemy, STGControl::getActors()->GetEnemyList() )
	{
		rebound += pEnemy->ApplyExternalForce( force );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToEnemies( const Vector2DF &force, const Vector2DF &center, 
	float linearAttenuation ,float quadraticAttenuation ) const
{
	Vector2DF rebound;

	foreach( PEnemy pEnemy, STGControl::getActors()->GetEnemyList() )
	{
		rebound += pEnemy->ApplyExternalForce( force * 
			GetAttenuation( pEnemy->GetPosition(), center, 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToEnemies( const Hit::RectI &hit, const Vector2DF &force ) const
{
	Vector2DF rebound;

	auto pEnemies = STGControl::getActors()->DetectEnemyHitAll( hit );
	foreach( PEnemy pEnemy, *pEnemies )
	{
		rebound += pEnemy->ApplyExternalForce( force );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToEnemies( const Hit::RectI &hit, const Vector2DF &force, 
	float linearAttenuation ,float quadraticAttenuation ) const
{
	Vector2DF rebound;

	auto pEnemies = STGControl::getActors()->DetectEnemyHitAll( hit );
	foreach( PEnemy pEnemy, *pEnemies )
	{
		rebound += pEnemy->ApplyExternalForce( force * 
			GetAttenuation( pEnemy->GetPosition(), hit.GetPosition(), 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToEnemies( float force, const Vector2DF &center ) const
{
	Vector2DF rebound;

	foreach( PEnemy pEnemy, STGControl::getActors()->GetEnemyList() )
	{
		rebound += pEnemy->ApplyExternalForce( 
			GetRadialVector( center, pEnemy->GetPosition(), force ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToEnemies( float force, const Vector2DF &center, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	Vector2DF rebound;

	foreach( PEnemy pEnemy, STGControl::getActors()->GetEnemyList() )
	{
		rebound += pEnemy->ApplyExternalForce( 
			GetRadialVector( center, pEnemy->GetPosition(), force ) * 
			GetAttenuation( pEnemy->GetPosition(), center, 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}


Vector2DF Auxs::ApplyExForceToItems( const Vector2DF &force ) const
{
	Vector2DF rebound;

	foreach( PItem pItem, STGControl::getActors()->GetItemList() )
	{
		rebound += pItem->ApplyExternalForce( force );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToItems( const Vector2DF &force, const Vector2DF &center, 
	float linearAttenuation ,float quadraticAttenuation ) const
{
	Vector2DF rebound;

	foreach( PItem pItem, STGControl::getActors()->GetItemList() )
	{
		rebound += pItem->ApplyExternalForce( force * 
			GetAttenuation( pItem->GetPosition(), center, 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToItems( const CircleI &hit, const Vector2DF &force ) const
{
	Vector2DF rebound;

	auto pItems = STGControl::getActors()->DetectItemHitAll( hit );
	foreach( PItem pItem, *pItems )
	{
		rebound += pItem->ApplyExternalForce( force );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToItems( const CircleI &hit, const Vector2DF &force, 
	float linearAttenuation ,float quadraticAttenuation ) const
{
	Vector2DF rebound;

	auto pItems = STGControl::getActors()->DetectItemHitAll( hit );
	foreach( PItem pItem, *pItems )
	{
		rebound += pItem->ApplyExternalForce( force * 
			GetAttenuation( pItem->GetPosition(), hit.GetCenter(), 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToItems( float force, const Vector2DF &center ) const
{
	Vector2DF rebound;

	foreach( PItem pItem, STGControl::getActors()->GetItemList() )
	{
		rebound += pItem->ApplyExternalForce( 
			GetRadialVector( center, pItem->GetPosition(), force ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToItems( float force, const Vector2DF &center, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	Vector2DF rebound;

	foreach( PItem pItem, STGControl::getActors()->GetItemList() )
	{
		rebound += pItem->ApplyExternalForce( 
			GetRadialVector( center, pItem->GetPosition(), force ) * 
			GetAttenuation( pItem->GetPosition(), center, 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToItems( const CircleI &hit, float force ) const
{
	Vector2DF rebound;

	auto pItems = STGControl::getActors()->DetectItemHitAll( hit );
	foreach( PItem pItem, *pItems )
	{
		rebound += pItem->ApplyExternalForce( 
			GetRadialVector( hit.GetCenter(), pItem->GetPosition(), force ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToItems( const CircleI &hit, float force, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	Vector2DF rebound;

	auto pItems = STGControl::getActors()->DetectItemHitAll( hit );
	foreach( PItem pItem, *pItems )
	{
		rebound += pItem->ApplyExternalForce( 
			GetRadialVector( hit.GetCenter(), pItem->GetPosition(), force ) * 
			GetAttenuation( pItem->GetPosition(), hit.GetCenter(), 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}


Vector2DF Auxs::ApplyExForceToMyShots( const Vector2DF &force ) const
{
	Vector2DF rebound;

	foreach( PMyShot pMyShot, STGControl::getActors()->GetMyShotList() )
	{
		rebound += pMyShot->ApplyExternalForce( force );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToMyShots( const Vector2DF &force, const Vector2DF &center, 
	float linearAttenuation ,float quadraticAttenuation ) const
{
	Vector2DF rebound;

	foreach( PMyShot pMyShot, STGControl::getActors()->GetMyShotList() )
	{
		rebound += pMyShot->ApplyExternalForce( force * 
			GetAttenuation( pMyShot->GetPosition(), center, 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToMyShots( const Hit::CircleI &hit, const Vector2DF &force ) const
{
	Vector2DF rebound;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		rebound += pMyShot->ApplyExternalForce( force );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToMyShots( const Hit::CircleI &hit, const Vector2DF &force, 
	float linearAttenuation ,float quadraticAttenuation ) const
{
	Vector2DF rebound;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		rebound += pMyShot->ApplyExternalForce( force * 
			GetAttenuation( pMyShot->GetPosition(), hit.GetCenter(), 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToMyShots( const Hit::RectI &hit, const Vector2DF &force ) const
{
	Vector2DF rebound;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		rebound += pMyShot->ApplyExternalForce( force );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExForceToMyShots( const Hit::RectI &hit, const Vector2DF &force, 
	float linearAttenuation ,float quadraticAttenuation ) const
{
	Vector2DF rebound;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		rebound += pMyShot->ApplyExternalForce( force * 
			GetAttenuation( pMyShot->GetPosition(), hit.GetPosition(), 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToMyShots( float force, const Vector2DF &center ) const
{
	Vector2DF rebound;

	foreach( PMyShot pMyShot, STGControl::getActors()->GetMyShotList() )
	{
		rebound += pMyShot->ApplyExternalForce( 
			GetRadialVector( center, pMyShot->GetPosition(), force ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToMyShots( float force, const Vector2DF &center, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	Vector2DF rebound;

	foreach( PMyShot pMyShot, STGControl::getActors()->GetMyShotList() )
	{
		rebound += pMyShot->ApplyExternalForce( 
			GetRadialVector( center, pMyShot->GetPosition(), force ) * 
			GetAttenuation( pMyShot->GetPosition(), center, 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToMyShots( const CircleI &hit, float force ) const
{
	Vector2DF rebound;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		rebound += pMyShot->ApplyExternalForce( 
			GetRadialVector( hit.GetCenter(), pMyShot->GetPosition(), force ) );
	}

	return rebound;
}

Vector2DF Auxs::ApplyExRadialForceToMyShots( const CircleI &hit, float force, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	Vector2DF rebound;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		rebound += pMyShot->ApplyExternalForce( 
			GetRadialVector( hit.GetCenter(), pMyShot->GetPosition(), force ) * 
			GetAttenuation( pMyShot->GetPosition(), hit.GetCenter(), 
			linearAttenuation, quadraticAttenuation ) );
	}

	return rebound;
}


unsigned Auxs::DestructBullets() const
{
	unsigned count = 0;

	foreach( PBullet pBullet, STGControl::getActors()->GetBulletList() )
	{
		pBullet->Destruct();
		count++;
	}

	return count;
}

unsigned Auxs::DestructBullets( const Hit::CircleI &hit ) const
{
	unsigned count = 0;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		pBullet->Destruct();
		count++;
	}

	return count;
}

unsigned Auxs::DestructBullets( const Hit::RectI &hit ) const
{
	unsigned count = 0;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		pBullet->Destruct();
		count++;
	}

	return count;
}

float Auxs::ApplyDamageToBullets( float damage ) const
{
	foreach( PBullet pBullet, STGControl::getActors()->GetBulletList() )
	{
		pBullet->Destruct( damage );
	}

	return damage * STGControl::getActors()->GetBulletList().size();
}

float Auxs::ApplyDamageToBullets( float damage, const Vector2DF &center, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	float damageSum = 0;

	foreach( PBullet pBullet, STGControl::getActors()->GetBulletList() )
	{
		float d = damage * GetAttenuation( pBullet->GetPosition(), center, 
			linearAttenuation, quadraticAttenuation );

		pBullet->Destruct( d );
		damageSum += d;
	}

	return damageSum;
}

float Auxs::ApplyDamageToBullets( const Hit::CircleI &hit, float damage ) const
{
	unsigned count = 0;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		pBullet->Destruct( damage );
		count++;
	}

	return damage * count;
}

float Auxs::ApplyDamageToBullets( const Hit::CircleI &hit, float damage, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	float damageSum = 0;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		float d = damage * GetAttenuation( pBullet->GetPosition(), hit.GetCenter(), 
			linearAttenuation, quadraticAttenuation );

		pBullet->Destruct( d );
		damageSum += d;
	}

	return damageSum;
}

float Auxs::ApplyDamageToBullets( const Hit::RectI &hit, float damage ) const
{
	unsigned count = 0;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		pBullet->Destruct( damage );
		count++;
	}

	return damage * count;
}

float Auxs::ApplyDamageToBullets( const Hit::RectI &hit, float damage, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	float damageSum = 0;

	auto pBullets = STGControl::getActors()->DetectBulletHitAll( hit );
	foreach( PBullet pBullet, *pBullets )
	{
		float d = damage * GetAttenuation( pBullet->GetPosition(), hit.GetPosition(), 
			linearAttenuation, quadraticAttenuation );

		pBullet->Destruct( d );
		damageSum += d;
	}

	return damageSum;
}


unsigned Auxs::DestructEnemies() const
{
	unsigned count = 0;

	foreach( PEnemy pEnemy, STGControl::getActors()->GetEnemyList() )
	{
		pEnemy->Destruct();
		count++;
	}

	return count;
}

unsigned Auxs::DestructEnemies( const Hit::RectI &hit ) const
{
	unsigned count = 0;

	auto pEnemies = STGControl::getActors()->DetectEnemyHitAll( hit );
	foreach( PEnemy pEnemy, *pEnemies )
	{
		pEnemy->Destruct();
		count++;
	}

	return count;
}

float Auxs::ApplyDamageToEnemies( float damage ) const
{
	foreach( PEnemy pEnemy, STGControl::getActors()->GetEnemyList() )
	{
		pEnemy->Destruct( damage );
	}

	return damage * STGControl::getActors()->GetEnemyList().size();
}

float Auxs::ApplyDamageToEnemies( float damage, const Vector2DF &center, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	float damageSum = 0;

	foreach( PEnemy pEnemy, STGControl::getActors()->GetEnemyList() )
	{
		float d = damage * GetAttenuation( pEnemy->GetPosition(), center, 
			linearAttenuation, quadraticAttenuation );

		pEnemy->Destruct( d );
		damageSum += d;
	}

	return damageSum;
}

float Auxs::ApplyDamageToEnemies( const Hit::RectI &hit, float damage ) const
{
	unsigned count = 0;

	auto pEnemies = STGControl::getActors()->DetectEnemyHitAll( hit );
	foreach( PEnemy pEnemy, *pEnemies )
	{
		pEnemy->Destruct( damage );
		count++;
	}

	return damage * count;
}

float Auxs::ApplyDamageToEnemies( const Hit::RectI &hit, float damage, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	float damageSum = 0;

	auto pEnemies = STGControl::getActors()->DetectEnemyHitAll( hit );
	foreach( PEnemy pEnemy, *pEnemies )
	{
		float d = damage * GetAttenuation( pEnemy->GetPosition(), hit.GetPosition(), 
			linearAttenuation, quadraticAttenuation );

		pEnemy->Destruct( d );
		damageSum += d;
	}

	return damageSum;
}

Game::Mdl::STG::Enemy::PEnemy Auxs::ApplyDamageAndGetEnemy( 
	const Hit::RectI &hit, float damage ) const
{
	auto pEnemy = STGControl::getActors()->DetectEnemyHit( hit );
	if( pEnemy )
	{
		pEnemy->Destruct( damage );
	}
	return pEnemy;
}


unsigned Auxs::DestructMyShots() const
{
	unsigned count = 0;

	foreach( PMyShot pMyShot, STGControl::getActors()->GetMyShotList() )
	{
		pMyShot->Destruct();
		count++;
	}

	return count;
}

unsigned Auxs::DestructMyShots( const Hit::CircleI &hit ) const
{
	unsigned count = 0;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		pMyShot->Destruct();
		count++;
	}

	return count;
}

unsigned Auxs::DestructMyShots( const Hit::RectI &hit ) const
{
	unsigned count = 0;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		pMyShot->Destruct();
		count++;
	}

	return count;
}

float Auxs::ApplyDamageToMyShots( float damage ) const
{
	foreach( PMyShot pMyShot, STGControl::getActors()->GetMyShotList() )
	{
		pMyShot->Destruct( damage );
	}

	return damage * STGControl::getActors()->GetMyShotList().size();
}

float Auxs::ApplyDamageToMyShots( float damage, const Vector2DF &center, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	float damageSum = 0;

	foreach( PMyShot pMyShot, STGControl::getActors()->GetMyShotList() )
	{
		float d = damage * GetAttenuation( pMyShot->GetPosition(), center, 
			linearAttenuation, quadraticAttenuation );

		pMyShot->Destruct( d );
		damageSum += d;
	}

	return damageSum;
}

float Auxs::ApplyDamageToMyShots( const Hit::CircleI &hit, float damage ) const
{
	unsigned count = 0;

	foreach( PMyShot pMyShot, STGControl::getActors()->GetMyShotList() )
	{
		if( pMyShot->IsHit( hit ) )
		{
			pMyShot->Destruct( damage );
			count++;
		}
	}

	return damage * count;
}

float Auxs::ApplyDamageToMyShots( const Hit::CircleI &hit, float damage, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	float damageSum = 0;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		float d = damage * GetAttenuation( pMyShot->GetPosition(), hit.GetCenter(), 
			linearAttenuation, quadraticAttenuation );

		pMyShot->Destruct( d );
		damageSum += d;
	}

	return damageSum;
}

float Auxs::ApplyDamageToMyShots( const Hit::RectI &hit, float damage ) const
{
	unsigned count = 0;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		pMyShot->Destruct( damage );
		count++;
	}

	return damage * count;
}

float Auxs::ApplyDamageToMyShots( const Hit::RectI &hit, float damage, 
	float linearAttenuation, float quadraticAttenuation ) const
{
	float damageSum = 0;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		float d = damage * GetAttenuation( pMyShot->GetPosition(), hit.GetPosition(), 
			linearAttenuation, quadraticAttenuation );

		pMyShot->Destruct( d );
		damageSum += d;
	}

	return damageSum;
}

float Auxs::AffectMyShotsByPA( const Hit::CircleI &hit, float force, float damage, 
	float linearAttenuation, float quadraticAttenuation, 
	const py::object &callback ) const
{
	float damageSum = 0;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		float attenuation = GetAttenuation( pMyShot->GetPosition(), hit.GetCenter(), 
			linearAttenuation, quadraticAttenuation );
		float d = damage * attenuation;
		float f = force * attenuation;

		pMyShot->ApplyExternalForce( 
			GetRadialVector( hit.GetCenter(), pMyShot->GetPosition(), f ) );
		pMyShot->Destruct( d );

		damageSum += pMyShot->GetPADamage();

		callback( pMyShot );
	}

	return damageSum;
}

float Auxs::GetMyShotsForcibleDamageForPA( const Hit::CircleI &hit ) const
{
	float damageSum = 0;

	auto pMyShots = STGControl::getActors()->DetectMyShotHitAll( hit );
	foreach( PMyShot pMyShot, *pMyShots )
	{
		if( pMyShot->IsForcibleForPA() )
		{
			damageSum += pMyShot->GetPADamage();
		}
	}

	return damageSum;
}


namespace
{
	void CreateBulletDrawParam( Auxs::DrawParameter &drawParam, 
		const Auxs::Vector2DF &pos, const Auxs::Vector2DF &size )
	{
		using namespace Selene;

		drawParam.SetSrc( RectF( 0, 0, 64.0f, 64.0f ) );
		drawParam.SetDst( pos.MakeRect( size ) );
		drawParam.SetPriority( View::PRI_ENEMYBULLET );
	}

	typedef Game::Util::Sprite::PTexture PTexture;
}

Auxs::DrawParameter Auxs::GetBulletRedDrawParam( 
	const Vector2DF &pos, const Vector2DF &size ) const
{
	DrawParameter drawParam;
	CreateBulletDrawParam( drawParam, pos, size );
	drawParam.SetTexture( 
		py::extract<PTexture>( 
		mCommonResource.attr( "get" )( "bulletRed" ) ) );

	return drawParam;
}

Auxs::DrawParameter Auxs::GetBulletGreenDrawParam( 
	const Vector2DF &pos, const Vector2DF &size ) const
{
	DrawParameter drawParam;
	CreateBulletDrawParam( drawParam, pos, size );
	drawParam.SetTexture( 
		py::extract<PTexture>( 
		mCommonResource.attr( "get" )( "bulletGreen" ) ) );

	return drawParam;
}

Auxs::DrawParameter Auxs::GetBulletBlueDrawParam( 
	const Vector2DF &pos, const Vector2DF &size ) const
{
	DrawParameter drawParam;
	CreateBulletDrawParam( drawParam, pos, size );
	drawParam.SetTexture( 
		py::extract<PTexture>( 
		mCommonResource.attr( "get" )( "bulletBlue" ) ) );

	return drawParam;
}

Auxs::DrawParameter Auxs::GetBulletWhiteDrawParam( 
	const Vector2DF &pos, const Vector2DF &size ) const
{
	DrawParameter drawParam;
	CreateBulletDrawParam( drawParam, pos, size );
	drawParam.SetTexture( 
		py::extract<PTexture>( 
		mCommonResource.attr( "get" )( "bulletWhite" ) ) );

	return drawParam;
}

Auxs::DrawParameter Auxs::GetBulletPurpleDrawParam( 
	const Vector2DF &pos, const Vector2DF &size ) const
{
	DrawParameter drawParam;
	CreateBulletDrawParam( drawParam, pos, size );
	drawParam.SetTexture( 
		py::extract<PTexture>( 
		mCommonResource.attr( "get" )( "bulletPurple" ) ) );

	return drawParam;
}


py::object Auxs::GetCommonResource() const
{
	return mCommonResource;
}