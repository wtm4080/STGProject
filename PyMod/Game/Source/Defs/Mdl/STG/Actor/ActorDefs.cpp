#include "PCH.h"
#include "ActorDefs.h"

#include "Animation.h"
#include "FadeOut.h"
#include "Particle/Creator.h"
#include "Particle/Parameter.h"
#include "Particle/Particle.h"

using namespace boost::python;
using namespace Defs::Mdl::STG::Actor;
using namespace Game::Util::STG;


void ActorDefs::Configurate()
{
	class_<Base, boost::noncopyable, bases<Game::Mdl::STG::Actor::IActor>>( "STGActorBase", no_init )
		.add_property( "objectId", &Base::GetId )
		.def( "update", &Base::Update )
		.def( "draw", &Base::Draw )
		.add_property( "valid", &Base::IsValid, &Base::SetValid )
		.def( "erase", &Base::Erase )
		.add_property( "validRect", &Base::GetValidRect, &Base::SetValidRect )
		.def( "setValidAreaMargin", &Base::SetValidAreaMargin )
		.add_property( "frameCount", &Base::GetFrameCount, &Base::SetFrameCount )
		.add_property( "validFrameNum", &Base::GetValidFrameNum, &Base::SetValidFrameNum )
		;
	class_<Animation, bases<Base>, PAnimation>( "STGAnimation", 
		init<const Hit::RectI &, const Util::Sprite::Animation::Manager &>() )
		.add_property( "position", &Animation::GetPosition )
		.def( "applyExternalForce", &Animation::ApplyExternalForce )
		.def( "getAnimationManager", &Animation::GetAnimationManager, return_value_policy<copy_non_const_reference>() )
		.def_readwrite( "locator", &Animation::mLocator )
		;
	class_<FadeOut, bases<Base>, PFadeOut>( "STGFadeOut", init<const Hit::RectI &>() )
		.add_property( "position", &FadeOut::GetPosition )
		.def( "applyExternalForce", &FadeOut::ApplyExternalForce )
		.def_readwrite( "drawParam", &FadeOut::mDrawParam )
		.add_property( "frameNum", &FadeOut::GetFrameNum, &FadeOut::SetFrameNum )
		.add_property( "frameCount", &FadeOut::GetFrameCount, &FadeOut::SetFrameCount )
		.def_readwrite( "locator", &FadeOut::mLocator )
		;
	class_<Particle::Creator>( "STGParticleCreator", init<const Particle::Parameter &>() )
		.add_property( "parameter", &Particle::Creator::GetParameter, &Particle::Creator::SetParameter )
		.def( "create", &Particle::Creator::Create )
		;
	class_<Particle::Parameter>( "STGParticleParameter", init<>() )
		.add_property( "drawParameter", &Particle::Parameter::GetDrawParameter, &Particle::Parameter::SetDrawParameter )
		.def( "setPosition", static_cast<void (Particle::Parameter::*)( float, float )>( &Particle::Parameter::SetPosition ) )
		.def( "setPosition", static_cast<void (Particle::Parameter::*)( const Vector2DF & )>( &Particle::Parameter::SetPosition ) )
		.def( "setPositionXRange", static_cast<void (Particle::Parameter::*)( float, float )>( &Particle::Parameter::SetPositionXRange ) )
		.def( "setPositionYRange", static_cast<void (Particle::Parameter::*)( float, float )>( &Particle::Parameter::SetPositionYRange ) )
		.def( "setAngle", &Particle::Parameter::SetAngle )
		.def( "setAngleRange", static_cast<void (Particle::Parameter::*)( float, float )>( &Particle::Parameter::SetAngleRange ) )
		.def( "setSpeed", &Particle::Parameter::SetSpeed )
		.def( "setSpeedRange", static_cast<void (Particle::Parameter::*)( float, float )>( &Particle::Parameter::SetSpeedRange ) )
		.def( "setAccel", &Particle::Parameter::SetAccel )
		.def( "setAccelRange", static_cast<void (Particle::Parameter::*)( float, float )>( &Particle::Parameter::SetAccelRange ) )
		.def( "setZoomRate", &Particle::Parameter::SetZoomRate )
		.def( "setZoomRateRange", static_cast<void (Particle::Parameter::*)( float, float )>( &Particle::Parameter::SetZoomRateRange ) )
		.def( "setZoomDecRate", &Particle::Parameter::SetZoomDecRate )
		.def( "setZoomDecRateRange", static_cast<void (Particle::Parameter::*)( float, float )>( &Particle::Parameter::SetZoomDecRateRange ) )
		.def( "setRotSpeed", &Particle::Parameter::SetRotSpeed )
		.def( "setRotSpeedRange", static_cast<void (Particle::Parameter::*)( float, float )>( &Particle::Parameter::SetRotSpeedRange ) )
		;
	class_<Particle::Particle, bases<Base>, Particle::PParticle>( "STGParticle", 
		init<const Vector2DF &, const Particle::Parameter::DrawParameter &>() )
		.add_property( "position", &Particle::Particle::GetPosition )
		.def( "applyExternalForce", &Particle::Particle::ApplyExternalForce )
		.def_readwrite( "locator", &Particle::Particle::mLocator )
		.def_readwrite( "drawParameter", &Particle::Particle::mDrawParam )
		.add_property( "zoomRate", &Particle::Particle::GetZoomRate, &Particle::Particle::SetZoomRate )
		.add_property( "zoomDecRate", &Particle::Particle::GetZoomDecRate, &Particle::Particle::SetZoomDecRate )
		.add_property( "rotSpeed", &Particle::Particle::GetRotSpeed, &Particle::Particle::SetRotSpeed )
		;
}