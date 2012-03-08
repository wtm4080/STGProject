#include "PCH.h"
#include "EnemyDefs.h"

#include "Base.h"
#include "HPGauge.h"

using namespace boost::python;
using namespace Defs::Mdl::STG;
using namespace Enemy;
using namespace Game::Util::STG;


void EnemyDefs::Configurate()
{
	class_<Base, boost::noncopyable, bases<Actor::Base, Game::Mdl::STG::Enemy::IEnemy>>( "STGEnemyBase", no_init )
		.def( "isHit", &Base::IsHit )
		.def( "destruct", static_cast<void (Base::*)()>( &Base::Destruct ) )
		.def( "applyDamage", static_cast<void (Base::*)( float )>( &Base::Destruct ) )
		.add_property( "hp", &Base::GetHP, &Base::SetHP )
		.add_property( "hitRect", &Base::GetHitRect, &Base::SetHitRect )
		.add_property( "hitRadius", &Base::GetHitRadius )
		.add_property( "paGenerated", &Base::IsPAGenerated )
		.add_property( "maxPAAmount", &Base::GetMaxPAAmount )
		.add_property( "paAmount", &Base::GetPAAmount )
		;
	class_<HPGauge>( "STGEnemyHPGauge", init<float>() )
		.def( "update", &HPGauge::Update )
		.def( "draw", &HPGauge::Draw )
		.def( "appear", &HPGauge::Appear )
		.def( "disappear", &HPGauge::Disappear )
		.add_property( "maxValue", &HPGauge::GetMaxValue, &HPGauge::SetMaxValue )
		.add_property( "value", &HPGauge::GetValue, &HPGauge::SetValue )
		.add_property( "visibleValue", &HPGauge::GetVisibleValue )
		;
}