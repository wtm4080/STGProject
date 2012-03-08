#include "PCH.h"
#include "HitObject.h"

#include "Util/STG/Hit/Circle.h"
#include "Util/STG/Hit/Rect.h"

using namespace boost::python;
using namespace Game;
using namespace Util::STG;
using namespace Selene;
using namespace Defs::Util;


void HitObject::Configurate()
{
	class_<Hit::CircleF>( "HitCircleF", init<>() )
		.def( init<const Hit::CircleF &>() )
		.def( init<const Hit::CircleI &>() )
		.def( init<float, float, float>() )
		.def( init<Sint32, Sint32, Sint32>() )
		.def( init<const Vector2DF &, float>() )
		.def( init<const Vector2DI &, Sint32>() )
		.def( "isHit", &Hit::CircleF::IsHit<float> )
		.def( "isHit", &Hit::CircleF::IsHit<Sint32> )
		.add_property( "center", 
			static_cast<Vector2DF (Hit::CircleF::*)() const>( &Hit::CircleF::GetCenter ), 
			static_cast<void (Hit::CircleF::*)( const Vector2DF & )>( &Hit::CircleF::SetCenter ) )
		.add_property( "center", 
			static_cast<Vector2DI (Hit::CircleF::*)() const>( &Hit::CircleF::_GetCenter ), 
			static_cast<void (Hit::CircleF::*)( const Vector2DI & )>( &Hit::CircleF::SetCenter ) )
		.add_property( "radius", &Hit::CircleF::GetRadius, &Hit::CircleF::SetRadius<float> )
		;
	class_<Hit::CircleI>( "HitCircleI", init<>() )
		.def( init<const Hit::CircleI &>() )
		.def( init<const Hit::CircleF &>() )
		.def( init<Sint32, Sint32, Sint32>() )
		.def( init<float, float, float>() )
		.def( init<const Vector2DI &, Sint32>() )
		.def( init<const Vector2DF &, float>() )
		.def( "isHit", &Hit::CircleI::IsHit<Sint32> )
		.def( "isHit", &Hit::CircleI::IsHit<float> )
		.add_property( "center", 
			static_cast<Vector2DI (Hit::CircleI::*)() const>( &Hit::CircleI::GetCenter ), 
			static_cast<void (Hit::CircleI::*)( const Vector2DI & )>( &Hit::CircleI::SetCenter ) )
		.add_property( "center", 
			static_cast<Vector2DF (Hit::CircleI::*)() const>( &Hit::CircleI::_GetCenter ), 
			static_cast<void (Hit::CircleI::*)( const Vector2DF & )>( &Hit::CircleI::SetCenter ) )
		.add_property( "radius", &Hit::CircleI::GetRadius, &Hit::CircleI::SetRadius<Sint32> )
		;
	class_<Hit::RectF>( "HitRectF", init<>() )
		.def( init<const Hit::RectF &>() )
		.def( init<const Hit::RectI &>() )
		.def( init<float, float, float, float, bool>() )
		.def( init<Sint32, Sint32, Sint32, Sint32, bool>() )
		.def( init<const Vector2DF &, float, float, bool>() )
		.def( init<const Vector2DI &, Sint32, Sint32, bool>() )
		.def( init<const Vector2DF &, const Vector2DF &, bool>() )
		.def( init<const Vector2DI &, const Vector2DF &, bool>() )
		.def( init<const Vector2DF &, const Vector2DI &, bool>() )
		.def( init<const Vector2DI &, const Vector2DI &, bool>() )
		.def( init<const RectF &>() )
		.def( init<const RectI &>() )
		.def( "isHit", &Hit::RectF::IsHit<float> )
		.def( "isHit", &Hit::RectF::IsHit<Sint32> )
		.add_property( "center", 
			static_cast<Vector2DF (Hit::RectF::*)() const>( &Hit::RectF::GetPosition ), 
			static_cast<void (Hit::RectF::*)( const Vector2DF & )>( &Hit::RectF::SetPosition ) )
		.add_property( "center", 
			static_cast<Vector2DI (Hit::RectF::*)() const>( &Hit::RectF::_GetPosition ), 
			static_cast<void (Hit::RectF::*)( const Vector2DI & )>( &Hit::RectF::SetPosition ) )
		.def( "getPosition", static_cast<Vector2DF (Hit::RectF::*)( bool ) const>( &Hit::RectF::GetPosition ) )
		.def( "setPosition", static_cast<void (Hit::RectF::*)( const Vector2DF &, bool )>( &Hit::RectF::SetPosition ) )
		.def( "setPosition", static_cast<void (Hit::RectF::*)( const Vector2DI &, bool )>( &Hit::RectF::SetPosition ) )
		.add_property( "size", &Hit::RectF::GetWidthHeight, 
			static_cast<void (Hit::RectF::*)( const Vector2DF & )>( &Hit::RectF::SetWidthHeight ) )
		//.add_property( "size", &Hit::RectF::_GetWidthHeight<Sint32>, 
		//	static_cast<void (Hit::RectF::*)( const Vector2DI & )>( &Hit::RectF::SetWidthHeight ) )
		;
	class_<Hit::RectI>( "HitRectI", init<>() )
		.def( init<const Hit::RectI &>() )
		.def( init<const Hit::RectF &>() )
		.def( init<Sint32, Sint32, Sint32, Sint32, bool>() )
		.def( init<float, float, float, float, bool>() )
		.def( init<const Vector2DI &, Sint32, Sint32, bool>() )
		.def( init<const Vector2DF &, float, float, bool>() )
		.def( init<const Vector2DI &, const Vector2DI &, bool>() )
		.def( init<const Vector2DF &, const Vector2DI &, bool>() )
		.def( init<const Vector2DI &, const Vector2DF &, bool>() )
		.def( init<const Vector2DF &, const Vector2DF &, bool>() )
		.def( init<const RectI &>() )
		.def( init<const RectF &>() )
		.def( "isHit", &Hit::RectI::IsHit<Sint32> )
		.def( "isHit", &Hit::RectI::IsHit<float> )
		.add_property( "center", 
			static_cast<Vector2DI (Hit::RectI::*)() const>( &Hit::RectI::GetPosition ), 
			static_cast<void (Hit::RectI::*)( const Vector2DI & )>( &Hit::RectI::SetPosition ) )
		.add_property( "center", 
			static_cast<Vector2DF (Hit::RectI::*)() const>( &Hit::RectI::_GetPosition ), 
			static_cast<void (Hit::RectI::*)( const Vector2DF & )>( &Hit::RectI::SetPosition ) )
		.def( "getPosition", static_cast<Vector2DI (Hit::RectI::*)( bool ) const>( &Hit::RectI::GetPosition ) )
		.def( "setPosition", static_cast<void (Hit::RectI::*)( const Vector2DI &, bool )>( &Hit::RectI::SetPosition ) )
		.def( "setPosition", static_cast<void (Hit::RectI::*)( const Vector2DF &, bool )>( &Hit::RectI::SetPosition ) )
		.add_property( "size", &Hit::RectI::GetWidthHeight, 
			static_cast<void (Hit::RectI::*)( const Vector2DI & )>( &Hit::RectI::SetWidthHeight ) )
		//.add_property( "size", &Hit::RectI::_GetWidthHeight<float>, 
		//	static_cast<void (Hit::RectI::*)( const Vector2DF & )>( &Hit::RectI::SetWidthHeight ) )
		;
}