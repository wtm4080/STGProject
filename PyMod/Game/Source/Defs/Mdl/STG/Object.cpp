#include "PCH.h"
#include "Object.h"
#include "Auxs.h"

#include "Mdl/STG/Actor/IActor.h"
#include "Mdl/STG/Bullet/IBullet.h"
#include "Mdl/STG/Enemy/IEnemy.h"
#include "Mdl/STG/Item/IItem.h"
#include "Mdl/STG/MyShip/IMyShip.h"
#include "Mdl/STG/MyShot/IMyShot.h"
#include "Mdl/STG/Stage/Stage/IStage.h"
#include "Util/STG/Hit/Circle.h"
#include "Util/STG/Hit/Rect.h"

using namespace boost::python;
using namespace Game::Util::STG;
using namespace Defs::Mdl::STG;
using namespace Selene;


void Object::Configurate()
{
	class_<Auxs>( "STGAuxs", init<>() )
		.def( "createFadeOut", static_cast<Actor::PFadeOut (Auxs::*)( const Auxs::DrawParameter & ) const>( &Auxs::CreateFadeOut ) )
		.def( "createFadeOut", static_cast<Actor::PFadeOut (Auxs::*)( const Auxs::DrawParameter &, unsigned ) const>( &Auxs::CreateFadeOut ) )
		.def( "createParticle", static_cast<void (Auxs::*)( const Auxs::DrawParameter & ) const>( &Auxs::CreateParticle ) )
		.def( "createParticle", static_cast<void (Auxs::*)( const Auxs::DrawParameter &, unsigned ) const>( &Auxs::CreateParticle ) )
		.def( "createExplosion", static_cast<Actor::PAnimation (Auxs::*)( const Auxs::Vector2DF & ) const>( &Auxs::CreateExplosion ) )
		.def( "createExplosion", static_cast<Actor::PAnimation (Auxs::*)( const Auxs::Vector2DF &, const Auxs::Vector2DF & ) const>( &Auxs::CreateExplosion ) )
		.def( "createExplosion", static_cast<Actor::PAnimation (Auxs::*)( const Auxs::Vector2DF &, const Auxs::Vector2DF &, float ) const>( &Auxs::CreateExplosion ) )
		.def( "createExplosion2", static_cast<Actor::PAnimation (Auxs::*)( const Auxs::Vector2DF &, const Auxs::Vector2DF &, float ) const>( &Auxs::CreateExplosion2 ) )
		.def( "createExplosion2", static_cast<Actor::PAnimation (Auxs::*)( const Auxs::Vector2DF &, const Auxs::Vector2DF &, float, Sint32 ) const>( &Auxs::CreateExplosion2 ) )
		.def( "createSmoke", &Auxs::CreateSmoke )
		.def( "eraseActors", &Auxs::EraseActors )
		.def( "eraseBullets", static_cast<unsigned (Auxs::*)() const>( &Auxs::EraseBullets ) )
		.def( "eraseBullets", static_cast<unsigned (Auxs::*)( const Hit::CircleI & ) const>( &Auxs::EraseBullets ) )
		.def( "eraseBullets", static_cast<unsigned (Auxs::*)( const Hit::RectI & ) const>( &Auxs::EraseBullets ) )
		.def( "eraseEnemies", static_cast<unsigned (Auxs::*)() const>( &Auxs::EraseEnemies ) )
		.def( "eraseEnemies", static_cast<unsigned (Auxs::*)( const Hit::RectI & ) const>( &Auxs::EraseEnemies ) )
		.def( "eraseItems", static_cast<unsigned (Auxs::*)() const>( &Auxs::EraseItems ) )
		.def( "eraseItems", static_cast<unsigned (Auxs::*)( const Hit::CircleI & ) const>( &Auxs::EraseItems ) )
		.def( "eraseMyShots", static_cast<unsigned (Auxs::*)() const>( &Auxs::EraseMyShots ) )
		.def( "eraseMyShots", static_cast<unsigned (Auxs::*)( const Hit::CircleI & ) const>( &Auxs::EraseMyShots ) )
		.def( "eraseMyShots", static_cast<unsigned (Auxs::*)( const Hit::RectI & ) const>( &Auxs::EraseMyShots ) )
		.def( "applyExRadialForceToMyShip", static_cast<Vector2DF (Auxs::*)( float, const Vector2DF & ) const>( &Auxs::ApplyExRadialForceToMyShip ) )
		.def( "applyExRadialForceToMyShip", static_cast<Vector2DF (Auxs::*)( float, const Vector2DF &, float, float ) const>( &Auxs::ApplyExRadialForceToMyShip ) )
		.def( "applyExRadialForceToMyShip", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, float ) const>( &Auxs::ApplyExRadialForceToMyShip ) )
		.def( "applyExRadialForceToMyShip", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, float, float, float ) const>( &Auxs::ApplyExRadialForceToMyShip ) )
		.def( "applyExForceToActors", static_cast<Vector2DF (Auxs::*)( const Vector2DF & ) const>( &Auxs::ApplyExForceToActors ) )
		.def( "applyExForceToActors", static_cast<Vector2DF (Auxs::*)( const Vector2DF &, const Vector2DF &, float, float ) const>( &Auxs::ApplyExForceToActors ) )
		.def( "applyExRadialForceToActors", static_cast<Vector2DF (Auxs::*)( float, const Vector2DF & ) const>( &Auxs::ApplyExRadialForceToActors ) )
		.def( "applyExRadialForceToActors", static_cast<Vector2DF (Auxs::*)( float, const Vector2DF &, float, float ) const>( &Auxs::ApplyExRadialForceToActors ) )
		.def( "applyExForceToBullets", static_cast<Vector2DF (Auxs::*)( const Vector2DF & ) const>( &Auxs::ApplyExForceToBullets ) )
		.def( "applyExForceToBullets", static_cast<Vector2DF (Auxs::*)( const Vector2DF &, const Vector2DF &, float, float ) const>( &Auxs::ApplyExForceToBullets ) )
		.def( "applyExForceToBullets", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, const Vector2DF & ) const>( &Auxs::ApplyExForceToBullets ) )
		.def( "applyExForceToBullets", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, const Vector2DF &, float, float ) const>( &Auxs::ApplyExForceToBullets ) )
		.def( "applyExForceToBullets", static_cast<Vector2DF (Auxs::*)( const Hit::RectI &, const Vector2DF & ) const>( &Auxs::ApplyExForceToBullets ) )
		.def( "applyExForceToBullets", static_cast<Vector2DF (Auxs::*)( const Hit::RectI &, const Vector2DF &, float, float ) const>( &Auxs::ApplyExForceToBullets ) )
		.def( "applyExRadialForceToBullets", static_cast<Vector2DF (Auxs::*)( float, const Vector2DF & ) const>( &Auxs::ApplyExRadialForceToBullets ) )
		.def( "applyExRadialForceToBullets", static_cast<Vector2DF (Auxs::*)( float, const Vector2DF &, float, float ) const>( &Auxs::ApplyExRadialForceToBullets ) )
		.def( "applyExRadialForceToBullets", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, float ) const>( &Auxs::ApplyExRadialForceToBullets ) )
		.def( "applyExRadialForceToBullets", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, float, float, float ) const>( &Auxs::ApplyExRadialForceToBullets ) )
		.def( "applyExForceToEnemies", static_cast<Vector2DF (Auxs::*)( const Vector2DF & ) const>( &Auxs::ApplyExForceToEnemies ) )
		.def( "applyExForceToEnemies", static_cast<Vector2DF (Auxs::*)( const Vector2DF &, const Vector2DF &, float, float ) const>( &Auxs::ApplyExForceToEnemies ) )
		.def( "applyExForceToEnemies", static_cast<Vector2DF (Auxs::*)( const Hit::RectI &, const Vector2DF & ) const>( &Auxs::ApplyExForceToEnemies ) )
		.def( "applyExForceToEnemies", static_cast<Vector2DF (Auxs::*)( const Hit::RectI &, const Vector2DF &, float, float ) const>( &Auxs::ApplyExForceToEnemies ) )
		.def( "applyExRadialForceToEnemies", static_cast<Vector2DF (Auxs::*)( float, const Vector2DF & ) const>( &Auxs::ApplyExRadialForceToEnemies ) )
		.def( "applyExRadialForceToEnemies", static_cast<Vector2DF (Auxs::*)( float, const Vector2DF &, float, float ) const>( &Auxs::ApplyExRadialForceToEnemies ) )
		.def( "applyExForceToItems", static_cast<Vector2DF (Auxs::*)( const Vector2DF & ) const>( &Auxs::ApplyExForceToItems ) )
		.def( "applyExForceToItems", static_cast<Vector2DF (Auxs::*)( const Vector2DF &, const Vector2DF &, float, float ) const>( &Auxs::ApplyExForceToItems ) )
		.def( "applyExForceToItems", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, const Vector2DF & ) const>( &Auxs::ApplyExForceToItems ) )
		.def( "applyExForceToItems", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, const Vector2DF &, float, float ) const>( &Auxs::ApplyExForceToItems ) )
		.def( "applyExRadialForceToItems", static_cast<Vector2DF (Auxs::*)( float, const Vector2DF & ) const>( &Auxs::ApplyExRadialForceToItems ) )
		.def( "applyExRadialForceToItems", static_cast<Vector2DF (Auxs::*)( float, const Vector2DF &, float, float ) const>( &Auxs::ApplyExRadialForceToItems ) )
		.def( "applyExRadialForceToItems", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, float ) const>( &Auxs::ApplyExRadialForceToItems ) )
		.def( "applyExRadialForceToItems", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, float, float, float ) const>( &Auxs::ApplyExRadialForceToItems ) )
		.def( "applyExForceToMyShots", static_cast<Vector2DF (Auxs::*)( const Vector2DF & ) const>( &Auxs::ApplyExForceToMyShots ) )
		.def( "applyExForceToMyShots", static_cast<Vector2DF (Auxs::*)( const Vector2DF &, const Vector2DF &, float, float ) const>( &Auxs::ApplyExForceToMyShots ) )
		.def( "applyExForceToMyShots", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, const Vector2DF & ) const>( &Auxs::ApplyExForceToMyShots ) )
		.def( "applyExForceToMyShots", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, const Vector2DF &, float, float ) const>( &Auxs::ApplyExForceToMyShots ) )
		.def( "applyExForceToMyShots", static_cast<Vector2DF (Auxs::*)( const Hit::RectI &, const Vector2DF & ) const>( &Auxs::ApplyExForceToMyShots ) )
		.def( "applyExForceToMyShots", static_cast<Vector2DF (Auxs::*)( const Hit::RectI &, const Vector2DF &, float, float ) const>( &Auxs::ApplyExForceToMyShots ) )
		.def( "applyExRadialForceToMyShots", static_cast<Vector2DF (Auxs::*)( float, const Vector2DF & ) const>( &Auxs::ApplyExRadialForceToMyShots ) )
		.def( "applyExRadialForceToMyShots", static_cast<Vector2DF (Auxs::*)( float, const Vector2DF &, float, float ) const>( &Auxs::ApplyExRadialForceToMyShots ) )
		.def( "applyExRadialForceToMyShots", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, float ) const>( &Auxs::ApplyExRadialForceToMyShots ) )
		.def( "applyExRadialForceToMyShots", static_cast<Vector2DF (Auxs::*)( const Hit::CircleI &, float, float, float ) const>( &Auxs::ApplyExRadialForceToMyShots ) )
		.def( "destructBullets", static_cast<unsigned (Auxs::*)() const>( &Auxs::DestructBullets ) )
		.def( "destructBullets", static_cast<unsigned (Auxs::*)( const Hit::CircleI & ) const>( &Auxs::DestructBullets ) )
		.def( "destructBullets", static_cast<unsigned (Auxs::*)( const Hit::RectI & ) const>( &Auxs::DestructBullets ) )
		.def( "applyDamageToBullets", static_cast<float (Auxs::*)( float ) const>( &Auxs::ApplyDamageToBullets ) )
		.def( "applyDamageToBullets", static_cast<float (Auxs::*)( float, const Vector2DF &, float, float ) const>( &Auxs::ApplyDamageToBullets ) )
		.def( "applyDamageToBullets", static_cast<float (Auxs::*)( const Hit::CircleI &, float ) const>( &Auxs::ApplyDamageToBullets ) )
		.def( "applyDamageToBullets", static_cast<float (Auxs::*)( const Hit::CircleI &, float, float, float ) const>( &Auxs::ApplyDamageToBullets ) )
		.def( "applyDamageToBullets", static_cast<float (Auxs::*)( const Hit::RectI &, float ) const>( &Auxs::ApplyDamageToBullets ) )
		.def( "applyDamageToBullets", static_cast<float (Auxs::*)( const Hit::RectI &, float, float, float ) const>( &Auxs::ApplyDamageToBullets ) )
		.def( "destructEnemies", static_cast<unsigned (Auxs::*)() const>( &Auxs::DestructEnemies ) )
		.def( "destructEnemies", static_cast<unsigned (Auxs::*)( const Hit::RectI & ) const>( &Auxs::DestructEnemies ) )
		.def( "applyDamageToEnemies", static_cast<float (Auxs::*)( float ) const>( &Auxs::ApplyDamageToEnemies ) )
		.def( "applyDamageToEnemies", static_cast<float (Auxs::*)( float, const Vector2DF &, float, float ) const>( &Auxs::ApplyDamageToEnemies ) )
		.def( "applyDamageToEnemies", static_cast<float (Auxs::*)( const Hit::RectI &, float ) const>( &Auxs::ApplyDamageToEnemies ) )
		.def( "applyDamageToEnemies", static_cast<float (Auxs::*)( const Hit::RectI &, float, float, float ) const>( &Auxs::ApplyDamageToEnemies ) )
		.def( "applyDamageAndGetEnemy", &Auxs::ApplyDamageAndGetEnemy )
		.def( "destructMyShots", static_cast<unsigned (Auxs::*)() const>( &Auxs::DestructMyShots ) )
		.def( "destructMyShots", static_cast<unsigned (Auxs::*)( const Hit::CircleI & ) const>( &Auxs::DestructMyShots ) )
		.def( "destructMyShots", static_cast<unsigned (Auxs::*)( const Hit::RectI & ) const>( &Auxs::DestructMyShots ) )
		.def( "applyDamageToMyShots", static_cast<float (Auxs::*)( float ) const>( &Auxs::ApplyDamageToMyShots ) )
		.def( "applyDamageToMyShots", static_cast<float (Auxs::*)( float, const Vector2DF &, float, float ) const>( &Auxs::ApplyDamageToMyShots ) )
		.def( "applyDamageToMyShots", static_cast<float (Auxs::*)( const Hit::CircleI &, float ) const>( &Auxs::ApplyDamageToMyShots ) )
		.def( "applyDamageToMyShots", static_cast<float (Auxs::*)( const Hit::CircleI &, float, float, float ) const>( &Auxs::ApplyDamageToMyShots ) )
		.def( "applyDamageToMyShots", static_cast<float (Auxs::*)( const Hit::RectI &, float ) const>( &Auxs::ApplyDamageToMyShots ) )
		.def( "applyDamageToMyShots", static_cast<float (Auxs::*)( const Hit::RectI &, float, float, float ) const>( &Auxs::ApplyDamageToMyShots ) )
		.def( "affectMyShotsByPA", &Auxs::AffectMyShotsByPA )
		.def( "getMyShotsForcibleDamageForPA", &Auxs::GetMyShotsForcibleDamageForPA )
		.def( "getBulletRedDrawParam", &Auxs::GetBulletRedDrawParam )
		.def( "getBulletGreenDrawParam", &Auxs::GetBulletGreenDrawParam )
		.def( "getBulletBlueDrawParam", &Auxs::GetBulletBlueDrawParam )
		.def( "getBulletWhiteDrawParam", &Auxs::GetBulletWhiteDrawParam )
		.def( "getBulletPurpleDrawParam", &Auxs::GetBulletPurpleDrawParam )
		;

	{
		using namespace Game::Mdl::STG::MyShip;
		class_<IMyShip, boost::noncopyable, PMyShip>( "STGMyShip", no_init )
			.def( "drawInfArea", &IMyShip::DrawInfArea )
			.def( "isHit", &IMyShip::IsHit )
			.def( "isHit_ItemRetrieve", &IMyShip::IsHit_ItemRetrieve )
			.def( "isHit_GetItem", &IMyShip::IsHit_GetItem )
			.def( "destruct", &IMyShip::Destruct )
			.add_property( "power", &IMyShip::GetPower )
			.def( "supplyPower", &IMyShip::SupplyPower )
			.add_property( "spAttack", &IMyShip::GetSpAttack )
			.def( "supplySpAttack", &IMyShip::SupplySpAttack )
			.add_property( "barriered", &IMyShip::IsBarriered )
			.add_property( "barrierCount", &IMyShip::GetBarrierCount )
			.def( "setBarrier", &IMyShip::SetBarrier )
			.add_property( "disappeared", &IMyShip::IsDisappeared )
			.add_property( "position", &IMyShip::GetPosition, &IMyShip::SetPosition )
			.def( "applyExternalForce", &IMyShip::ApplyExternalForce )
			.add_property( "remainder", &IMyShip::GetRemainder )
			.def( "addRemainder", &IMyShip::AddRemainder )
			.def( "setInitRemainder", &IMyShip::SetInitRemainder )
			.def( "setMoveForbidFlag", &IMyShip::SetMoveForbidFlag )
			.def( "setShotForbidFlag", &IMyShip::SetShotForbidFlag )
			.def( "setSpecialAttackForbidFlag", &IMyShip::SetSpecialAttackForbidFlag )
			;
	}
	{
		using namespace Game::Mdl::STG::Actor;
		class_<IActor, boost::noncopyable, PActor>( "STGActor", no_init )
			.add_property( "objectId", &IActor::GetId )
			.add_property( "valid", &IActor::IsValid, &IActor::SetValid )
			.def( "erase", &IActor::Erase )
			.add_property( "position", &IActor::GetPosition )
			.def( "applyExternalForce", &IActor::ApplyExternalForce )
			.add_property( "validRect", &IActor::GetValidRect, &IActor::SetValidRect )
			.def( "setValidAreaMargin", &IActor::SetValidAreaMargin )
			.add_property( "frameCount", &IActor::GetFrameCount, &IActor::SetFrameCount )
			.add_property( "validFrameNum", &IActor::GetValidFrameNum, &IActor::SetValidFrameNum )
			;
		{
			using namespace Game::Mdl::STG::Bullet;
			class_<IBullet, boost::noncopyable, PBullet, bases<IActor>>( "STGBullet", no_init )
				.def( "isHitCircle", static_cast<bool (IBullet::*)( const Hit::CircleI & ) const>( &IBullet::IsHit ) )
				.def( "isHitRect", static_cast<bool (IBullet::*)( const Hit::RectI & ) const>( &IBullet::IsHit ) )
				.def( "destruct", static_cast<void (IBullet::*)()>( &IBullet::Destruct ) )
				.def( "applyDamage", static_cast<void (IBullet::*)( float )>( &IBullet::Destruct ) )
				.add_property( "hp", &IBullet::GetHP )
				.add_property( "hitRadius", &IBullet::GetHitRadius )
				;
		}
		{
			using namespace Game::Mdl::STG::Enemy;
			class_<IEnemy, boost::noncopyable, PEnemy, bases<IActor>>( "STGEnemy", no_init )
				.def( "isHit", &IEnemy::IsHit )
				.def( "destruct", static_cast<void (IEnemy::*)()>( &IEnemy::Destruct ) )
				.def( "applyDamage", static_cast<void (IEnemy::*)( float )>( &IEnemy::Destruct ) )
				.add_property( "hp", &IEnemy::GetHP )
				.add_property( "hitRect", &IEnemy::GetHitRect )
				.add_property( "hitRadius", &IEnemy::GetHitRadius )
				.add_property( "paGenerated", &IEnemy::IsPAGenerated )
				.add_property( "maxPAAmount", &IEnemy::GetMaxPAAmount )
				.add_property( "paAmount", &IEnemy::GetPAAmount )
				;
		}
		{
			using namespace Game::Mdl::STG::Item;
			class_<IItem, boost::noncopyable, PItem, bases<IActor>>( "STGItem", no_init )
				.add_property( "hitRadius", &IItem::GetHitRadius )
				;
		}
		{
			using namespace Game::Mdl::STG::MyShot;
			class_<IMyShot, boost::noncopyable, PMyShot, bases<IActor>>( "STGMyShot", no_init )
				.def( "isHitCircle", static_cast<bool (IMyShot::*)( const Hit::CircleI &) const>( &IMyShot::IsHit ) )
				.def( "isHitRect", static_cast<bool (IMyShot::*)( const Hit::RectI &) const>( &IMyShot::IsHit ) )
				.def( "destruct", static_cast<void (IMyShot::*)()>( &IMyShot::Destruct ) )
				.def( "applyDamage", static_cast<void (IMyShot::*)( float )>( &IMyShot::Destruct ) )
				.add_property( "hp", &IMyShot::GetHP )
				.add_property( "hitRadius", &IMyShot::GetHitRadius )
				.add_property( "paDamage", &IMyShot::GetPADamage )
				.add_property( "forcibleForPA", &IMyShot::IsForcibleForPA )
				;
		}
	}
	{
		using namespace Game::Mdl::STG::Stage::Stage;
		class_<IStage, boost::noncopyable, PStage>( "STGStage", no_init )
			.def( "update", &IStage::Update )
			.def( "draw", &IStage::Draw )
			.add_property( "end", &IStage::IsEnd )
			.add_property( "_internalPyObject", &IStage::GetInternalPyObject )
			;
	}
}