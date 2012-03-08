#include "PCH.h"
#include "MyShotDefs.h"

#include "Base.h"
#include "Linear.h"

using namespace boost::python;
using namespace Defs::Mdl::STG;
using namespace MyShot;
using namespace Game::Util::STG;

void MyShotDefs::Configurate()
{
	class_<Base, boost::noncopyable, bases<Actor::Base, Game::Mdl::STG::MyShot::IMyShot>>( "STGMyShotBase", no_init )
		.def( "isHitCircle", static_cast<bool (Base::*)( const Hit::CircleI & ) const>( &Base::IsHit ) )
		.def( "isHitRect", static_cast<bool (Base::*)( const Hit::RectI & ) const>( &Base::IsHit ) )
		.def( "destruct", static_cast<void (Base::*)()>( &Base::Destruct ) )
		.def( "applyDamage", static_cast<void (Base::*)( float )>( &Base::Destruct ) )
		.add_property( "maxHP", &Base::GetMaxHP, &Base::SetMaxHP )
		.add_property( "hp", &Base::GetHP, &Base::SetHP )
		.add_property( "hitRadius", &Base::GetHitRadius, &Base::SetHitRadius )
		.add_property( "damage", &Base::GetDamage )
		.add_property( "paDamage", &Base::GetPADamage )
		.add_property( "forcibleForPA", &Base::IsForcibleForPA, &Base::SetForcibleForPA )
		.add_property( "noDamage", &Base::IsNoDamage, &Base::SetNoDamage )
		.add_property( "baseDamage", &Base::GetBaseDamage, &Base::SetBaseDamage )
		.add_property( "paBaseDamage", &Base::GetPABaseDamage, &Base::SetPABaseDamage )
		.add_property( "damageRate", &Base::GetDamageRate, &Base::SetDamageRate )
		.add_property( "damageRateDec", &Base::GetDamageRateDec, &Base::SetDamageRateDec )
		.add_property( "damageRateMin", &Base::GetDamageRateMin, &Base::SetDamageRateMin )
		;
	class_<Linear, bases<Base>, PLinear>( "STGMyShotLinear", 
		init<const Linear::Locator &, int, const Linear::DrawParameter &, float>() )
		.def( init<const Linear::Locator &, int, const Linear::DrawParameter &, float, const Linear::Animation &>() )
		.add_property( "position", &Linear::GetPosition )
		.def( "applyExternalForce", &Linear::ApplyExternalForce )
		.def_readwrite( "locator", &Linear::mLocator )
		.def_readwrite( "drawParameter", &Linear::mDrawParam )
		.add_property( "rotDegreeCorrection", &Linear::GetRotDegreeCorrection, &Linear::SetRotDegreeCorrection )
		.def( "setDestructionCallback", &Linear::SetDestructionCallback )
		.add_property( "damageToBullet", &Linear::GetDamageToBullet, &Linear::SetDamageToBullet )
		.add_property( "damageKickbackRateToBullet", &Linear::GetDamageKickbackRateToBullet, &Linear::SetDamageKickbackRateToBullet )
		.def( "setDamageToBulletCallback", &Linear::SetDamageToBulletCallback )
		;
}