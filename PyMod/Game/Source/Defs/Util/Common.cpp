#include "PCH.h"
#include "Common.h"
#include "Consts.h"
#include "ArrowLocator.h"

#include "Util/STG/Circling.h"

using namespace boost::python;
using namespace Selene;
using namespace Defs::Util;


void Common::Configurate()
{
	class_<Point2DF>( "Point2DF", init<>() )
		.def( init<float, float>() )
		.def( init<const Point2DF &>() )
		.def( init<const Point2DI &>() )
		.def_readwrite( "x", &Point2DF::x )
		.def_readwrite( "y", &Point2DF::y )
		.def( self + self )
		.def( self + float() )
		.def( self - self )
		.def( self - float() )
		.def( self * self )
		.def( self * float() )
		.def( self / self )
		.def( self / float() )
		.def( self += self )
		.def( self += float() )
		.def( self -= self )
		.def( self -= float() )
		.def( self *= self )
		.def( self *= float() )
		.def( self /= self )
		.def( self /= float() )
		.def( "limitLength", &Point2DF::LimitLength )
		.def( "normalize", &Point2DF::Normalize )
		;
	class_<Point2DI>( "Point2DI", init<>() )
		.def( init<Sint32, Sint32>() )
		.def( init<const Point2DI &>() )
		.def( init<const Point2DF &>() )
		.def_readwrite( "x", &Point2DI::x )
		.def_readwrite( "y", &Point2DI::y )
		.def( self + self )
		.def( self + Sint32() )
		.def( self - self )
		.def( self - Sint32() )
		.def( self * self )
		.def( self * Sint32() )
		.def( self / self )
		.def( self / Sint32() )
		.def( self += self )
		.def( self += Sint32() )
		.def( self -= self )
		.def( self -= Sint32() )
		.def( self *= self )
		.def( self *= Sint32() )
		.def( self /= self )
		.def( self /= Sint32() )
		.def( "limitLength", &Point2DI::LimitLength )
		.def( "normalize", &Point2DI::Normalize )
		;
	class_<ColorF>( "ColorF", init<>() )
		.def( init<float>() )
		.def( init<float, float>() )
		.def( init<float, float, float>() )
		.def( init<float, float, float, float>() )
		.def( init<const ColorF &>() )
		.def_readwrite( "r", &ColorF::r )
		.def_readwrite( "g", &ColorF::g )
		.def_readwrite( "b", &ColorF::b )
		.def_readwrite( "a", &ColorF::a )
		.def( self + self )
		.def( self - self )
		.def( self * self )
		.def( self / self )
		.def( self += self )
		.def( self -= self )
		.def( self *= self )
		.def( self /= self )
		.def( self == self )
		.def( self != self )
		;
	class_<RectF>( "RectF", init<>() )
		.def( init<float, float, float, float>() )
		.def( init<const RectF &>() )
		.def( init<const RectI &>() )
		.def_readwrite( "x", &RectF::x )
		.def_readwrite( "y", &RectF::y )
		.def_readwrite( "w", &RectF::w )
		.def_readwrite( "h", &RectF::h )
		.def( "getPosition", &RectF::Position )
		.def( "getLocalPosition", &RectF::LocalPosition )
		.def( "getSize", &RectF::Size )
		.def( "clip", &RectF::Clip )
		.def( "checkHit", &RectF::CheckHit )
		.def( "scaleByCenter", &RectF::ScaleByCenter<float> )
		;
	class_<RectI>( "RectI", init<>() )
		.def( init<Sint32, Sint32, Sint32, Sint32>() )
		.def( init<const RectI &>() )
		.def( init<const RectF &>() )
		.def_readwrite( "x", &RectI::x )
		.def_readwrite( "y", &RectI::y )
		.def_readwrite( "w", &RectI::w )
		.def_readwrite( "h", &RectI::h )
		.def( "getPosition", &RectI::Position )
		.def( "getLocalPosition", &RectI::LocalPosition )
		.def( "getSize", &RectI::Size )
		.def( "clip", &RectI::Clip )
		.def( "checkHit", &RectI::CheckHit )
		.def( "scaleByCenter", &RectI::ScaleByCenter<Sint32> )
		;

	class_<Consts>( "Consts", no_init )
		.def_readonly( "ScreenSize", &Consts::SCREEN_SIZE )
		.def_readonly( "StgInfAreaSize", &Consts::STG_INFAREA_SIZE )
		;

	{
		using namespace Game::Util;

		def( "sin", &Sin );
		def( "cos", &Cos );
		def( "atan2", &Atan2 );

		class_<Random::IRandom, boost::noncopyable, Random::PRandom>( "Random", no_init )
			.def( "getInt", static_cast<int (Random::IRandom::*)( int, int )>( &Random::IRandom::GetInt ) )
			.def( "getFloat", static_cast<float (Random::IRandom::*)( float, float )>( &Random::IRandom::GetFloat ) )
			.def( "getBool", &Random::IRandom::GetBool )
			;

		class_<RepeatCounter>( "RepeatCounter", init<>() )
			.def( init<const RepeatCounter &>() )
			.def( init<float>() )
			.def( "update", &RepeatCounter::UpdateState )
			.add_property( "repeatCount", &RepeatCounter::GetRepeatCount )
			.def( "reset", &RepeatCounter::Reset )
			.add_property( "interval", &RepeatCounter::GetInterval, &RepeatCounter::SetInterval )
			;
	}

	class_<ArrowLocator>( "ArrowLocator", init<int, int, int>() )
		.def( init<int, int, int, bool>() )
		.def( init<int, int, int, bool, bool>() )
		.def( "update", &ArrowLocator::UpdateState )
		.add_property( "position", &ArrowLocator::GetPosition, &ArrowLocator::SetPosition )
		.add_property( "top", &ArrowLocator::GetTop, &ArrowLocator::SetTop )
		.add_property( "bottom", &ArrowLocator::GetBottom, &ArrowLocator::SetBottom )
		.add_property( "horizontal", &ArrowLocator::GetHorizontal, &ArrowLocator::SetHorizontal )
		.add_property( "repeatWait", &ArrowLocator::GetRepeatWait, &ArrowLocator::SetRepeatWait )
		.add_property( "repeatInterval", &ArrowLocator::GetRepeatInterval, &ArrowLocator::SetRepeatInterval )
		.add_property( "controller", &ArrowLocator::GetController, &ArrowLocator::SetController )
		.def( "setMoveCallback", &ArrowLocator::SetMoveCallback )
		;

	{
		using Game::Util::STG::CirclingF;

		class_<CirclingF>( "CirclingF", init<>() )
			.def( init<float>() )
			.def( "update", &CirclingF::Update )
			.add_property( "circling", &CirclingF::IsCircling, &CirclingF::SetCircling )
			.add_property( "angle", &CirclingF::GetAngle, &CirclingF::SetAngle )
			.add_property( "circlingAngle", &CirclingF::GetCirclingAngle, &CirclingF::SetCirclingAngle )
			.add_property( "targetAngle", &CirclingF::GetTargetAngle, &CirclingF::SetTargetAngle )
			;
	}
}