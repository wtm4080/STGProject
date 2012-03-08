#include "PCH.h"
#include "BulletDefs.h"

#include "Defs/Mdl/STG/Actor/Base.h"
#include "BulletML/MLActor.h"
#include "Simple.h"

using namespace boost::python;
using namespace Defs::Mdl::STG;
using namespace Bullet;
using namespace Game::Util::STG;


void BulletDefs::Configurate()
{
	class_<Base, boost::noncopyable, bases<Actor::Base, Game::Mdl::STG::Bullet::IBullet>>( "STGBulletBase", no_init )
		.def( "isHitCircle", static_cast<bool (Base::*)( const Hit::CircleI &) const>( &Base::IsHit ) )
		.def( "isHitRect", static_cast<bool (Base::*)( const Hit::RectI &) const>( &Base::IsHit ) )
		.def( "destruct", static_cast<void (Base::*)()>( &Base::Destruct ) )
		.def( "applyDamage", static_cast<void (Base::*)( float )>( &Base::Destruct ) )
		.add_property( "hp", &Base::GetHP, &Base::SetHP )
		.add_property( "hitRadius", &Base::GetHitRadius, &Base::SetHitRadius )
		;
	class_<Linear, bases<Base>, PLinear>( "STGBulletLinear", 
		init<const Locator::LinearF &, int, const Linear::DrawParameter &>() )
		.add_property( "position", &Linear::GetPosition )
		.def( "applyExternalForce", &Linear::ApplyExternalForce )
		.def_readwrite( "locator", &Linear::mLocator )
		.def_readwrite( "drawParameter", &Linear::mDrawParam )
		;
	class_<Rotate, bases<Base>, PRotate>( "STGBulletRotate", 
		init<const Locator::RotateF &, int, const Rotate::DrawParameter &>() )
		.add_property( "position", &Rotate::GetPosition )
		.def( "applyExternalForce", &Rotate::ApplyExternalForce )
		.def_readwrite( "locator", &Rotate::mLocator )
		.def_readwrite( "drawParameter", &Rotate::mDrawParam )
		;
	class_<BulletML::CreateParam>( "STGBulletMLCreateParam", init<>() )
		.add_property( "popped", &BulletML::CreateParam::IsPopped, &BulletML::CreateParam::SetPopped )
		.add_property( "hitRadius", &BulletML::CreateParam::GetHitRadius, &BulletML::CreateParam::SetHitRadius )
		.def_readwrite( "drawParameter", &BulletML::CreateParam::mDrawParam )
		.add_property( "hp", &BulletML::CreateParam::GetHP, &BulletML::CreateParam::SetHP )
		;
	class_<BulletML::MLActor, bases<Base>, BulletML::PMLActor>( "STGBulletMLActor", 
		init<BulletML::MLActor::PBMLParser, const Vector2DF &>() )
		.def( init<BulletML::MLActor::PBMLParser, const Locator::LinearF &, int, const BulletML::MLActor::DrawParameter &>() )
		.add_property( "position", &BulletML::MLActor::GetPosition )
		.def( "applyExternalForce", &BulletML::MLActor::ApplyExternalForce )
		.def_readwrite( "locator", &BulletML::MLActor::mLocator )
		.def_readwrite( "drawParameter", &BulletML::MLActor::mDrawParam )
		.def_readonly( "defaultRank", &BulletML::MLActor::DEFAULT_RANK )
		.add_property( "rank", &BulletML::MLActor::GetRank, &BulletML::MLActor::SetRank )
		.def( "createParamList", range( &BulletML::MLActor::GetCreateParamListBegin, &BulletML::MLActor::GetCreateParamListEnd ) )
		.def( "addCreateParam", &BulletML::MLActor::AddCreateParam )
		;
}