#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "SLNFwd.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace STG
{
	class ArrowLocator;
	template <class T>
	class Circling;
	typedef Circling<float> CirclingF;
	typedef Circling<Selene::Sint32> CirclingI;
	class NWay;
	template <typename T>
	class Vector2D;
	typedef Vector2D<float> Vector2DF;
	typedef Vector2D<Selene::Sint32> Vector2DI;

	namespace Hit
	{
		template <class T>
		class Circle;
		typedef Circle<Selene::Sint32> CircleI;
		typedef Circle<float> CircleF;

		template <class T>
		class Rect;
		typedef Rect<Selene::Sint32> RectI;
		typedef Rect<float> RectF;
	}

	namespace Locator
	{
		template <class T>
		class ILocator;
		typedef ILocator<float> ILocatorF;
		typedef ILocator<Selene::Sint32> ILocatorI;

		template <class T>
		class Linear;
		typedef Linear<float> LinearF;
		typedef Linear<Selene::Sint32> LinearI;

		template <class T>
		class Rotate;
		typedef Rotate<float> RotateF;
		typedef Rotate<Selene::Sint32> RotateI;

		template <class T>
		class Trace;
		typedef Trace<float> TraceF;
		typedef Trace<Selene::Sint32> TraceI;
	}
}
}
}