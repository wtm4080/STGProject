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
	class Rect
	{
	public:
		Rect()
			: mUpperLeft()
			, mLowerRight()
		{}
		Rect( T x, T y, T width, T height, bool centerPos = true )
			: mUpperLeft( x, y )
			, mLowerRight( x, y )
		{
			if( centerPos )
			{
				Vector2D<T> wh( width/2, height/2 );
				mUpperLeft -= wh;
				mLowerRight += wh;
			}
			else
			{
				mLowerRight += Vector2D<T>( width, height );
			}
		}
		template <class U>
		Rect( U x, U y, U width, U height, bool centerPos = true )
			: mUpperLeft( x, y )
			, mLowerRight( x, y )
		{
			if( centerPos )
			{
				Vector2D<T> wh( width/2, height/2 );
				mUpperLeft -= wh;
				mLowerRight += wh;
			}
			else
			{
				mLowerRight += Vector2D<T>( width, height );
			}
		}
		Rect( const Vector2D<T> &pos, T width, T height, bool centerPos = true )
			: mUpperLeft( pos )
			, mLowerRight( pos )
		{
			if( centerPos )
			{
				Vector2D<T> wh( width/2, height/2 );
				mUpperLeft -= wh;
				mLowerRight += wh;
			}
			else
			{
				mLowerRight += Vector2D<T>( width, height );
			}
		}
		template <class U>
		Rect( const Vector2D<U> &pos, U width, U height, bool centerPos = true )
			: mUpperLeft( pos )
			, mLowerRight( pos )
		{
			if( centerPos )
			{
				Vector2D<T> wh( width/2, height/2 );
				mUpperLeft -= wh;
				mLowerRight += wh;
			}
			else
			{
				mLowerRight += Vector2D<T>( width, height );
			}
		}
		Rect( const Vector2D<T> &pos, const Vector2D<T> &widthHeight, bool centerPos = true )
			: mUpperLeft( pos )
			, mLowerRight( pos )
		{
			if( centerPos )
			{
				mUpperLeft -= widthHeight/2;
				mLowerRight += widthHeight/2;
			}
			else
			{
				mLowerRight += widthHeight;
			}
		}
		Rect( const Selene::Rect<T> &rect )
			: mUpperLeft( rect.x, rect.y )
			, mLowerRight( rect.x + rect.w, rect.y + rect.h )
		{}
		template <class U>
		Rect( const Selene::Rect<U> &rect )
			: mUpperLeft( boost::numeric_cast<T>( rect.x ), boost::numeric_cast<T>( rect.y ) )
			, mLowerRight( boost::numeric_cast<T>( rect.x + rect.w ), boost::numeric_cast<T>( rect.y + rect.h ) )
		{}
		Rect( const Rect<T> &rect )
			: mUpperLeft( rect.mUpperLeft )
			, mLowerRight( rect.mLowerRight )
		{}
		template <class U>
		Rect( const Rect<U> &rect )
			: mUpperLeft( rect.GetPosition( false ) )
			, mLowerRight( rect.GetPosition( false ) + rect.GetWidthHeight() )
		{}

		bool IsHit( const Rect<T> &oper ) const
		{
			if( mUpperLeft.x < oper.mLowerRight.x && 
				oper.mUpperLeft.x < mLowerRight.x && 
				mUpperLeft.y < oper.mLowerRight.y && 
				oper.mUpperLeft.y < mLowerRight.y )
			{
				return true;
			}

			return false;
		}
		template <class U>
		bool IsHit( const Rect<U> &oper ) const
		{
			return IsHit( Rect<T>( oper ) );
		}

		Vector2D<T> GetPosition() const
		{
			return GetPosition( true );
		}
		template <class U>
		Vector2D<U> _GetPosition() const
		{
			return GetPosition( true );
		}
		Vector2D<T> GetPosition( bool centerPos ) const
		{
			if( centerPos )
			{
				return mUpperLeft + GetWidthHeight() / 2;
			}
			else
			{
				return mUpperLeft;
			}
		}
		void SetPosition( T x, T y, bool centerPos = true )
		{
			SetPosition( Vector2D<T>( x, y ), centerPos );
		}
		template <class U>
		void SetPosition( U x, U y, bool centerPos = true )
		{
			SetPosition( Vector2D<T>( x, y ), centerPos );
		}
		void SetPosition( const Vector2D<T> &pos )
		{
			SetPosition( pos, true );
		}
		template <class U>
		void SetPosition( const Vector2D<U> &pos )
		{
			SetPosition( pos, true );
		}
		void SetPosition( const Vector2D<T> &pos, bool centerPos )
		{
			Vector2D<T> widthHeight = GetWidthHeight();

			if( centerPos )
			{
				mUpperLeft = pos;
				mUpperLeft -= widthHeight/2;
			}
			else
			{
				mUpperLeft = pos;
			}

			mLowerRight = mUpperLeft + widthHeight;
		}
		template <class U>
		void SetPosition( const Vector2D<U> &pos, bool centerPos )
		{
			SetPosition( Vector2D<T>( pos ), centerPos );
		}

		Vector2D<T> GetWidthHeight() const
		{
			return mLowerRight - mUpperLeft;
		}
		template<class U>
		Vector2D<U> _GetWidthHeight() const
		{
			return mLowerRight - mUpperLeft;
		}
		void SetWidthHeight( T width, T height, bool centerPos = true )
		{
			SetWidthHeight( Vector2D<T>( width, height ), centerPos );
		}
		template <class U>
		void SetWidthHeight( U width, U height, bool centerPos = true )
		{
			SetWidthHeight( Vector2D<T>( width, height ), centerPos );
		}
		void SetWidthHeight( const Vector2D<T> &widthHeight )
		{
			SetWidthHeight( widthHeight, true );
		}
		template <class U>
		void SetWidthHeight( const Vector2D<U> &widthHeight )
		{
			SetWidthHeight( widthHeight, true );
		}
		void SetWidthHeight( const Vector2D<T> &widthHeight, bool centerPos )
		{
			if( centerPos )
			{
				Vector2D<T> pos = mUpperLeft + GetWidthHeight()/2;

				mUpperLeft = pos - widthHeight/2;
				mLowerRight = pos + widthHeight/2;
			}
			else
			{
				mLowerRight = mUpperLeft + widthHeight;
			}
		}
		template <class U>
		void SetWidthHeight( const Vector2D<T> &widthHeight, bool centerPos = true )
		{
			SetWidthHeight( Vector2D<T>( widthHeight ), centerPos );
		}

	private:
		Vector2D<T> mUpperLeft, mLowerRight;
	};

	typedef Rect<Selene::Sint32> RectI;
	typedef Rect<float> RectF;
}
}
}
}