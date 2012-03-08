#include "PCH.h"
#include "Vector.h"

#include "Util/STG/Vector2D.h"

using namespace boost::python;
using namespace Game;
using namespace Util::STG;
using namespace Selene;
using namespace Defs::Util;


void Vector::Configurate()
{
	class_<Vector2DF>( "Vector2DF", init<>() )
		.def( init<float, float>() )
		.def( init<Sint32, Sint32>() )
		.def( init<const Vector2DF &>() )
		.def( init<const Vector2DI &>() )
		.def_readwrite( "x", &Vector2DF::x )
		.def_readwrite( "y", &Vector2DF::y )
		.def( self + self )
		.def( self + Vector2DI() )
		.def( self + float() )
		.def( self + Sint32() )
		.def( self - self )
		.def( self - Vector2DI() )
		.def( self - float() )
		.def( self - Sint32() )
		.def( self * self )
		.def( self * Vector2DI() )
		.def( self * float() )
		.def( self * Sint32() )
		.def( self / self )
		.def( self / Vector2DI() )
		.def( self / float() )
		.def( self / Sint32() )
		.def( self += self )
		.def( self += Vector2DI() )
		.def( self += float() )
		.def( self += Sint32() )
		.def( self -= self )
		.def( self -= Vector2DI() )
		.def( self -= float() )
		.def( self -= Sint32() )
		.def( self *= self )
		.def( self *= Vector2DI() )
		.def( self *= float() )
		.def( self *= Sint32() )
		.def( self /= self )
		.def( self /= Vector2DI() )
		.def( self /= float() )
		.def( self /= Sint32() )
		.def( -self )
		.def( "getXY", &Vector2DF::GetXY )
		.def( "setXY", &Vector2DF::SetXY<float>, return_value_policy<copy_non_const_reference>() )
		.def( "getAbs", &Vector2DF::GetAbs )
		.def( "normalize", &Vector2DF::Normalize, return_value_policy<copy_non_const_reference>() )
		.def( "setUnitVector", &Vector2DF::SetUnitVector, return_value_policy<copy_non_const_reference>() )
		.def( "getAngle", 
			static_cast<float (Vector2DF::*)() const>( &Vector2DF::GetAngle ) )
		.def( "getAngle", 
			static_cast<float (Vector2DF::*)( float, float ) const>( &Vector2DF::GetAngle ) )
		.def( "getAngle", 
			static_cast<float (Vector2DF::*)( const Vector2DF & ) const>( &Vector2DF::GetAngle ) )
		.def( "getDistance", &Vector2DF::GetDistance<float> )
		.def( "rotate", 
			static_cast<void (Vector2DF::*)( float )>( &Vector2DF::Rotate ) )
		.def( "rotate", 
			static_cast<void (Vector2DF::*)( float, const Vector2DF & )>( &Vector2DF::Rotate ) )
		.def( "makeRect", 
			static_cast<RectF (Vector2DF::*)( float, float, bool ) const>( &Vector2DF::MakeRect ) )
		.def( "makeRect", 
			static_cast<RectF (Vector2DF::*)( const Vector2DF &, bool ) const>( &Vector2DF::MakeRect ) )
		;
	class_<Vector2DI>( "Vector2DI", init<>() )
		.def( init<Sint32, Sint32>() )
		.def( init<float, float>() )
		.def( init<const Vector2DI &>() )
		.def( init<const Vector2DF &>() )
		.def_readwrite( "x", &Vector2DI::x )
		.def_readwrite( "y", &Vector2DI::y )
		.def( self + self )
		.def( self + Vector2DF() )
		.def( self + float() )
		.def( self + Sint32() )
		.def( self - self )
		.def( self - Vector2DF() )
		.def( self - float() )
		.def( self - Sint32() )
		.def( self * self )
		.def( self * Vector2DF() )
		.def( self * float() )
		.def( self * Sint32() )
		.def( self / self )
		.def( self / Vector2DF() )
		.def( self / float() )
		.def( self / Sint32() )
		.def( self += self )
		.def( self += Vector2DF() )
		.def( self += float() )
		.def( self += Sint32() )
		.def( self -= self )
		.def( self -= Vector2DF() )
		.def( self -= float() )
		.def( self -= Sint32() )
		.def( self *= self )
		.def( self *= Vector2DF() )
		.def( self *= float() )
		.def( self *= Sint32() )
		.def( self /= self )
		.def( self /= Vector2DF() )
		.def( self /= float() )
		.def( self /= Sint32() )
		.def( -self )
		.def( "getXY", &Vector2DI::GetXY )
		.def( "setXY", &Vector2DI::SetXY<Sint32>, return_value_policy<copy_non_const_reference>() )
		.def( "getAbs", &Vector2DI::GetAbs )
		.def( "normalize", &Vector2DI::Normalize, return_value_policy<copy_non_const_reference>() )
		.def( "setUnitVector", &Vector2DI::SetUnitVector, return_value_policy<copy_non_const_reference>() )
		.def( "getAngle", 
			static_cast<Sint32 (Vector2DI::*)() const>( &Vector2DI::GetAngle ) )
		.def( "getAngle", 
			static_cast<Sint32 (Vector2DI::*)( Sint32, Sint32 ) const>( &Vector2DI::GetAngle ) )
		.def( "getAngle", 
			static_cast<Sint32 (Vector2DI::*)( const Vector2DI & ) const>( &Vector2DI::GetAngle ) )
		.def( "getDistance", &Vector2DI::GetDistance<Sint32> )
		.def( "rotate", 
			static_cast<void (Vector2DI::*)( Sint32 )>( &Vector2DI::Rotate ) )
		.def( "rotate", 
			static_cast<void (Vector2DI::*)( Sint32, const Vector2DI & )>( &Vector2DI::Rotate ) )
		.def( "makeRect", 
			static_cast<RectI (Vector2DI::*)( Sint32, Sint32, bool ) const>( &Vector2DI::MakeRect ) )
		.def( "makeRect", 
			static_cast<RectI (Vector2DI::*)( const Vector2DI &, bool ) const>( &Vector2DI::MakeRect ) )
		;
}