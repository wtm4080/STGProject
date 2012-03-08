#include "PCH.h"
#include "ItemDefs.h"

#include "Defs/Mdl/STG/Actor/Base.h"
#include "Extend.h"
#include "PowerUp.h"
#include "SpAttack.h"

using namespace boost::python;
using namespace Defs::Mdl::STG;
using namespace Item;
using namespace Game::Util::STG;


void ItemDefs::Configurate()
{
	class_<Base, boost::noncopyable, bases<Actor::Base, Game::Mdl::STG::Item::IItem>>( "STGItemBase", no_init )
		.add_property( "position", &Base::GetPosition )
		.def( "applyExternalForce", &Base::ApplyExternalForce )
		.add_property( "hitRadius", &Base::GetHitRadius )
		;
	class_<Extend, bases<Base>, PExtend>( "STGItemExtend", init<const Vector2DF &>() )
		.def( init<const Vector2DF &, float>() )
		;
	class_<PowerUp, bases<Base>, PPowerUp>( "STGItemPowerUp", init<const Vector2DF &>() )
		.def( init<const Vector2DF &, float>() )
		.def( "setEffectCallback", &PowerUp::SetEffectCallback )
		;
	class_<SpAttack, bases<Base>, PSpAttack>( "STGItemSpAttack", init<const Vector2DF &>() )
		.def( init<const Vector2DF &, float>() )
		.def( "setEffectCallback", &SpAttack::SetEffectCallback )
		;
}