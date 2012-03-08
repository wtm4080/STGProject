#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "../Vector2D.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace STG
{
namespace Hit
{
	template <class T>
	class Circle
	{
	public:
		Circle()
			: mCenter()
			, mRadius()
		{}
		Circle( T x, T y, T radius )
			: mCenter( x, y )
			, mRadius( radius )
		{}
		template <class U>
		Circle( U x, U y, U radius )
			: mCenter( boost::numeric_cast<T>( x ), boost::numeric_cast<T>( y ) )
			, mRadius( boost::numeric_cast<T>( radius ) )
		{}
		Circle( const Vector2D<T> &center, T radius )
			: mCenter( center )
			, mRadius( radius )
		{}
		template <class U>
		Circle( const Vector2D<U> &center, U radius )
			: mCenter( center )
			, mRadius( boost::numeric_cast<T>( radius ) )
		{}
		Circle( const Circle<T> &circle )
			: mCenter( circle.mCenter )
			, mRadius( circle.mRadius )
		{}
		template <class U>
		Circle( const Circle<U> &circle )
			: mCenter( circle.GetCenter() )
			, mRadius( boost::numeric_cast<T>( circle.GetRadius() ) )
		{}

		bool IsHit( const Circle<T> &oper ) const
		{
			if( Pow( oper.mCenter.x - mCenter.x ) + 
				Pow( oper.mCenter.y - mCenter.y ) < 
				Pow( mRadius + oper.mRadius ) )
			{
				return true;
			}

			return false;
		}
		template <class U>
		bool IsHit( const Circle<U> &oper ) const
		{
			return IsHit( Circle<T>( oper ) );
		}

		Vector2D<T> GetCenter() const
		{
			return mCenter;
		}
		template <class U>
		Vector2D<U> _GetCenter() const
		{
			return mCenter;
		}
		void SetCenter( T x, T y )
		{
			mCenter.SetXY( x, y );
		}
		template <class U>
		void SetCenter( U x, U y )
		{
			mCenter.SetXY( x, y );
		}
		void SetCenter( const Vector2D<T> &center )
		{
			mCenter = center;
		}
		template <class U>
		void SetCenter( const Vector2D<U> &center )
		{
			mCenter = center;
		}

		T GetRadius() const
		{
			return mRadius;
		}
		void SetRadius( T radius )
		{
			mRadius = radius;
		}
		template <class U>
		void SetRadius( U radius )
		{
			mRadius = boost::numeric_cast<T>( radius );
		}

	private:
		Vector2D<T> mCenter;
		T mRadius;
	};

	typedef Circle<Selene::Sint32> CircleI;
	typedef Circle<float> CircleF;
}
}
}
}