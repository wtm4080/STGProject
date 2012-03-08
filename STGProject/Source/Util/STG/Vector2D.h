#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Common.h"
#include <boost/cast.hpp>


//----------------------------------------------------------------------------------
//	Define
//----------------------------------------------------------------------------------

#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
#define NUMERIC_CAST( t, x ) ( boost::numeric_cast<t>( x ) )
#else
#define NUMERIC_CAST( t, x ) ( static_cast<t>( x ) )
#endif


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace STG
{
	// ２次元ベクトル
	template <typename T>
	class Vector2D
	{
	public:
		// コンストラクタ
		Vector2D()
			: x( 0 )
			, y( 0 )
		{}
		Vector2D( const Vector2D<T> &vec2d )
			: x( vec2d.x )
			, y( vec2d.y )
		{}
		template <typename U>
		Vector2D( const Vector2D<U> &vec2d )
			: x( NUMERIC_CAST( T, vec2d.x ) )
			, y( NUMERIC_CAST( T, vec2d.y ) )
		{}
		Vector2D( T _x, T _y )
			: x( _x )
			, y( _y )
		{}
		template <typename U>
		Vector2D( U _x, U _y )
			: x( NUMERIC_CAST( T, _x ) )
			, y( NUMERIC_CAST( T, _y ) )
		{}

		// 各種演算子
		Vector2D<T> operator + ( const Vector2D<T> &vec2d ) const
		{
			Vector2D<T> ret;
			ret.x = x + vec2d.x;
			ret.y = y + vec2d.y;
			return ret;
		}
		template <typename U>
		Vector2D<T> operator + ( const Vector2D<U> &vec2d ) const
		{
			Vector2D<T> ret;
			ret.x = x + NUMERIC_CAST( T, vec2d.x );
			ret.y = y + NUMERIC_CAST( T, vec2d.y );
			return ret;
		}
		Vector2D<T> operator - ( const Vector2D<T> &vec2d ) const
		{
			Vector2D<T> ret;
			ret.x = x - vec2d.x;
			ret.y = y - vec2d.y;
			return ret;
		}
		template <typename U>
		Vector2D<T> operator - ( const Vector2D<U> &vec2d ) const
		{
			Vector2D<T> ret;
			ret.x = x - NUMERIC_CAST( T, vec2d.x );
			ret.y = y - NUMERIC_CAST( T, vec2d.y );
			return ret;
		}
		Vector2D<T> operator * ( const Vector2D<T> &vec2d ) const
		{
			Vector2D<T> ret;
			ret.x = x * vec2d.x;
			ret.y = y * vec2d.y;
			return ret;
		}
		template <typename U>
		Vector2D<T> operator * ( const Vector2D<U> &vec2d ) const
		{
			Vector2D<T> ret;
			ret.x = x * NUMERIC_CAST( T, vec2d.x );
			ret.y = y * NUMERIC_CAST( T, vec2d.y );
			return ret;
		}
		Vector2D<T> operator / ( const Vector2D<T> &vec2d ) const
		{
			Vector2D ret;
			ret.x = x / vec2d.x;
			ret.y = y / vec2d.y;
			return ret;
		}
		template <typename U>
		Vector2D<T> operator / ( const Vector2D<U> &vec2d ) const
		{
			Vector2D ret;
			ret.x = x / NUMERIC_CAST( T, vec2d.x );
			ret.y = y / NUMERIC_CAST( T, vec2d.y );
			return ret;
		}

		Vector2D<T> &operator = ( const Vector2D<T> &vec2d )
		{
			x = vec2d.x;
			y = vec2d.y;
			return *this;
		}
		template <typename U>
		Vector2D<T> &operator = ( const Vector2D<U> &vec2d )
		{
			x = NUMERIC_CAST( T, vec2d.x );
			y = NUMERIC_CAST( T, vec2d.y );
			return *this;
		}
		Vector2D<T> &operator += ( const Vector2D<T> &vec2d )
		{
			x += vec2d.x;
			y += vec2d.y;
			return *this;
		}
		template <typename U>
		Vector2D<T> &operator += ( const Vector2D<U> &vec2d )
		{
			x += NUMERIC_CAST( T, vec2d.x );
			y += NUMERIC_CAST( T, vec2d.y );
			return *this;
		}
		Vector2D<T> &operator -= ( const Vector2D<T> &vec2d )
		{
			x -= vec2d.x;
			y -= vec2d.y;
			return *this;
		}
		template <typename U>
		Vector2D<T> &operator -= ( const Vector2D<U> &vec2d )
		{
			x -= NUMERIC_CAST( T, vec2d.x );
			y -= NUMERIC_CAST( T, vec2d.y );
			return *this;
		}
		Vector2D<T> &operator *= ( const Vector2D<T> &vec2d )
		{
			x *= vec2d.x;
			y *= vec2d.y;
			return *this;
		}
		template <typename U>
		Vector2D<T> &operator *= ( const Vector2D<U> &vec2d )
		{
			x *= NUMERIC_CAST( T, vec2d.x );
			y *= NUMERIC_CAST( T, vec2d.y );
			return *this;
		}
		Vector2D<T> &operator /= ( const Vector2D<T> &vec2d )
		{
			x /= vec2d.x;
			y /= vec2d.y;
			return *this;
		}
		template <typename U>
		Vector2D<T> &operator /= ( const Vector2D<U> &vec2d )
		{
			x /= NUMERIC_CAST( T, vec2d.x );
			y /= NUMERIC_CAST( T, vec2d.y );
			return *this;
		}

		Vector2D<T> operator + ( T n ) const
		{
			Vector2D<T> ret;
			ret.x = x + n;
			ret.y = y + n;
			return ret;
		}
		template <typename U>
		Vector2D<T> operator + ( U n ) const
		{
			Vector2D<T> ret;
			ret.x = x + NUMERIC_CAST( T, n );
			ret.y = y + NUMERIC_CAST( T, n );
			return ret;
		}
		Vector2D<T> operator - ( T n ) const
		{
			Vector2D<T> ret;
			ret.x = x - n;
			ret.y = y - n;
			return ret;
		}
		template <typename U>
		Vector2D<T> operator - ( U n ) const
		{
			Vector2D<T> ret;
			ret.x = x - NUMERIC_CAST( T, n );
			ret.y = y - NUMERIC_CAST( T, n );
			return ret;
		}
		Vector2D<T> operator * ( T n ) const
		{
			Vector2D<T> ret;
			ret.x = x * n;
			ret.y = y * n;
			return ret;
		}
		template <typename U>
		Vector2D<T> operator * ( U n ) const
		{
			Vector2D<T> ret;
			ret.x = x * NUMERIC_CAST( T, n );
			ret.y = y * NUMERIC_CAST( T, n );
			return ret;
		}
		Vector2D<T> operator / ( T n ) const
		{
			Vector2D<T> ret;
			ret.x = x / n;
			ret.y = y / n;
			return ret;
		}
		template <typename U>
		Vector2D<T> operator / ( U n ) const
		{
			Vector2D<T> ret;
			ret.x = x / NUMERIC_CAST( T, n );
			ret.y = y / NUMERIC_CAST( T, n );
			return ret;
		}

		Vector2D<T> &operator = ( T n )
		{
			x = n;
			y = n;
			return *this;
		}
		template <typename U>
		Vector2D<T> &operator = ( U n )
		{
			x = NUMERIC_CAST( T, n );
			y = NUMERIC_CAST( T, n );
			return *this;
		}
		Vector2D<T> &operator += ( T n )
		{
			x += n;
			y += n;
			return *this;
		}
		template <typename U>
		Vector2D<T> &operator += ( U n )
		{
			x += NUMERIC_CAST( T, n );
			y += NUMERIC_CAST( T, n );
			return *this;
		}
		Vector2D<T> &operator -= ( T n )
		{
			x -= n;
			y -= n;
			return *this;
		}
		template <typename U>
		Vector2D<T> &operator -= ( U n )
		{
			x -= NUMERIC_CAST( T, n );
			y -= NUMERIC_CAST( T, n );
			return *this;
		}
		Vector2D<T> &operator *= ( T n )
		{
			x *= n;
			y *= n;
			return *this;
		}
		template <typename U>
		Vector2D<T> &operator *= ( U n )
		{
			x *= NUMERIC_CAST( T, n );
			y *= NUMERIC_CAST( T, n );
			return *this;
		}
		Vector2D<T> &operator /= ( T n )
		{
			x /= n;
			y /= n;
			return *this;
		}
		template <typename U>
		Vector2D<T> &operator /= ( U n )
		{
			x /= NUMERIC_CAST( T, n );
			y /= NUMERIC_CAST( T, n );
			return *this;
		}

		Vector2D<T> operator - () const
		{
			Vector2D<T> ret;
			ret.x = x * static_cast<T>( -1 );
			ret.y = y * static_cast<T>( -1 );
			return ret;
		}

		std::pair<T, T> GetXY() const
		{
			return std::pair<T, T>( x, y );
		}
		Vector2D<T> &SetXY( T _x, T _y )
		{
			x = _x;
			y = _y;

			return *this;
		}
		template <typename U>
		Vector2D<T> &SetXY( U _x, U _y )
		{
			x = NUMERIC_CAST( T, _x );
			y = NUMERIC_CAST( T, _y );

			return *this;
		}

		// 絶対値を求める
		T GetAbs() const
		{
			return NUMERIC_CAST( T, 
				sqrt( NUMERIC_CAST( double, x*x + y*y ) ) );
		}

		// 正規化する（|v| = 1 にする）
		Vector2D<T> &Normalize()
		{
			T abs = GetAbs();
			if( abs == 0 )
			{
				// 何もしない
			}
			else
			{
				*this /= GetAbs();
			}

			return *this;
		}

		// 角度から単位ベクトルを設定する
		Vector2D<T> &SetUnitVector( T degree )
		{
			float deg = NUMERIC_CAST( float, degree );
			x = NUMERIC_CAST( T, Cos( deg ) );
			y = NUMERIC_CAST( T, Sin( deg ) );

			return *this;
		}

		// 原点からの角度を求める
		T GetAngle() const
		{
			return NUMERIC_CAST( T, Atan2( 
				NUMERIC_CAST( float, y ), NUMERIC_CAST( float, x ) ) );
		}
		// 他の座標への角度を求める
		T GetAngle( T _x, T _y ) const
		{
			return NUMERIC_CAST( T, Atan2( 
				NUMERIC_CAST( float, _y - y ), 
				NUMERIC_CAST( float, _x - x ) ) );
		}
		template <typename U>
		T GetAngle( U _x, U _y ) const
		{
			T 
				__x = NUMERIC_CAST( T, _x ), 
				__y = NUMERIC_CAST( T, _y );

			return NUMERIC_CAST( T, Atan2( 
				NUMERIC_CAST( float, __y - y ), 
				NUMERIC_CAST( float, __x - x ) ) );
		}
		T GetAngle( const Vector2D<T> &pos ) const
		{
			return GetAngle( pos.x, pos.y );
		}
		template <typename U>
		T GetAngle( const Vector2D<U> &pos ) const
		{
			return GetAngle( pos.x, pos.y );
		}

		// 他の座標への距離を求める
		template <typename U>
		T GetDistance( const Vector2D<U> &pos ) const
		{
			return NUMERIC_CAST( T, sqrt( 
				NUMERIC_CAST( double, 
				Pow( pos.x - x ) + Pow( pos.y - y ) ) ) );
		}

		// 回転する
		void Rotate( T degree )
		{
			float deg = NUMERIC_CAST( float, degree );
			float _cos = Cos( deg ), _sin = Sin( deg );
			T _x = x, _y = y;

			x = NUMERIC_CAST( T, ( _cos * _x ) - ( _sin * _y ) );
			y = NUMERIC_CAST( T, ( _sin * _x ) + ( _cos * _y ) );
		}
		void Rotate( T degree, const Vector2D<T> &center )
		{
			float deg = NUMERIC_CAST( float, degree );
			float _cos = Cos( deg ), _sin = Sin( deg );
			T _x = x, _y = y;

			*this -= center;
			x = NUMERIC_CAST( T, ( _cos * _x ) - ( _sin * _y ) );
			y = NUMERIC_CAST( T, ( _sin * _x ) + ( _cos * _y ) );
			*this += center;
		}

		// Senele::Rect<T> の生成
		Selene::Rect<T> MakeRect( T w, T h, bool center = true ) const
		{
			if( center )
			{
				return Selene::Rect<T>( x - w/2, y - h/2, w, h );
			}
			else
			{
				return Selene::Rect<T>( x, y, w, h );
			}
		}
		template <typename U>
		Selene::Rect<T> MakeRect( U w, U h, bool center = true ) const
		{
			T
				_w = NUMERIC_CAST( T, w ), 
				_h = NUMERIC_CAST( T, h );

			if( center )
			{
				return Selene::Rect<T>( x - _w/2, y - _h/2, _w, _h );
			}
			else
			{
				return Selene::Rect<T>( x, y, _w, _h );
			}
		}
		Selene::Rect<T> MakeRect( const Vector2D<T> &widthHeight, bool center = true ) const
		{
			return MakeRect( widthHeight.x, widthHeight.y, center );
		}
		template <typename U>
		Selene::Rect<T> MakeRect( const Vector2D<U> &widthHeight, bool center = true ) const
		{
			return MakeRect( widthHeight.x, widthHeight.y, center );
		}

		operator Selene::Point2D<T>()
		{
			return Selene::Point2D<T>( x, y );
		}

	public:
		T x;
		T y;
	};

	template <typename T>
	inline bool operator == ( const Vector2D<T> &oper1, const Vector2D<T> &oper2 )
	{
		return 
			oper1.x == oper2.x && 
			oper1.y == oper2.y;
	}
	template <typename T>
	inline bool operator != ( const Vector2D<T> &oper1, const Vector2D<T> &oper2 )
	{
		return !( oper1 == oper2 );
	}

	typedef Vector2D<float> Vector2DF;
	typedef Vector2D<Selene::Sint32> Vector2DI;
}
}
}


#undef NUMERIC_CAST