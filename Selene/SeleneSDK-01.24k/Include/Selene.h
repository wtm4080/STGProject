#pragma once
#ifdef __cplusplus_cli
#pragma managed( push, off )
#endif
#include <windows.h>
#include <xmmintrin.h>
#include <string>
#include <vector>
#include <map>
/**
	@file
	@brief 共通定義
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
// WARNING
//-----------------------------------------------------------------------------------
#pragma inline_depth ( 16 )
#pragma inline_recursion ( on )

#pragma warning ( disable : 4201 )
#pragma warning ( disable : 4995 )

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
// LIBRARY
//-----------------------------------------------------------------------------------
#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "comdlg32.lib" )
#pragma comment( lib, "advapi32.lib" )
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "shell32.lib" )

//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#define OFFSET_OF(Class,Value)				static_cast<Uint16>(offsetof(Class,Value))						///< 構造体オフセット
#define toF(val)							(static_cast<float>(val))										///< floatへのキャスト
#define toI(val)							(static_cast<Sint32>(val))										///< intへのキャスト
#define REV(val)							(1.0f/toF(val))													///< 逆数算出マクロ

#define SAFE_ADDREF(val)					if ( (val) != NULL ) { (val)->AddRef(); }						///< COM安全AddRefマクロ
#define SAFE_RELEASE(val)					if ( (val) != NULL ) { (val)->Release(); (val) = NULL; }		///< COM安全Releaseマクロ
#define SAFE_DELETE(val)					if ( (val) != NULL ) { delete (val); (val) = NULL; }			///< newメモリ安全解放
#define SAFE_DELETE_ARRAY(val)				if ( (val) != NULL ) { delete [] (val); (val) = NULL; }			///< new[]メモリ安全解放

#define V_ALLOC(size)						VirtualAlloc( NULL, size, MEM_COMMIT, PAGE_READWRITE )
#define V_FREE(pointer)						if ( (pointer) != NULL ) { VirtualFree( pointer, 0, MEM_RELEASE ); (pointer) = NULL; }

//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#if defined(SLN_DEBUG)

#define SLN_ABORT()			(*((int*)0x0) = 0x0)
#define SLN_PRINT( ... )	printf( __VA_ARGS__ )

#define SLN_ERROR(msg)															\
{																				\
	char __error_msg__[1024] = "";												\
	sprintf_s(																	\
		__error_msg__,															\
		sizeof(__error_msg__),													\
		"FILE: %s\nLINE: %d\nMESSAGE: %s\n",									\
		__FILE__, __LINE__, msg );												\
	printf( __error_msg__ );													\
	MessageBoxA( ::GetActiveWindow(), __error_msg__, "ERROR", MB_ICONSTOP );	\
	SLN_ABORT();																\
}

#define SLN_ASSERT(flag,msg)														\
{																					\
	if ( !(flag) )																	\
	{																				\
		char __error_msg__[1024] = "";												\
		sprintf_s(																	\
			__error_msg__,															\
			sizeof(__error_msg__),													\
			"FILE: %s\nLINE: %d\nERROR: %s\nMESSAGE: %s\n",							\
			__FILE__, __LINE__, #flag, msg );										\
		printf( __error_msg__ );													\
		MessageBoxA( ::GetActiveWindow(), __error_msg__, "ERROR", MB_ICONSTOP );	\
		SLN_ABORT();																\
	}																				\
}

#else // SLN_DEBUG

#define SLN_ABORT()
#define SLN_PRINT( ... )
#define SLN_ERROR(msg)
#define SLN_ASSERT(flag,msg)

#endif

#define SLN_ERR_MSG( ... )															\
{																					\
	char __title__[512] = "";														\
	sprintf_s( __title__, 512, "%s (line %u)", __FILE__, __LINE__ );				\
	MessageBoxW(																	\
		GetActiveWindow(),															\
		Kernel::String::Utility::Format( __VA_ARGS__ ).c_str(),						\
		Kernel::String::Utility::ToWide( __title__ ).c_str(),						\
		MB_ICONSTOP );																\
	SLN_ABORT();																	\
}

#define SLN_STDCALL		__stdcall
#define SLN_CDECL		__cdecl

//-----------------------------------------------------------------------------------
// TYPEDEF
//-----------------------------------------------------------------------------------
namespace Selene
{
	typedef char					Sint8;					///< signed char 型の別定義
	typedef short					Sint16;					///< signed short 型の別定義
	typedef long					Sint32;					///< signed long 型の別定義
	typedef long long				Sint64;					///< signed long 型の別定義
	typedef unsigned char			Uint8;					///< unsigned char 型の別定義
	typedef unsigned short			Uint16;					///< unsigned short 型の別定義
	typedef unsigned long			Uint32;					///< unsigned long 型の別定義
	typedef unsigned long long		Uint64;					///< unsigned long long 型の別定義
	typedef __m128					Uint128;				///< __m128 型の別定義

	static const Uint32 JOYSTICK_BUTTON_MAX				= 32;
	static const Uint32 JOYSTICK_AXIS_MAX				= (((3 * 2) + 1) * 4) + 2;
	static const Uint32 JOYSTICK_VIRTUAL_BUTTON_MAX		= JOYSTICK_BUTTON_MAX + (JOYSTICK_AXIS_MAX * 2);
	static const float PI								= 3.141592653589793238462643383279f;				///< π
	static const float PI2								= 6.283185307179586476925286766559f;				///< 2π
	static const float PI_INV							= 1.0f / PI;										///< 1.0 / π
	static const float PI2_INV							= 1.0f / PI2;										///< 1.0 / 2π

	/**
		@brief ２次元座標
		@author 葉迩話
		@note ２次元の座標を示すクラス
	*/
	template <typename T>
	class Point2D
	{
	public:
		T x;		///< X座標
		T y;		///< Y座標

	public:
		Point2D()
			: x	( 0 )
			, y	( 0 )
		{
		}

		Point2D( const Point2D<T>& In )
			: x	( In.x )
			, y	( In.y )
		{
		}

		template <typename U>
		Point2D( const Point2D<U>& In )
			: x	( static_cast<T>(In.x) )
			, y	( static_cast<T>(In.y) )
		{
		}

		Point2D( T _x, T _y )
			: x	( _x )
			, y	( _y )
		{
		}

		template <typename U>
		Point2D<T> operator + ( const Point2D<U>& In ) const
		{
			Point2D<T> Out;
			Out.x = x + static_cast<T>(In.x);
			Out.y = y + static_cast<T>(In.y);
			return Out;
		}

		template <typename U>
		Point2D<T> operator - ( const Point2D<U>& In ) const
		{
			Point2D<T> Out;
			Out.x = x - static_cast<T>(In.x);
			Out.y = y - static_cast<T>(In.y);
			return Out;
		}

		template <typename U>
		Point2D<T> operator * ( const Point2D<U>& In ) const
		{
			Point2D<T> Out;
			Out.x = x * static_cast<T>(In.x);
			Out.y = y * static_cast<T>(In.y);
			return Out;
		}

		template <typename U>
		Point2D<T> operator / ( const Point2D<U>& In ) const
		{
			Point2D<T> Out;
			Out.x = x / static_cast<T>(In.x);
			Out.y = y / static_cast<T>(In.y);
			return Out;
		}

		template <typename U>
		Point2D<T>& operator += ( const Point2D<U>& In )
		{
			x += static_cast<T>(In.x);
			y += static_cast<T>(In.y);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator -= ( const Point2D<U>& In )
		{
			x -= static_cast<T>(In.x);
			y -= static_cast<T>(In.y);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator *= ( const Point2D<U>& In )
		{
			x *= static_cast<T>(In.x);
			y *= static_cast<T>(In.y);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator /= ( const Point2D<U>& In )
		{
			x /= static_cast<T>(In.x);
			y /= static_cast<T>(In.y);
			return *this;
		}

		template <typename U>
		Point2D<T> operator + ( U In ) const
		{
			Point2D<T> Out;
			Out.x = x + static_cast<T>(In);
			Out.y = y + static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point2D<T> operator - ( U In ) const
		{
			Point2D<T> Out;
			Out.x = x - static_cast<T>(In);
			Out.y = y - static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point2D<T> operator * ( U In ) const
		{
			Point2D<T> Out;
			Out.x = x * static_cast<T>(In);
			Out.y = y * static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point2D<T> operator / ( U In ) const
		{
			Point2D<T> Out;
			Out.x = x / static_cast<T>(In);
			Out.y = y / static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point2D<T>& operator += ( U In )
		{
			x += static_cast<T>(In);
			y += static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator -= ( U In )
		{
			x -= static_cast<T>(In);
			y -= static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator *= ( U In )
		{
			x *= static_cast<T>(In);
			y *= static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator /= ( U In )
		{
			x /= static_cast<T>(In);
			y /= static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator = ( const Point2D<U>& In )
		{
			x = static_cast<T>(In.x);
			y = static_cast<T>(In.y);
			return *this;
		}

		Point2D<T> LimitLength( float Limit ) const
		{
			float _x = static_cast<float>(x);
			float _y = static_cast<float>(y);
			float Length = sqrtf( (_x * _x) + (_y * _y) );
			if ( Length > Limit )
			{
				float Div = Limit / Length;
				_x *= Div;
				_y *= Div;
			}
			return Point2D<T>( static_cast<T>(_x), static_cast<T>(_y) );
		}

		Point2D<T> Normalize() const
		{
			return LimitLength( 1.0f );
		}
	};

	template <typename T>
	inline bool operator == ( const Point2D<T>& lhs, const Point2D<T>& rhs )
	{
		if ( lhs.x != rhs.x ) return false;
		if ( lhs.y != rhs.y ) return false;
		return true;
	}
	template <typename T>
	inline bool operator != ( const Point2D<T>& lhs, const Point2D<T>& rhs )
	{
		return !(lhs == rhs);
	}

	typedef Point2D<float>	Point2DF;
	typedef Point2D<Sint32>	Point2DI;

	/**
		@brief ３次元座標
		@author 葉迩話
		@note ３次元の座標を示すクラス
	*/
	template <typename T>
	class Point3D
	{
	public:
		T x;		///< X座標
		T y;		///< Y座標
		T z;		///< Z座標

	public:
		Point3D()
			: x	( 0 )
			, y	( 0 )
			, z	( 0 )
		{
		}

		Point3D( const Point3D<T>& In )
			: x	( In.x )
			, y	( In.y )
			, z	( In.z )
		{
		}

		template <typename U>
		Point3D( const Point3D<U>& In )
			: x	( static_cast<T>(In.x) )
			, y	( static_cast<T>(In.y) )
			, z	( static_cast<T>(In.z) )
		{
		}

		Point3D( T _x, T _y, T _z )
			: x	( _x )
			, y	( _y )
			, z	( _z )
		{
		}

		template <typename U>
		Point3D<T> operator + ( const Point3D<U>& In ) const
		{
			Point3D<T> Out;
			Out.x = x + static_cast<T>(In.x);
			Out.y = y + static_cast<T>(In.y);
			Out.z = z + static_cast<T>(In.z);
			return Out;
		}

		template <typename U>
		Point3D<T> operator - ( const Point3D<U>& In ) const
		{
			Point3D<T> Out;
			Out.x = x - static_cast<T>(In.x);
			Out.y = y - static_cast<T>(In.y);
			Out.z = z - static_cast<T>(In.z);
			return Out;
		}

		template <typename U>
		Point3D<T> operator * ( const Point3D<U>& In ) const
		{
			Point3D<T> Out;
			Out.x = x * static_cast<T>(In.x);
			Out.y = y * static_cast<T>(In.y);
			Out.z = z * static_cast<T>(In.z);
			return Out;
		}

		template <typename U>
		Point3D<T> operator / ( const Point3D<U>& In ) const
		{
			Point3D<T> Out;
			Out.x = x / static_cast<T>(In.x);
			Out.y = y / static_cast<T>(In.y);
			Out.z = z / static_cast<T>(In.z);
			return Out;
		}

		template <typename U>
		Point3D<T>& operator += ( const Point3D<U>& In )
		{
			x += static_cast<T>(In.x);
			y += static_cast<T>(In.y);
			z += static_cast<T>(In.z);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator -= ( const Point3D<U>& In )
		{
			x -= static_cast<T>(In.x);
			y -= static_cast<T>(In.y);
			z -= static_cast<T>(In.z);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator *= ( const Point3D<U>& In )
		{
			x *= static_cast<T>(In.x);
			y *= static_cast<T>(In.y);
			z *= static_cast<T>(In.z);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator /= ( const Point3D<U>& In )
		{
			x /= static_cast<T>(In.x);
			y /= static_cast<T>(In.y);
			z /= static_cast<T>(In.z);
			return *this;
		}

		template <typename U>
		Point3D<T> operator + ( const U In ) const
		{
			Point3D<T> Out;
			Out.x = x + static_cast<T>(In);
			Out.y = y + static_cast<T>(In);
			Out.z = z + static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point3D<T> operator - ( const U In ) const
		{
			Point3D<T> Out;
			Out.x = x - static_cast<T>(In);
			Out.y = y - static_cast<T>(In);
			Out.z = z - static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point3D<T> operator * ( const U In ) const
		{
			Point3D<T> Out;
			Out.x = x * static_cast<T>(In);
			Out.y = y * static_cast<T>(In);
			Out.z = z * static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point3D<T> operator / ( const U In ) const
		{
			Point3D<T> Out;
			Out.x = x / static_cast<T>(In);
			Out.y = y / static_cast<T>(In);
			Out.z = z / static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point3D<T>& operator += ( const U In )
		{
			x += static_cast<T>(In);
			y += static_cast<T>(In);
			z += static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator -= ( const U In )
		{
			x -= static_cast<T>(In);
			y -= static_cast<T>(In);
			z -= static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator *= ( const U In )
		{
			x *= static_cast<T>(In);
			y *= static_cast<T>(In);
			z *= static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator /= ( const U In )
		{
			x /= static_cast<T>(In);
			y /= static_cast<T>(In);
			z /= static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator = ( const Point3D<U>& In )
		{
			x = static_cast<T>(In.x);
			y = static_cast<T>(In.y);
			z = static_cast<T>(In.z);
			return *this;
		}
	};

	template <typename T>
	inline bool operator == ( const Point3D<T>& lhs, const Point3D<T>& rhs )
	{
		if ( lhs.x != rhs.x ) return false;
		if ( lhs.y != rhs.y ) return false;
		if ( lhs.z != rhs.z ) return false;
		return true;
	}
	template <typename T>
	inline bool operator != ( const Point3D<T>& lhs, const Point3D<T>& rhs )
	{
		return !(lhs == rhs);
	}

	typedef Point3D<float>	Point3DF;
	typedef Point3D<Sint32>	Point3DI;

	/**
		@brief 矩形定義
		@author 葉迩話
		@note 矩形の定義
	*/
	template <typename T>
	class Rect
	{
	public:
		T	x;		///< X位置
		T	y;		///< Y位置
		T	w;		///< X幅
		T	h;		///< Y幅

	public:
		Rect()
			: x	( 0 )
			, y	( 0 )
			, w	( 0 )
			, h	( 0 )
		{
		}

		Rect( const Rect<T>& In )
			: x	( In.x )
			, y	( In.y )
			, w	( In.w )
			, h	( In.h )
		{
		}

		Rect( T _x, T _y, T _w, T _h )
			: x	( _x )
			, y	( _y )
			, w	( _w )
			, h	( _h )
		{
		}

		Point2D<T> Position() const
		{
			return Point2D<T>( x, y );
		}

		Point2D<T> LocalPosition( const Point2D<T>& Position ) const
		{
			return Point2D<T>( Position.x - x, Position.y - y );
		}

		Point2D<T> Size() const
		{
			return Point2D<T>( w, h );
		}

		Rect<T> Clip( const Rect<T>& In ) const
		{
			T sx1 = In.x;
			T sy1 = In.y;
			T sx2 = In.x + In.w;
			T sy2 = In.y + In.h;

			T dx1 = this->x;
			T dy1 = this->y;
			T dx2 = this->x + this->w;
			T dy2 = this->y + this->h;

			if ( dx1 < sx1 ) dx1 = sx1;
			if ( dy1 < sy1 ) dy1 = sy1;
			if ( dx2 > sx2 ) dx2 = sx2;
			if ( dy2 > sy2 ) dy2 = sy2;

			T x = dx1;
			T y = dy1;
			T w = dx2 - dx1;
			T h = dy2 - dy1;
			if ( x < 0 ) x = 0;
			if ( y < 0 ) y = 0;
			if ( w < 0 ) w = 0;
			if ( h < 0 ) h = 0;

			return Rect<T>( x, y, w, h );
		}

		bool CheckHit( const Point2D<T>& In ) const
		{
			if ( In.x < x ) return false;
			if ( In.y < y ) return false;
			if ( In.x > x + w ) return false;
			if ( In.y > y + h ) return false;

			return true;
		}

		template <typename U>
		Rect<T> ScaleByCenter( U In ) const
		{
			return Rect<T>(
				static_cast<T>(static_cast<U>(x) - In),
				static_cast<T>(static_cast<U>(y) - In),
				static_cast<T>(static_cast<U>(w) + In * 2),
				static_cast<T>(static_cast<U>(h) + In * 2) );
		}

		template <typename U>
		Rect( const Rect<U>& In )
		{
			x = static_cast<T>(In.x);
			y = static_cast<T>(In.y);
			w = static_cast<T>(In.w);
			h = static_cast<T>(In.h);
		}

		template <typename U>
		Rect<T>& operator = ( const Rect<U>& In )
		{
			x = static_cast<T>(In.x);
			y = static_cast<T>(In.y);
			w = static_cast<T>(In.w);
			h = static_cast<T>(In.h);
			return *this;
		}
	};

	template <typename T>
	inline bool operator == ( const Rect<T>& lhs, const Rect<T>& rhs )
	{
		if ( lhs.x != rhs.x ) return false;
		if ( lhs.y != rhs.y ) return false;
		if ( lhs.w != rhs.w ) return false;
		if ( lhs.h != rhs.h ) return false;
		return true;
	}
	template <typename T>
	inline bool operator != ( const Rect<T>& lhs, const Rect<T>& rhs )
	{
		return !(lhs == rhs);
	}

	typedef Rect<float>		RectF;
	typedef Rect<Sint32>	RectI;

	/**
		@brief 色定義
		@author 葉迩話
		@note 色の定義
	*/
	struct ColorU
	{
	public:
		Uint8 r;		///< 色のR要素
		Uint8 g;		///< 色のG要素
		Uint8 b;		///< 色のB要素
		Uint8 a;		///< 色のA要素

	public:
		ColorU( Uint8 _r = 0xFF, Uint8 _g = 0xFF, Uint8 _b = 0xFF, Uint8 _a = 0xFF )
			: r	( _r )
			, g	( _g )
			, b	( _b )
			, a	( _a )
		{
		}

		ColorU( Uint32 c )
			: r	( static_cast<Uint8>((c >>  0) & 0xFF) )
			, g	( static_cast<Uint8>((c >>  8) & 0xFF) )
			, b	( static_cast<Uint8>((c >> 16) & 0xFF) )
			, a	( static_cast<Uint8>((c >> 24) & 0xFF) )
		{
		}

		Uint32 GetRGBA() const
		{
			return (a << 24) | (b << 16) | (g << 8) | (r << 0);
		}

		ColorU& operator = ( Uint32 value )
		{
			*this = ColorU( value );
			return *this;
		}
	};

	inline bool operator == ( const ColorU& lhs, const ColorU& rhs )
	{
		if ( lhs.r != rhs.r ) return false;
		if ( lhs.g != rhs.g ) return false;
		if ( lhs.b != rhs.b ) return false;
		if ( lhs.a != rhs.a ) return false;
		return true;
	}

	inline bool operator != ( const ColorU& lhs, const ColorU& rhs )
	{
		return !(lhs == rhs);
	}

	/**
		@brief 色定義
		@author 葉迩話
		@note 色の定義
	*/
	struct ColorF
	{
	public:
		float r;		///< 色のR要素
		float g;		///< 色のG要素
		float b;		///< 色のB要素
		float a;		///< 色のA要素

	public:
		ColorF( float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f )
			: r	( _r )
			, g	( _g )
			, b	( _b )
			, a	( _a )
		{
		}

		ColorF( Uint32 c )
			: r	( static_cast<float>((c >>  0) & 0xFF) / 255.0f )
			, g	( static_cast<float>((c >>  8) & 0xFF) / 255.0f )
			, b	( static_cast<float>((c >> 16) & 0xFF) / 255.0f )
			, a	( static_cast<float>((c >> 24) & 0xFF) / 255.0f )
		{
		}

		Uint32 GetRGBA() const
		{
			Sint32 r = static_cast<Sint32>(this->r * 255.0f);
			Sint32 g = static_cast<Sint32>(this->g * 255.0f);
			Sint32 b = static_cast<Sint32>(this->b * 255.0f);
			Sint32 a = static_cast<Sint32>(this->a * 255.0f);
			if ( r < 0x00 ) r = 0x00;
			if ( g < 0x00 ) g = 0x00;
			if ( b < 0x00 ) b = 0x00;
			if ( a < 0x00 ) a = 0x00;
			if ( r > 0xFF ) r = 0xFF;
			if ( g > 0xFF ) g = 0xFF;
			if ( b > 0xFF ) b = 0xFF;
			if ( a > 0xFF ) a = 0xFF;
			return (a << 24) | (b << 16) | (g << 8) | (r << 0);
		}

		ColorF& operator = ( Uint32 value )
		{
			*this = ColorF( value );
			return *this;
		}

		ColorF operator + ( const ColorF &In ) const
		{
			ColorF Out;
			Out.a = a + In.a;
			Out.r = r + In.r;
			Out.g = g + In.g;
			Out.b = b + In.b;
			return Out;
		}

		ColorF operator - ( const ColorF &In ) const
		{
			ColorF Out;
			Out.a = a - In.a;
			Out.r = r - In.r;
			Out.g = g - In.g;
			Out.b = b - In.b;
			return Out;
		}

		ColorF operator * ( const ColorF &In ) const
		{
			ColorF Out;
			Out.a = a * In.a;
			Out.r = r * In.r;
			Out.g = g * In.g;
			Out.b = b * In.b;
			return Out;
		}

		ColorF operator / ( const ColorF &In ) const
		{
			ColorF Out;
			Out.a = a / In.a;
			Out.r = r / In.r;
			Out.g = g / In.g;
			Out.b = b / In.b;
			return Out;
		}

		ColorF& operator += ( const ColorF &In )
		{
			a += In.a;
			r += In.r;
			g += In.g;
			b += In.b;
			return *this;
		}

		ColorF& operator -= ( const ColorF &In )
		{
			a -= In.a;
			r -= In.r;
			g -= In.g;
			b -= In.b;
			return *this;
		}

		ColorF& operator *= ( const ColorF &In )
		{
			a *= In.a;
			r *= In.r;
			g *= In.g;
			b *= In.b;
			return *this;
		}

		ColorF& operator /= ( const ColorF &In )
		{
			a /= In.a;
			r /= In.r;
			g /= In.g;
			b /= In.b;
			return *this;
		}
	};

	inline bool operator == ( const ColorF& lhs, const ColorF& rhs )
	{
		if ( lhs.r != rhs.r ) return false;
		if ( lhs.g != rhs.g ) return false;
		if ( lhs.b != rhs.b ) return false;
		if ( lhs.a != rhs.a ) return false;
		return true;
	}

	inline bool operator != ( const ColorF& lhs, const ColorF& rhs )
	{
		return !(lhs == rhs);
	}
}

//-----------------------------------------------------------------------------------
// INLINE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief 整数⇒浮動小数変換
		@author 葉迩倭
		@param iVal		[in] 入力値
		@return 浮動小数点化された入力値
		@note
		メモリ上の状態をそのままに浮動小数点に変換します
	*/
	inline float toFloat( Sint32 iVal )
	{
		return *reinterpret_cast<float*>(&iVal);
	}

	/**
		@brief 整数⇒浮動小数変換
		@author 葉迩倭
		@param iVal		[in] 入力値
		@return 浮動小数点化された入力値
		@note
		メモリ上の状態をそのままに浮動小数点に変換します
	*/
	inline float toFloat( Uint32 iVal )
	{
		return *reinterpret_cast<float*>(&iVal);
	}

	/**
		@brief 浮動小数⇒整数変換
		@author 葉迩倭
		@param Value		[in] 入力値
		@return 整数化された入力値
		@note
		メモリ上の状態をそのままに整数に変換します
	*/
	inline Sint32 toInt( float Value )
	{
		return *reinterpret_cast<Sint32*>(&Value);
	}

	/**
		@brief 浮動小数⇒整数変換
		@author 葉迩倭
		@param Value		[in] 入力値
		@return 整数化された入力値
		@note
		メモリ上の状態をそのままに整数に変換します
	*/
	inline Uint32 toUint( float Value )
	{
		return *reinterpret_cast<Uint32*>(&Value);
	}

	/**
		@brief FP16⇒FP32変換
		@author 葉迩倭
		@param In	[in] 16bit浮動小数点
		@return 32Bit浮動小数点
		@note
		16Bit浮動小数点を32Bit浮動小数点に変換します。
	*/
	inline float FP16toFP32( Uint16 In )
	{
		Uint32 Out = In;
		Out = ((Out & 0x8000) << 16) + ((((Out & 0x7C00) >> 10) - 15 + 127) << 23) + ((Out & 0x3FF) << 13);
		return toFloat( Out );
	}

	/**
		@brief sqrt算出
		@author 葉迩倭
		@param Value		[in] 入力値
		@return Valueのsqrt値
		@note
		精度を犠牲に高速にsqrtを取得します
	*/
	inline float FastSqrt( float Value )
	{
		Sint32 iVal = toInt( Value );

		iVal &= 0x7FFFFFFF;
		iVal -= 0x3F800000;
		iVal >>= 1;
		iVal += 0x3F800000;

		return toFloat( iVal );
	}

	/**
		@brief sqrtの逆数算出
		@author 葉迩倭
		@param Value		[in] 入力値
		@return Valueのsqrtの逆数
		@note
		精度を犠牲に高速にsqrtの逆数を取得します
	*/
	inline float InvSqrt( float Value )
	{
		float ValHalf = Value * 0.5f;

		Sint32 iVal = toInt( Value );

		iVal = 0x5F375A86 - (iVal >> 1);

		Value = toFloat( iVal );

		return Value * (1.5f - ValHalf * Value * Value);
	}

	/**
		@brief 絶対値取得
		@author 葉迩倭
		@param Value		[in] 入力値
		@return 入力値の絶対値
		@note
		指定されたア値の絶対値を取得します
	*/
	inline float Abs( const float Value )
	{
		Sint32 iVal = toInt( Value );

		iVal &= 0x7FFFFFFF;

		return toFloat( iVal );
	}

	/**
		@brief 絶対値取得
		@author 葉迩倭
		@param iVal		[in] 入力値
		@return 入力値の絶対値
		@note
		指定されたア値の絶対値を取得します
	*/
	inline Sint32 Abs( const Sint32 iVal )
	{
		return iVal < 0 ? -iVal : +iVal;
	}

	/**
		@brief 2Byte文字チェック
		@author 葉迩倭
		@retval true	2Byte文字
		@retval false	1Byte文字
		@note
		指定されたASCII文字が2Byte文字の1文字目かどうかをチェックします。
	*/
	inline bool Is2ByteChara( char Src )
	{
		Uint8 Code = *reinterpret_cast<Uint8*>(&Src);

		if ( Code <= 0x80 ) return false;
		if ( Code <= 0x9F ) return true;
		if ( Code <= 0xDF ) return false;
		if ( Code <= 0xFE ) return true;

		return false;
	}

	/**
		@brief エンディアンのチェック
		@author 葉迩倭
		@retval true	リトルエンディアン
		@retval false	ビッグエンディアン
		@note
		リトルエンディアン環境かをチェックします
	*/
	inline bool IsLittleEndian()
	{
		static union
		{
			Uint8  Byte[2];
			Uint16 UShort;
		}
		Union = { 0x00, 0xFF };

		return Union.UShort == 0xFF00;
	}

	/**
		@brief エンディアンの変換
		@author 葉迩倭
		@param In	[in] 変換元
		@return 変換後の値
		@note
		リトル⇔ビッグでエンディアンの変換をします
	*/
	template <typename T>
	inline T ChengeEndian( const T& In )
	{
		const Uint8* pByte = reinterpret_cast<const Uint8*>(&In);

		switch ( sizeof(T) )
		{
		case 2:
			{
				Uint8 Temp[] = { pByte[1], pByte[0] } __declspec( align( 2 ) );
				return *reinterpret_cast<T*>(Temp);
			}
			break;
		case 4:
			{
				Uint8 Temp[] = { pByte[3], pByte[2], pByte[1], pByte[0] } __declspec( align( 4 ) );
				return *reinterpret_cast<T*>(Temp);
			}
			break;
		case 8:
			{
				Uint8 Temp[] = { pByte[7], pByte[6], pByte[5], pByte[4], pByte[3], pByte[2], pByte[1], pByte[0] } __declspec( align( 8 ) );
				return *reinterpret_cast<T*>(Temp);
			}
			break;
		}

		return In;
	}

	/**
		@brief 最小値
		@author 葉迩倭
		@param lhs	[in] 比較値
		@param rhs	[in] 比較値
		@note
		２つの数値のうち小さい値を返します
	*/
	template <typename T, typename U>
	T Min( T lhs, U rhs )
	{
		return (lhs < rhs) ? lhs : rhs;
	}

	/**
		@brief 最大値
		@author 葉迩倭
		@param lhs	[in] 比較値
		@param rhs	[in] 比較値
		@note
		２つの数値のうち大きい値を返します
	*/
	template <typename T, typename U>
	T Max( T lhs, U rhs )
	{
		return (lhs > rhs) ? lhs : rhs;
	}

	/**
		@brief 値交換
		@author 葉迩倭
		@param lhs	[in] 値
		@param rhs	[in] 値
		@note
		２つの数値の値を好感します。
	*/
	template <typename T>
	void Swap( T& lhs, T& rhs )
	{
		lhs = rhs - lhs;
		rhs -= lhs;
		lhs += rhs;
	}
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief インターフェイス
		@author 葉迩倭

		@note
		インターフェイスの基底クラス
	*/
	class Interface
	{
	protected:
		virtual ~Interface(){}

	public:
		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			@note
			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Sint32 Release() = 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			@note
			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Sint32 AddRef() = 0;

		/**
			@brief 参照カウンタ取得
			@author 葉迩倭
			@return 参照カウント

			@note
			現在の参照カウンタを取得
		*/
		virtual Sint32 GetReferenceCount() = 0;
	};
}


#ifdef __cplusplus_cli
#pragma managed( push, off )
#endif
/**
	@file
	@brief Engine基本定義
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
/**
	@brief ライブラリ名前空間
*/
namespace Selene
{
	/**
		@brief カーネル
	*/
	namespace Kernel
	{
		namespace Math
		{
			class Vector2;
			class Vector3;
			class Vector4;
			class VectorS;
			class Quaternion;
			class Matrix;
			class Camera;
		}

		namespace Collision
		{
			class AABB;
			class OBB;
			class Plane;
			class Sphere;
		}

		namespace File
		{
			class FileControl;
			class LogFile;
		}
	}
}


/**
	@file
	@brief コピー禁止オブジェクト
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Object
{
	/**
		@brief コピー禁止クラス
		@author 葉迩倭
	*/
	class NoneCopyableObject
	{
	private:
		NoneCopyableObject& operator = ( const NoneCopyableObject& In );

	public:
		NoneCopyableObject() {}
		virtual ~NoneCopyableObject() {}
	};
}
}
}




//----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Misc
{
	class ModuleLoader
	{
	private:
		HMODULE						m_hDLL;
		std::map<std::string,void*>	m_Function;

	public:
		ModuleLoader();
		~ModuleLoader();
		bool Load( const wchar_t* pModuleName );
		void Unload();
		bool LoadFunction( const char* pFunction );
		void* GetFunction( const char* pFunction );
	};
}
}
}


/**
	@file
	@brief アトミック変数
	@author 葉迩倭
*/


//----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Thread
{
	/*
		@brief アトミック変数
		@author 葉迩倭
	*/
	class Atomic
	{
	private:
		volatile Sint32 m_Value;

	public:
		/*
			@brief コンストラクタ
			@author 葉迩倭
			@param Value	[in] 初期値
		*/
		Atomic( Sint32 Value = 0 );
		/*
			@brief デストラクタ
			@author 葉迩倭
		*/
		~Atomic();
		/*
			@brief 値取得
			@author 葉迩倭
			@return アトミックの値
			@note
			アトミックの値を取得します。
		*/
		Sint32 Get() const;
		/*
			@brief 値設定
			@author 葉迩倭
			@param Value	アトミックの値
			@note
			アトミックの値を設定します。
		*/
		void Set( Sint32 Value );
		/*
			@brief 加算
			@author 葉迩倭
			@param Value	アトミックの値
			@note
			アトミックの値を加算します。
		*/
		Sint32 Add( Sint32 Value );
		/*
			@brief インクリメント
			@author 葉迩倭
			@return インクリメント後の値
			@note
			アトミックの値をインクリメントします。
		*/
		Sint32 Increment();
		/*
			@brief デクリメント
			@author 葉迩倭
			@return デクリメント後の値
			@note
			アトミックの値をデクリメントします。
		*/
		Sint32 Decrement();

		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		void operator = ( Sint32 Value );
		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		bool operator == ( Sint32 Value ) const;
		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		bool operator != ( Sint32 Value ) const;
		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		bool operator < ( Sint32 Value ) const;
		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		bool operator > ( Sint32 Value ) const;
		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		bool operator <= ( Sint32 Value ) const;
		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		bool operator >= ( Sint32 Value ) const;
		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		void operator = ( const Atomic& Value );
		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		bool operator == ( const Atomic& Value ) const;
		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		bool operator != ( const Atomic& Value ) const;
		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		bool operator < ( const Atomic& Value ) const;
		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		bool operator > ( const Atomic& Value ) const;
		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		bool operator <= ( const Atomic& Value ) const;
		/*
			@brief オペレーター
			@author 葉迩倭
		*/
		bool operator >= ( const Atomic& Value ) const;
	};
}
}
}


/**
	@file
	@brief メモリ操作
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Memory
{
	/**
		@brief メモリクリア
		@author 葉迩倭
		@param pDst	[in] クリア先
		@param Size	[in] クリア値
		@note
		メモリをクリアします
	*/
	void Clear( void* pDst, size_t Size );
	/**
		@brief メモリ初期化
		@author 葉迩倭
		@param pDst	[in] クリア先
		@param Src	[in] クリア値
		@param Size	[in] クリアbyte数
		@note
		メモリを指定した値でクリアします
	*/
	void Fill( void* pDst, Uint8 Src, size_t Size );
	/**
		@brief メモリ移動
		@author 葉迩倭
		@param pDst	[in] 移動先
		@param pSrc	[in] 移動元
		@param Size	[in] 移動byte数
		@note
		メモリの内容をを移動します
	*/
	void Move( void* pDst, const void* pSrc, size_t Size );
	/**
		@brief メモリコピー
		@author 葉迩倭
		@param pDst	[in] コピー先
		@param pSrc	[in] コピー元
		@param Size	[in] コピーbyte数
		@note
		メモリの内容をコピーします
	*/
	void Copy( void* pDst, const void* pSrc, size_t Size );
	/**
		@brief 16Byteアライメントメモリ確保
		@author 葉迩倭
		@param Size		[in] 確保するbyte数
		@return メモリポインタ
		@note
		16Byteアライメントされたメモリを確保します。
	*/
	void* Alloc( size_t Size );
	/**
		@brief 16Byteアライメントメモリ確保
		@author 葉迩倭
		@param Size		[in] 確保するbyte数
		@param Init		[in] メモリの初期値
		@return メモリポインタ
		@note
		16Byteアライメントされたメモリを確保します。
	*/
	void* Alloc( size_t Size, Uint8 Init );
	/**
		@brief 16Byteアライメントメモリ解放
		@author 葉迩倭
		@param pData	[in] 解放するメモリ
		@note
		16Byteアライメントされたメモリを解放します。
	*/
	void Free( const void* pData );
}
}
}


/**
	@file
	@brief メモリ管理用オブジェクト
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Object
{
	/**
		@brief メモリ管理用オブジェクト
		@author 葉迩倭
		@note
		16Byteアラインされたクラスを生成する為に使います。
	*/
	class MemoryObject
	{
	public:
		/**
			@brief newオーバーライド
			@param Size	[in] 確保サイズ
		*/
		void *operator new ( size_t Size )
		{
			return Memory::Alloc( Size );
		}
		/**
			@brief deleteオーバーライド
			@param pData	[in] 解放領域
		*/
		void operator delete ( void* pData )
		{
			Memory::Free( pData );
		}
		/**
			@brief new[]オーバーライド
			@param Size	[in] 確保サイズ
		*/
		void *operator new[] ( size_t Size )
		{
			return Memory::Alloc( Size );
		}
		/**
			@brief delete[]オーバーライド
			@param pData	[in] 解放領域
		*/
		void operator delete[] ( void* pData )
		{
			Memory::Free( pData );
		}
	};
}
}
}


/**
	@file
	@brief 参照カウンタオブジェクト
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Object
{
	/**
		@brief 参照カウンタクラス
		@author 葉迩倭
	*/
	class ReferenceObject
		: public MemoryObject
		, public NoneCopyableObject
	{
	private:
		Thread::Atomic m_ReferenceCount;

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		ReferenceObject()
			: m_ReferenceCount	( 1 )
		{
		}
		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		virtual ~ReferenceObject()
		{
		}
		/**
			@brief 参照カウント取得
			@author 葉迩倭
			@return 参照カウント
			@note
			現在の参照カウントを取得します。
		*/
		virtual Sint32 GetReferenceCount()
		{
			return m_ReferenceCount.Get();
		}
		/**
			@brief 参照カウントインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント
			@note
			参照カウントの値をインクリメントします
		*/
		virtual Sint32 AddRef()
		{
			return m_ReferenceCount.Increment();
		}
		/**
			@brief 参照カウントデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント
			@note
			参照カウントの値をデクリメントし、<BR>
			0になったらdeleteします。
		*/
		virtual Sint32 Release()
		{
			Sint32 Count = m_ReferenceCount.Decrement();
			if ( Count == 0 )
			{
				delete this;
			}
			return Count;
		}
	};
}
}
}


/**
	@file
	@brief クリティカルセクション
	@author 葉迩倭
*/


//----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Thread
{
	/*
		@brief クリティカルセクション
		@author 葉迩倭
	*/
	class CriticalSection
		: public Object::NoneCopyableObject
	{
	private:
		mutable CRITICAL_SECTION m_CriticalSection;

	public:
		/*
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CriticalSection();
		/*
			@brief デストラクタ
			@author 葉迩倭
		*/
		~CriticalSection();
		/*
			@brief クリティカルセクションに入る
			@author 葉迩倭
		*/
		void Enter() const;
		/*
			@brief クリティカルセクションから出る
			@author 葉迩倭
		*/
		void Leave() const;
	};

	/*
		@brief 自動クリティカルセクション
		@author 葉迩倭
	*/
	class ScopedLock
		: public Object::NoneCopyableObject
	{
	private:
		const CriticalSection& m_cs;

	public:
		/*
			@brief コンストラクタ
			@author 葉迩倭
			@note
			自動的にクリティカルセクションに入ります
		*/
		ScopedLock( const CriticalSection& cs )
			: m_cs	( cs )
		{
			m_cs.Enter();
		}

		/*
			@brief デストラクタ
			@author 葉迩倭
			@note
			自動的にクリティカルセクションから出ます
		*/
		~ScopedLock()
		{
			m_cs.Leave();
		}
	};
}
}
}


/**
	@file
	@brief アトミック変数
	@author 葉迩倭
*/


//----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Thread
{
	/*
		@brief アトミック変数
		@author 葉迩倭
	*/
	class Semaphore
	{
	private:
		HANDLE	m_hSemaphore;

	public:
		/*
			@brief コンストラクタ
			@author 葉迩倭
			@param IsAutoReset	[in] 自動リセットON/OFF
		*/
		Semaphore::Semaphore( bool IsAutoReset = true );
		/*
			@brief デストラクタ
			@author 葉迩倭
		*/
		~Semaphore();
		/*
			@brie 同期待ち
			@author 葉迩倭
			@note
			セマフォの同期を待ちます。
		*/
		void Wait();
		/*
			@brief 開始
			@author 葉迩倭
			@note
			セマフォの同期を解除します。
		*/
		void Signal();
		/*
			@brief リセット
			@author 葉迩倭
			@note
			セマフォの同期を開始します。
		*/
		void Reset();
		/*
			@brie 同期状態チェック
			@author 葉迩倭
			@note
			セマフォの同期状態を調べます。
		*/
		bool IsSignal();
	};
}
}
}


/**
	@file
	@brief アトミック変数
	@author 葉迩倭
*/


//----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Thread
{
	/*
		@brief アトミック変数
		@author 葉迩倭
	*/
	class MultipleSemaphore
	{
	private:
		std::vector<HANDLE>	m_Handle;

	public:
		/*
			@brief コンストラクタ
			@author 葉迩倭
			@param IsAutoReset	[in] 自動リセットON/OFF
		*/
		MultipleSemaphore( Uint32 Count, bool IsAutoReset = true );
		/*
			@brief デストラクタ
			@author 葉迩倭
		*/
		~MultipleSemaphore();
		/*
			@brie 同期待ち
			@author 葉迩倭
			@note
			セマフォの同期を待ちます。
		*/
		void WaitAll();
		/*
			@brief 開始
			@author 葉迩倭
			@note
			セマフォの同期を解除します。
		*/
		void Signal( Uint32 Index );
		/*
			@brief リセット
			@author 葉迩倭
			@note
			セマフォの同期を開始します。
		*/
		void Reset( Uint32 Index );
	};
}
}
}


/**
	@file
	@brief スレッド制御
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Thread
{
	/**
		@brief スレッド管理操作クラス
		@author 葉迩倭
	*/
	class Threading
		: public Object::NoneCopyableObject
	{
	private:
		/**
			@brief スレッド用関数
			@author 葉迩倭
			@param pArguments	[in] Threadのポインタ
			@note
			クラスの関数を直接は指定できないので<BR>
			staticな関数を経由して呼び出す。
		*/
		static Uint32 SLN_STDCALL ThreadProc( void* pArguments );

	private:
		HANDLE m_hThread;					///< スレッドハンドル
		Uint32 m_ThreadId;					///< スレッドID
		void* m_pData;						///< スレッドデータ伝達用ポインタ
		void (*m_pMainProc)( void* );		///< スレッド関数
		CriticalSection m_CS;				///< クリティカルセクション

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		Threading();

		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		~Threading();

	public:
		/**
			@brief スレッド生成
			@author 葉迩倭
			@param pThreadFunc	[in] スレッド関数
			@param pData		[in] スレッドに引き渡すデータポインタ
			@param CoreNo		[in] 利用するCPUコア番号（-1でシステムまかせ）
			@param ThreadName	[in] スレッド名
			@retval false	生成失敗for既にスレッドが生成されている
			@retval true	生成完了
			@note
			スレッドの生成を行います。
		*/
		bool Create( void (*pThreadFunc)( void* ), void* pData, Uint32 CoreNo, const char* ThreadName );

		/**
			@brief スレッド終了待ち
			@author 葉迩倭
			@retval false	スレッドは終了していない
			@retval true	スレッドは終了した
			@note
			スレッドが終了するのを待ちます
		*/
		bool IsExitThread() const;

		/**
			@brief スレッド終了待ち
			@author 葉迩倭
			@retval false	スレッドは終了していない
			@retval true	スレッドは終了した
			@note
			スレッドが終了するのを待ちます
		*/
		bool Wait() const;
	};
}
}
}


/**
	@file
	@brief		スレッドユーティリティ　定義
	@author		椿
*/


namespace Selene
{
namespace Kernel
{
namespace Thread
{
	//---------------------------------------------------------------------------//
	/**
		@brief		スレッドユーティリティ
		@author		椿
	*/
	class Utility
	{
		//---------------------------------------------------------------------------//
		/**
			@internal
			@brief		コンストラクタ(定義禁止)
		*/
		Utility();

	public:
		//---------------------------------------------------------------------------//
		/**
			@brief		CPU数を取得する
		*/
		static Uint32 GetNumberOfProcessors();

		//---------------------------------------------------------------------------//
		/**
			@brief		CPUをスリープさせる
		*/
		static void Sleep( Uint32 Time );
	};

}	// namespace Thread
}	// namespace Kernel
}	// namespace Selene



/**
	@file
	@brief ログ用HTMLファイル
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace File
{
	/**
		@brief ログ用HTMLファイル操作
		@author 葉迩倭
	*/
	class LogFile
	{
	private:
		HANDLE	m_hFile;

	private:
		Sint32 Write( const void* pData, Sint32 Size );
		Sint32 GetFileSize();
		Sint32 GetFilePosition();
		Sint32 SeekStart( Sint32 Offset );
		Sint32 SeekEnd( Sint32 Offset );
		Sint32 Seek( Sint32 Offset );

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param pFileName	[in] ファイル名
			@param pTitle		[in] タイトル
			@note
			指定したファイル名のhtmlファイルを生成します。
		*/
		LogFile( const wchar_t* pFileName, const wchar_t* pTitle );
		/**
			@brief デストラクタ
			@author 葉迩倭
			@note
			htmlタグを閉じてファイルをcloseします。
		*/
		~LogFile();
		/**
			@brief 描画
			@author 葉迩倭
			@param Color	[in] 描画色
			@param pStr		[in] 描画文字列（printfと同じ書式）
			@note
			文字列の描画をします。
		*/
		void Print( Sint32 Color, const wchar_t* pStr,... );
		/**
			@brief 太字描画
			@author 葉迩倭
			@param Color	[in] 描画色
			@param pStr		[in] 描画文字列（printfと同じ書式）
			@note
			太字で文字列の描画をします。
		*/
		void PrintStrong( Sint32 Color, const wchar_t* pStr,... );
		/**
			@brief 改行付き描画
			@author 葉迩倭
			@param Color	[in] 描画色
			@param pStr		[in] 描画文字列（printfと同じ書式）
			@note
			改行付きの文字列の描画をします。
		*/
		void PrintLine( Sint32 Color, const wchar_t* pStr,... );
		/**
			@brief 改行付き太字描画
			@author 葉迩倭
			@param Color	[in] 描画色
			@param pStr		[in] 描画文字列（printfと同じ書式）
			@note
			改行付きの太字で文字列の描画をします。
		*/
		void PrintStrongLine( Sint32 Color, const wchar_t* pStr,... );
		/**
			@brief テーブル描画
			@author 葉迩倭
			@param Width	[in] タイトル幅
			@param pTitle	[in] タイトル
			@param pStr		[in] 描画文字列（printfと同じ書式）
			@note
			１行完結のテーブルを描画します
		*/
		void PrintTable( Sint32 Width, const wchar_t* pTitle, const wchar_t* pStr,... );
		/**
			@brief テーブル描画
			@author 葉迩倭
			@param ColorTitle	[in] タイトル色
			@param Color		[in] 文字色
			@param pTitle		[in] タイトル
			@param pKind		[in] 種類
			@param pStr			[in] 描画文字列（printfと同じ書式）
			@note
			１行完結のテーブルを描画します
		*/
		void PrintTable( Sint32 ColorTitle, Sint32 Color, const wchar_t* pTitle, const wchar_t* pKind, const wchar_t* pStr,... );
		/**
			@brief セルタイトル描画
			@author 葉迩倭
			@param Color		[in] 文字色
			@param pTitle		[in] タイトル
			@note
			セルのタイトルを描画します。
		*/
		void PrintCellTitle( Sint32 Color, const wchar_t* pTitle );
		/**
			@brief セル種類描画
			@author 葉迩倭
			@param pKind	[in] 種類（printfと同じ書式）
			@note
			セルの種類を描画します。
		*/
		void PrintCellKind( const wchar_t* pKind,... );
		/**
			@brief テーブル開始
			@author 葉迩倭
			@note
			テーブルの開始をします。
		*/
		void TableBegin();
		/**
			@brief テーブル終了
			@author 葉迩倭
			@note
			テーブルの終了をします。
		*/
		void TableEnd();
		/**
			@brief １行テーブル
			@author 葉迩倭
			@param Bold	[in] 高さ
			@note
			１行だけのテーブルを出力します。
		*/
		void TableLine( Sint32 Bold );
		/**
			@brief セル開始
			@author 葉迩倭
			@param Width	[in] セルの幅
			@note
			セルの開始をします。
		*/
		void CellBegin( Sint32 Width );
		/**
			@brief セル終了
			@author 葉迩倭
			@note
			セルの終了をします。
		*/
		void CellEnd();
	};
}
}
}


/**
	@file
	@brief ファイル制御
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace File
{
	/**
		@brief ファイルオープンモード
		@author 葉迩倭
	*/
	enum eFileOpenType
	{
		FILE_OPEN_TYPE_WRITE,			///< 書き込み専用
		FILE_OPEN_TYPE_READ,			///< 読み込み専用
		FILE_OPEN_TYPE_READ_WRITE,		///< 読み書き用

		FILE_OPEN_TYPE_INVALID,			///< 無効
	};

	/**
		@brief ファイル操作
		@author 葉迩倭
	*/
	class FileControl
	{
	private:
		wchar_t			m_FileName[MAX_PATH];	///< ファイル名
		HANDLE			m_hFile;				///< ファイルハンドル
		eFileOpenType	m_Type;					///< ファイルオープンモード
		FILETIME		m_TimeCreate;			///< ファイル作成時間
		FILETIME		m_TimeAccess;			///< ファイルアクセス時間
		FILETIME		m_TimeLastWrite;		///< ファイル書き込み時間

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		FileControl( const wchar_t* pFileName, eFileOpenType Type );

		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		~FileControl();

		/**
			@brief ファイルオープンチェック
			@author 葉迩倭
			@retval false	ファイルは開かれていない
			@retval true	ファイルは開かれている
		*/
		const wchar_t* GetFileName() const;

		/**
			@brief ファイルオープンチェック
			@author 葉迩倭
			@retval false	ファイルは開かれていない
			@retval true	ファイルは開かれている
		*/
		bool IsOpened() const;

		/**
			@brief ファイルクローズ
			@author 葉迩倭
		*/
		void Close();

		/**
			@brief ファイル書き込み
			@author 葉迩倭
			@param pData	[in] 書き込みデータ
			@param Size		[in] データサイズ
			@return 実際の書き込みサイズ
		*/
		Sint32 Write( const void* pData, Sint32 Size );

		/**
			@brief ファイル読み込み
			@author 葉迩倭
			@param pData	[in] 読み込みデータ
			@param Size		[in] データサイズ
			@return 実際の読み込みサイズ
		*/
		Sint32 Read( void* pData, Sint32 Size );

		/**
			@brief ファイルサイズ取得
			@author 葉迩倭
			@return ファイルサイズ
		*/
		Sint32 GetFileSize() const;

		/**
			@brief ファイル位置取得
			@author 葉迩倭
			@return ファイル位置
		*/
		Sint32 GetFilePosition() const;

		/**
			@brief 先頭からシーク
			@author 葉迩倭
			@param Offset	[in] 先頭からのオフセット
			@return ファイル位置
		*/
		Sint32 SeekStart( Sint32 Offset );

		/**
			@brief 終端からシーク
			@author 葉迩倭
			@param Offset	[in] 終端からのオフセット
			@return ファイル位置
		*/
		Sint32 SeekEnd( Sint32 Offset );

		/**
			@brief シーク
			@author 葉迩倭
			@param Offset	[in] 現在位置からのオフセット
			@return ファイル位置
		*/
		Sint32 Seek( Sint32 Offset );
	};
}
}
}


/**
	@file
	@brief 疑似乱数
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	/**
		@brief 乱数処理クラス
		@author 葉迩倭
	*/
	class Random
	{
		enum { N = 624 };

	private:
		Sint32 m_MersenneTwister[N];
		Sint32 m_MersenneTwisterCount;

	private:
		Sint32 GenerateInt32();

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		Random();

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		Random( Sint32 Param );

		/**
			@brief 乱数用種設定
			@author 葉迩倭
			@param Param	[in] シード値
			@note
			乱数生成の種を設定します。
		*/
		void Seed( Sint32 Param );

		/**
			@brief 32Bit整数乱数取得
			@author 葉迩倭
			@return 乱数値
			@note
			32Bit整数の乱数値を取得します。
		*/
		Sint32 GetInt32();

		/**
			@brief 64Bit整数乱数取得
			@author 葉迩倭
			@return 乱数値
			@note
			64Bit整数の乱数値を取得します。
		*/
		Uint64 GetInt64();

		/**
			@brief 32Bit浮動小数乱数取得
			@author 葉迩倭
			@return 乱数値
			@note
			32Bit浮動小数の乱数値を取得します。
		*/
		float GetFloat32();

		/**
			@brief 指定範囲乱数取得
			@author 葉迩倭
			@param Min [in] 最小値
			@param Max [in] 最大値
			@return 乱数値
			@note
			指定範囲内の整数乱数を取得します。
		*/
		Sint32 GetInt( Sint32 Min, Sint32 Max );

		/**
			@brief 指定範囲乱数取得
			@author 葉迩倭
			@param Min [in] 最小値
			@param Max [in] 最大値
			@return 乱数値
			@note
			指定範囲内の浮動小数乱数を取得します。
		*/
		float GetFloat( float Min, float Max );
	};
}
}
}


/**
	@file
	@brief 三角関数
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	static const Sint32 ANGLE_TABLE_BIT		= 12;						///< サインテーブルのビット数
	static const Sint32 ANGLE_TABLE_MAX		= 1 << ANGLE_TABLE_BIT;		///< サインテーブルのサイズ
	static const Sint32 ANGLE_TABLE_MASK	= ANGLE_TABLE_MAX - 1;		///< サインテーブルのアクセス用マスク

	/**
		@brief 角度正規化
		@author 葉迩倭
		@param Value		[in] 角度（1周4096）
		@return 角度（1周4096）
	*/
	inline Sint32 NormalizeAngle( Sint32 Value )
	{
		return Value & ANGLE_TABLE_MASK;
	}

	/**
		@brief 角度変換
		@author 葉迩倭
		@param Value		[in] 角度（1周360）
		@return 角度（1周4096）
	*/
	inline Sint32 DegToAngle( float Value )
	{
		return toI(Value * toF(ANGLE_TABLE_MAX) / 360.0f);
	}

	/**
		@brief 角度変換
		@author 葉迩倭
		@param Value		[in] 角度（1周4096）
		@return 角度（1周360）
	*/
	inline Sint32 AngleToDeg( Sint32 Value )
	{
		return Value * 360 / ANGLE_TABLE_MAX;
	}

	/**
		@brief 角度変換
		@author 葉迩倭
		@param Value		[in] 角度（1周2π）
		@return 角度（1周4096）
	*/
	inline Sint32 PiToAngle( float Value )
	{
		return toI(Value * toF(ANGLE_TABLE_MAX) / PI2);
	}

	/**
		@brief 角度変換
		@author 葉迩倭
		@param Value		[in] 角度（1周4096）
		@return 角度（1周2π）

	*/
	inline float AngleToPi( Sint32 Value )
	{
		return toF(Value) * PI2 / toF(ANGLE_TABLE_MAX);
	}

	/**
		@brief 角度変換
		@author 葉迩倭
		@param Value		[in] 角度（1周360）
		@return 角度（1周2π）
	*/
	inline float DegToPi( float Value )
	{
		return Value * PI2 / 360.0f;
	}

	/**
		@brief 角度変換
		@author 少佐
		@param Value		[in] 角度（1周2π）
		@return 角度（1周360）
	*/
	inline float PiToDeg( float Value )
	{
		return Value * 360.0f / PI2;
	}

	/**
		@brief 高速sin取得
		@author 葉迩倭
		@param Angle	[in] 角度（1周4096）
		@return sin値
		@note
		テーブルを用いて高速にsin値を取得します。<BR>
		1周を4096分割した場合の値なのでそれ以上の精度が必要な場合は<BR>
		標準関数のsinfを利用してください。
	*/
	float FastSin( Sint32 Angle );

	/**
		@brief 高速cos取得
		@author 葉迩倭
		@param Angle	[in] 角度（1周4096）
		@return cos値
		@note
		テーブルを用いて高速にcos値を取得します。<BR>
		1周を4096分割した場合の値なのでそれ以上の精度が必要な場合は<BR>
		標準関数のcosfを利用してください。
	*/
	float FastCos( Sint32 Angle );

	/**
		@brief 高速sin取得
		@author 葉迩倭
		@param Angle	[in] 角度（1周2π）
		@return sin値
		@note
		テーブルを用いて高速にsin値を取得します。<BR>
		1周を4096分割した場合の値なのでそれ以上の精度が必要な場合は<BR>
		標準関数のsinfを利用してください。
	*/
	float FastSin( float Angle );

	/**
		@brief 高速cos取得
		@author 葉迩倭
		@param Angle	[in] 角度（1周2π）
		@return cos値
		@note
		テーブルを用いて高速にcos値を取得します。<BR>
		1周を4096分割した場合の値なのでそれ以上の精度が必要な場合は<BR>
		標準関数のcosfを利用してください。
	*/
	float FastCos( float Angle );
}
}
}


/**
	@file
	@brief 2次元ベクトル
	@author 椿
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	//---------------------------------------------------------------------------//
	/**
		@brief		2次元ベクトル
	*/
	class Vector2
	{
	public:
		float x;
		float y;

	public:
		Vector2();
		Vector2( const Vector2& rhs );
		Vector2( float _x, float _y );

		Vector2& operator=( const Vector2& rhs );
		Vector2& operator+=( const Vector2& rhs );
		Vector2& operator-=( const Vector2& rhs );
		Vector2& operator*=( const Vector2& rhs );
		Vector2& operator*=( float rhs );

		Vector2 operator+( const Vector2& rhs ) const;
		Vector2 operator-( const Vector2& rhs ) const;
		Vector2 operator*( const Vector2& rhs ) const;
		Vector2 operator*( float rhs ) const;
	};

	//---------------------------------------------------------------------------//
	/**
		@brief		スカラー乗算
	*/
	Vector2 operator*( float lhs, const Vector2& rhs );

	//---------------------------------------------------------------------------//
	/**
		@brief		2次元ベクトル演算
	*/
	class Vec2
	{
		Vec2();	// 実装禁止！

	public:
		static Vector2	Add( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Subtract( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Multiply( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Divide( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Scale( const Vector2& vec, float actor );
		static Vector2	Reciprocal( const Vector2& value );
		static Vector2	ReciprocalSqrt( const Vector2& value );
		static Vector2	Normal( const Vector2& value );
		static Vector2	Sqrt( const Vector2& value );
		static float	Length( const Vector2& value );
		static float	LengthSq( const Vector2& value );
		static float	Dot( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Min( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Max( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Rotate( const Vector2& value, float Radian );
	};

	class Vector2H
	{
	public:
		Sint16 x, y;
	};
}
}
}


/**
	@file
	@brief 3次元ベクトル
	@author 椿
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	//---------------------------------------------------------------------------//
	/**
		@brief		3次元ベクトル
	*/
	class Vector3
	{
	public:
		float x;
		float y;
		float z;

	public:
		Vector3();
		Vector3( const class Vector2& rhs );
		Vector3( const class Vector3& rhs );
		Vector3( const class Vector4& rhs );
		Vector3( const class VectorS& rhs );
		Vector3( float _x, float _y, float _z );

		Vector3& operator=( const Vector3& rhs );
		Vector3& operator+=( const Vector3& rhs );
		Vector3& operator-=( const Vector3& rhs );
		Vector3& operator*=( const Vector3& rhs );
		Vector3& operator*=( float rhs );

		Vector3 operator+( const Vector3& rhs ) const;
		Vector3 operator-( const Vector3& rhs ) const;
		Vector3 operator*( const Vector3& rhs ) const;
		Vector3 operator*( float rhs ) const;
	};

	//---------------------------------------------------------------------------//
	/**
		@brief		スカラー乗算
	*/
	Vector3 operator*( float lhs, const Vector3& rhs );

	//---------------------------------------------------------------------------//
	/**
		@brief		3次元ベクトル演算
	*/
	class Vec3
	{
		Vec3();	// 実装禁止！

	public:
		static Vector3	Add( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Subtract( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Multiply( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Divide( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Scale( const Vector3& vec, float actor );
		static Vector3	Reciprocal( const Vector3& value );
		static Vector3	ReciprocalSqrt( const Vector3& value );
		static Vector3	Normal( const Vector3& value );
		static Vector3	Sqrt( const Vector3& value );
		static float	Length( const Vector3& value );
		static float	LengthSq( const Vector3& value );
		static float	Dot( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Cross( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Min( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Max( const Vector3& lhs, const Vector3& rhs );

		/**
			@brief X軸単位ベクトル
			@author 少佐
			@note
			X軸方向の単位ベクトルを取得する。
		*/
		static Vector3  UnitX();

		/**
			@brief Y軸単位ベクトル
			@author 少佐
			@note
			Y軸方向の単位ベクトルを取得する。
		*/
		static Vector3  UnitY();

		/**
			@brief Z軸単位ベクトル
			@author 少佐
			@note
			Z軸方向の単位ベクトルを取得する。
		*/
		static Vector3  UnitZ();
	};
}
}
}


/**
	@file
	@brief 4次元ベクトル
	@author 椿
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	//---------------------------------------------------------------------------//
	/**
		@brief		4次元ベクトル
	*/
	class Vector4
	{
	public:
		float x;
		float y;
		float z;
		float w;

	public:
		Vector4();
		Vector4( const Vector4& rhs );
		Vector4( const VectorS& rhs );
		Vector4( float _x, float _y, float _z, float _w );

		Vector4& operator=( const Vector4& rhs );
		Vector4& operator=( const VectorS& rhs );
		Vector4& operator+=( const Vector4& rhs );
		Vector4& operator-=( const Vector4& rhs );
		Vector4& operator*=( const Vector4& rhs );
		Vector4& operator*=( float rhs );

		Vector4 operator+( const Vector4& rhs ) const;
		Vector4 operator-( const Vector4& rhs ) const;
		Vector4 operator*( const Vector4& rhs ) const;
		Vector4 operator*( float rhs ) const;
	};

	//---------------------------------------------------------------------------//
	/**
		@brief		スカラー乗算
	*/
	Vector4 operator*( float lhs, const Vector4& rhs );

	//---------------------------------------------------------------------------//
	/**
		@brief		4次元ベクトル演算
	*/
	class Vec4
	{
		Vec4();	// 実装禁止！

	public:
		static Vector4	Add( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Subtract( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Multiply( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Divide( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Scale( const Vector4& vec, float actor );
		static Vector4	Reciprocal( const Vector4& value );
		static Vector4	ReciprocalSqrt( const Vector4& value );
		static Vector4	Normal( const Vector4& value );
		static Vector4	Sqrt( const Vector4& value );
		static float	Length( const Vector4& value );
		static float	LengthSq( const Vector4& value );
		static float	Dot( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Cross3( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Min( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Max( const Vector4& lhs, const Vector4& rhs );

		/**
			@brief X軸単位ベクトル
			@author 少佐
			@note
			X軸方向の単位ベクトルを取得する。
		*/
		static Vector4	UnitX();

		/**
			@brief Y軸単位ベクトル
			@author 少佐
			@note
			Y軸方向の単位ベクトルを取得する。
		*/
		static Vector4	UnitY();

		/**
			@brief Z軸単位ベクトル
			@author 少佐
			@note
			Z軸方向の単位ベクトルを取得する。
		*/
		static Vector4	UnitZ();

		/**
			@brief W軸単位ベクトル
			@author 少佐
			@note
			W軸方向の単位ベクトルを取得する。
		*/
		static Vector4	UnitW();
	};

	class Vector4H
	{
	public:
		Sint16 x, y, z, w;
	};
}
}
}


/**
	@file
	@brief 四元数演算
	@author 椿
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	class Vector4;

	//---------------------------------------------------------------------------//
	/**
		@brief		クォータニオン
	*/
	class Quaternion
		: public Object::MemoryObject
	{
	public:
		union
		{
			struct
			{
				float x, y, z, w;
			};
			struct
			{
				int ix, iy, iz, iw;
			};
			struct
			{
				unsigned ux, uy, uz, uw;
			};
			Uint128 v;
		};

	public:
		Quaternion();
		Quaternion( const Quaternion& rhs );
		Quaternion( const Matrix& rhs );
		Quaternion( Uint128 rhs );
		Quaternion( float _x, float _y, float _z );
		Quaternion( float _x, float _y, float _z, float _w );
		explicit Quaternion( const Vector4& rhs );

		Quaternion operator=( const Quaternion& rhs );
		Quaternion operator+=( const Quaternion& rhs );
		Quaternion operator-=( const Quaternion& rhs );
		Quaternion operator*=( const Quaternion& rhs );
		Quaternion operator*=( float rhs );
		Quaternion operator&=( const Quaternion& rhs );
		Quaternion operator|=( const Quaternion& rhs );
		Quaternion operator^=( const Quaternion& rhs );

		Quaternion operator-() const;

		Quaternion operator+( const Quaternion& rhs ) const;
		Quaternion operator-( const Quaternion& rhs ) const;
		Quaternion operator*( const Quaternion& rhs ) const;
		Quaternion operator*( float rhs ) const;
		Quaternion operator&( const Quaternion& rhs ) const;
		Quaternion operator|( const Quaternion& rhs ) const;
		Quaternion operator^( const Quaternion& rhs ) const;
	};

	//---------------------------------------------------------------------------//
	/**
		@brief		スカラー乗算
	*/
	Quaternion operator*( float lhs, const Quaternion& rhs );

	//---------------------------------------------------------------------------//
	/**
		@brief		クォータニオン演算
	*/
	class Quat
	{
		Quat();	// 実装禁止！

	public:
		static Quaternion	RotationX( float Radian );
		static Quaternion	RotationY( float Radian );
		static Quaternion	RotationZ( float Radian );
		static Quaternion	RotationXYZ( const Vector3& Radian );
		static Quaternion	RotationAxis( const Vector3& Axis, float Radian );
		static Vector3		GetRotationAngle( const Quaternion& value );
		static Quaternion	Conjugate( const Quaternion& value );
		static Quaternion	Rotate( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Lerp( const Quaternion& lhs, const Quaternion& rhs, float value );
		static Quaternion	Slerp( const Quaternion& lhs, const Quaternion& rhs, float value );
		static Quaternion	Negative( const Quaternion& value );
		static Quaternion	Add( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Subtract( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Multiply( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Divide( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Scale( const Quaternion& vec, float actor );
		static Quaternion	Reciprocal( const Quaternion& value );
		static Quaternion	ReciprocalSqrt( const Quaternion& value );
		static Quaternion	Normal( const Quaternion& value );
		static Quaternion	Sqrt( const Quaternion& value );
		static Quaternion	Length( const Quaternion& value );
		static Quaternion	LengthSq( const Quaternion& value );
		static Quaternion	Dot( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Dot3( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Cross3( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Min( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Max( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Abs( const Quaternion& value );

		static Quaternion	And( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	AndNot( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Or( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Xor( const Quaternion& lhs, const Quaternion& rhs );

		static Quaternion	SplatX( const Quaternion& value );
		static Quaternion	SplatY( const Quaternion& value );
		static Quaternion	SplatZ( const Quaternion& value );
		static Quaternion	SplatW( const Quaternion& value );

		static Quaternion	SwizzleX( const Quaternion& toX, const Quaternion& toY, const Quaternion& toZ, const Quaternion& toW );
		static Quaternion	MergeXYZ_W( const Quaternion& xyz, const Quaternion& w );

		static Quaternion	Set( float x, float y, float z, float w );
		static Quaternion	SetInt( unsigned x, unsigned y, unsigned z, unsigned w );
		static Quaternion	LoadU( const float* pFloat4 );
		static Quaternion	LoadA( const float* pFloat4Aligned );
		static Quaternion	Zero();
		static void		Prefetch( const Quaternion* pAddress );
		static void		StoreU( float* pFloat4, const Quaternion& source );
		static void		StoreA( float* pFloat4Aligned, const Quaternion& source );
		static Quaternion	Fill( float value );
		static Quaternion	FReciprocal( const Quaternion& value );
		static Quaternion	FReciprocalSqrt( const Quaternion& value );
		static Quaternion	HorizonalAdd( const Quaternion& value );
		static Quaternion	HorizonalAnd( const Quaternion& value );
		static Quaternion	HorizonalOr( const Quaternion& value );

		static Quaternion	Equal( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	NotEqual( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Greater( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	GreaterEqual( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Less( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	LessEqual( const Quaternion& lhs, const Quaternion& rhs );

		static bool		ArbitraryTrue( const Quaternion& value );
		static bool		ExistTrue( const Quaternion& value );
		static bool		ArbitraryFalse( const Quaternion& value );
		static bool		ExistFalse( const Quaternion& value );
		static bool		ArbitraryTrue3( const Quaternion& value );
		static bool		ExistTrue3( const Quaternion& value );
		static bool		ArbitraryFalse3( const Quaternion& value );
		static bool		ExistFalse3( const Quaternion& value );

		static Quaternion	UnitX();
		static Quaternion	UnitY();
		static Quaternion	UnitZ();
		static Quaternion	UnitW();

		//---------------------------------------------------------------------------//
		/**
			@brief		シャッフル
			@par		SSEのshuffle命令に従って入れ替えします。
						XYに左要素、ZWに右要素が入ります。具体的には
						lhs = (V0,V1,V2,V3)
						rhs = (W0,W1,W2,W3)
						↓
						result = (Va,Vb,Wc,Wd)
		*/
		template<int a, int b, int c, int d>
		static Quaternion	Shuffle( const Quaternion& lhs, const Quaternion& rhs )
		{
			return _mm_shuffle_ps( lhs.v, rhs.v, _MM_SHUFFLE(d,c,b,a) );
		}

		//---------------------------------------------------------------------------//
		/**
			@brief		シャッフル
			@par		SSEのshuffle命令で左右同じオペランドを指定するのと同義です。
		*/
		template<int a, int b, int c, int d>
		static Quaternion	Shuffle( const Quaternion& value )
		{
			return Shuffle<a,b,c,d>( value, value );
		}


		static const Quaternion	One;		///< 1.0f
		static const Quaternion	Half;		///< 0.5f
		static const Quaternion	NegOne;		///< -1.0f
		static const Quaternion	NegHalf;	///< -0.5f
	};
}
}
}


/**
	@file
	@brief SIMDベクトル
	@author 椿
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	//---------------------------------------------------------------------------//
	/**
		@brief		SIMDベクトル
	*/
	class VectorS
		: public Object::MemoryObject
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
			struct
			{
				Sint32 ix;
				Sint32 iy;
				Sint32 iz;
				Sint32 iw;
			};
			struct
			{
				Uint32 ux;
				Uint32 uy;
				Uint32 uz;
				Uint32 uw;
			};
			Uint128 v;
		};

	public:
		VectorS();
		VectorS( const VectorS& rhs );
		VectorS( const Vector3& rhs );
		VectorS( const Vector4& rhs );
		VectorS( const Uint128& rhs );
		VectorS( float _x, float _y, float _z );
		VectorS( float _x, float _y, float _z, float _w );

		VectorS& operator=( const Vector2& rhs );
		VectorS& operator=( const Vector3& rhs );
		VectorS& operator=( const Vector4& rhs );
		VectorS& operator=( const VectorS& rhs );
		VectorS& operator+=( const VectorS& rhs );
		VectorS& operator-=( const VectorS& rhs );
		VectorS& operator*=( const VectorS& rhs );
		VectorS& operator*=( float rhs );
		VectorS& operator&=( const VectorS& rhs );
		VectorS& operator|=( const VectorS& rhs );
		VectorS& operator^=( const VectorS& rhs );

		VectorS operator-() const;

		VectorS operator+( const VectorS& rhs ) const;
		VectorS operator-( const VectorS& rhs ) const;
		VectorS operator*( const VectorS& rhs ) const;
		VectorS operator*( float rhs ) const;
		VectorS operator&( const VectorS& rhs ) const;
		VectorS operator|( const VectorS& rhs ) const;
		VectorS operator^( const VectorS& rhs ) const;
	};

	//---------------------------------------------------------------------------//
	/**
		@brief		スカラー乗算
	*/
	VectorS operator*( float lhs, const VectorS& rhs );

	//---------------------------------------------------------------------------//
	/**
		@brief		SIMDベクトル演算
	*/
	class VecS
	{
		VecS();	// 実装禁止！

	public:
		static VectorS	Rotate( const VectorS& v, const Quaternion& q );
		static VectorS	Negative( const VectorS& value );
		static VectorS	Add( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Subtract( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Multiply( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Divide( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Scale( const VectorS& vec, float actor );
		static VectorS	Reciprocal( const VectorS& value );
		static VectorS	ReciprocalSqrt( const VectorS& value );
		static VectorS	Normal( const VectorS& value );
		static VectorS	Normal3( const VectorS& value );
		static VectorS	Sqrt( const VectorS& value );
		static VectorS	Length( const VectorS& value );
		static VectorS	Length3( const VectorS& value );
		static VectorS	LengthSq( const VectorS& value );
		static VectorS	LengthSq3( const VectorS& value );
		static VectorS	Dot( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Dot3( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Cross3( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Min( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Max( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Abs( const VectorS& value );

		static VectorS	And( const VectorS& lhs, const VectorS& rhs );
		static VectorS	AndNot( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Or( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Xor( const VectorS& lhs, const VectorS& rhs );

		static VectorS	SplatX( const VectorS& value );
		static VectorS	SplatY( const VectorS& value );
		static VectorS	SplatZ( const VectorS& value );
		static VectorS	SplatW( const VectorS& value );

		static VectorS	SwizzleX( const VectorS& toX, const VectorS& toY, const VectorS& toZ, const VectorS& toW );
		static VectorS	MergeXYZ_W( const VectorS& xyz, const VectorS& w );

		static VectorS	Set( float x, float y, float z, float w );
		static VectorS	SetInt( unsigned x, unsigned y, unsigned z, unsigned w );
		static VectorS	LoadU( const float* pFloat4 );
		static VectorS	LoadA( const float* pFloat4Aligned );
		static VectorS	Zero();
		static void		Prefetch( const VectorS* pAddress );
		static void		StoreU( float* pFloat4, const VectorS& source );
		static void		StoreA( float* pFloat4Aligned, const VectorS& source );
		static VectorS	Fill( float value );
		static VectorS	FReciprocal( const VectorS& value );
		static VectorS	FReciprocalSqrt( const VectorS& value );
		static VectorS	HorizonalAdd( const VectorS& value );
		static VectorS	HorizonalAnd( const VectorS& value );
		static VectorS	HorizonalOr( const VectorS& value );

		static VectorS	Equal( const VectorS& lhs, const VectorS& rhs );
		static VectorS	NotEqual( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Greater( const VectorS& lhs, const VectorS& rhs );
		static VectorS	GreaterEqual( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Less( const VectorS& lhs, const VectorS& rhs );
		static VectorS	LessEqual( const VectorS& lhs, const VectorS& rhs );

		static bool		ArbitraryTrue( const VectorS& value );
		static bool		ExistTrue( const VectorS& value );
		static bool		ArbitraryFalse( const VectorS& value );
		static bool		ExistFalse( const VectorS& value );
		static bool		ArbitraryTrue3( const VectorS& value );
		static bool		ExistTrue3( const VectorS& value );
		static bool		ArbitraryFalse3( const VectorS& value );
		static bool		ExistFalse3( const VectorS& value );

		/**
			@brief 成分除去
			@author 少佐
			@param value		[in] ベクトル
			@param component	[in] 成分方向（単位ベクトル）
			@note
			ベクトルから成分方向の成分を取り除く。
		*/
		static VectorS	RemoveComponent( const VectorS& value, const VectorS& component );

		/**
			@brief 成分除去
			@author 少佐
			@param value		[in] ベクトル
			@param component	[in] 成分方向（単位ベクトル）
			@note
			ベクトルから成分方向の成分を取り除く。
		*/
		static VectorS	RemoveComponent3( const VectorS& value, const VectorS& component );

		/**
			@brief 角度取得
			@author 少佐
			@param lhs		[in] 単位ベクトル
			@param rhs		[in] 単位ベクトル
			@return 角度（1周2π、0～π）
			@note
			hsからrhsまで何度あるか取得する。
		*/
		static float	AngleAbs3( const VectorS& lhs, const VectorS& rhs );

		/**
			@brief 角度取得
			@author 少佐
			@param axis		[in] 軸（単位ベクトル）
			@param lhs		[in] ベクトル
			@param rhs		[in] ベクトル
			@return 角度（1周2π、-π～π）
			@note
			任意の軸周りにlhsからrhsまで何度あるか時計周りの回転で取得する。lhsとaxis、rhsとaxisが直行している必要はない。
		*/
		static float	Angle3( const VectorS& axis, const VectorS& lhs, const VectorS& rhs );

		/**
			@brief X軸単位ベクトル
			@author 椿
			@note
			X軸方向の単位ベクトルを取得する。
		*/
		static VectorS	UnitX();

		/**
			@brief Y軸単位ベクトル
			@author 椿
			@note
			X軸方向の単位ベクトルを取得する。
		*/
		static VectorS	UnitY();

		/**
			@brief Z軸単位ベクトル
			@author 椿
			@note
			X軸方向の単位ベクトルを取得する。
		*/
		static VectorS	UnitZ();

		/**
			@brief W軸単位ベクトル
			@author 椿
			@note
			X軸方向の単位ベクトルを取得する。
		*/
		static VectorS	UnitW();

		//---------------------------------------------------------------------------//
		/**
			@brief		シャッフル
			@par		SSEのshuffle命令に従って入れ替えします。
						XYに左要素、ZWに右要素が入ります。具体的には
						lhs = (V0,V1,V2,V3)
						rhs = (W0,W1,W2,W3)
						↓
						result = (Va,Vb,Wc,Wd)
		*/
		template<int a, int b, int c, int d>
		static VectorS	Shuffle( const VectorS& lhs, const VectorS& rhs )
		{
			return _mm_shuffle_ps( lhs.v, rhs.v, _MM_SHUFFLE(d,c,b,a) );
		}

		//---------------------------------------------------------------------------//
		/**
			@brief		シャッフル
			@par		SSEのshuffle命令で左右同じオペランドを指定するのと同義です。
		*/
		template<int a, int b, int c, int d>
		static VectorS	Shuffle( const VectorS& value )
		{
			return Shuffle<a,b,c,d>( value, value );
		}


		static const VectorS	One;		///< 1.0f
		static const VectorS	Half;		///< 0.5f
		static const VectorS	NegOne;		///< -1.0f
		static const VectorS	NegHalf;	///< -0.5f
	};
}
}
}


/**
	@file
	@brief 行列演算
	@author 椿
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	class Vector3;

	//---------------------------------------------------------------------------//
	/**
		@brief		行列
	*/
	class Matrix
		: public Object::MemoryObject
	{
	public:
		union
		{
			struct
			{
				VectorS	x;
				VectorS	y;
				VectorS	z;
				VectorS	w;
			};
			struct
			{
				VectorS	r[4];
			};
		};

	public:
		Matrix();
		Matrix( const Matrix& rhs );
		Matrix(
			float _00, float _01, float _02, float _03,
			float _10, float _11, float _12, float _13,
			float _20, float _21, float _22, float _23,
			float _30, float _31, float _32, float _33
			);
		Matrix(
			const VectorS& r0,
			const VectorS& r1,
			const VectorS& r2,
			const VectorS& r3
			);

		Matrix& operator=( const Matrix& rhs );
		Matrix& operator+=( const Matrix& rhs );
		Matrix& operator-=( const Matrix& rhs );
		Matrix& operator*=( const Matrix& rhs );
		Matrix& operator*=( float rhs );

		Matrix operator+( const Matrix& rhs ) const;
		Matrix operator-( const Matrix& rhs ) const;
		Matrix operator*( const Matrix& rhs ) const;
		Matrix operator*( float rhs ) const;

		const VectorS& GetRight() const;
		const VectorS& GetUp() const;
		const VectorS& GetFront() const;
		const VectorS& GetPosition() const;

		void SetRight( const VectorS& value );
		void SetUp( const VectorS& value );
		void SetFront( const VectorS& value );
		void SetPosition( const VectorS& value );
	};

	//---------------------------------------------------------------------------//
	/**
		@brief		スカラー乗算
	*/
	Vector4 operator*( float lhs, const Vector4& rhs );

	//---------------------------------------------------------------------------//
	/**
		@brief		行列オペレータ
	*/
	class MatX
	{
		MatX();	// 実装禁止！

	public:
		/**
			@brief 角度取得
			@author 椿
			@param value	[in] 行列
			@return 角度
			@note
			行列から回転角度を取得する。
		*/
		static Vector3	GetRotationAngle( const Matrix& value );

		/**
			@brief 加算
			@author 椿
			@param lhs	[in] 行列
			@param rhs	[in] 行列
			@note
			行列同士を加算した結果の行列を生成する。
		*/
		static Matrix	Add( const Matrix& lhs, const Matrix& rhs );

		/**
			@brief 減算
			@author 椿
			@param lhs	[in] 行列
			@param rhs	[in] 行列
			@note
			行列同士を減算した結果の行列を生成する。
		*/
		static Matrix	Subtract( const Matrix& lhs, const Matrix& rhs );

		
		/**
			@brief 乗算
			@author 椿
			@param lhs	[in] 行列
			@param rhs	[in] 行列
			@note
			行列同士を乗算した結果の行列を生成する。
		*/
		static Matrix	Multiply( const Matrix& lhs, const Matrix& rhs );

		/**
			@brief スカラー倍
			@author 椿
			@param value	[in] 行列
			@param factor	[in] 倍率
			@note
			すべての成分をスカラー倍した行列を生成する。
		*/
		static Matrix	Scale( const Matrix& value, float factor );

		/**
			@brief 転置行列生成
			@author 椿
			@param value	[in] 行列
			@note
			指定された行列の転置行列を生成する。
		*/
		static Matrix	Transpose( const Matrix& value );

		/**
			@brief 逆行列生成
			@author 椿
			@param value	[in] 行列
			@note
			指定された行列の逆行列を生成する。
		*/
		static Matrix	Inverse( const Matrix& value );

		/**
			@brief 逆行列生成
			@author 椿
			@param value	[in] 回転移動行列
			@note
			指定された回転移動のみの行列の逆行列を生成する。
		*/
		static Matrix	InverseRT( const Matrix& value );

		/**
			@brief 逆行列生成
			@author 椿
			@param value	[in] 拡大回転移動行列
			@note
			指定された拡大回転移動のみの行列の逆行列を生成する。
		*/
		static Matrix	InverseSRT( const Matrix& value );

		/**
			@brief 行列式生成
			@author 少佐
			@param value	[in] 拡大回転移動行列
			@note
			指定された拡大回転移動のみの行列の行列式を取得する。
		*/
		static float	DeterminantSRT( const Matrix& value );

		/**
			@brief 移動行列生成
			@author 椿
			@param translation	[in] 移動距離
			@note
			移動を行う行列を生成する。
		*/
		static Matrix	Translation( const Vector3& translation );

		/**
			@brief 移動行列生成
			@author 椿
			@param translation	[in] 移動距離
			@note
			移動を行う行列を生成する。
		*/
		static Matrix	Translation( const VectorS& translation );

		/**
			@brief X軸回転行列生成
			@author 椿
			@param angle	[in] 角度（1周2π）
			@note
			X軸周りに時計周りの回転を行う行列を生成する。
		*/
		static Matrix	RotationX( float angle );

		/**
			@brief Y軸回転行列生成
			@author 椿
			@param angle	[in] 角度（1周2π）
			@note
			Y軸周りに時計周りの回転を行う行列を生成する。
		*/
		static Matrix	RotationY( float angle );

		/**
			@brief Z軸回転行列生成
			@author 椿
			@param angle	[in] 角度（1周2π）
			@note
			Z軸周りに時計周りの回転を行う行列を生成する。
		*/
		static Matrix	RotationZ( float angle );

		/**
			@brief 任意軸回転行列生成
			@author 少佐
			@param axis		[in] 軸
			@param angle	[in] 角度（1周2π）
			@note
			任意の軸周りに時計周りの回転を行う行列を生成する。
		*/
		static Matrix	RotationAxis( const Vector3& axis, float angle );
		static Matrix	RotationAxis( const VectorS& axis, float angle );

		/**
			@brief 拡大縮小行列生成
			@author 椿
			@param scaling	[in] 拡大縮小率
			@note
			拡大縮小を行う行列を生成する。
		*/
		static Matrix	Scaling( const Vector3& scaling );

		/**
			@brief 拡大縮小行列生成
			@author 椿
			@param scaling	[in] 拡大縮小率
			@note
			拡大縮小を行う行列を生成する。
		*/
		static Matrix	Scaling( const VectorS& scaling );

		/**
			@brief 左手座標系ビュー行列生成
			@author 椿
			@param eye		[in] カメラの注視対象の座標
			@param at		[in] カメラの座標
			@param up		[in] カメラの上方向
			@note
			左手座標系ビュー行列を生成する。
		*/
		static Matrix	LookAtLH( const VectorS& eye, const VectorS& at, const VectorS& up );

		/**
			@brief 左手座標系パースペクティブ射影行列生成
			@author 椿
			@param ovY			[in] y方向の視野(ラジアン)
			@param aspect		[in] 縦横比
			@param zn			[in] 近いビュー平面のZ値
			@param zf			[in] 遠いビュー平面のZ値
			@note
			左手座標系パースペクティブ射影行列を生成する。
		*/
		static Matrix	PerspectiveFovLH( float ovY, float aspect, float zn, float zf );

		/**
			@brief 左手座標系正射影行列生成
			@author 椿
			@param width		[in] 横の長さ
			@param height		[in] 縦の長さ
			@param zn			[in] 近いビュー平面のZ値
			@param zf			[in] 遠いビュー平面のZ値
			@note
			左手座標系正射影行列を生成する。
		*/
		static Matrix	OrthographicLH( float width, float height, float zn, float zf );

		/**
			@brief 零行列生成
			@author 椿
			@note
			零行列を生成する。
		*/
		static const Matrix& Zero();

		/**
			@brief 単位行列生成
			@author 椿
			@note
			単位行列を生成する。
		*/
		static const Matrix& Identity();

		/**
			@brief 回転行列生成
			@author 椿
			@param Quat		[in] 変換されるクォータニオン
			@note
			クォータニオンから回転行列を生成する。
		*/
		static Matrix	Rotation( const Quaternion& Quat );

		/**
			@brief ベクトル演算
			@author 椿
			@param vIn		[in] 掛けるベクトル
			@param mIn		[in] 掛ける行列
			@note
			ベクトルに行列を掛けた値を出力する。移動は行わない。
		*/
		static Vector3	Transform3( const Vector3& vIn, const Matrix& mIn );

		/**
			@brief ベクトル演算
			@author 椿
			@param vIn		[in] 掛けるベクトル
			@param mIn		[in] 掛ける行列
			@note
			ベクトルに行列を掛けた値を出力する。移動は行う。
		*/
		static Vector3	Transform4( const Vector3& vIn, const Matrix& mIn );

		/**
			@brief ベクトル演算
			@author 椿
			@param vIn		[in] 掛けるベクトル
			@param mIn		[in] 掛ける行列
			@note
			ベクトルに行列を掛けた値を出力する。移動は行わない。
		*/
		static VectorS	Transform3( const VectorS& vIn, const Matrix& mIn );

		/**
			@brief ベクトル演算
			@author 椿
			@param vIn		[in] 掛けるベクトル
			@param mIn		[in] 掛ける行列
			@note
			ベクトルに行列を掛けた値を出力する。移動は行う。
		*/
		static VectorS	Transform4( const VectorS& vIn, const Matrix& mIn );

		/**
			@brief ベクトル演算
			@author 椿
			@param vIn		[in] 掛けるベクトル
			@param mIn		[in] 掛ける行列
			@note
			指定された行列により 3D ベクトルをトランスフォームし、その結果を w = 1 に射影する。
		*/
		static Vector3	TransformProjection( const Vector3& vIn, const Matrix& mIn );

		/**
			@brief ベクトル演算
			@author 椿
			@param vIn		[in] 掛けるベクトル
			@param mIn		[in] 掛ける行列
			@note
			指定された行列により 3D ベクトルをトランスフォームし、その結果を w = 1 に射影する。
		*/
		static VectorS	TransformProjection( const VectorS& vIn, const Matrix& mIn );

		/**
			@brief 任意軸固定ビルボード行列生成
			@author 少佐
			@param vAxis		[in] 軸
			@param vCameraPosition	[in] カメラの座標
			@param vBillboardPosition	[in] ビルボードの座標
			@note
			視点から任意軸を固定したビルボードの行列を生成する。
		*/
		static Matrix	AxisBillboard( const VectorS& vAxis, const VectorS& vCameraPosition, const VectorS& vBillboardPosition );

		/**
			@brief 鏡面反射用行列生成
			@author 葉迩倭
			@param mCamera			[in] カメラの行列
			@param Plane			[in] 反射させる平面
			@note
			鏡面反射用の行列を生成します。
		*/
		static Matrix	Reflect( const Matrix& mCamera, const Kernel::Collision::Plane& Plane );
	};
}
}
}


/**
	@file
	@brief 補間
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
namespace Interpolation
{
	/**
		@brief 等速運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		等速運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Linear( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(Time) / toF(TimeAll);
		return (TypeA)(toF(Start) + toF(End - Start) * Rate);
	}

	/**
		@brief 加速運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		加速運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Add( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(Time) / toF(TimeAll);
		Rate *= Rate;
		return (TypeA)(toF(Start) + toF(End - Start) * Rate);
	}

	/**
		@brief 減速運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		減速運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sub( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(TimeAll-Time) / toF(TimeAll);
		Rate *= Rate;
		return (TypeA)(toF(End) + toF(Start - End) * Rate);
	}

	/**
		@brief 加速運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		加速運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Add2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(Time) / toF(TimeAll);
		Rate *= Rate;
		Rate *= Rate;
		return (TypeA)(toF(Start) + toF(End - Start) * Rate);
	}

	/**
		@brief 減速運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		減速運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sub2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(TimeAll-Time) / toF(TimeAll);
		Rate *= Rate;
		Rate *= Rate;
		return (TypeA)(toF(End) + toF(Start - End) * Rate);
	}

	/**
		@brief 加速運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		加速運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Add4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(Time) / toF(TimeAll);
		Rate *= Rate;
		Rate *= Rate;
		Rate *= Rate;
		return (TypeA)(toF(Start) + toF(End - Start) * Rate);
	}

	/**
		@brief 減速運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		減速運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sub4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(TimeAll-Time) / toF(TimeAll);
		Rate *= Rate;
		Rate *= Rate;
		Rate *= Rate;
		return (TypeA)(toF(End) + toF(Start - End) * Rate);
	}

	/**
		@brief 加速→減速運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		加速→減速運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA AddSub( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Add( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Sub( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

	/**
		@brief 減速→加速運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		加速→減速運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA SubAdd( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Sub( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Add( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

	/**
		@brief 加速→減速運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		加速→減速運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA AddSub2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Add2( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Sub2( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

	/**
		@brief 減速→加速運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		減速→加速運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA SubAdd2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Sub2( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Add2( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

	/**
		@brief 加速→減速運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		加速→減速運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA AddSub4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Add4( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Sub4( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

	/**
		@brief 減速→加速運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		減速→加速運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA SubAdd4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Sub4( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Add4( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

	/**
		@brief sin運動
		@author 葉迩倭
		@param Start	[in] 開始値
		@param End		[in] 終了値
		@param TimeAll	[in] End到達時間
		@param Time		[in] 現在時間
		@return Timeにおける値
		@note
		sin波で運動を行うときの補間値を取得します。
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sin( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Sint32 Angle = (Sint32)( Kernel::Math::DegToAngle(180) * Time / TimeAll);
		float Rate = Kernel::Math::FastSin( Angle );
		return (TypeA)(toF(Start) + toF(End - Start) * Rate);
	}

	/**
		@brief ネヴィル補間
		@author 葉迩倭
		@param Start	[in] 開始値
		@param Center	[in] 中間値
		@param End		[in] 終了値
		@param Time	[in] 現在時間（0.0～1.0）
		@return Timeにおける値
		@note
		ネヴィル補間を行うときの補間値を取得します。
	*/
	inline float Neville( float Start, float Center, float End, float Time )
	{
		Time *= 2.0f;
		Start = Center + (Center - Start) * (Time - 1.0f);
		Center = End + (End - Center) * (Time - 2.0f);
		return Center + (Center - Start) * (Time - 2.0f) * 0.5f;
	}
}
}
}
}


/**
	@file
	@brief 線分
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Collision
{
	/**
		@brief 線分
		@author 葉迩倭
	*/
	class Ray
	{
	public:
		Kernel::Math::VectorS	Point[2];

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param start	[in] 始点
			@param end		[in] 終点
		*/
		Ray( const Kernel::Math::VectorS& start, const Kernel::Math::VectorS& end )
		{
			Point[0] = start;
			Point[1] = end;
		}

	public:
		/**
			@brief Ray生成
			@author 葉迩倭
			@param ray		[out] 軸平行ボックス格納先
			@param Start	[in] 始点
			@param End		[in] 終点
			@note
			線分を生成します。
		*/
		static void Create( Ray& ray, const Kernel::Math::VectorS& Start, const Kernel::Math::VectorS& End );
	};
}
}
}

/**
	@file
	@brief 軸平行ボックス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Collision
{
	/**
		@brief 軸平行ボックス
		@author 葉迩倭
	*/
	class AABB
	{
	public:
		Kernel::Math::VectorS	Min;		///< 最小点
		Kernel::Math::VectorS	Max;		///< 最大点

	public:
		/**
			@brief AABB生成
			@author 葉迩倭
			@param aabb	[out] 軸平行ボックス格納先
			@param Min	[in] ボックスの最小点
			@param Max	[in] ボックスの最大店
			@note
			軸平行ボックスを生成します。
		*/
		static void Create( AABB& aabb, const Kernel::Math::VectorS& Min, const Kernel::Math::VectorS& Max );
		/**
			@brief AABB生成
			@author 葉迩倭
			@param aabb		[out] 軸平行ボックス格納先
			@param pPoints	[in] ポイントのテーブル
			@param Count	[in] pPointのポイント数
			@note
			軸平行ボックスを生成します。
		*/
		static void Create( AABB& aabb, const Kernel::Math::VectorS* pPoints, Sint32 Count );
	};
}
}
}

/**
	@file
	@brief 球
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Collision
{
	/**
		@brief 球
		@author 葉迩倭
	*/
	class Sphere
	{
	public:
		Kernel::Math::VectorS	Center;		///< 球の中心
		float					Radius;		///< 球の半径
		AABB					AaBb;		///< 球のAABB

	public:
		/**
			@brief 球生成
			@author 葉迩倭
			@param sphere	[out] 球格納先
			@param Center	[in] 球の中心
			@param Radius	[in] 球の半径
			@note
			球を生成します。
		*/
		static void Create( Sphere& sphere, const Kernel::Math::VectorS& Center, float Radius );
		/**
			@brief 球生成
			@author 葉迩倭
			@param sphere	[out] 球格納先
			@param pPoints	[in] ポイントのテーブル
			@param Count	[in] pPointのポイント数
			@note
			球を生成します。
		*/
		static void Create( Sphere& sphere, const Kernel::Math::VectorS* pPoints, Sint32 Count );
	};
}
}
}

/**
	@file
	@brief 無限平面
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Collision
{
	/**
		@brief 無限平面
		@author 葉迩倭
	*/
	class Plane
	{
	public:
		Kernel::Math::VectorS	Normal;

	public:
		Plane()
			: Normal	( 0.0f, 0.0f, 0.0f, 0.0f )
		{
		}

		/**
			@brief 平面生成
			@author 葉迩倭
			@param plane	[out] 平面格納先
			@param p0		[in] 平面上の点
			@param p1		[in] 平面上の点
			@param p2		[in] 平面上の点
			@note
			平面を生成します。
		*/
		static void Create( Plane& plane, const Kernel::Math::VectorS& p0, const Kernel::Math::VectorS& p1, const Kernel::Math::VectorS& p2 );
		/**
			@brief 平面生成
			@author 葉迩倭
			@param plane	[out] 平面格納先
			@param Normal	[in] 平面の法線
			@param d		[in] 平面の距離
			@note
			平面を生成します。
		*/
		static void Create( Plane& plane, const Kernel::Math::VectorS& Normal, float d );
		/**
			@brief 距離取得
			@author 葉迩倭
			@param plane	[in] 平面
			@param Point	[in] 距離を見る点
			@note
			平面からの距離を取得します。
		*/
		static float GetDistance( const Plane& plane, const Kernel::Math::VectorS& Point );
	};
}
}
}

/**
	@file
	@brief 回転あり六面体
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Collision
{
	/**
		@brief 回転あり六面体
		@author 葉迩倭
	*/
	class OBB
	{
	public:
		enum
		{
			PLANE_FRONT,
			PLANE_BACK,
			PLANE_TOP,
			PLANE_BOTTOM,
			PLANE_LEFT,
			PLANE_RIGHT,
			PLANE_MAX,
		};
		enum
		{
			POINT_FRONT_BOTTOM_LEFT,
			POINT_FRONT_BOTTOM_RIGHT,
			POINT_FRONT_TOP_LEFT,
			POINT_FRONT_TOP_RIGHT,
			POINT_BACK_BOTTOM_LEFT,
			POINT_BACK_BOTTOM_RIGHT,
			POINT_BACK_TOP_LEFT,
			POINT_BACK_TOP_RIGHT,
			POINT_MAX,
		};

	public:
		Plane					Plane[PLANE_MAX];	///< 回転あり六面体の面
		Kernel::Math::VectorS	Point[POINT_MAX];	///< 回転あり六面体の点
		AABB					AaBb;				///< 回転あり六面体のAABB

	public:
		/**
			@brief 回転あり六面体生成
			@author 葉迩倭
			@param Obb		[out] 回転あり六面体格納先
			@param Camera	[in] 回転あり六面体を生成するカメラ
			@note
			回転あり六面体を生成します。
		*/
		static void Create( OBB& Obb, const Kernel::Math::Camera& Camera );
		/**
			@brief 回転あり六面体生成
			@author 葉迩倭
			@param Obb		[out] 回転あり六面体格納先
			@param AaBb		[in] 回転あり六面体を生成するAABB
			@note
			回転あり六面体を生成します。
		*/
		static void Create( OBB& Obb, const AABB& AaBb );
	};
}
}
}


/**
	@file
	@brief カメラ
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Collision
{
	/**
		@brief 面に対する位置
		@author 葉迩倭
	*/
	enum eSide
	{
		SIDE_FRONT,
		SIDE_BACK,
		SIDE_BOTH,
	};

	//------------------------------------------------------------

	/**
		@brief 接触判定
		@author 葉迩倭
		@param lhs	[in] 接触判定用のコリジョン
		@param rhs	[in] 接触判定用のコリジョン
		@return 当たっていればtrue
		@note
		二つのコリジョンの接触判定をします。
	*/
	bool IsIntersect( const Ray& lhs, const Sphere& rhs );
	/**
		@brief 接触判定
		@author 葉迩倭
		@param lhs	[in] 接触判定用のコリジョン
		@param rhs	[in] 接触判定用のコリジョン
		@return 当たっていればtrue
		@note
		二つのコリジョンの接触判定をします。
	*/
	bool IsIntersect( const Ray& lhs, const AABB& rhs );
	/**
		@brief 接触判定
		@author 葉迩倭
		@param lhs	[in] 接触判定用のコリジョン
		@param rhs	[in] 接触判定用のコリジョン
		@return 当たっていればtrue
		@note
		二つのコリジョンの接触判定をします。
	*/
	bool IsIntersect( const Ray& lhs, const OBB& rhs );
	/**
		@brief 接触判定
		@author 葉迩倭
		@param lhs	[in] 接触判定用のコリジョン
		@param rhs	[in] 接触判定用のコリジョン
		@return 当たっていればtrue
		@note
		二つのコリジョンの接触判定をします。
	*/
	bool IsIntersect( const Ray& lhs, const Plane& rhs );

	//------------------------------------------------------------

	/**
		@brief 接触判定
		@author 葉迩倭
		@param lhs	[in] 接触判定用のコリジョン
		@param rhs	[in] 接触判定用のコリジョン
		@return 当たっていればtrue
		@note
		二つのコリジョンの接触判定をします。
	*/
	bool IsIntersect( const Sphere& lhs, const Sphere& rhs );
	/**
		@brief 接触判定
		@author 葉迩倭
		@param lhs	[in] 接触判定用のコリジョン
		@param rhs	[in] 接触判定用のコリジョン
		@return 当たっていればtrue
		@note
		二つのコリジョンの接触判定をします。
	*/
	bool IsIntersect( const Sphere& lhs, const AABB& rhs );
	/**
		@brief 接触判定
		@author 葉迩倭
		@param lhs	[in] 接触判定用のコリジョン
		@param rhs	[in] 接触判定用のコリジョン
		@return 当たっていればtrue
		@note
		二つのコリジョンの接触判定をします。
	*/
	bool IsIntersect( const Sphere& lhs, const OBB& rhs );
	/**
		@brief 接触判定
		@author 葉迩倭
		@param lhs	[in] 接触判定用のコリジョン
		@param rhs	[in] 接触判定用のコリジョン
		@return 当たっていればtrue
		@note
		二つのコリジョンの接触判定をします。
	*/
	bool IsIntersect( const Sphere& lhs, const Plane& rhs );

	//------------------------------------------------------------

	/**
		@brief 接触判定
		@author 葉迩倭
		@param lhs	[in] 接触判定用のコリジョン
		@param rhs	[in] 接触判定用のコリジョン
		@return 当たっていればtrue
		@note
		二つのコリジョンの接触判定をします。
	*/
	bool IsIntersect( const AABB& lhs, const AABB& rhs );
	/**
		@brief 接触判定
		@author 葉迩倭
		@param lhs	[in] 接触判定用のコリジョン
		@param rhs	[in] 接触判定用のコリジョン
		@return 当たっていればtrue
		@note
		二つのコリジョンの接触判定をします。
	*/
	bool IsIntersect( const AABB& lhs, const OBB& rhs );
	/**
		@brief 接触判定
		@author 葉迩倭
		@param lhs	[in] 接触判定用のコリジョン
		@param rhs	[in] 接触判定用のコリジョン
		@return 当たっていればtrue
		@note
		二つのコリジョンの接触判定をします。
	*/
	bool IsIntersect( const AABB& lhs, const Plane& rhs );

	//------------------------------------------------------------

	/**
		@brief 接触判定
		@author 葉迩倭
		@param lhs	[in] 接触判定用のコリジョン
		@param rhs	[in] 接触判定用のコリジョン
		@return 当たっていればtrue
		@note
		二つのコリジョンの接触判定をします。
	*/
	bool IsIntersect( const OBB& lhs, const OBB& rhs );
	/**
		@brief 接触判定
		@author 葉迩倭
		@param lhs	[in] 接触判定用のコリジョン
		@param rhs	[in] 接触判定用のコリジョン
		@return 当たっていればtrue
		@note
		二つのコリジョンの接触判定をします。
	*/
	bool IsIntersect( const OBB& lhs, const Plane& rhs );

	//------------------------------------------------------------

	/**
		@brief 面の対する位置の取得
		@author 葉迩倭
		@param lhs	[in] 対象の面
		@param rhs	[in] 対象の箱
		@return 平面に対してどちら側にあるか
		@note
		平面に対してどちら側にあるかを調べます。
	*/
	eSide Side( const Plane& lhs, const AABB& rhs );
	/**
		@brief 面の対する位置の取得
		@author 葉迩倭
		@param lhs	[in] 対象の面
		@param rhs	[in] 対象の球
		@return 平面に対してどちら側にあるか
		@note
		平面に対してどちら側にあるかを調べます。
	*/
	eSide Side( const Plane& lhs, const Sphere& rhs );
}
}
}


/**
	@file
	@brief カメラ
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	/**
		@brief カメラクラス
		@author 葉迩倭
	*/
	class Camera
		: public Object::MemoryObject
	{
	protected:
		Matrix					m_mProjection;
		Kernel::Collision::OBB	m_Frustum;
		VectorS					m_vAxisX;
		VectorS					m_vAxisY;
		VectorS					m_vAxisZ;
		VectorS					m_vPosition;
		float					m_NearZ;
		float					m_FarZ;
		float					m_Aspect;
		float					m_Fov;

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		Camera();
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param value	[in] 初期値
		*/
		Camera( const Camera& value );
		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		virtual ~Camera();

	public:
		/**
			@brief フラスタムの更新
			@author 葉迩倭
		*/
		void UpdateFrustum();
		/**
			@brief 透視変換用プロジェクション行列生成
			@author 葉迩倭
			@param ovY		[in] 画角
			@param aspect	[in] アスペクト比
			@param zn		[in] Z近クリップ平面
			@param zf		[in] Z遠クリップ平面
			@note
			一般的な左手座標系プロジェクション行列を生成します。
		*/
		void PerspectiveFovLH( float ovY, float aspect, float zn, float zf );
		/**
			@brief 平行投影用プロジェクション行列生成
			@author 葉迩倭
			@param width	[in] 幅
			@param height	[in] 高さ
			@param zn		[in] Z近クリップ平面
			@param zf		[in] Z遠クリップ平面
			@note
			平行投影する為の左手座標系プロジェクション行列を生成します。
		*/
		void OrthographicLH( float width, float height, float zn, float zf );
		/**
			@brief 平行投影用プロジェクション行列生成
			@author 葉迩倭
			@note
			カメラの状態を初期化します。<BR>
			座標(0.0, 0.0, 0.0)から方向(0.0, 0.0, 1.0)を見ている状態になります。
		*/
		void Identity();
		/**
			@brief 移動
			@author 葉迩倭
			@param vMove	[in] 移動先
			@note
			カメラの移動をします。
		*/
		void Translation( const VectorS& vMove );
		/**
			@brief X軸回転
			@author 葉迩倭
			@param Angle	[in] 回転角度（ラジアン）
			@note
			カメラのX軸回転をします。
		*/
		void RotationX( float Angle );
		/**
			@brief Y軸回転
			@author 葉迩倭
			@param Angle	[in] 回転角度（ラジアン）
			@note
			カメラのY軸回転をします。
		*/
		void RotationY( float Angle );
		/**
			@brief Z軸回転
			@author 葉迩倭
			@param Angle	[in] 回転角度（ラジアン）
			@note
			カメラのZ軸回転をします。
		*/
		void RotationZ( float Angle );
		/**
			@brief 任意視点カメラ
			@author 葉迩倭
			@param vPosition	[in] カメラの位置
			@param vTarget		[in] カメラの注視位置
			@param Bank		[in] バンク角度（傾き）
			@note
			指定した位置から指定した場所を見るカメラを作成します。
		*/
		void LookAt( const VectorS& vPosition, const VectorS& vTarget, float Bank );
		/**
			@brief 任意視点カメラ
			@author 葉迩倭
			@param vPosition	[in] カメラの位置
			@param vTarget		[in] カメラの注視位置
			@param vUp			[in] カメラの上向き
			@note
			指定した位置から指定した場所を見るカメラを作成します。
		*/
		void LookAt( const VectorS& vPosition, const VectorS& vTarget, const VectorS& vUp );
		/**
			@brief ビュー行列を設定
			@author 葉迩倭
			@param mView	[in] ビュー行列
			@note
			カメラのビュー行列を設定します。
		*/
		void SetViewMatrix( const Matrix& mView );
		/**
			@brief ワールド行列を設定
			@author 葉迩倭
			@param mWorld	[in] ワールド行列
			@note
			カメラのワールド行列を設定します。
		*/
		void SetWorldMatrix( const Matrix& mWorld );
		/**
			@brief プロジェクション行列を設定
			@author 葉迩倭
			@param mProjection	[in] プロジェクション行列
			@note
			カメラのプロジェクション行列を設定します。
		*/
		void SetProjectionMatrix( const Matrix& mProjection );
		/**
			@brief 近クリップ距離取得
			@author 葉迩倭
			@return 近クリップ距離
			@note
			カメラの近クリップ距離を取得します。
		*/
		float GetNearClip() const;
		/**
			@brief 遠クリップ距離取得
			@author 葉迩倭
			@return 遠クリップ距離
			@note
			カメラの遠クリップ距離を取得します。
		*/
		float GetFarClip() const;
		/**
			@brief 位置取得
			@author 葉迩倭
			@return 位置
			@note
			カメラの位置を取得します。
		*/
		VectorS GetPosition() const;
		/**
			@brief ビュー行列を取得
			@author 葉迩倭
			@return ビュー行列
			@note
			カメラのビュー行列を取得します。
		*/
		Matrix GetViewMatrix() const;
		/**
			@brief ビューの逆行列を取得
			@author 葉迩倭
			@return ビューの逆行列
			@note
			カメラのビュー行列の逆行列を取得します。
		*/
		Matrix GetViewMatrixInverse() const;
		/**
			@brief ビューの逆行列を取得
			@author 葉迩倭
			@return ビューの逆行列
			@note
			カメラのビュー行列の逆行列を取得します。
		*/
		Matrix GetViewMatrixInverseDisableBank() const;
		/**
			@brief ワールド行列を取得
			@author 葉迩倭
			@return ワールド行列
			@note
			カメラのワールド行列を取得します。
		*/
		Matrix GetWorldMatrix() const;
		/**
			@brief プロジェクション行列を取得
			@author 葉迩倭
			@return プロジェクション行列
			@note
			カメラのプロジェクション行列を取得します。
		*/
		const Matrix& GetProjectionMatrix() const;
		/**
			@brief プロジェクション行列を取得
			@author 葉迩倭
			@return プロジェクション行列
			@note
			カメラのプロジェクション行列を取得します。
		*/
		Matrix& GetProjectionMatrix();
		/**
			@brief プロジェクション行列のFOVを取得
			@author 葉迩倭
			@return プロジェクション行列のFOV
			@note
			カメラのプロジェクション行列のFOVを取得します。
		*/
		float GetFov() const;
		/**
			@brief プロジェクション行列のアスペクトを取得
			@author 葉迩倭
			@return プロジェクション行列のアスペクト
			@note
			カメラのプロジェクション行列のアスペクトを取得します。
		*/
		float GetAspect() const;
		/**
			@brief プロジェクション内に軸並行箱が入っているかチェック
			@author 葉迩倭
			@param Aabb	[in] チェックする軸並行箱
			@return 入っていればtrue
			@note
			カメラのプロジェクション内に軸並行箱が入っているかチェックします。
		*/
		bool FrustumCulling( const Kernel::Collision::AABB& Aabb ) const;
		/**
			@brief プロジェクション内に軸並行箱が入っているかチェック
			@author 葉迩倭
			@param Sphere [in] チェックする球
			@return 入っていればtrue
			@note
			カメラのプロジェクション内に軸並行箱が入っているかチェックします。
		*/
		bool FrustumCulling( const Kernel::Collision::Sphere& Sphere ) const;

		/**
			@brief スクリーン座標からワールド座標を取得
			@author 少佐
			@param vScreenPosition	[in] スクリーン座標
			@param ScreenSize		[in] 画面サイズ
			@return ワールド座標
			@note
			スクリーン座標からワールド座標を取得を取得します。
		*/
		VectorS GetWorldPosition( const VectorS& vScreenPosition, const Vector2& ScreenSize ) const;

		/**
			@brief ワールド座標からスクリーン座標を取得
			@author 少佐
			@param vWorldPosition	[in] ワールド座標
			@param ScreenSize		[in] 画面サイズ
			@param IsInScreen		[out] 画面内かどうか
			@return ワールド座標
			@note
			ワールド座標からスクリーン座標を取得します。
		*/
		VectorS GetScreenPosition( const VectorS& vWorldPosition, const Vector2& ScreenSize, bool& IsInScreen ) const;

		/**
			@brief ビューフラスタム取得
			@author 葉迩倭
			@return ビューフラスタム
			@note
			カメラのビューふラスタムを取得します。
		*/
		const Kernel::Collision::OBB& GetFrustum() const;
	};
}
}
}


/**
	@file
	@brief デリゲート
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
	class Delegate00
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call() const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)();

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call() const
			{
				m_Function();
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)();

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call() const
			{
				(m_pClass->*m_Method)();
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate00()
			: m_pDelegate	( NULL )
		{
		}

		Delegate00( const Delegate00& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate00( T* pClass, void (T::*Method)() )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate00( void (SLN_STDCALL *Function)() )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate00()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call() const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call();
			}
		}

		void operator ()() const
		{
			Call();
		}

		Delegate00& operator = ( const Delegate00& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1 >
	class Delegate01
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1 ) const
			{
				m_Function( a1 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1 ) const
			{
				(m_pClass->*m_Method)( a1 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate01()
			: m_pDelegate	( NULL )
		{
		}

		Delegate01( const Delegate01& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate01( T* pClass, void (T::*Method)(A1) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate01( void (SLN_STDCALL *Function)(A1) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate01()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1 );
			}
		}

		void operator ()( A1 a1 ) const
		{
			Call( a1 );
		}

		Delegate01& operator = ( const Delegate01& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2 >
	class Delegate02
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2 ) const
			{
				m_Function( a1, a2 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2 ) const
			{
				(m_pClass->*m_Method)( a1, a2 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate02()
			: m_pDelegate	( NULL )
		{
		}

		Delegate02( const Delegate02& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate02( T* pClass, void (T::*Method)(A1,A2) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate02( void (SLN_STDCALL *Function)(A1,A2) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate02()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2 );
			}
		}

		void operator ()( A1 a1, A2 a2 ) const
		{
			Call( a1, a2 );
		}

		Delegate02& operator = ( const Delegate02& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2, typename A3 >
	class Delegate03
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2, A3 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2, A3 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3 ) const
			{
				m_Function( a1, a2, a3 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2, A3 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3 ) const
			{
				(m_pClass->*m_Method)( a1, a2, a3 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate03()
			: m_pDelegate	( NULL )
		{
		}

		Delegate03( const Delegate03& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate03( T* pClass, void (T::*Method)(A1,A2,A3) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate03( void (SLN_STDCALL *Function)(A1,A2,A3) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate03()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2, A3 a3 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2, a3 );
			}
		}

		void operator ()( A1 a1, A2 a2, A3 a3 ) const
		{
			Call( a1, a2, a3 );
		}

		Delegate03& operator = ( const Delegate03& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2, typename A3, typename A4 >
	class Delegate04
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2, A3, A4 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2, A3, A4 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4 ) const
			{
				m_Function( a1, a2, a3, a4 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2, A3, A4 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4 ) const
			{
				(m_pClass->*m_Method)( a1, a2, a3, a4 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate04()
			: m_pDelegate	( NULL )
		{
		}

		Delegate04( const Delegate04& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate04( T* pClass, void (T::*Method)(A1,A2,A3,A4) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate04( void (SLN_STDCALL *Function)(A1,A2,A3,A4) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate04()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2, A3 a3, A4 a4 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2, a3, a4 );
			}
		}

		void operator ()( A1 a1, A2 a2, A3 a3, A4 a4 ) const
		{
			Call( a1, a2, a3, a4 );
		}

		Delegate04& operator = ( const Delegate04& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2, typename A3, typename A4, typename A5 >
	class Delegate05
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2, A3, A4, A5 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2, A3, A4, A5 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ) const
			{
				m_Function( a1, a2, a3, a4, a5 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2, A3, A4, A5 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ) const
			{
				(m_pClass->*m_Method)( a1, a2, a3, a4, a5 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate05()
			: m_pDelegate	( NULL )
		{
		}

		Delegate05( const Delegate05& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate05( T* pClass, void (T::*Method)(A1,A2,A3,A4,A5) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate05( void (SLN_STDCALL *Function)(A1,A2,A3,A4,A5) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate05()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2, a3, a4, a5 );
			}
		}

		void operator ()( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ) const
		{
			Call( a1, a2, a3, a4, a5 );
		}

		Delegate05& operator = ( const Delegate05& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2, typename A3, typename A4, typename A5, typename A6 >
	class Delegate06
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2, A3, A4, A5, A6 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2, A3, A4, A5, A6 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6 ) const
			{
				m_Function( a1, a2, a3, a4, a5, a6 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2, A3, A4, A5, A6 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6 ) const
			{
				(m_pClass->*m_Method)( a1, a2, a3, a4, a5, a6 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate06()
			: m_pDelegate	( NULL )
		{
		}

		Delegate06( const Delegate06& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate06( T* pClass, void (T::*Method)(A1,A2,A3,A4,A5,A6) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate06( void (SLN_STDCALL *Function)(A1,A2,A3,A4,A5,A6) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate06()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2, a3, a4, a5, a6 );
			}
		}

		void operator ()( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6 ) const
		{
			Call( a1, a2, a3, a4, a5, a6 );
		}

		Delegate06& operator = ( const Delegate06& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7 >
	class Delegate07
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2, A3, A4, A5, A6, A7 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2, A3, A4, A5, A6, A7 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7 ) const
			{
				m_Function( a1, a2, a3, a4, a5, a6, a7 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2, A3, A4, A5, A6, A7 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7 ) const
			{
				(m_pClass->*m_Method)( a1, a2, a3, a4, a5, a6, a7 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate07()
			: m_pDelegate	( NULL )
		{
		}

		Delegate07( const Delegate07& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate07( T* pClass, void (T::*Method)(A1,A2,A3,A4,A5,A6,A7) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate07( void (SLN_STDCALL *Function)(A1,A2,A3,A4,A5,A6,A7) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate07()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2, a3, a4, a5, a6, a7 );
			}
		}

		void operator ()( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7 ) const
		{
			Call( a1, a2, a3, a4, a5, a6, a7 );
		}

		Delegate07& operator = ( const Delegate07& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8 >
	class Delegate08
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2, A3, A4, A5, A6, A7, A8 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2, A3, A4, A5, A6, A7, A8 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8 ) const
			{
				m_Function( a1, a2, a3, a4, a5, a6, a7, a8 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2, A3, A4, A5, A6, A7, A8 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8 ) const
			{
				(m_pClass->*m_Method)( a1, a2, a3, a4, a5, a6, a7, a8 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate08()
			: m_pDelegate	( NULL )
		{
		}

		Delegate08( const Delegate08& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate08( T* pClass, void (T::*Method)(A1,A2,A3,A4,A5,A6,A7,A8) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate08( void (SLN_STDCALL *Function)(A1,A2,A3,A4,A5,A6,A7,A8) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate08()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2, a3, a4, a5, a6, a7, a8 );
			}
		}

		void operator ()( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8 ) const
		{
			Call( a1, a2, a3, a4, a5, a6, a7, a8 );
		}

		Delegate08& operator = ( const Delegate08& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	//--------------------------------------------------------------------------------------------------------------------------//

	template < typename T >
	Delegate00 CreateDelegate( T* pClass, void (T::*pFunction)() )
	{
		return Delegate00( pClass, pFunction );
	}
	template < typename T, typename A1 >
	Delegate01< A1 > CreateDelegate( T* pClass, void (T::*pFunction)( A1 ) )
	{
		return Delegate01< A1 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2 >
	Delegate02< A1, A2 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2 ) )
	{
		return Delegate02< A1, A2 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2, typename A3 >
	Delegate03< A1, A2, A3 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2, A3 ) )
	{
		return Delegate03< A1, A2, A3 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2, typename A3, typename A4 >
	Delegate04< A1, A2, A3, A4 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2, A3, A4 ) )
	{
		return Delegate04< A1, A2, A3, A4 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2, typename A3, typename A4, typename A5 >
	Delegate05< A1, A2, A3, A4, A5 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2, A3, A4, A5 ) )
	{
		return Delegate05< A1, A2, A3, A4, A5 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6 >
	Delegate06< A1, A2, A3, A4, A5, A6 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2, A3, A4, A5, A6 ) )
	{
		return Delegate06< A1, A2, A3, A4, A5, A6 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7 >
	Delegate07< A1, A2, A3, A4, A5, A6, A7 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2, A3, A4, A5, A6, A7 ) )
	{
		return Delegate07< A1, A2, A3, A4, A5, A6, A7 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8 >
	Delegate08< A1, A2, A3, A4, A5, A6, A7, A8 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2, A3, A4, A5, A6, A7, A8 ) )
	{
		return Delegate08< A1, A2, A3, A4, A5, A6, A7, A8 >( pClass, pFunction );
	}

	//--------------------------------------------------------------------------------------------------------------------------//

	#define SLN_EVENT(...)		Kernel::CreateDelegate( this, __VA_ARGS__ )

}	// namespace Kernel
}	// namespace Selene


/**
	@file
	@brief		文字列ユーティリティ　定義
	@author		椿
*/


namespace Selene
{
namespace Kernel
{
namespace String
{
	//---------------------------------------------------------------------------//
	/**
		@brief		文字列ユーティリティ
		@author		椿
		@note		色んなことをやります。速度は無視します
	*/
	class Utility
	{
		///< 実装しちゃだめ！
		Utility();

	public:
		static std::string ToMultiByte( const wchar_t* pText )
		{
			Sint32 Len = ::WideCharToMultiByte( CP_ACP, 0, pText, -1, NULL, 0, NULL, NULL );

			char* pOut = new char [ Len + 1 ];
			::WideCharToMultiByte( CP_ACP, 0, pText, -1, pOut, Len, NULL, NULL );
			std::string Out( pOut );
			delete [] pOut;

			return Out;
		}

		static std::wstring ToWide( const char* pText )
		{
			Sint32 Len = ::MultiByteToWideChar( CP_ACP, 0, pText, -1, NULL, 0 );

			wchar_t* pOut = new wchar_t [ Len + 1 ];
			::MultiByteToWideChar( CP_ACP, 0, pText, -1, pOut, Len );
			std::wstring Out( pOut );
			delete [] pOut;

			return Out;
		}

		static std::wstring Format( const wchar_t* pString, ... )
		{
			wchar_t Text[1024];
			vswprintf_s( Text, 1024, pString, reinterpret_cast<va_list>(&pString + 1) );
			return std::wstring( Text );
		}

		template<typename T>
		static std::basic_string<T>	Trim( const std::basic_string<T>& str, const T* aChar )
		{
			std::basic_string<T>::size_type begin_pos = str.find_first_not_of( aChar );
			std::basic_string<T>::size_type end_pos = str.find_last_not_of( aChar );
			return str.substr( begin_pos, end_pos - begin_pos + 1 );
		}

		///< 実装しちゃだめ！
		template<typename T>
		static std::basic_string<T> TrimSpace( const std::basic_string<T>& str );

		template<>
		static std::basic_string<char> TrimSpace( const std::basic_string<char>& str )
		{
			return Trim( str, "\r\n\t " );
		}

		template<>
		static std::basic_string<wchar_t> TrimSpace( const std::basic_string<wchar_t>& str )
		{
			return Trim( str, L"\r\n\t " );
		}
	};

}	// namespace String
}	// namespace Kernel
}	// namespace Selene


/**
	@file
	@brief CPUタイマー
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Timer
{
	static Uint64 CPUTIMER_COUNT = 1000000;		///< １秒のカウント数

	/**
		@brief CPUタイマー
		@author 葉迩倭
	*/
	class SystemTimer
	{
	private:
		static Uint64 m_OneSecCount;

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		SystemTimer();
		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		~SystemTimer();
		/**
			@brief カウント取得
			@author 葉迩倭
			@return CPUカウント
		*/
		Uint64 Get() const;
	};
}
}
}


/**
	@file
	@brief プロファイラー
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Timer
{
	/**
		@brief プロファイラー
		@author 葉迩倭
	*/
	class Profiler
	{
	private:
		SystemTimer	m_Timer;
		wchar_t		m_Name[64];
		Uint64		m_Start;
		Uint64		m_Count;

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		Profiler();
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param pName	[in] プロファイル名
		*/
		Profiler( const wchar_t* pName );
		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		~Profiler();
		/**
			@brief 名前設定
			@author 葉迩倭
			@param pName	[in] プロファイル名
			@note
			プロファイルの名前を設定します
		*/
		void SetName( const wchar_t* pName );
		/**
			@brief プロファイル開始
			@author 葉迩倭
			@return プロファイル名
			@note
			プロファイルの名前を取得します
		*/
		const wchar_t* GetName() const;
		/**
			@brief プロファイル開始
			@author 葉迩倭
			@note
			プロファイルの処理を開始します
		*/
		void Begin();
		/**
			@brief プロファイル終了
			@author 葉迩倭
			@note
			プロファイルの処理を終了します
		*/
		void End();
		/**
			@brief プロファイル時間リセット
			@author 葉迩倭
			@note
			プロファイルの処理時間を初期化します
		*/
		void Reset();
		/**
			@brief プロファイル時間取得
			@author 葉迩倭
			@return プロファイル時間
			@note
			プロファイルのBegin()からEnd()までの所要時間を取得します
		*/
		float Get() const;
	};
}
}
}



#ifdef __cplusplus_cli
#pragma managed(pop)
#endif
#ifdef __cplusplus_cli
#pragma managed( push, off )
#endif
/**
	@file
	@brief Engine基本定義
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
/**
	@brief ライブラリ名前空間
*/
namespace Selene
{
	/**
		@brief エンジン
	*/
	namespace Engine
	{
		class ICore;

		/**
			@brief ウィンドウ
		*/
		namespace Window
		{
			class IWindow;
		}

		/**
			@brief タスク
		*/
		namespace Task
		{
			class ITaskManager;
		}

		/**
			@brief ファイル
		*/
		namespace File
		{
			class IManager;
			class IPackFile;
			class IStreamFile;
			class IFile;
		}

		/**
			@brief グラフィック
		*/
		namespace Graphics
		{
			/**
				@brief バッファロックフラグ
			*/
			enum eLock
			{
				LOCK_STATIC,		///< 通常ロック
				LOCK_DISCARD,		///< 全更新ロック（IsDyanmic=true時限定）
				LOCK_NOOVERWRITE,	///< 部分更新ロック（IsDyanmic=true時限定）
			};

			class IManager;

			/**
				@brief ステート
			*/
			namespace State
			{
				class IRenderState;
			}

			/**
				@brief シンプル
			*/
			namespace Simple
			{
				class ILineRenderer;
				class ISpriteRenderer;
				class ISpriteRenderer3D;
				class ITriangleRenderer;
				class ITextRenderer;
			}

			/**
				@brief リソース
			*/
			namespace Resource
			{
				class ITexture;
				class IShaderConstantBuffer;
				class IGeometryShader;
				class IVertexShader;
				class IVertexLayout;
				class IVertexBuffer;
				class IIndexBuffer;
				class IPixelShader;
				class IMaterialPlugin;
				class IMaterialListener;
				class IFileLoadListener;
				class IDrawObject;
				class IMaterial;
				class IRenderTable;
				class ILocalResource;
				class IRootMotion;

				/**
					@brief SMFモデル
				*/
				namespace SMF
				{
					class IConstraint;
					class INode;
					class IModel;
					class IModelController;
					class IMotion;
					class IMotionController;
					class IMotionScheduler;
				}

				/**
					@brief STMモデル
				*/
				namespace STM
				{
					class IModelController;
				}

				/**
					@brief テキスト
				*/
				namespace Text
				{
					class ITextData;
				}

				/**
					@brief ポリゴンライン
				*/
				namespace PolyLine
				{
					class IPolyLineController;
				}

				/**
					@brief スプライト
				*/
				namespace Sprite
				{
					class ISpriteController;
				}

				/**
					@brief プリミティブ
				*/
				namespace Primitive
				{
					class IPrimitiveController;
				}

				/**
					@brief パーティクル
				*/
				namespace Particle
				{
					struct SParameter;
					class IParticleController;
					class IVolumeParticleController;
					class IEnhancedParticleController;
				}
			}
		}

		/**
			@brief レンダラー
		*/
		namespace Renderer
		{
			class IManager;

			/**
				@brief 標準実装
			*/
			namespace Standard
			{
				struct SMaterialOption;
				class IRenderer;

				namespace Material
				{
					namespace Standard
					{
						class IMaterial;
					}

					namespace Water
					{
						class IMaterial;
					}
				}
			}
		}

		/**
			@brief サウンド
		*/
		namespace Sound
		{
			class IManager;

			namespace Resource
			{
				class IStaticSound;
				class IStreamSound;
			}
		}

		/**
			@brief 入力デバイス
		*/
		namespace Input
		{
			/**
				@brief ボタンの状態
				@author 葉迩倭
			*/
			enum eButtonState
			{
				BUTTON_STATE_FREE,	///< 離している
				BUTTON_STATE_PULL,	///< 離された
				BUTTON_STATE_PUSH,	///< 押された
				BUTTON_STATE_HOLD,	///< 押している
			};

			/**
				@brief 仮想キーコード
				@author 葉迩倭
			*/
			enum eKeyCode
			{
				KEY_ESCAPE          = 0x01,
				KEY_1               = 0x02,
				KEY_2               = 0x03,
				KEY_3               = 0x04,
				KEY_4               = 0x05,
				KEY_5               = 0x06,
				KEY_6               = 0x07,
				KEY_7               = 0x08,
				KEY_8               = 0x09,
				KEY_9               = 0x0A,
				KEY_0               = 0x0B,
				KEY_MINUS           = 0x0C,
				KEY_EQUALS          = 0x0D,
				KEY_BACK            = 0x0E,
				KEY_TAB             = 0x0F,
				KEY_Q               = 0x10,
				KEY_W               = 0x11,
				KEY_E               = 0x12,
				KEY_R               = 0x13,
				KEY_T               = 0x14,
				KEY_Y               = 0x15,
				KEY_U               = 0x16,
				KEY_I               = 0x17,
				KEY_O               = 0x18,
				KEY_P               = 0x19,
				KEY_LBRACKET        = 0x1A,
				KEY_RBRACKET        = 0x1B,
				KEY_RETURN          = 0x1C,
				KEY_LCONTROL        = 0x1D,
				KEY_A               = 0x1E,
				KEY_S               = 0x1F,
				KEY_D               = 0x20,
				KEY_F               = 0x21,
				KEY_G               = 0x22,
				KEY_H               = 0x23,
				KEY_J               = 0x24,
				KEY_K               = 0x25,
				KEY_L               = 0x26,
				KEY_SEMICOLON       = 0x27,
				KEY_APOSTROPHE      = 0x28,
				KEY_GRAVE           = 0x29,
				KEY_LSHIFT          = 0x2A,
				KEY_BACKSLASH       = 0x2B,
				KEY_Z               = 0x2C,
				KEY_X               = 0x2D,
				KEY_C               = 0x2E,
				KEY_V               = 0x2F,
				KEY_B               = 0x30,
				KEY_N               = 0x31,
				KEY_M               = 0x32,
				KEY_COMMA           = 0x33,
				KEY_PERIOD          = 0x34,
				KEY_SLASH           = 0x35,
				KEY_RSHIFT          = 0x36,
				KEY_MULTIPLY        = 0x37,
				KEY_LMENU           = 0x38,
				KEY_SPACE           = 0x39,
				KEY_CAPITAL         = 0x3A,
				KEY_F1              = 0x3B,
				KEY_F2              = 0x3C,
				KEY_F3              = 0x3D,
				KEY_F4              = 0x3E,
				KEY_F5              = 0x3F,
				KEY_F6              = 0x40,
				KEY_F7              = 0x41,
				KEY_F8              = 0x42,
				KEY_F9              = 0x43,
				KEY_F10             = 0x44,
				KEY_NUMLOCK         = 0x45,
				KEY_SCROLL          = 0x46,
				KEY_NUMPAD7         = 0x47,
				KEY_NUMPAD8         = 0x48,
				KEY_NUMPAD9         = 0x49,
				KEY_SUBTRACT        = 0x4A,
				KEY_NUMPAD4         = 0x4B,
				KEY_NUMPAD5         = 0x4C,
				KEY_NUMPAD6         = 0x4D,
				KEY_ADD             = 0x4E,
				KEY_NUMPAD1         = 0x4F,
				KEY_NUMPAD2         = 0x50,
				KEY_NUMPAD3         = 0x51,
				KEY_NUMPAD0         = 0x52,
				KEY_DECIMAL         = 0x53,
				KEY_OEM_102         = 0x56,
				KEY_F11             = 0x57,
				KEY_F12             = 0x58,
				KEY_KANA            = 0x70,
				KEY_ABNT_C1         = 0x73,
				KEY_CONVERT         = 0x79,
				KEY_NOCONVERT       = 0x7B,
				KEY_YEN             = 0x7D,
				KEY_ABNT_C2         = 0x7E,
				KEY_NUMPADEQUALS    = 0x8D,
				KEY_PREVTRACK       = 0x90,
				KEY_NUMPADENTER     = 0x9C,
				KEY_RCONTROL        = 0x9D,
				KEY_NUMPADCOMMA     = 0xB3,
				KEY_DIVIDE          = 0xB5,
				KEY_SYSRQ           = 0xB7,
				KEY_RMENU           = 0xB8,
				KEY_PAUSE           = 0xC5,
				KEY_HOME            = 0xC7,
				KEY_UP              = 0xC8,
				KEY_PRIOR           = 0xC9,
				KEY_LEFT            = 0xCB,
				KEY_RIGHT           = 0xCD,
				KEY_END             = 0xCF,
				KEY_DOWN            = 0xD0,
				KEY_NEXT            = 0xD1,
				KEY_INSERT          = 0xD2,
				KEY_DELETE          = 0xD3,
				KEY_LWIN            = 0xDB,
				KEY_RWIN            = 0xDC,

				KEY_DISABLE         = 0x00
			};

			class IManager;
			class IInputController;
			class IJoystick;
			class IKeyboard;
			class IMouse;
		}

		/**
			@brief ネットワーク
		*/
		namespace Network
		{
			/**
				@brief	ホスト情報
				@author 葉迩倭
			*/
			struct SHostInfo
			{
				char Name[64];						///< ホスト名
				char Alias[16][64];					///< ホスト別名テーブル
				char Address[16][64];				///< IPアドレステーブル
				Sint32 Type;						///< データタイプ
				Sint32 Length;						///< データサイズ
				Sint32 AliasCount;					///< エイリアス数
				Sint32 AddressCount;				///< IPアドレス数
			};

			class IManager;

			/**
				@brief TCP通信
			*/
			namespace TCP
			{
				class IClient;
				class IServer;
				class IClientOfServer;
				class IServerReciver;
				class IServerSender;
			}

			/**
				@brief UDP通信
			*/
			namespace UDP
			{
				class IConnect;
			}
		}

		/**
			@brief 物理
		*/
		namespace Dynamics
		{
			class IManager;

			namespace Body
			{
				class IBody;
				class IDynamicsBody;
				class IBox;
				class ICapsule;
				class ICharaProxy;
				class ICharaProxySimple;
				class IPlane;
				class ISphere;
				class ITriMesh;
				class ITriggerBox;
				class ICompound;
				class ICollisionBody;
				class ICollisionSphere;
				class ICollisionCapsule;
				class ICollisionBox;
				class ICollisionTriMesh;
				class ISoftBody;
				class IRope;

				/**
					@brief キャラクタのボディの種類
					@author 少佐
				*/
				enum eProxyType
				{
					PROXY_TYPE_SPHERE,					///< 球
					PROXY_TYPE_CAPSULE,					///< カプセル
				};

				/**
					@brief ボディの種類
					@author 葉迩倭
				*/
				enum eBodyType
				{
					BODY_TYPE_BOX,						///< 箱
					BODY_TYPE_CAPSULE,					///< カプセル
					BODY_TYPE_CHARA,					///< キャラクター
					BODY_TYPE_PLANE,					///< 平面
					BODY_TYPE_SPHERE,					///< 球
					BODY_TYPE_TRIMESH,					///< ポリゴンメッシュ
					BODY_TYPE_COMPOUND,					///< 複合
					BODY_TYPE_TRIGGER_BOX,				///< トリガー箱
					BODY_TYPE_ROPE,						///< ロープ
					BODY_TYPE_COLLISION_CAPSULE,		///< 衝突判定用カプセル
					BODY_TYPE_COLLISION_SPHERE,			///< 衝突判定用球
					BODY_TYPE_COLLISION_BOX,			///< 衝突判定用箱
					BODY_TYPE_COLLISION_TRIMESH,		///< 衝突判定用ポリゴンメッシュ
				};

				/**
					@brief 接触点情報
					@author 葉迩倭
				*/
				struct SContactInfo
				{
					Kernel::Math::Vector3	Normal;		///< 接触点法線
					Kernel::Math::Vector3	Position;	///< 接触点位置
					IBody*					pTarget;	///< 接触ボディ
				};

				/**
					@brief 複合オブジェクト
					@author 葉迩倭
				*/
				struct CompoundShape
					: public Kernel::Object::MemoryObject
				{
					/**
						@brief 複合オブジェクトの種類
						@author 葉迩倭
					*/
					enum Type
					{
						SPHERE,		///< 球
						CAPSULE,	///< カプセル
						BOX,		///< 箱
					};

					Kernel::Math::VectorS Position;		///< 位置
					Kernel::Math::VectorS Rotation;		///< 回転角度

					virtual ~CompoundShape(){}
					virtual Type GetType() const = 0;
				};

				/**
					@brief 複合オブジェクト球
					@author 葉迩倭
				*/
				struct CompoundShapeSphere
					: public CompoundShape
				{
					float Radius;		///< 半径

					virtual ~CompoundShapeSphere(){}
					virtual Type GetType() const { return SPHERE; }
				};

				/**
					@brief 複合オブジェクトカプセル
					@author 葉迩倭
				*/
				struct CompoundShapeCapsule
					: public CompoundShape
				{
					float Radius;		///< 半径
					float Length;		///< 長さ

					virtual ~CompoundShapeCapsule(){}
					virtual Type GetType() const { return CAPSULE; }
				};

				/**
					@brief 複合オブジェクト箱
					@author 葉迩倭
				*/
				struct CompoundShapeBox
					: public CompoundShape
				{
					Kernel::Math::VectorS Size;	//< サイズ

					virtual ~CompoundShapeBox(){}
					virtual Type GetType() const { return BOX; }
				};
			}

			/**
				@brief ジョイント
			*/
			namespace Joint
			{
				class IJoint;
				class ISliderJoint;
				class IHingeJoint;
				class IPointJoint;
				class IDofSpringJoint;
			}
		}

		/**
			@brief グラフィカルユーザーインターフェイス
		*/
		namespace GUI
		{
			class IManager;
			class IHelper;

			/**
				@brief GUIコントロール
			*/
			namespace Control
			{
				class IControl;
				class IIme;
				class IWindow;
				class IButton;
				class IProgressBar;
				class ISliderBar;
				class IScrollBar;
				class ILabel;
				class IGroupBox;
				class ICheckBox;
				class IListBox;
				class IComboBox;
				class IEditBox;
				class ITextBox;
				class IDialog;
				class IMenuBar;
				class IMenuButton;
				class IMenuList;
			}
		}
	}
}

/**
	@file
	@brief ゲーム用ウィンドウ
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Window
{
	/**
		@brief ゲーム用ウィンドウ管理クラス
		@author 葉迩倭
		@note
		ゲーム用ウィンドウ処理を統一して扱うためのインターフェイスです。
	*/
	class IWindow
		: public Interface
	{
	protected:
		virtual ~IWindow(){}

	public:
		/**
			@brief ウィンドウのハンドルを取得
			@author 葉迩倭
			@note
			ウィンドウのハンドルを取得します。
		*/
		virtual HWND GetHandle() = 0;

		/**
			@brief 閉じているかチェック
			@author 葉迩倭
			@retval true	閉じている
			@retval false	閉じていない
			@note
			ウィンドウが閉じられているか取得します。
		*/
		virtual bool IsClosed() = 0;

		/**
			@brief タイトルバーのテキスト設定
			@author 葉迩倭
			@param pText
			@note
			タイトルバーに表示するテキストを設定します。
		*/
		virtual void SetTitleText( const wchar_t* pText ) = 0;

		/**
			@brief ウィンドウサイズ取得
			@author 葉迩倭
			@return ウィンドウのサイズ
			@note
			ウィンドウのサイズを取得します。
		*/
		virtual Point2DI GetSize() = 0;

		/**
			@brief アクティブチェック
			@author 葉迩倭
			@retval true	ウィンドウはアクティブ
			@retval false	ウィンドウは非アクティブ
			@note
			ウィンドウがアクティブかどうかを取得します。
		*/
		virtual bool IsActive() = 0;

		/**
			@brief カーソル表示ON/OFF
			@author 葉迩倭
			@param IsShow	[in] 表示させる場合はtrue/表示を消す場合はfalse
			@note
			マウスカーソルの表示のON/OFFを設定します。
		*/
		virtual void SetShowCursor( bool IsShow ) = 0;

		/**
			@brief ウィンドウ終了処理時のコールバックイベント設定
			@author 葉迩倭
			@param Event	[in] コールバックイベント
			@note
			ウィンドウ終了の時のコールバックイベントを設定します。<BR>
			引数のbool値にfalseを設定するとウィンドウの終了をキャンセル出来ます。
		*/
		virtual void SetWindowCloseEvent( const Kernel::Delegate01<bool&>& Event ) = 0;

		/**
			@brief ファイルドラッグアンドドロップ処理時のコールバックイベント設定
			@author 葉迩倭
			@param Event	[in] コールバックイベント
			@note
			ファイルドラッグアンドドロップの時のコールバックイベントを設定します。
		*/
		virtual void SetFileDropEvent( const Kernel::Delegate02<Uint32,const wchar_t**>& Event ) = 0;

		/**
			@brief ウィンドウメッセージ処理時のコールバックイベント設定
			@author 葉迩倭
			@param Event	[in] コールバックイベント
			@note
			ウィンドウメッセージの時のコールバックイベントを設定します。
		*/
		virtual void SetWindowMessageEvent( const Kernel::Delegate04<Uint32,Sint64,Sint64&,bool&>& Event ) = 0;
	};
}
}
}

/**
	@file
	@brief ファイル操作用共通インターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace File
{
	/**
		@brief ファイル操作
		@author 葉迩倭
	*/
	class IFile
		: public Interface
	{
	protected:
		virtual ~IFile(){};

	public:
		/**
			@brief 読み込みチェック
			@author 葉迩倭
			@return trueなら正常に読まれている
			@note
			ファイルが正常に読まれているか否か
		*/
		virtual bool IsLoaded() const = 0;

		/**
			@brief ファイル名取得
			@author 葉迩倭
			@return ファイル名の先頭アドレス
			@note
			ファイル名の先頭アドレスを取得します。
		*/
		virtual const wchar_t* GetFileName() const = 0;

		/**
			@brief ファイルサイズ取得
			@author 葉迩倭
			@return ファイルサイズ
			@note
			ファイルのサイズを取得します。
		*/
		virtual Sint32 GetSize() const = 0;

		/**
			@brief データ取得
			@author 葉迩倭
			@return データの先頭ポインター
			@note
			ファイル内容のデータのポインターを取得します。
		*/
		virtual const void* GetData() const = 0;
	};
}
}
}

/**
	@file
	@brief ストリームファイルインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace File
{
	/**
		@brief ファイルストリーム操作
		@author 葉迩倭
	*/
	class IStreamFile
		: public Interface
	{
	protected:
		virtual ~IStreamFile(){};

	public:
		/**
			@brief ファイル名取得
			@author 葉迩倭
			@return ファイル名の先頭アドレス
			@note
			ファイル名の先頭アドレスを取得します。
		*/
		virtual const wchar_t* GetFileName() const = 0;

		/**
			@brief ファイルへの読み込み
			@author 葉迩倭
			@param pData	[in] 読み込みデータ
			@param Size		[in] 読み込みデータサイズ
			@return 実際に書き込んだバイト数
			@note
			ファイルへの読み込みを行います。<BR>
			読み込み可能なファイルはインターフェイス生成時に<BR>
			FILE_OPEN_TYPE_READかFILE_OPEN_TYPE_READ_WRITEフラグを<BR>
			指定する必要があります。
		*/
		virtual Sint32 Read( void* pData, Sint32 Size ) = 0;

		/**
			@brief ファイルサイズ取得
			@author 葉迩倭
			@return ファイルサイズ
			@note
			ファイルのサイズを取得します。
		*/
		virtual Sint32 GetFileSize() const = 0;

		/**
			@brief ファイルポインター位置取得
			@author 葉迩倭
			@return ファイルポインターの位置
			@note
			現在のファイルポインタの位置を取得します。
		*/
		virtual Sint32 GetFilePosition() const = 0;

		/**
			@brief ファイルシーク
			@author 葉迩倭
			@param Offset	[in] 移動量
			@return ファイルポインターの位置
			@note
			ファイルポインターの位置をファイルの先頭からOffsetバイト移動します。
		*/
		virtual Sint32 SeekStart( Sint32 Offset ) = 0;

		/**
			@brief ファイルシーク
			@author 葉迩倭
			@param Offset	[in] 移動量
			@return ファイルポインターの位置
			@note
			ファイルポインターの位置をファイルの終端からOffsetバイト移動します。
		*/
		virtual Sint32 SeekEnd( Sint32 Offset ) = 0;

		/**
			@brief ファイルシーク
			@author 葉迩倭
			@param Offset	[in] 移動量
			@return ファイルポインターの位置
			@note
			ファイルポインターの位置を現在の位置からOffsetバイト移動します。
		*/
		virtual Sint32 Seek( Sint32 Offset ) = 0;
	};
}
}
}

/**
	@file
	@brief パックファイルインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace File
{
	/**
		@brief パックファイルクラス
		@author 葉迩倭

		パックファイルの読み込み処理を行うためのインターフェイスです。
	*/
	class IPackFile
		: public Interface
	{
	protected:
		virtual ~IPackFile(){}

	public:
		/**
			@brief 読み込みチェック
			@author 葉迩倭
			@return trueなら正常に読まれている
			@note
			ファイルが正常に読まれているか否か
		*/
		virtual bool IsLoaded() const = 0;

		/**
			@brief IFileインターフェイスの取得
			@author 葉迩倭
			@param pDataName	[in] 取得するデータ名
			@return IFileインターフェイス
			@note
			指定したデータももつIFileインターフェイスを取得します
		*/
		virtual Engine::File::IFile* GetFile( const wchar_t* pDataName ) = 0;

		/**
			@brief IPackFileインターフェイスの取得
			@author 葉迩倭
			@param pDataName	[in] 取得するデータ名
			@return IPackFileインターフェイス
			@note
			パックファイル内のパックファイルを取得する為にIPackFileインターフェイスを取得します
		*/
		virtual IPackFile* GetPackFile( const wchar_t* pDataName ) = 0;

		/**
			@brief ファイルのシーク
			@author 葉迩倭
			@param pDataName	[in] シークするデータ名
			@return trueなら正常にシークできた
			@note
			指定したデータの先頭までファイルをシークします。
		*/
		virtual bool Seek( const wchar_t* pDataName ) = 0;

		/**
			@brief ファイル名取得
			@author 葉迩倭
			@return ファイル名の先頭アドレス
			@note
			ファイル名の先頭アドレスを取得します。
		*/
		virtual const wchar_t* GetFileName() const = 0;

		/**
			@brief ファイルサイズ取得
			@author 葉迩倭
			@return ファイルサイズ
			@note
			ファイルのサイズを取得します。
		*/
		virtual Sint32 GetSize() const = 0;

		/**
			@brief データ取得
			@author 葉迩倭
			@return データの先頭ポインター
			@note
			ファイル内容のデータのポインターを取得します。
		*/
		virtual const void* GetData() const = 0;
	};
}
}
}

/**
	@file
	@brief ファイルマネージャーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace File
{
	/**
		@brief ファイル管理クラス
		@author 葉迩倭

		ファイルの読み込み処理を行うためのインターフェイスです。
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		/**
			@brief ファイルアクセスのロック
			@author 葉迩倭
			@note
			ファイルアクセスをする時の排他処理を開始します。
		*/
		virtual void Lock() = 0;

		/**
			@brief ファイルアクセスのアンロック
			@author 葉迩倭
			@note
			ファイルアクセスをする時の排他処理を終了します。
		*/
		virtual void Unlock() = 0;

		/**
			@brief データ圧縮
			@author 葉迩倭
			@param pDst		[in/out] 圧縮後データ格納先
			@param DstSize	[out] 圧縮後データサイズ
			@param pSrc		[in] 元データ格納先
			@param SrcSize	[in] 元データサイズ
			@note
			データの圧縮を行います。
		*/
		virtual bool Compress( void* pDst, Uint32& DstSize, const void* pSrc, Uint32 SrcSize ) = 0;

		/**
			@brief データ解凍
			@author 葉迩倭
			@param pDst		[in/out] 解凍後データ格納先
			@param DstSize	[out] 解凍後データサイズ
			@param pSrc		[in] 元データ格納先
			@param SrcSize	[in] 元データサイズ
			@note
			データの解凍を行います。
		*/
		virtual bool Decompress( void* pDst, Uint32 DstSize, const void* pSrc, Uint32 SrcSize ) = 0;

		/**
			@brief 暗号用プラグイン＆パスワード設定
			@author 葉迩倭
			@param pPluginPath	[in] プラグイン名
			@param pPassword	[in] パスワード
			@note
			パックファイルの展開用の暗号プラグインとパスワードを設定します。
		*/
		virtual void SetCryptPlugin( const wchar_t* pPluginPath, const char* pPassword ) = 0;

		/**
			@brief 読み込み用ルートパス更新
			@author 葉迩倭
			@param pRootPathList	[in] ルートパスのリスト
			@note
			読み込み用のパスのルートのリストを設定します。<BR>
			配列の後ろに記述されている程、検索の優先度が高いです。
		*/
		virtual void UpdateRootPath( const wchar_t* pRootPathList[] ) = 0;

		/**
			@brief 読み込み用ルートパス追加
			@author 少佐
			@param pRootPath		[in] ルートパス
			@note
			読み込み用のパスのルートのリストを追加します。<BR>
			後に追加するほど、検索の優先度が高いです。
		*/
		virtual void AppendRootPath( const wchar_t* pRootPath ) = 0;

		/**
			@brief 読み込み用ルートパス書き出し
			@author 少佐
			@param pListFile		[in] ファイルリスト保存用ファイル名
			@note
			読み込み用のパスのルートのリストを出力します。
		*/
		virtual void SaveRootPath( const wchar_t* pListFile ) = 0;

		/**
			@brief 読み込み用ルートパス読み込み
			@author 葉迩倭
			@param pListFile		[in] 利用するファイルリストのファイル名
			@note
			読み込み用のパスのルートのリストを設定します。<BR>
			ファイルリストに書かれているファイルを登録します。
		*/
		virtual void LoadRootPath( const wchar_t* pListFile ) = 0;

		/**
			@brief 読み込み用カレントパス設定
			@author 葉迩倭
			@param pPath	[in] カレントのパス（LoadRootPathをルートとして指定する）
			@note
			読み込みを行うときのカレントのパスを設定します。
		*/
		virtual void SetCurrentPath( const wchar_t* pPath ) = 0;

		/**
			@brief ファイルのフルパスを取得
			@author 葉迩倭
			@param pOut			[out] パス格納先
			@param pFileName	[in] ファイル名
			@note
			ファイルの読み込み用のパスを取得します。
		*/
		virtual void GetFileFullPath( wchar_t* pOut, const wchar_t* pFileName ) = 0;

		/**
			@brief 同期ファイル読み込み
			@author 葉迩倭
			@param pFileName		[in] ファイル名
			@param IsLoadAbsPath	[in] 指定パスでファイル検索するかどうか
			@return Engine::File::IFileインターフェイス
			@note
			ファイルのブロック読み込みを行います。
		*/
		virtual Engine::File::IFile* OpenSyncFile( const wchar_t* pFileName, bool IsLoadAbsPath = false ) = 0;

		/**
			@brief 非同期ファイル読み込み
			@author 葉迩倭
			@param pFileName		[in] ファイル名
			@param IsLoadAbsPath	[in] 指定パスでファイル検索するかどうか
			@return Engine::File::IFileインターフェイス
			@note
			ファイルの非ブロック読み込みを行います。
		*/
		virtual Engine::File::IFile* OpenASyncFile( const wchar_t* pFileName, bool IsLoadAbsPath = false ) = 0;

		/**
			@brief ストリーム用ファイル読み込み
			@author 葉迩倭
			@param pFileName		[in] ファイル名
			@param IsLoadAbsPath	[in] 指定パスでファイル検索するかどうか
			@return Engine::File::IStreamFileインターフェイス
			@note
			ファイルのストリーム用インターフェイスを生成します。
		*/
		virtual Engine::File::IStreamFile* OpenStreamFile( const wchar_t* pFileName, bool IsLoadAbsPath = false ) = 0;

		/**
			@brief ストリーム用ファイル読み込み
			@author 葉迩倭
			@param pFile		[in] ファイル
			@return Engine::File::IStreamFileインターフェイス
			@note
			ファイルのストリーム用インターフェイスを生成します。
		*/
		virtual Engine::File::IStreamFile* OpenStreamFile( Engine::File::IFile* pFile ) = 0;

		/**
			@brief パックファイルからアクセス用のインターフェイスを生成
			@author 葉迩倭
			@param pFile		[in] ファイル
			@return IPackDataインターフェイス
			@note
			パックファイルのアクセス用のインターフェイスを生成します。
		*/
		virtual IPackFile* CreatePackFile( Engine::File::IFile* pFile ) = 0;
	};
}
}
}

/**
	@file
	@brief ステート管理用インターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace State
{
	/**
		@brief アルファブレンディング
		@author 葉迩倭
	*/
	enum eAlphaBlend
	{
		AB_OPACITY,				///< 不透明
		AB_BLEND,				///< 透明
		AB_ADD,					///< 加算
		AB_ADD_ALPHADISABLE,	///< 加算（アルファチャンネル無視）
		AB_SUB,					///< 減算
		AB_SUB_ALPHADISABLE,	///< 減算（アルファチャンネル無視）
		AB_MUL,					///< 乗算
		AB_SCREEN,				///< スクリーン

		AB_TYPE_MAX,
	};

	/**
		@brief カリング
		@author 葉迩倭
	*/
	enum eCulling
	{
		CULL_FRONT,		///< 全面を表示
		CULL_BACK,		///< 背面を表示
		CULL_DOUBLE,	///< 両面表示

		CULL_TYPE_MAX,
	};

	/**
		@brief シザリング
		@author 葉迩倭
	*/
	enum eScissorTest
	{
		ST_DISABLE,		///< シザリングしない
		ST_ENABLE,		///< シザリングする

		ST_TYPE_MAX,
	};

	/**
		@brief アルファテスト
		@author 葉迩倭
	*/
	enum eAlphaTest
	{
		AT_DISABLE,		///< アルファテストしない
		AT_ENABLE,		///< アルファテストする

		AT_TYPE_MAX,
	};

	/**
		@brief 深度テスト
		@author 葉迩倭
	*/
	enum eDepthTest
	{
		DT_DISABLE,		///< 深度テストしない
		DT_ENABLE,		///< 深度テストする

		DT_TYPE_MAX,
	};

	/**
		@brief 深度書き込み
		@author 葉迩倭
	*/
	enum eDepthWrite
	{
		DW_DISABLE,		///< 深度書き込みしない
		DW_ENABLE,		///< 深度書き込みする

		DW_TYPE_MAX,
	};

	/**
		@brief ポリゴン塗りつぶし
		@author 葉迩倭
	*/
	enum ePolygonFill
	{
		PF_SOLID,		///< 塗りつぶし
		PF_WIRE,		///< ワイヤフレーム

		PF_TYPE_MAX,
	};

	/**
		@brief ステート管理用インターフェイス
		@author 葉迩倭
		@note ステートの管理をするためのインターフェイス
	*/
	class IRenderState
		: public Interface
	{
	protected:
		virtual ~IRenderState(){}

	public:
		/**
			@brief アルファブレンド設定
			@author 葉迩倭
			@param Param	[in] アルファブレンドタイプ
			@note
			アルファブレンドに関する設定をします
		*/
		virtual void SetAlphaBlend( eAlphaBlend Param ) = 0;
		/**
			@brief カリング設定
			@author 葉迩倭
			@param Param	[in] カリングタイプ
			@note
			カリングに関する設定をします
		*/
		virtual void SetCulling( eCulling Param ) = 0;
		/**
			@brief シザーテスト設定
			@author 葉迩倭
			@param Param	[in] シザーテストタイプ
			@note
			シザーテストに関する設定をします
		*/
		virtual void SetScissorTest( eScissorTest Param ) = 0;
		/**
			@brief アルファテスト設定
			@author 葉迩倭
			@param Param	[in] アルファテストタイプ
			@note
			アルファテストに関する設定をします
		*/
		virtual void SetAlphaTest( eAlphaTest Param ) = 0;
		/**
			@brief 深度テスト設定
			@author 葉迩倭
			@param Param	[in] 深度テストタイプ
			@note
			深度テストに関する設定をします
		*/
		virtual void SetDepthTest( eDepthTest Param ) = 0;
		/**
			@brief 深度書き込み設定
			@author 葉迩倭
			@param Param	[in] 深度書き込みタイプ
			@note
			深度書き込みに関する設定をします
		*/
		virtual void SetDepthWrite( eDepthWrite Param ) = 0;
		/**
			@brief ポリゴン塗りつぶし設定
			@author 葉迩倭
			@param Param	[in] ポリゴン塗りつぶしタイプ
			@note
			ポリゴン塗りつぶしに関する設定をします
		*/
		virtual void SetPolygonFill( ePolygonFill Param ) = 0;
		/**
			@brief アルファブレンド取得
			@author 葉迩倭
			@return アルファブレンドタイプ
			@note
			アルファブレンドに関する設定を取得します
		*/
		virtual eAlphaBlend GetAlphaBlend() const = 0;
		/**
			@brief カリング取得
			@author 葉迩倭
			@return カリングタイプ
			@note
			カリングに関する設定を取得します
		*/
		virtual eCulling GetCulling() const = 0;
		/**
			@brief シザーテスト取得
			@author 葉迩倭
			@return シザーテストタイプ
			@note
			シザーテストに関する設定を取得します
		*/
		virtual eScissorTest GetScissorTest() const = 0;
		/**
			@brief アルファテスト取得
			@author 葉迩倭
			@return アルファテストタイプ
			@note
			アルファテストに関する設定を取得します
		*/
		virtual eAlphaTest GetAlphaTest() const = 0;
		/**
			@brief 深度テスト取得
			@author 葉迩倭
			@return 深度テストタイプ
			@note
			深度テストに関する設定を取得します
		*/
		virtual eDepthTest GetDepthTest() const = 0;
		/**
			@brief 深度書き込み取得
			@author 葉迩倭
			@return 深度書き込みタイプ
			@note
			深度書き込みに関する設定を取得します
		*/
		virtual eDepthWrite GetDepthWrite() const = 0;
		/**
			@brief ポリゴン塗りつぶし取得
			@author 葉迩倭
			@return ポリゴン塗りつぶしタイプ
			@note
			ポリゴン塗りつぶしに関する設定を取得します
		*/
		virtual ePolygonFill GetPolygonFill() const = 0;
		/**
			@brief クローン生成
			@author 葉迩倭
			@return 生成されたステート
			@note
			同一のステートを持つクローンを生成します。
		*/
		virtual IRenderState* Clone() const = 0;
		/**
			@brief 同一ステートチェック
			@author 葉迩倭
			@param pIn	[in] 比較するステート
			@note
			同一のステートかどうかチェックします
		*/
		virtual bool IsEqual( const IRenderState* pIn ) const = 0;
	};
}
}
}
}
/**
	@file
	@brief 簡易ライン描画用インターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Simple
{
	/**
		@brief ライン描画用頂点
		@author 葉迩倭
	*/
	struct SLineVertex
	{
		float Px;
		float Py;
		float Pz;
		ColorU Color;
	};

	/**
		@brief ライン描画モード
		@author 葉迩倭
	*/
	enum eLineMode
	{
		LINE_MODE_2D,	///< 2Dのラインを描画
		LINE_MODE_3D,	///< 3Dのラインを描画
	};

	/**
		@brief 2D簡易描画インターフェイス
		@author 葉迩倭
		@note 2D簡易描画をするためのインターフェイス
	*/
	class ILineRenderer
		: public Interface
	{
	protected:
		virtual ~ILineRenderer(){}

	public:
		/**
			@brief 描画開始
			@author 葉迩倭
			@param Mode		[in] ラインの描画モード
			@note
			このメソッドを呼ぶことで文字列の描画の開始を宣言できます。
		*/
		virtual void CacheReset( eLineMode Mode ) = 0;
		/**
			@brief 描画終了
			@author 葉迩倭
			@note
			このメソッドが呼ばれた時に実際に画面に対して描画が行われます。
		*/
		virtual void CacheDraw() = 0;
		/**
			@brief カメラ行列設定
			@author 葉迩倭
			@param Matrix	[in] カメラの行列
			@note
			描画に利用するカメラのマトリックスを設定します。<BR>
			これはBeing()の引数のeLineModeがLINE_MODE_3Dの場合に利用されます。
		*/
		virtual void SetCameraMatrix( const Kernel::Math::Matrix& Matrix ) = 0;
		/**
			@brief 描画乗算色設定
			@author 葉迩倭
			@param Color	[in] 乗算する色
			@note
			描画時に全体に乗算する色を設定できます。
		*/
		virtual void SetModulateColor( const ColorF& Color ) = 0;
		/**
			@brief 四角形描画リクエスト
			@author 葉迩倭
			@param Points	[in] 線文を構成する点データ（２つで１線分）
			@param Count	[in] 点の数（2点で１線分になるので最低でも２）
			@note
			キューに対して描画のリクエストを行います。
		*/
		virtual void DrawRequest( const SLineVertex* Points, Sint32 Count ) = 0;
	};
}
}
}
}

/**
	@file
	@brief 2D簡易描画用インターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Simple
{
	/**
		@brief 2D簡易描画インターフェイス
		@author 葉迩倭
		@note 2D簡易描画をするためのインターフェイス
	*/
	class ISpriteRenderer
		: public Interface
	{
	protected:
		virtual ~ISpriteRenderer(){}

	public:
		virtual void CacheReset() = 0;
		virtual void CacheDraw() = 0;

		virtual void SetScissorRect( const RectI& ScissorRect ) = 0;
		virtual const RectI& GetScissorRect() const = 0;

		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF& Color, Graphics::State::eAlphaBlend AlphaBlend ) = 0;
		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF ColorTbl[], Graphics::State::eAlphaBlend AlphaBlend ) = 0;

		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF& Color, Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF ColorTbl[], Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;

		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF& Color, const RectF& Src, Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend ) = 0;
		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF ColorTbl[], const RectF& Src, Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend ) = 0;

		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF& Color, const RectF& Src, Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF ColorTbl[], const RectF& Src, Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		virtual void PolygonRequest( const Point2DF DstTbl[], Sint32 Priority, const ColorF ColorTbl[], const Point2DF SrcTbl[], Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend ) = 0;

		virtual void SquareDirect( const RectF& Dst, const ColorF& Color, const RectF& Src, Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		virtual void SquareDirect( const RectF& Dst, const ColorF ColorTbl[], const RectF& Src, Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		virtual void PolygonDirect( const Point2DF DstTbl[], const ColorF ColorTbl[], const Point2DF SrcTbl[], Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
	};
}
}
}
}

/**
	@file
	@brief 2D簡易描画用インターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Simple
{
	/**
		@brief 2D簡易描画インターフェイス
		@author 葉迩倭
		@note 2D簡易描画をするためのインターフェイス
	*/
	class ISpriteRenderer3D
		: public Interface
	{
	protected:
		virtual ~ISpriteRenderer3D(){}

	public:
		/**
			@brief 描画開始
			@author 葉迩倭
			@note
			このメソッドを呼ぶことで文字列の描画の開始を宣言できます。
		*/
		virtual void CacheReset() = 0;
		/**
			@brief 描画終了
			@author 葉迩倭
			@note
			このメソッドが呼ばれた時に実際に画面に対して描画が行われます。
		*/
		virtual void CacheDraw() = 0;
		/**
			@brief 描画データ空チェック
			@author 葉迩倭
			@return 描画データがあればtrue
			@note
			描画するデータがあるかを返します。
		*/
		virtual bool IsEmpty() = 0;
		/**
			@brief カメラ行列設定
			@author 葉迩倭
			@param mView		[in] ビューの行列
			@param mProjection	[in] プロジェクションの行列
			@note
			描画に利用するカメラのマトリックスを設定します。
		*/
		virtual void SetCameraMatrix( const Kernel::Math::Matrix& mView, const Kernel::Math::Matrix& mProjection ) = 0;
		/**
			@brief 描画乗算色設定
			@author 葉迩倭
			@param Color	[in] 乗算する色
			@note
			描画時に全体に乗算する色を設定できます。
		*/
		virtual void SetModulateColor( const ColorF& Color ) = 0;
		/**
			@brief テクスチャフィルター有無設定
			@author 葉迩倭
			@param IsFilterEnable	[in] フィルターの有無
			@note
			描画するポリゴンに対するテクスチャのフィルターの有無を設定します。
		*/
		virtual void SetTextureFilterEnable( bool IsFilterEnable ) = 0;
		/**
			@brief テクスチャ繰り返し有無設定
			@author 葉迩倭
			@param IsFilterEnable	[in] 繰り返しの有無
			@note
			描画するポリゴンに対するテクスチャの繰り返しの有無を設定します。
		*/virtual void SetTextureRepeatEnable( bool IsRepeatEnable ) = 0;
		/**
			@brief 四角形描画リクエスト
			@author 葉迩倭
			@param Position			[in] 描画先
			@param PositionOffset	[in] 描画先オフセット
			@param Size				[in] 描画サイズ
			@param Color			[in] 描画色
			@param Src				[in] 描画元
			@param pTexture			[in] 描画テクスチャ（NULLでColor単色塗りつぶし）
			@param AlphaBlend		[in] アルファブレンドの種類
			@param Radian			[in] 回転角度
			@param RotateOffset		[in] 回転時の中心からのオフセット
			@note
			キューに対して描画のリクエストを行います。<BR>
			このメソッドではテクスチャ付きの単純な四角形の描画を行います。
		*/
		virtual void SquareRequest( const Kernel::Math::Vector3& Position, const Kernel::Math::Vector3& PositionOffset, const Kernel::Math::Vector2& Size, const ColorF& Color, const RectF& Src, Resource::ITexture* pTexture, State::eAlphaBlend AlphaBlend, float Radian = 0.0f, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		/**
			@brief 四角形描画
			@author 葉迩倭
			@param Position			[in] 描画先
			@param PositionOffset	[in] 描画先オフセット
			@param Size				[in] 描画サイズ
			@param Color			[in] 描画色
			@param Src				[in] 描画元
			@param pTexture			[in] 描画テクスチャ（NULLでColor単色塗りつぶし）
			@param AlphaBlend		[in] アルファブレンドの種類
			@param Radian			[in] 回転角度
			@param RotateOffset		[in] 回転時の中心からのオフセット
			@note
			キューに対して描画のリクエストを行わずに直接描画を行います。<BR>
			このメソッドではテクスチャ付きの単純な四角形の描画を行います。
		*/
		virtual void SquareDirect( const Kernel::Math::Vector3& Position, const Kernel::Math::Vector3& PositionOffset, const Kernel::Math::Vector2& Size, const ColorF& Color, const RectF& Src, Resource::ITexture* pTexture, State::eAlphaBlend AlphaBlend, float Radian = 0.0f, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		/**
			@brief 四角形描画リクエスト
			@author 葉迩倭
			@param Position			[in] 描画先
			@param PositionOffset	[in] 描画先オフセット
			@param Size				[in] 描画サイズ
			@param ColorTbl			[in] 描画色（左上・右上・左下・右下の順番で４つ）
			@param Src				[in] 描画元
			@param pTexture			[in] 描画テクスチャ（NULLでColor塗りつぶし）
			@param AlphaBlend		[in] アルファブレンドの種類
			@param Radian			[in] 回転角度
			@param RotateOffset		[in] 回転時の中心からのオフセット
			@note
			キューに対して描画のリクエストを行います。<BR>
			このメソッドではテクスチャ付きの単純な四角形の描画を行います。
		*/
		virtual void SquareRequest( const Kernel::Math::Vector3& Position, const Kernel::Math::Vector3& PositionOffset, const Kernel::Math::Vector2& Size, const ColorF ColorTbl[], const RectF& Src, Resource::ITexture* pTexture, State::eAlphaBlend AlphaBlend, float Radian = 0.0f, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		/**
			@brief 四角形描画
			@author 葉迩倭
			@param Position			[in] 描画先
			@param PositionOffset	[in] 描画先オフセット
			@param Size				[in] 描画サイズ
			@param ColorTbl			[in] 描画色（左上・右上・左下・右下の順番で４つ）
			@param Src				[in] 描画元
			@param pTexture			[in] 描画テクスチャ（NULLでColor塗りつぶし）
			@param AlphaBlend		[in] アルファブレンドの種類
			@param Radian			[in] 回転角度
			@param RotateOffset		[in] 回転時の中心からのオフセット
			@note
			キューに対して描画のリクエストを行わずに直接描画を行います。<BR>
			このメソッドではテクスチャ付きの単純な四角形の描画を行います。
		*/
		virtual void SquareDirect( const Kernel::Math::Vector3& Position, const Kernel::Math::Vector3& PositionOffset, const Kernel::Math::Vector2& Size, const ColorF ColorTbl[], const RectF& Src, Resource::ITexture* pTexture, State::eAlphaBlend AlphaBlend, float Radian = 0.0f, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
	};
}
}
}
}

/**
	@file
	@brief テキスト描画用インターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Simple
{
	/**
		@brief テキスト描画インターフェイス
		@author 葉迩倭
		@note テキスト描画をするためのインターフェイス
	*/
	class ITextRenderer
		: public Interface
	{
	protected:
		virtual ~ITextRenderer(){}

	public:
		/**
			@brief 描画開始
			@author 葉迩倭
			@note
			このメソッドを呼ぶことで文字列の描画の開始を宣言できます。
		*/
		virtual void CacheReset() = 0;
		/**
			@brief 描画終了
			@author 葉迩倭
			@note
			このメソッドが呼ばれた時に実際に画面に対して描画が行われます。
		*/
		virtual void CacheDraw() = 0;
		/**
			@brief 文字列描画
			@author 葉迩倭
			@param Position		[in] 描画位置
			@param Color		[in] 文字色
			@param pText		[in] 文字列（書式はprintf）
			@note
			文字列の描画処理を行います。<BR>
			このメソッドでは実際に描画は行われず描画のリクエストだけを行います。
		*/
		virtual Point2DI DrawRequest( const Point2DI& Position, const ColorF& Color, const wchar_t* pText, ... ) = 0;
		/**
			@brief 左揃えテキストデータの文字描画
			@author 葉迩倭
			@param Position		[in] 描画位置
			@param Color			[in] 描画色
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@param IsBasePosition	[in] ベースポジションから描画するかどうかのフラグ
			@return 文字描画終端位置
			@note
			対象のインデックスに対して左揃えで文字の描画を行います。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual Point2DI DrawRequestBasePosition( const Point2DI& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief 左揃えテキストデータの文字描画
			@author 葉迩倭
			@param Rect				[in] 描画矩形
			@param Color			[in] 描画色
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@param IsBasePosition	[in] ベースポジションから描画するかどうかのフラグ
			@return 文字描画終端位置
			@note
			対象のインデックスに対して左揃えで文字の描画を行います。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual Point2DI DrawRequestLeft( const RectI& Rect, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief 中央揃えテキストデータの文字描画
			@author 葉迩倭
			@param Rect				[in] 描画矩形
			@param Color			[in] 描画色
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@param IsBasePosition	[in] ベースポジションから描画するかどうかのフラグ
			@return 文字描画終端位置
			@note
			対象のインデックスに対して中央揃えで文字の描画を行います。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual Point2DI DrawRequestCenter( const RectI& Rect, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief 右揃えテキストデータの文字描画
			@author 葉迩倭
			@param Rect				[in] 描画矩形
			@param Color			[in] 描画色
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@param IsBasePosition	[in] ベースポジションから描画するかどうかのフラグ
			@return 文字描画終端位置
			@note
			対象のインデックスに対して右揃えで文字の描画を行います。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual Point2DI DrawRequestRight( const RectI& Rect, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief テキストデータの描画優先度を設定
			@author 葉迩倭
			@param Priority	[in] 描画優先度
			@note
			テキストの描画時の描画優先度を設定します。<BR>
			内部的にはSimple::ISpriteRendererに対して同じことを行います。
		*/
		virtual void SetPriority( Sint32 Priority ) = 0;
		/**
			@brief テキスト描画用のスプライト設定
			@author 葉迩倭
			@param pSprite	[in] スプライトインターフェイス
			@note
			テキストの描画に使うスプライトを設定します。<BR>
			このメソッドによる設定を行わない場合は内部で保持している<BR>
			スプライトを利用居て描画されます。
		*/
		virtual void SetDrawSprite( Simple::ISpriteRenderer* pSprite ) = 0;
		/**
			@brief テキストデータの文字描画サイズ取得
			@author 葉迩倭
			@param pString		[in] サイズを調べる文字列
			@param Length		[in] 文字数（-1で全部）
			@return 文字描画サイズ
			@note
			文字の実際に描画した場合のサイズを取得します。
		*/
		virtual Point2DI GetDrawSize( const wchar_t* pString, Sint32 Length = -1 ) = 0;
		/**
			@brief テキストデータの文字描画位置設定
			@author 葉迩倭
			@param Rect		[in] シザリング領域
			@note
			対象のインデックスに対して文字データの文字描画位置を設定します。
		*/
		virtual void SetScissorRect( const RectI& Rect ) = 0;
		/**
			@brief テキストデータの文字描画位置設定
			@author 葉迩倭
			@param Position		[in] 文字描画位置
			@note
			対象のインデックスに対して文字データの文字描画位置を設定します。
		*/
		virtual void SetDrawBasePosition( const Point2DI& Position ) = 0;
	};
}
}
}
}
/**
	@file
	@brief 簡易トライアングル描画用インターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Simple
{
	/**
		@brief トライアングル描画用頂点
		@author 葉迩倭
	*/
	struct STriangleVertex
	{
		float Px;
		float Py;
		float Pz;
		float Nx;
		float Ny;
		float Nz;
		ColorU Color;
	};

	/**
		@brief トライアングル描画モード
		@author 葉迩倭
	*/
	enum eTriangleMode
	{
		TRIANGLE_MODE_2D,	///< 2Dのトライアングルを描画
		TRIANGLE_MODE_3D,	///< 3Dのトライアングルを描画
	};

	/**
		@brief 2D簡易描画インターフェイス
		@author 葉迩倭
		@note 2D簡易描画をするためのインターフェイス
	*/
	class ITriangleRenderer
		: public Interface
	{
	protected:
		virtual ~ITriangleRenderer(){}

	public:
		/**
			@brief 簡易ライト
			@author 葉迩倭
			@param DirectionVector	[in] ライトの方向
			@param ColorVector		[in] ライトの色
			@param AmbientVector	[in] 環境色
			@note
			シンプルなら平行光源の設定を行います。
		*/
		virtual void SetSimpleLight( const Kernel::Math::VectorS& DirectionVector, const Kernel::Math::VectorS& ColorVector, const Kernel::Math::VectorS& AmbientVector ) = 0;
		/**
			@brief 描画開始
			@author 葉迩倭
			@param Mode		[in] トライアングルの描画モード
			@note
			このメソッドを呼ぶことで文字列の描画の開始を宣言できます。
		*/
		virtual void CacheReset( eTriangleMode Mode ) = 0;
		/**
			@brief 描画終了
			@author 葉迩倭
			@note
			このメソッドが呼ばれた時に実際に画面に対して描画が行われます。
		*/
		virtual void CacheDraw() = 0;
		/**
			@brief クリップ領域設定
			@author 葉迩倭
			@param Matrix	[in] カメラの行列
			@note
			描画に利用するカメラのマトリックスを設定します。<BR>
			これはBeing()の引数のeTriangleModeがTRIANGLE_MODE_3Dの場合に利用されます。
		*/
		virtual void SetCameraMatrix( const Kernel::Math::Matrix& Matrix ) = 0;
		/**
			@brief 描画乗算色設定
			@author 葉迩倭
			@param Color	[in] 乗算する色
			@note
			描画時に全体に乗算する色を設定できます。
		*/
		virtual void SetModulateColor( const ColorF& Color ) = 0;
		/**
			@brief 三角形描画リクエスト
			@author 葉迩倭
			@param Points	[in] ポリゴンを構成する点データ（３つで１トライアングル）
			@param Count	[in] 点の数（３点で１トライアングルになるので最低でも３）
			@note
			キューに対して描画のリクエストを行います。
		*/
		virtual void DrawRequest( const STriangleVertex* Points, Sint32 Count ) = 0;
	};
}
}
}
}
/**
	@file
	@brief モーションインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief モーションインターフェイス
		@author 葉迩倭
	*/
	class IRootMotion
		: public Interface
	{
	protected:
		virtual ~IRootMotion(){}

	public:
		/**
			@brief 拡大縮小キーを取得
			@author 葉迩倭
			@return 値
			@note
			モーションから拡大縮小キーを取得します。
		*/
		virtual const Kernel::Math::VectorS& GetScaling() const = 0;
		/**
			@brief 回転キーを取得
			@author 葉迩倭
			@return 値
			@note
			モーションから回転キーを取得します。
		*/
		virtual const Kernel::Math::Quaternion& GetRotation() const = 0;
		/**
			@brief 位置キーを取得
			@author 葉迩倭
			@return 値
			@note
			モーションから位置キーを取得します。
		*/
		virtual const Kernel::Math::VectorS& GetPosition() const = 0;

		/**
			@brief 長さ取得
			@author 葉迩倭
			@return モーションの長さ（フレーム数）
			@note
			モーションの長さを取得します。
		*/
		virtual float GetLength() const = 0;

		/**
			@brief フレームレート設定
			@author 葉迩倭
			@param FrameRate	[in] フレームレート
			@note
			モーションのフレームレートを設定します。
		*/
		virtual void SetFrameRate( Sint32 FrameRate ) = 0;

		/**
			@brief モーションの更新
			@author 葉迩倭
			@param Frame	[in] フレーム
			@note
			モーションを１フレーム進めます。
		*/
		virtual void Update( float Frame, bool IsScale, bool IsRotate, bool IsMove ) = 0;
	};
}
}
}
}

/**
	@file
	@brief テクスチャーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief テクスチャーロック情報
		@author 葉迩倭
		@note テクスチャーロック時の情報格納用
	*/
	struct STextureLockInfo
	{
		void* pPixels;		///< 画像情報の戦闘アドレス
		Uint32 Pitch;		///< 画像の１ラインのバイト数
		Point2DI Size;		///< 画像のピクセルサイズ
	};

	/**
		@brief テクスチャーインターフェイス
		@author 葉迩倭
		@note テクスチャー用インターフェイス
	*/
	class ITexture
		: public Interface
	{
	protected:
		virtual ~ITexture(){}

	public:
		/**
			@brief テクスチャーサイズ取得
			@author 葉迩倭
			@return 生成時の要求サイズ
			@note
			テクスチャーの生成時の要求サイズ
		*/
		virtual const Point2DI& GetRequestSize() const = 0;
		/**
			@brief テクスチャーサイズ取得
			@author 葉迩倭
			@return 生成後の実際のサイズ
			@note
			テクスチャーの生成後の実際のサイズ
		*/
		virtual const Point2DI& GetTextureSize() const = 0;
		/**
			@brief テクスチャー⇒UV変換値取得
			@author 葉迩倭
			@return テクスチャのピクセル位置をUVに変換する為の値
			@note
			テクスチャのピクセル位置をUVに変換する為の値を取得します<BR>
			この値は 1.0f / GetTextureSize() と同じものです。
		*/
		virtual const Point2DF& GetTexel2UVTransform() const = 0;
		/**
			@brief テクスチャーを画像として保存
			@author 葉迩倭
			@param pFilePath	[in] ファイルパス
			@note
			テクスチャをBMPファイルとして保存します。
		*/
		virtual void SaveToBMP( const wchar_t* pFilePath ) const = 0;
		/**
			@brief テクスチャーを画像として保存
			@author 葉迩倭
			@param pFilePath	[in] ファイルパス
			@note
			テクスチャをPNGファイルとして保存します。
		*/
		virtual void SaveToPNG( const wchar_t* pFilePath ) const = 0;
		/**
			@brief テクスチャーを画像として保存
			@author 葉迩倭
			@param pFilePath	[in] ファイルパス
			@note
			テクスチャをDDSファイルとして保存します。
		*/
		virtual void SaveToDDS( const wchar_t* pFilePath ) const = 0;
		/**
			@brief テクスチャーをロック
			@author 葉迩倭
			@param Info			[in] ロックしたテクスチャの情報を格納するための構造体
			@note
			テクスチャへのCPUからのアクセスを開始します<BR>
			CPUアクセス可能なテクスチャ以外では失敗します。
		*/
		virtual bool Lock( STextureLockInfo& Info ) = 0;
		/**
			@brief テクスチャーをアンロック
			@author 葉迩倭
			@note
			テクスチャへのCPUからのアクセスを終了します<BR>
			CPUアクセス可能なテクスチャ以外では失敗します。
		*/
		virtual void Unlock() = 0;
		/**
			@brief テクスチャーをバックアップ
			@author 葉迩倭
			@note
			レンダリングターゲットテクスチャの内容を<BR>
			システムメモリへバックアップします。<BR>
			当然かなり重い処理なので要所要所で使いましょう。
		*/
		virtual bool BackupToSystem() = 0;
	};
}
}
}
}

/**
	@file
	@brief ジオメトリシェーダーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief ジオメトリシェーダーインターフェイス
		@author 葉迩倭
		@note ジオメトリシェーダー用インターフェイス
	*/
	class IGeometryShader
		: public Interface
	{
	protected:
		virtual ~IGeometryShader(){}
	};
}
}
}
}
/**
	@file
	@brief 頂点シェーダーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief 頂点シェーダーインターフェイス
		@author 葉迩倭
		@note 頂点シェーダー用インターフェイス
	*/
	class IVertexShader
		: public Interface
	{
	protected:
		virtual ~IVertexShader(){}
	};
}
}
}
}
/**
	@file
	@brief 頂点レイアウトインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief 頂点レイアウトフォーマット
		@author 葉迩倭
	*/
	enum eVertexLayoutFormat
	{
		VLF_FLOAT32x1,			///< 32Bit float x1
		VLF_FLOAT32x2,			///< 32Bit float x2
		VLF_FLOAT32x3,			///< 32Bit float x3
		VLF_FLOAT32x4,			///< 32Bit float x4
		VLF_FLOAT16x2,			///< 16Bit float x2
		VLF_FLOAT16x4,			///< 16Bit float x4
		VLF_R8G8B8A8,			///< (a,b,g,r) Packed unsigned int
		VLF_UINT8x4,			///< unsigned char x4
		VLF_UINT8Nx4,			///< unsigned char x4 (x/255, y/255, z/255, w/255)
		VLF_UINT16Nx2,			///< unsigned short x2 (x/65535, y/65535, 0.0, 1.0)
		VLF_UINT16Nx4,			///< unsigned short x4 (x/65535, y/65535, z/65535, w/65535)
		VLF_SINT16x2,			///< signed short x2
		VLF_SINT16x4,			///< signed short x4
		VLF_SINT16Nx2,			///< signed short x2 (x/32767, y/32767, 0.0, 1.0)
		VLF_SINT16Nx4,			///< signed short x4 (x/32767, y/32767, z/32767, w/32767)
	};

	/**
		@brief 頂点レイアウト種類
		@author 葉迩倭
	*/
	enum eVertexLayoutType
	{
		VLT_POSITION,			///< ワールド位置
		VLT_BLENDWEIGHT,		///< ブレンド用ウェイト
		VLT_BLENDINDEX,			///< ブレンド用インデックス
		VLT_NORMAL,				///< 法線
		VLT_TANGENT,			///< 接戦
		VLT_BINORMAL,			///< 従法線
		VLT_COLOR,				///< 色
		VLT_TEXCOORD,			///< テクスチャＵＶ
	};

	/**
		@brief 頂点レイアウト用
		@author 葉迩倭
	*/
	struct SVertexLayoutTable
	{
		Sint32 StreamNo;				///< ストリームの番号
		Sint32 Offset;					///< 構造体のオフセット
		eVertexLayoutFormat Format;		///< データのフォーマット
		eVertexLayoutType Type;			///< データのタイプ
		Sint32 TypeIndex;				///< タイプ毎のインデックス
	};

	/**
		@brief 頂点レイアウトインターフェイス
		@author 葉迩倭
		@note
		頂点のレイアウトを扱うためのインターフェイス
	*/
	class IVertexLayout
		: public Interface
	{
	protected:
		virtual ~IVertexLayout(){}

	public:
	};
}
}
}
}
/**
	@file
	@brief 頂点バッファインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief 頂点バッファインターフェイス
		@author 葉迩倭
		@note
		頂点のバッファを扱うためのインターフェイス
	*/
	class IVertexBuffer
		: public Interface
	{
	protected:
		virtual ~IVertexBuffer(){}

	public:
		/**
			@brief リングバッファ残頂点数種特
			@author 葉迩倭
			@param 残りの頂点数
			@note
			リングバッファの残りの要領を取得します。
		*/
		virtual Uint32 GetRingBufferRest() = 0;
		/**
			@brief リングバッファ書き込み
			@author 葉迩倭
			@note
			頂点バッファをリングバッファとして扱って書き込みます。
		*/
		virtual Uint32 RingBufferWrite( const void* pData, Uint32 Count ) = 0;
		/**
			@brief リングバッファ書き込み
			@author 葉迩倭
			@note
			頂点バッファをリングバッファとして扱って書き込みます。
		*/
		virtual Uint32 RingBufferWriteByPointer( const void* pData[], Uint32 Count ) = 0;
		/**
			@brief ロック
			@author 葉迩倭
			@note
			頂点バッファをロックして書き込み可能な状態にします。
		*/
		virtual void Lock() = 0;
		/**
			@brief ロック解除
			@author 葉迩倭
			@note
			頂点バッファのロックを解除して利用可能な状態にします。
		*/
		virtual void Unlock() = 0;
		/**
			@brief 追加
			@author 葉迩倭
			@note
			ロック中の頂点バッファにデータの追加をします。
		*/
		virtual void Push( const void* pBuffer, Sint32 Count ) = 0;
		/**
			@brief Pushされた頂点数取得
			@author 葉迩倭
			@return 頂点数
			@note
			実際にPushされている頂点数を取得します。
		*/
		virtual Sint32 GetCount() const = 0;
		/**
			@brief 頂点の１要素のサイズ
			@author 葉迩倭
			@return 頂点のサイズ
			@note
			頂点のサイズを取得します。
		*/
		virtual Sint32 GetSize() const = 0;
		/**
			@brief バッファ直接取得
			@author 葉迩倭
			@param Count	[in] 頂点数
			@return 頂点バッファ
			@note
			頂点データの格納先を取得します。
		*/
		virtual void* GetBufferDirect( Sint32 Count ) = 0;
	};
}
}
}
}
/**
	@file
	@brief 頂点インデックスバッファインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief 頂点インデックスインターフェイス
		@author 葉迩倭
		@note
		頂点のインデックスを扱うためのインターフェイス
	*/
	class IIndexBuffer
		: public Interface
	{
	protected:
		virtual ~IIndexBuffer(){}

	public:
		/**
			@brief ロック
			@author 葉迩倭
			@note
			頂点インデックスをロックして書き込み可能な状態にします。
		*/
		virtual void Lock() = 0;
		/**
			@brief ロック解除
			@author 葉迩倭
			@note
			頂点インデックスのロックを解除して利用可能な状態にします。
		*/
		virtual void Unlock() = 0;
		/**
			@brief 追加
			@author 葉迩倭
			@note
			ロック中の頂点インデックスにデータの追加をします。<BR>
			生成時のIs32BitIndexにtrueを指定している場合はunsigned intの配列を、<BR>
			falseを指定している場合はunsigned shortの配列を指定して下さい。
		*/
		virtual void Push( const void* pBuffer, Sint32 Count ) = 0;
		/**
			@brief Pushされたインデックス数取得
			@author 葉迩倭
			@return インデックス数
			@note
			実際にPushされているインデックス数を取得します。
		*/
		virtual Sint32 GetCount() const = 0;
		/**
			@brief バッファ直接取得
			@author 葉迩倭
			@param Count	[in] インデックス数
			@return インデックスバッファ
			@note
			インデックスデータ
		*/
		virtual void* GetBufferDirect( Sint32 Count ) = 0;
	};
}
}
}
}
/**
	@file
	@brief ピクセルシェーダーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief ピクセルシェーダーインターフェイス
		@author 葉迩倭
		@note ピクセルシェーダー用インターフェイス
	*/
	class IPixelShader
		: public Interface
	{
	protected:
		virtual ~IPixelShader(){}
	};
}
}
}
}
/**
	@file
	@brief ファイル読み込み用リスナーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief ファイル読み込み用インターフェイス
		@author 葉迩倭
	*/
	class IFileLoadListener
	{
	protected:
		virtual ~IFileLoadListener(){}

	public:
		/**
			@brief 読み込み時イベント
			@author 葉迩倭
			@param pFileName	[in] 要求ファイル名
			@param pFileBuffer	[in] ファイルのバッファー格納先
			@param FileSize		[in] ファイルサイズ
			@param pUserData	[in] ユーザー定義のポインター（読み込み時に指定されているポインター）
			@param pUserSetData	[in] ユーザーがセットするポインター（OnReleaseへの受け渡し）
			@note
			ファイル読み込みが必要になった時にエンジン内から呼び出されるコールバックメソッドです。
		*/
		virtual bool OnLoad( const wchar_t* pFileName, const void*& pFileBuffer, Sint32& FileSize, void*& pUserData, void* pUserSetData ) = 0;
		/**
			@brief 解放時イベント
			@author 葉迩倭
			@param pFileBuffer	[in] ファイルのバッファー格納先
			@param FileSize		[in] ファイルサイズ
			@param pUserData	[in] ユーザー定義のポインター（読み込み時に指定されているポインター）
			@param pUserSetData	[in] ユーザーがセットしたポインター（OnLoadからの受け渡し）
			@note
			ファイル解放が必要になった時にエンジン内から呼び出されるコールバックメソッドです。
		*/
		virtual void OnRelease( const void* pFileBuffer, Sint32 FileSize, void* pUserData, void* pUserSetData ) = 0;
	};
}
}
}
}

/**
	@file
	@brief 描画分割テーブルインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief 描画分割テーブル
		@author 葉迩倭
	*/
	class IRenderTable
		: public Interface
	{
	protected:
		virtual ~IRenderTable(){}

	public:
		/**
			@brief ボーン数
			@author 葉迩倭
			@return ボーン数
			@note
			テーブル内のボーンの数を取得します。
		*/
		virtual Sint32 GetBoneCount() const = 0;
		/**
			@brief ボーン番号テーブル
			@author 葉迩倭
			@return ボーン番号テーブル
			@note
			テーブル内のボーン番号テーブルを取得します。
		*/
		virtual const Uint8* GetBoneNoTable() const = 0;

		/**
			@brief ポリゴン開始インデックス取得
			@author 葉迩倭
			@return ポリゴン開始インデックス
			@note
			テーブル内のポリゴンの開始インデックスを取得します。
		*/
		virtual Uint32 GetPolygonStart() const = 0;
		/**
			@brief ポリゴン数取得
			@author 葉迩倭
			@return ポリゴン数
			@note
			テーブル内のポリゴン数を取得します。
		*/
		virtual Uint32 GetPolygonCount() const = 0;
		/**
			@brief 頂点開始インデックス取得
			@author 葉迩倭
			@return 頂点開始インデックス
			@note
			テーブル内の頂点の開始インデックスを取得します。
		*/
		virtual Uint32 GetVertexStart() const = 0;
		/**
			@brief 頂点数取得
			@author 葉迩倭
			@return 頂点数
			@note
			テーブル内の頂点の数を取得します。
		*/
		virtual Uint32 GetVertexCount() const = 0;
	};
}
}
}
}

/**
	@file
	@brief 描画オブジェクトインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	enum eDrawObjectType
	{
		DRAWOBJECT_TYPE_PRIMITIVE,
		DRAWOBJECT_TYPE_SPRITE,
		DRAWOBJECT_TYPE_PARTICLE,
		DRAWOBJECT_TYPE_POLYLINE,
	};

	class IDrawObject
		: public Interface
	{
	protected:
		virtual ~IDrawObject(){}

	public:
		virtual void Rendering( const Kernel::Math::Camera& Camera ) = 0;
		virtual void Rendering( Sint32 VertexStart, Sint32 VertexCount, Sint32 IndexStart, Sint32 IndexCount ) = 0;
		virtual Uint32 GetParticleSortKey() = 0;

		virtual void FlipMatrix() = 0;
		virtual const Kernel::Math::VectorS& GetModelCenter() const = 0;
		virtual const Kernel::Math::Matrix& GetWorldMatrix() const = 0;
		virtual const Kernel::Math::Matrix& GetWorldMatrixPrev() const = 0;
		virtual const Kernel::Math::Matrix* GetBoneMatrixTable() const = 0;
		virtual const Kernel::Math::Matrix* GetBoneMatrixTablePrev() const = 0;

		virtual Sint32 GetWeightCount() const = 0;
		virtual Sint32 GetBoneCount() const = 0;

		virtual IMaterial* GetMaterial( Sint32 Index ) = 0;
		virtual Sint32 GetMaterialCount() const = 0;

		virtual void SetUserData( Kernel::Object::ReferenceObject* pUserData ) = 0;
		virtual Kernel::Object::ReferenceObject* GetUserData() = 0;

		virtual eDrawObjectType GetDrawObjectType() const = 0;
		virtual bool IsDrawEnable() const = 0;
		virtual bool IsDisableBankParticle() const = 0;
		virtual bool ViewFrustumCulling( const Kernel::Math::Camera& Camera ) const = 0;

		virtual void DebugDraw_ViewBounding( Engine::Graphics::Simple::ILineRenderer* pRenderer ) = 0;
	};
}
}
}
}

/**
	@file
	@brief ローカルリソースインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief ローカルリソース
		@author 葉迩倭
	*/
	class ILocalResource
		: public Interface
	{
	protected:
		virtual ~ILocalResource(){}

	public:
		/**
			@brief ローカルリソースの取得
			@author 葉迩倭
			@param Index	[in] リソースインデックス
			@param pData	[out] データのポインタ
			@param Size		[out] データサイズ
			@retval true	成功
			@retval false	失敗
			@note
			リソース内のローカルなリソースの取得を行います。
		*/
		virtual bool Get( Uint32 Index, const void*& pData, Uint32& Size ) = 0;
	};
}
}
}
}

/**
	@file
	@brief マテリアルインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	static const Sint32 MATERIAL_USERDATA_MAX	= 8;
	static const Sint32 MATERIAL_SHADER_MAX		= 8;

	class IMaterialPlugin
		: public Kernel::Object::ReferenceObject
	{
	protected:
		virtual ~IMaterialPlugin() {}

	public:
		virtual const char* GetPluginName() const = 0;
		virtual bool IsLightEnable() const = 0;
		virtual void SetLightEnable( bool IsEnable ) = 0;
		virtual Resource::ITexture* GetTexture( Sint32 Index ) = 0;
		virtual void SetTexture( Sint32 Index, Resource::ITexture* pTex ) = 0;
	};

	class IMaterialListener
		: public Interface
		, public Kernel::Object::ReferenceObject
	{
	protected:
		virtual ~IMaterialListener(){}

	public:
		virtual void OnLoadFromFile( IMaterial* pMaterialInterface, const void* pMaterialData, Sint32 MaterialSize, ILocalResource* pLocalResource ) = 0;
		virtual Engine::Graphics::Resource::IMaterialPlugin* CloneMaterialPluginData( const Engine::Graphics::Resource::IMaterialPlugin* pOriginal ) = 0;

	public:
		virtual Sint32 Release() { return Kernel::Object::ReferenceObject::Release(); }
		virtual Sint32 AddRef()  { return Kernel::Object::ReferenceObject::AddRef(); }
		virtual Sint32 GetReferenceCount() { return Kernel::Object::ReferenceObject::GetReferenceCount(); }
	};

	class IMaterial
		: public Interface
	{
	protected:
		virtual ~IMaterial(){}

	public:
		virtual State::IRenderState* GetRenderState() = 0;

		virtual void* GetUserData( Uint32 Index ) = 0;
		virtual void SetUserData( Uint32 Index, void* pData ) = 0;

		virtual Resource::IVertexShader* GetVertexShader( Uint32 Index ) = 0;
		virtual void SetVertexShader( Uint32 Index, Resource::IVertexShader* pShader ) = 0;

		virtual Resource::IPixelShader* GetPixelShader( Uint32 Index ) = 0;
		virtual void SetPixelShader( Uint32 Index, Resource::IPixelShader* pShader ) = 0;

		virtual bool GetVisible() = 0;
		virtual void SetVisible( bool IsVisible ) = 0;

		virtual IMaterialPlugin* GetMaterialPluginData() = 0;
		virtual void SetMaterialPluginData( IMaterialPlugin* pMaterialPlugin ) = 0;

		virtual IMaterialListener* GetMaterialListener() = 0;
		virtual void SetMaterialListener( IMaterialListener* pMaterialListener ) = 0;

		virtual IRenderTable* GetRenderTable( Sint32 Index ) = 0;
		virtual Sint32 GetRenderTableCount() const = 0;

		virtual void SetType( Sint32 Type ) = 0;
		virtual Sint32 GetType() const = 0;

		virtual bool IsCullEnable() const = 0;
		virtual void SetCullEnable( bool Enable ) = 0;

		virtual bool IsZWriteEnable() const = 0;
		virtual void SetZWriteEnable( bool Enable ) = 0;

		virtual bool IsZTestEnable() const = 0;
		virtual void SetZTestEnable( bool Enable ) = 0;

		virtual State::eAlphaBlend GetAlphaBlend() const = 0;
		virtual void SetAlphaBlend( State::eAlphaBlend Type ) = 0;

		virtual State::ePolygonFill GetPolygonFill() const = 0;
		virtual void SetPolygonFill( State::ePolygonFill Fill ) = 0;
	};
}
}
}
}

/**
	@file
	@brief ノードインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief ノード
		@author 葉迩倭
	*/
	class INode
		: public Interface
	{
	protected:
		virtual ~INode(){}

	public:
		/**
			@brief ローカル行列設定
			@author 葉迩倭
			@param mIn	[in] ローカル行列
			@note
			ノードのローカル行列を設定します。
		*/
		virtual void SetLocalMatrix( const Kernel::Math::Matrix& mIn ) = 0;
		/**
			@brief ローカル行列取得
			@author 葉迩倭
			@return ローカル行列
			@note
			ノードのローカル行列を取得します。
		*/
		virtual const Kernel::Math::Matrix& GetLocalMatrix() = 0;

		/**
			@brief ワールド行列設定
			@author 葉迩倭
			@param mIn				[in] ワールド行列
			@param HierarchyLevel	[in] ヒエラルキーの更新レベル（指定した階層分ヒエラルキーの更新をします）
			@note
			ノードのワールド行列を設定します。
		*/
		virtual void SetWorldMatrix( const Kernel::Math::Matrix& mIn, Uint32 HierarchyLevel = 0xFFFFFFFF ) = 0;
		/**
			@brief ワールド行列取得
			@author 葉迩倭
			@return ワールド行列
			@note
			ノードのワールド行列を取得します。
		*/
		virtual const Kernel::Math::Matrix& GetWorldMatrix() = 0;

		/**
			@brief 親のノード番号取得
			@author 葉迩倭
			@return 親のノード番号
			@note
			ノードの親のノードの番号を取得します。
		*/
		virtual Sint32 GetParentNodeNo() = 0;

		/**
			@brief ノードの描画有無を取得
			@author 葉迩倭
			@retval true	描画する
			@retval false	描画しない
			@note
			ノードの描画の有無を取得します。
		*/
		virtual bool GetVisible() = 0;
		/**
			@brief ノードの描画有無を設定
			@author 葉迩倭
			@param IsVisible	[in] 描画するかどうか
			@note
			ノードの描画の有無を設定します。
		*/
		virtual void SetVisible( bool IsVisible ) = 0;

		virtual const char* GetName() = 0;
	};
}
}
}
}
}

/**
	@file
	@brief コンストレイントインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief コンストレイント
		@author 葉迩倭
	*/
	class IConstraint
		: public Interface
	{
	protected:
		virtual ~IConstraint(){}

	public:
		/**
			@brief ローカル行列取得
			@author 葉迩倭
			@return ローカル行列
			@note
			コンストレイントのローカル行列を取得します。
		*/
		virtual Kernel::Math::Matrix GetLocalMatrix() = 0;
		/**
			@brief ワールド行列取得
			@author 葉迩倭
			@return ワールド行列
			@note
			コンストレイントのワールド行列を取得します。
		*/
		virtual Kernel::Math::Matrix GetWorldMatrix() = 0;
	};
}
}
}
}
}

/**
	@file
	@brief モーションスケジューラーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief モーションスケジューラーコントローラー
		@author 葉迩倭
	*/
	class IMotionScheduler
		: public Interface
	{
	public:
		typedef Uint64								MOTION_HANDLE;
		typedef Kernel::Delegate01<MOTION_HANDLE>	ExitEvent;

	protected:
		virtual ~IMotionScheduler(){}

	public:
		/**
			@brief 再生開始
			@author 葉迩倭
			@param pMC			[in] モーションコントローラー
			@param BlendTime	[in] ブレンド時間
			@return モーションハンドル
			@note
			モーションの再生を開始します。
		*/
		virtual MOTION_HANDLE Play( IMotionController* pMC, Sint32 BlendTime ) = 0;
		/**
			@brief 終了時コールバックイベント設定
			@author 葉迩倭
			@param Handle	[in] モーションハンドル
			@param Event	[in] イベント
			@note
			モーションの終了時のコールバックイベントを設定します。
		*/
		virtual void SetExitCallbackEvent( MOTION_HANDLE Handle, const ExitEvent& Event ) = 0;
		/**
			@brief モーション停止
			@author 葉迩倭
			@param Handle	[in] モーションハンドル
			@note
			モーションの再生を停止します。
		*/
		virtual void Stop( MOTION_HANDLE Handle ) = 0;
		/**
			@brief モーション遅延停止
			@author 葉迩倭
			@param Handle	[in] モーションハンドル
			@param Frame	[in] 削除するまでのフレーム
			@note
			モーションの再生を遅延停止します。
		*/
		virtual void DelayStop( MOTION_HANDLE Handle, Uint32 Frame ) = 0;
		/**
			@brief モーションブレンド率設定
			@author 葉迩倭
			@param Handle		[in] モーションハンドル
			@param BlendRate	[in] ブレンド率
			@note
			モーションのブレンド率を設定します。
		*/
		virtual void SetBlendRate( MOTION_HANDLE Handle, float BlendRate ) = 0;
		/**
			@brief モーションプライオリティ設定
			@author 葉迩倭
			@param Handle	[in] モーションハンドル
			@param Priority	[in] プライオリティ
			@note
			モーションの再生プライオリティを設定します。
		*/
		virtual void SetPriority( MOTION_HANDLE Handle, Uint8 Priority ) = 0;
		/**
			@brief モーション再生速度設定
			@author 葉迩倭
			@param Handle	[in] モーションハンドル
			@param Speed	[in] 再生速度
			@note
			モーションの再生速度を設定します。
		*/
		virtual void SetSpeed( MOTION_HANDLE Handle, float Speed ) = 0;
		/**
			@brief モーション終了チェック
			@author 葉迩倭
			@param Handle	[in] モーションハンドル
			@retval true	再生中
			@retval false	停止中
			@note
			モーションが再生中かどうかを取得します。
		*/
		virtual bool IsEnd( MOTION_HANDLE Handle ) = 0;

		virtual float GetFrame( MOTION_HANDLE Handle ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief モーションコントローラーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief モーションコントローラー
		@author 葉迩倭
	*/
	class IMotionController
		: public Interface
	{
	protected:
		virtual ~IMotionController(){}

	public:
		/**
			@brief フレームレート設定
			@author 葉迩倭
			@param FrameRate	[in] モーションのフレームレート
			@note
			モーションのフレームレートを設定します。
		*/
		virtual void SetFrameRate( Sint32 FrameRate ) = 0;

		/**
			@brief 更新
			@author 葉迩倭
			@note
			モーションを１フレーム分進めます。
		*/
		virtual void Update() = 0;

		/**
			@brief 長さ設定
			@author 葉迩倭
			@param Length	[in] モーションの長さ（フレーム数）
			@note
			モーションの長さを取得します。
		*/
		virtual void SetLength( Sint32 Length ) = 0;

		/**
			@brief 長さ取得
			@author 葉迩倭
			@return モーションの長さ（フレーム数）
			@note
			モーションの長さを取得します。
		*/
		virtual float GetLength() const = 0;

		/**
			@brief ループ設定
			@author 葉迩倭
			@param IsLoop	[in] ループの有無
			@note
			モーションのループの有無を設定します。
		*/
		virtual void SetLoop( bool IsLoop ) = 0;
		/**
			@brief ループ有無取得
			@author 葉迩倭
			@retval true	ループあり
			@retval false	ループなし
			@note
			モーションのループの有無を取得します。
		*/
		virtual bool GetLoop() const = 0;

		/**
			@brief ループ開始フレーム設定
			@author 少佐
			@param Frame	[in] フレーム
			@note
			ループを開始するときのフレームを設定します。
		*/
		virtual void SetLoopStartFrame( float Frame ) = 0;

		/**
			@brief ループ開始フレーム取得
			@author 少佐
			@return フレーム
			@note
			ループを開始するときのフレームを取得します。
		*/
		virtual float GetLoopStartFrame() const = 0;

		/**
			@brief 速度設定
			@author 葉迩倭
			@param Speed	[in] 速度の有無
			@note
			モーションの速度の有無を設定します。
		*/
		virtual void SetSpeed( float Speed ) = 0;
		/**
			@brief 速度有無取得
			@author 葉迩倭
			@return 速度
			@note
			モーションの速度の有無を取得します。
		*/
		virtual float GetSpeed() const = 0;

		/**
			@brief フレーム設定
			@author 葉迩倭
			@param Frame	[in] フレーム
			@note
			モーションのフレームの有無を設定します。
		*/
		virtual void SetFrame( float Frame ) = 0;
		/**
			@brief フレーム有無取得
			@author 葉迩倭
			@return フレーム数
			@note
			モーションのフレームの有無を取得します。
		*/
		virtual float GetFrame() const = 0;

		/**
			@brief 優先度設定
			@author 葉迩倭
			@param Priority	[in] 優先度
			@note
			モーションの優先度の有無を設定します。
		*/
		virtual void SetPriority( Uint8 Priority ) = 0;
		/**
			@brief 優先度有無取得
			@author 葉迩倭
			@return 優先度
			@note
			モーションの優先度の有無を取得します。
		*/
		virtual Uint8 GetPriority() const = 0;

		/**
			@brief モーション数取得
			@author 葉迩倭
			@return モーションインターフェイス数
			@note
			モーションコントローラーに含まれるモーション数を取得します。
		*/
		virtual Sint32 GetMotionCount() const = 0;
		/**
			@brief モーション取得
			@author 葉迩倭
			@param Index	[in] モーションのインデックス
			@return モーションインターフェイス
			@note
			モーションコントローラーに含まれるモーションを取得します。
		*/
		virtual IMotion* GetMotion( Sint32 Index ) = 0;
		/**
			@brief モーション取得
			@author 葉迩倭
			@param NodeId	[in] モーションのノードインデックス
			@return モーションインターフェイス
			@note
			モーションコントローラーに含まれるモーションを取得します。
		*/
		virtual IMotion* GetMotionByNodeId( Sint32 NodeId ) = 0;
		/**
			@brief モーション取得
			@author 葉迩倭
			@param pNodeName	[in] モーションのノード名
			@return モーションインターフェイス
			@note
			モーションコントローラーに含まれるモーションを取得します。
		*/
		virtual IMotion* GetMotionByNodeName( const char* pNodeName ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief モーションインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief モーションインターフェイス
		@author 葉迩倭
	*/
	class IMotion
		: public Interface
	{
	protected:
		virtual ~IMotion(){}

	public:
		/**
			@brief 拡大縮小キーを取得
			@author 葉迩倭
			@return 値
			@note
			モーションから拡大縮小キーを取得します。
		*/
		virtual const Kernel::Math::VectorS& GetScaling() const = 0;
		/**
			@brief 回転キーを取得
			@author 葉迩倭
			@return 値
			@note
			モーションから回転キーを取得します。
		*/
		virtual const Kernel::Math::Quaternion& GetRotation() const = 0;
		/**
			@brief 位置キーを取得
			@author 葉迩倭
			@return 値
			@note
			モーションから位置キーを取得します。
		*/
		virtual const Kernel::Math::VectorS& GetPosition() const = 0;

		/**
			@brief 長さ取得
			@author 葉迩倭
			@return モーションの長さ（フレーム数）
			@note
			モーションの長さを取得します。
		*/
		virtual float GetLength() const = 0;

		/**
			@brief フレームレート設定
			@author 葉迩倭
			@param FrameRate	[in] フレームレート
			@note
			モーションのフレームレートを設定します。
		*/
		virtual void SetFrameRate( Sint32 FrameRate ) = 0;

		/**
			@brief モーションの更新
			@author 葉迩倭
			@note
			モーションを１フレーム進めます。
		*/
		virtual void Update() = 0;

		/**
			@brief ループ設定
			@author 葉迩倭
			@param IsLoop	[in] ループの有無
			@note
			モーションのループの有無を設定します。
		*/
		virtual void SetLoop( bool IsLoop ) = 0;
		/**
			@brief ループ有無取得
			@author 葉迩倭
			@retval true	ループあり
			@retval false	ループなし
			@note
			モーションのループの有無を取得します。
		*/
		virtual bool GetLoop() const = 0;

		/**
			@brief 速度設定
			@author 葉迩倭
			@param Speed	[in] 速度の有無
			@note
			モーションの速度の有無を設定します。
		*/
		virtual void SetSpeed( float Speed ) = 0;
		/**
			@brief 速度有無取得
			@author 葉迩倭
			@return 速度
			@note
			モーションの速度の有無を取得します。
		*/
		virtual float GetSpeed() const = 0;

		/**
			@brief フレーム設定
			@author 葉迩倭
			@param Frame	[in] フレーム
			@note
			モーションのフレームの有無を設定します。
		*/
		virtual void SetFrame( float Frame ) = 0;
		/**
			@brief フレーム有無取得
			@author 葉迩倭
			@return フレーム数
			@note
			モーションのフレームの有無を取得します。
		*/
		virtual float GetFrame() const = 0;

		/**
			@brief 優先度設定
			@author 葉迩倭
			@param Priority	[in] 優先度
			@note
			モーションの優先度の有無を設定します。
		*/
		virtual void SetPriority( Uint8 Priority ) = 0;
		/**
			@brief 優先度有無取得
			@author 葉迩倭
			@return 優先度
			@note
			モーションの優先度の有無を取得します。
		*/
		virtual Uint8 GetPriority() const = 0;

		/**
			@brief ノードインデックス取得
			@author 葉迩倭
			@return ノードのインデックス
			@note
			モーションの対象のモデルのノードのインデックスを取得します。
		*/
		virtual Sint32 GetNodeIndex() const = 0;

		/**
			@brief ノード名取得
			@author 葉迩倭
			@return ノード名
			@note
			モーションの対象のモデルのノード名を取得します。
		*/
		virtual const char* GetNodeName() const = 0;
	};
}
}
}
}
}

/**
	@file
	@brief モデルコントローラーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief モデルコントローラー
		@author 葉迩倭
	*/
	class IModelController
		: public Interface
	{
	protected:
		virtual ~IModelController(){}

	public:
		/**
			@brief アクティブの設定
			@author 葉迩倭
			@param IsActive	[in] アクティブかどうか
			@note
			モデルのアクティブ状態を設定します。<BR>
			非アクティブになると描画されません。
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief ワールド行列設定
			@author 葉迩倭
			@param mIn	[in] ワールド行列
			@note
			モデルのワールド行列を設定します。
		*/
		virtual void SetWorldMatrix( const Kernel::Math::Matrix& mIn ) = 0;

		/**
			@brief 描画オブジェクト数取得
			@author 葉迩倭
			@return 描画オブジェクト数
			@note
			インターフェイスに含まれる描画オブジェクトの数を取得します。
		*/
		virtual Sint32 GetDrawObjectCount() = 0;
		/**
			@brief 描画オブジェクト取得
			@author 葉迩倭
			@param Index	[in] 描画オブジェクトのインデックス
			@return 描画オブジェクト
			@note
			インターフェイスに含まれる描画オブジェトを取得します。
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;

		/**
			@brief スケジューラーの更新
			@author 葉迩倭
			@param StepTime	[in] 進行時間
			@note
			モデルに関連付けられているスケジュラーを更新します。<BR>
			これにはモーション等が含まれます。
		*/
		virtual void UpdateScheduler( float StepTime = 1.0f ) = 0;
		/**
			@brief スケルトンの更新
			@author 葉迩倭
			@note
			モデルのスケルトンを更新します。<BR>
			同時に階層構造の更新もおこなわれます。
		*/
		virtual void UpdateSkelton() = 0;

		/**
			@brief モーション登録
			@author 葉迩倭
			@param pMotonGroup	[in] 所属するモーショングループ名
			@param pData		[in] モーションデータのポインタ
			@param Size			[in] モーションデータのサイズ
			@note
			モデルにモーションを登録します。
		*/
		virtual void RegistMotion( const char* pMotonGroup, const void* pData, Sint32 Size ) = 0;
		/**
			@brief モーション削除
			@author 葉迩倭
			@param pMotonGroup	[in] 削除モーショングループ名
			@note
			モデルに登録されているモーションをモーショングループ単位で削除します。
		*/
		virtual void UnRegistMotion( const char* pMotonGroup ) = 0;
		/**
			@brief 全モーション削除
			@author 葉迩倭
			@note
			全てのモーションを削除します。
		*/
		virtual void UnRegistAllMotion() = 0;

		/**
			@brief モーションコントローラー取得
			@author 葉迩倭
			@param pName	[in] モーションコントローラー名
			@note
			モデル内のモーションコントローラーを取得します。
		*/
		virtual IMotionController* GetMotionController( const char* pName ) = 0;
		/**
			@brief モーションスケジューラー取得
			@author 葉迩倭
			@note
			モデル内のモーションスケジューラーを取得します。
		*/
		virtual IMotionScheduler* GetMotionScheduler() = 0;
		/**
			@brief コンストレイント取得
			@author 葉迩倭
			@param pName	[in] コンストレイント名
			@note
			モデル内のコンストレイントを取得します。
		*/
		virtual IConstraint* GetConstraint( const char* pName ) = 0;
		/**
			@brief コンストレイント数取得
			@author 葉迩倭
			@return コンストレイント数
			@note
			モデル内のコンストレイント数を取得します。
		*/
		virtual Uint32 GetConstraintCount() = 0;
		/**
			@brief コンストレイント名取得
			@author 葉迩倭
			@param Index	[in] コンストレイントのインデックス
			@param pName	[out] コンストレイント名
			@param NameSize	[in] pNameのバッファサイズ
			@note
			モデル内のコンストレイント名を取得します。
		*/
		virtual void GetConstraintName( Uint32 Index, char* pName, Uint32 NameSize ) = 0;
		/**
			@brief ノード取得
			@author 葉迩倭
			@param pName	[in] ノード名
			@note
			モデル内のノードを取得します。
		*/
		virtual INode* GetNode( const char* pName ) = 0;
		/**
			@brief ノード数取得
			@author 葉迩倭
			@note
			モデル内のノード数を取得します。
		*/
		virtual Uint32 GetNodeCount() = 0;
		/**
			@brief ノード取得
			@author 葉迩倭
			@param Index	[in] ノードのインデックス
			@note
			モデル内のノードを取得します。
		*/
		virtual INode* GetNode( Uint32 Index ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief モデルインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief モデル
		@author 葉迩倭
	*/
	class IModel
		: public Interface
	{
	protected:
		virtual ~IModel(){}

	public:
		/**
			@brief モデルコントローラーの生成
			@author 葉迩倭
			@return モデルコントローラー
			@note
			モデルの操作用コントローラーを生成します。
		*/
		virtual IModelController* CreateController() = 0;
	};
}
}
}
}
}

/**
	@file
	@brief モデルコントローラーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace STM
{
	/**
		@brief モデルコントローラー
		@author 葉迩倭
	*/
	class IModelController
		: public Interface
	{
	protected:
		virtual ~IModelController(){}

	public:
		/**
			@brief アクティブの設定
			@author 葉迩倭
			@param IsActive	[in] アクティブかどうか
			@note
			モデルのアクティブ状態を設定します。<BR>
			非アクティブになると描画されません。
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief 描画セル数取得
			@author 葉迩倭
			@return 描画セル数
			@note
			カリング後に実際に描画されるセルの数を取得します。
		*/
		virtual Sint32 GetDrawCellCount() = 0;
		/**
			@brief 描画オブジェクト数取得
			@author 葉迩倭
			@return 描画オブジェクト数
			@note
			インターフェイスに含まれる描画オブジェクトの数を取得します。
		*/
		virtual Sint32 GetDrawObjectCount() = 0;
		/**
			@brief 描画オブジェクト取得
			@author 葉迩倭
			@param Index	[in] 描画オブジェクトのインデックス
			@return 描画オブジェクト
			@note
			インターフェイスに含まれる描画オブジェトを取得します。
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;
		/**
			@brief ビューフラスタムカリング
			@author 葉迩倭
			@param Camera	[in] カリングを行うカメラ
			@note
			STMモデル全体に対してビューフラスタムカリングを行います。
		*/
		virtual void UpdateViewFrustumCulling( const Kernel::Math::Camera& Camera ) = 0;
		/**
			@brief コリジョン用メッシュ数の取得
			@author 葉迩倭
			@return コリジョン用メッシュ数
			@note
		*/
		virtual Uint32 GetCollisionMeshCount() const = 0;
		/**
			@brief コリジョン用メッシュのアトリビュート取得
			@author 葉迩倭
			@param Index	[in] コリジョン用メッシュのインデックス
			@return コリジョン用メッシュのアトリビュート
			@note
			コリジョン用メッシュのアトリビュートを取得します。
		*/
		virtual Uint32 GetCollisionAttribute( Uint32 Index ) const = 0;
		/**
			@brief コリジョン用メッシュの頂点数取得
			@author 葉迩倭
			@param Index	[in] コリジョン用メッシュのインデックス
			@return コリジョン用メッシュの頂点数
			@note
			コリジョン用メッシュの頂点数を取得します。
		*/
		virtual Uint32 GetCollisionMeshVertexCount( Uint32 Index ) const = 0;
		/**
			@brief コリジョン用メッシュの頂点インデックス数取得
			@author 葉迩倭
			@param Index	[in] コリジョン用メッシュのインデックス
			@return コリジョン用メッシュの頂点インデックス数
			@note
			コリジョン用メッシュの頂点インデックス数を取得します。
		*/
		virtual Uint32 GetCollisionMeshIndexCount( Uint32 Index ) const = 0;
		/**
			@brief コリジョン用メッシュの頂点取得
			@author 葉迩倭
			@param Index	[in] コリジョン用メッシュのインデックス
			@return コリジョン用メッシュの頂点
			@note
			コリジョン用メッシュの頂点を取得します。
		*/
		virtual const Kernel::Math::Vector3* GetCollisionMeshVertex( Uint32 Index ) const = 0;
		/**
			@brief コリジョン用メッシュの頂点インデックス取得
			@author 葉迩倭
			@param Index	[in] コリジョン用メッシュのインデックス
			@return コリジョン用メッシュの頂点インデックス
			@note
			コリジョン用メッシュの頂点インデックスを取得します。
		*/
		virtual const Uint32* GetCollisionMeshIndex( Uint32 Index ) const = 0;
	};
}
}
}
}
}

/**
	@file
	@brief パーティクルコントローラーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Particle
{
	/**
		@brief パーティクル用パラメーター
		@author 葉迩倭
	*/
	struct SParameter
	{
		State::IRenderState*	pRenderState;		///< ステート
		IMaterialPlugin*		pMaterialData;		///< 利用するマテリアルプラグインデータ
		Uint32					SortKey;			///< 描画優先度
		bool					IsSortEnable;		///< パーティクルのソートの有無
		bool					IsBankDisable;		///< パーティクルのバンク回転を封じる

		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param pState		[in] 描画に利用するステート（必須）
			@param pMaterial	[in] 描画に利用するマテリアル（必須）
			@param IsSort		[in] パーティクルのソートの有無
		*/
		SParameter( State::IRenderState* pState, IMaterialPlugin* pMaterial, bool IsSort )
			: pRenderState		( pState )
			, pMaterialData		( pMaterial )
			, SortKey			( 0 )
			, IsSortEnable		( IsSort )
			, IsBankDisable		( false )
		{
			SAFE_ADDREF( pRenderState )
			SAFE_ADDREF( pMaterialData )
		}
		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		~SParameter()
		{
			SAFE_RELEASE( pRenderState )
			SAFE_RELEASE( pMaterialData )
		}
	};
}
}
}
}
}

/**
	@file
	@brief パーティクルコントローラーインターフェイス
	@author 葉迩倭
*/

/**
	@file
	@brief パーティクルコントローラーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Particle
{
	/**
		@brief パーティクルコントローラー
		@author 葉迩倭
	*/
	class IParticleController
		: public Interface
	{
	protected:
		virtual ~IParticleController(){}

	public:
		/**
			@brief アクティブの設定
			@author 葉迩倭
			@param IsActive	[in] アクティブかどうか
			@note
			モデルのアクティブ状態を設定します。<BR>
			非アクティブになると描画されません。
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief 描画オブジェクト数取得
			@author 葉迩倭
			@return 描画オブジェクト数
			@note
			インターフェイスに含まれる描画オブジェクトの数を取得します。
		*/
		virtual Sint32 GetDrawObjectCount() const = 0;
		/**
			@brief 描画オブジェクト取得
			@author 葉迩倭
			@param Index	[in] 描画オブジェクトのインデックス
			@return 描画オブジェクト
			@note
			インターフェイスに含まれる描画オブジェトを取得します。
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;
		/**
			@brief 生成開始
			@author 葉迩倭
			@note
			パーティクルの生成処理を開始します。
		*/
		virtual void Begin() = 0;
		/**
			@brief 生成終了
			@author 葉迩倭
			@note
			パーティクルの生成処理を終了します。
		*/
		virtual void End() = 0;
		/**
			@brief 描画ページのフリップ
			@author 葉迩倭
			@note
			フレームの最後で呼び出してください。
		*/
		virtual void FlipPage() = 0;
		/**
			@brief パーティクル生成
			@author 葉迩倭
			@param Position		[in] 位置
			@param Size			[in] サイズ
			@param Color		[in] 色
			@param Texture		[in] テクスチャ矩形
			@param Radian		[in] 回転角度
			@note
			パーティクルの生成を行います。<BR>
			１矩形単位でBegin/End間に追加してください。
		*/
		virtual void DrawRequest( const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2& Size, const ColorF& Color, const RectF& Texture, float Radian ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief パーティクルコントローラーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Particle
{
	/**
		@brief パーティクルコントローラー
		@author 葉迩倭
	*/
	class IVolumeParticleController
		: public Interface
	{
	protected:
		virtual ~IVolumeParticleController(){}

	public:
		/**
			@brief アクティブの設定
			@author 葉迩倭
			@param IsActive	[in] アクティブかどうか
			@note
			モデルのアクティブ状態を設定します。<BR>
			非アクティブになると描画されません。
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief 描画オブジェクト数取得
			@author 葉迩倭
			@return 描画オブジェクト数
			@note
			インターフェイスに含まれる描画オブジェクトの数を取得します。
		*/
		virtual Sint32 GetDrawObjectCount() const = 0;
		/**
			@brief 描画オブジェクト取得
			@author 葉迩倭
			@param Index	[in] 描画オブジェクトのインデックス
			@return 描画オブジェクト
			@note
			インターフェイスに含まれる描画オブジェトを取得します。
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;
		/**
			@brief 生成開始
			@author 葉迩倭
			@note
			パーティクルの生成処理を開始します。
		*/
		virtual void Begin() = 0;
		/**
			@brief 生成終了
			@author 葉迩倭
			@note
			パーティクルの生成処理を終了します。
		*/
		virtual void End() = 0;
		/**
			@brief 描画ページのフリップ
			@author 葉迩倭
			@note
			フレームの最後で呼び出してください。
		*/
		virtual void FlipPage() = 0;
		/**
			@brief パーティクル生成
			@author 葉迩倭
			@param Position		[in] 位置
			@param Size			[in] サイズ
			@param Color		[in] 色
			@param Texture		[in] テクスチャ矩形
			@param Radian		[in] 回転角度
			@param BasePosition	[in] 基準位置（この位置にポイントライトが置かれる形でライティングされます）
			@note
			パーティクルの生成を行います。<BR>
			１矩形単位でBegin/End間に追加してください。
		*/
		virtual void DrawRequest( const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2& Size, const ColorF& Color, const RectF& Texture, float Radian, const Kernel::Math::VectorS& BasePosition ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief パーティクルコントローラーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Particle
{
	/**
		@brief パーティクルコントローラー
		@author 葉迩倭
	*/
	class IEnhancedParticleController
		: public Interface
	{
	protected:
		virtual ~IEnhancedParticleController(){}

	public:
		/**
			@brief アクティブの設定
			@author 葉迩倭
			@param IsActive	[in] アクティブかどうか
			@note
			モデルのアクティブ状態を設定します。<BR>
			非アクティブになると描画されません。
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief 描画オブジェクト数取得
			@author 葉迩倭
			@return 描画オブジェクト数
			@note
			インターフェイスに含まれる描画オブジェクトの数を取得します。
		*/
		virtual Sint32 GetDrawObjectCount() const = 0;
		/**
			@brief 描画オブジェクト取得
			@author 葉迩倭
			@param Index	[in] 描画オブジェクトのインデックス
			@return 描画オブジェクト
			@note
			インターフェイスに含まれる描画オブジェトを取得します。
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;
		/**
			@brief 生成開始
			@author 葉迩倭
			@note
			パーティクルの生成処理を開始します。
		*/
		virtual void Begin() = 0;
		/**
			@brief 生成終了
			@author 葉迩倭
			@note
			パーティクルの生成処理を終了します。
		*/
		virtual void End() = 0;
		/**
			@brief 描画ページのフリップ
			@author 葉迩倭
			@note
			フレームの最後で呼び出してください。
		*/
		virtual void FlipPage() = 0;
		/**
			@brief パーティクル生成
			@author 葉迩倭
			@param Position		[in] 位置
			@param Size			[in] サイズ
			@param Color		[in] 色
			@param Texture		[in] テクスチャ矩形
			@param Radian		[in] 回転角度
			@param AlphaBlend	[in] アルファブレンド指定
			@note
			パーティクルの生成を行います。<BR>
			１矩形単位でBegin/End間に追加してください。
		*/
		virtual void DrawRequest( const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2& Size, const ColorF& Color, const RectF& Texture, float Radian, State::eAlphaBlend AlphaBlend ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief プリミティブコントローラーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Primitive
{
	/**
		@brief プリミティブ用パラメーター
		@author 葉迩倭
	*/
	struct SParameter
	{
		State::IRenderState*	pRenderState;		///< ステート
		IMaterialPlugin*		pMaterialData;		///< 利用するマテリアルプラグインデータ
		Sint32					BoneWeightCount;	///< ボーンの１頂点あたりのウェイト数（最大４）
		Sint32					BoneCount;			///< ボーンの本数（最大４０）
		bool					IsDynamic;			///< 動的バッファのON/OFF（毎フレーム以上書き換える場合はONに）
		bool					IsWireFrame;		///< ワイヤーフレーム描画

		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param pState		[in] 描画に利用するステート（必須）
			@param pMaterial	[in] 描画に利用するマテリアル（必須）
		*/
		SParameter( State::IRenderState* pState, IMaterialPlugin* pMaterial )
			: pRenderState		( pState )
			, pMaterialData		( pMaterial )
			, BoneWeightCount	( 0 )
			, BoneCount			( 0 )
			, IsDynamic			( false )
			, IsWireFrame		( false )
		{
			SAFE_ADDREF( pRenderState )
			SAFE_ADDREF( pMaterialData )
		}
		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		~SParameter()
		{
			SAFE_RELEASE( pRenderState )
			SAFE_RELEASE( pMaterialData )
		}
	};

	/**
		@brief プリミティブ用頂点データ
		@author 葉迩倭
	*/
	struct SVertex
	{
		Kernel::Math::Vector3	Position;	///< 位置
		Kernel::Math::Vector3	Normal;		///< 法線
		Uint32					Color;		///< 色
		Kernel::Math::Vector2	Texture;	///< テクスチャUV
		union {
			Uint32 Weight;					///< 頂点ウェイト
			Uint8 Weights[4];				///< 頂点ウェイト
		};
		union {
			Uint32 Index;					///< 頂点スキニング用インデックス
			Uint8 Indexs[4];				///< 頂点スキニング用インデックス
		};
	};

	/**
		@brief プリミティブコントローラー
		@author 葉迩倭
	*/
	class IPrimitiveController
		: public Interface
	{
	protected:
		virtual ~IPrimitiveController(){}

	public:
		/**
			@brief アクティブの設定
			@author 葉迩倭
			@param IsActive	[in] アクティブかどうか
			@note
			モデルのアクティブ状態を設定します。<BR>
			非アクティブになると描画されません。
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief ワールド行列設定
			@author 葉迩倭
			@param mIn	[in] ワールド行列
			@note
			プリミティブのワールド行列を設定します。
		*/
		virtual void SetWorldMatrix( const Kernel::Math::Matrix& mIn ) = 0;

		/**
			@brief ボーン用行列設定
			@author 葉迩倭
			@param pMatrix	[in] 行列テーブル
			@param Count	[in] 行列数
			@note
			ボーンスキニング用の行列を設定します。
		*/
		virtual void SetBoneMatrix( const Kernel::Math::Matrix* pMatrix, Sint32 Count ) = 0;

		/**
			@brief ボーン用行列設定
			@author 葉迩倭
			@param Matrix	[in] 行列テーブル
			@param Index	[in] 行列数
			@note
			ボーンスキニング用の行列を設定します。
		*/
		virtual void SetBoneMatrix( const Kernel::Math::Matrix& Matrix, Sint32 Index ) = 0;

		/**
			@brief 描画オブジェクト数取得
			@author 葉迩倭
			@return 描画オブジェクト数
			@note
			インターフェイスに含まれる描画オブジェクトの数を取得します。
		*/
		virtual Sint32 GetDrawObjectCount() const = 0;
		/**
			@brief 描画オブジェクト取得
			@author 葉迩倭
			@param Index	[in] 描画オブジェクトのインデックス
			@return 描画オブジェクト
			@note
			インターフェイスに含まれる描画オブジェトを取得します。
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;

		/**
			@brief 生成開始
			@author 葉迩倭
			@note
			データの生成開始する事を通知します。
		*/
		virtual void Begin() = 0;
		/**
			@brief 生成終了
			@author 葉迩倭
			@note
			データの生成終了した事を通知します。
		*/
		virtual void End() = 0;
		/**
			@brief 描画ページのフリップ
			@author 葉迩倭
			@note
			フレームの最後で呼び出してください。
		*/
		virtual void FlipPage() = 0;
		/**
			@brief 頂点データ設定
			@author 葉迩倭
			@param pVertex	[in] 頂点データ
			@param Count	[in] 頂点数
			@note
			頂点データを設定します。<BR>
			既に生成されているものに対して追加になります。
		*/
		virtual void SetVertex( const SVertex* pVertex, Sint32 Count ) = 0;
		/**
			@brief 頂点インデックスデータ設定
			@author 葉迩倭
			@param pIndex	[in] 頂点インデックスデータ
			@param Count	[in] 頂点インデックス数
			@note
			頂点インデックスデータを設定します。<BR>
			既に生成されているものに対して追加になります。<BR>
			32Bitインデックスの場合はUint32になり、16Bitインデックスの場合はUint16になります。
		*/
		virtual void SetIndex( const void* pIndex, Sint32 Count ) = 0;
		/**
			@brief 32Bitインデックスかを取得
			@author 葉迩倭
			@retval true	32Bitインデックス
			@retval false	16Bitインデックス
			@note
			頂点インデックスが32Bitかどうかを取得します。
		*/
		virtual bool Is32BitIndex() const = 0;
		/**
			@brief 頂点数取得
			@author 葉迩倭
			@return 頂点数
			@note
			現在の頂点数を取得します。
		*/
		virtual Sint32 GetVertexCount() const = 0;
		/**
			@brief 頂点インデックス数取得
			@author 葉迩倭
			@return 頂点インデックス数
			@note
			現在の頂点インデックス数を取得します。
		*/
		virtual Sint32 GetIndexCount() const = 0;
	};
}
}
}
}
}

/**
	@file
	@brief スプライトインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Sprite
{
	/**
		@brief プリミティブ用パラメーター
		@author 葉迩倭
	*/
	struct SParameter
	{
		State::IRenderState*	pRenderState;		///< ステート
		IMaterialPlugin*		pMaterialData;		///< 利用するマテリアルプラグインデータ
		bool					IsSortEnable;		///< ソートのするかどうか

		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param pState		[in] 描画に利用するステート（必須）
			@param pMaterial	[in] 描画に利用するマテリアル（必須）
			@param IsSort		[in] 描画時にソートをするかどうか
		*/
		SParameter( State::IRenderState* pState, IMaterialPlugin* pMaterial, bool IsSort )
			: pRenderState		( pState )
			, pMaterialData		( pMaterial )
			, IsSortEnable		( IsSort )
		{
			SAFE_ADDREF( pRenderState )
			SAFE_ADDREF( pMaterialData )
		}
		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		~SParameter()
		{
			SAFE_RELEASE( pMaterialData )
			SAFE_RELEASE( pRenderState )
		}
	};

	/**
		@brief スプライトコントローラー
		@author 葉迩倭
	*/
	class ISpriteController
		: public Interface
	{
	protected:
		virtual ~ISpriteController(){}

	public:
		/**
			@brief アクティブの設定
			@author 葉迩倭
			@param IsActive	[in] アクティブかどうか
			@note
			モデルのアクティブ状態を設定します。<BR>
			非アクティブになると描画されません。
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief 描画オブジェクト数取得
			@author 葉迩倭
			@return 描画オブジェクト数
			@note
			インターフェイスに含まれる描画オブジェクトの数を取得します。
		*/
		virtual Sint32 GetDrawObjectCount() const = 0;
		/**
			@brief 描画オブジェクト取得
			@author 葉迩倭
			@param Index	[in] 描画オブジェクトのインデックス
			@return 描画オブジェクト
			@note
			インターフェイスに含まれる描画オブジェトを取得します。
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;
		/**
			@brief 生成開始
			@author 葉迩倭
			@note
			スプライトの生成処理を開始します。
		*/
		virtual void Begin() = 0;
		/**
			@brief 生成終了
			@author 葉迩倭
			@note
			スプライトの生成処理を終了します。
		*/
		virtual void End() = 0;
		/**
			@brief 描画ページのフリップ
			@author 葉迩倭
			@note
			フレームの最後で呼び出してください。
		*/
		virtual void FlipPage() = 0;
		/**
			@brief スプライトの描画
			@author 葉迩倭
			@param mWorld	[in] ワールド行列
			@param Size		[in] サイズ
			@param Src		[in] 描画に使うテクスチャの矩形
			@param Color	[in] 描画色
			@param UvIndex	[in] 描画に使うテクスチャのインデックス
			@note
			スプライトの描画を行います。<BR>
			必ずBegin()/End()の間で呼び出して下さい。
		*/
		virtual void Draw( const Kernel::Math::Matrix &mWorld, const Kernel::Math::Vector2& Size, const RectF& Src, ColorF Color, Sint32 UvIndex = 0 ) = 0;
		/**
			@brief スプライトの描画
			@author 葉迩倭
			@param mWorld	[in] ワールド行列
			@param PointTbl	[in] 描画の４点（左上、右上、左下、右下）
			@param Src		[in] 描画に使うテクスチャの矩形
			@param Color	[in] 描画色
			@param UvIndex	[in] 描画に使うテクスチャのインデックス
			@note
			スプライトの描画を行います。<BR>
			必ずBegin()/End()の間で呼び出して下さい。
		*/
		virtual void Draw( const Kernel::Math::Matrix &mWorld, const Kernel::Math::Vector2 PointTbl[], const RectF& Src, ColorF Color, Sint32 UvIndex = 0 ) = 0;
		/**
			@brief ビルボードの描画
			@author 葉迩倭
			@param Position	[in] 描画位置
			@param Size		[in] サイズ
			@param Src		[in] 描画に使うテクスチャの矩形
			@param Color	[in] 描画色
			@param UvIndex	[in] 描画に使うテクスチャのインデックス
			@note
			スプライトの描画を行います。<BR>
			必ずBegin()/End()の間で呼び出して下さい。
		*/
		virtual void DrawBillboard( const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2& Size, const RectF& Src, ColorF Color, Sint32 UvIndex = 0 ) = 0;
		/**
			@brief ビルボードの描画
			@author 葉迩倭
			@param Position	[in] 描画位置
			@param PointTbl	[in] 描画の４点（左上、右上、左下、右下）
			@param Src		[in] 描画に使うテクスチャの矩形
			@param Color	[in] 描画色
			@param UvIndex	[in] 描画に使うテクスチャのインデックス
			@note
			スプライトの描画を行います。<BR>
			必ずBegin()/End()の間で呼び出して下さい。
		*/
		virtual void DrawBillboard( const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2 PointTbl[], const RectF& Src, ColorF Color, Sint32 UvIndex = 0 ) = 0;
		/**
			@brief 任意軸固定ビルボードの描画
			@author 葉迩倭
			@param Axis		[in] 回転軸(単位ベクトル)
			@param Position	[in] 描画位置
			@param Size		[in] サイズ
			@param Src		[in] 描画に使うテクスチャの矩形
			@param Color	[in] 描画色
			@param UvIndex	[in] 描画に使うテクスチャのインデックス
			@note
			スプライトの描画を行います。<BR>
			必ずBegin()/End()の間で呼び出して下さい。
		*/
		virtual void DrawAxisBillboard( const Kernel::Math::VectorS& Axis, const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2& Size, const RectF& Src, ColorF Color, Sint32 UvIndex = 0 ) = 0;
		/**
			@brief 任意軸固定ビルボードの描画
			@author 葉迩倭
			@param Axis		[in] 回転軸(単位ベクトル)
			@param Position	[in] 描画位置
			@param PointTbl	[in] 描画の４点（左上、右上、左下、右下）
			@param Src		[in] 描画に使うテクスチャの矩形
			@param Color	[in] 描画色
			@param UvIndex	[in] 描画に使うテクスチャのインデックス
			@note
			スプライトの描画を行います。<BR>
			必ずBegin()/End()の間で呼び出して下さい。
		*/
		virtual void DrawAxisBillboard( const Kernel::Math::VectorS& Axis, const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2 PointTbl[], const RectF& Src, ColorF Color, Sint32 UvIndex = 0 ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief ポリラインコントローラーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace PolyLine
{
	/**
		@brief DrawList用構造体
		@author 葉迩倭
	*/
	struct SListData
	{
		Kernel::Math::VectorS Position;	///< 中心点
		float Width;					///< 幅
		ColorF Color;					///< 色
	};

	/**
		@brief ポリライン用パラメーター
		@author 葉迩倭
	*/
	struct SParameter
	{
		State::IRenderState*	pRenderState;		///< ステート
		IMaterialPlugin*		pMaterialData;		///< 利用するマテリアルプラグインデータ
		bool					IsDynamic;			///< 動的バッファのON/OFF（毎フレーム以上書き換える場合はONに）
		bool					IsAutoResize;		///< 自動リサイズのON/OFF

		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param pState		[in] 描画に利用するステート（必須）
			@param pMaterial	[in] 描画に利用するマテリアル（必須）
		*/
		SParameter( State::IRenderState* pState, IMaterialPlugin* pMaterial )
			: pRenderState		( pState )
			, pMaterialData		( pMaterial )
			, IsDynamic			( false )
			, IsAutoResize		( false )
		{
			SAFE_ADDREF( pRenderState )
			SAFE_ADDREF( pMaterialData )
		}
		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		~SParameter()
		{
			SAFE_RELEASE( pRenderState )
			SAFE_RELEASE( pMaterialData )
		}
	};

	/**
		@brief ポリラインコントローラー
		@author 葉迩倭
	*/
	class IPolyLineController
		: public Interface
	{
	protected:
		virtual ~IPolyLineController(){}

	public:
		/**
			@brief アクティブの設定
			@author 葉迩倭
			@param IsActive	[in] アクティブかどうか
			@note
			モデルのアクティブ状態を設定します。<BR>
			非アクティブになると描画されません。
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief 描画オブジェクト数取得
			@author 葉迩倭
			@return 描画オブジェクト数
			@note
			インターフェイスに含まれる描画オブジェクトの数を取得します。
		*/
		virtual Sint32 GetDrawObjectCount() const = 0;
		/**
			@brief 描画オブジェクト取得
			@author 葉迩倭
			@param Index	[in] 描画オブジェクトのインデックス
			@return 描画オブジェクト
			@note
			インターフェイスに含まれる描画オブジェトを取得します。
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;
		/**
			@brief 生成開始
			@author 葉迩倭
			@note
			ポリラインの生成処理を開始します。
		*/
		virtual void Begin() = 0;
		/**
			@brief 生成終了
			@author 葉迩倭
			@note
			ポリラインの生成処理を終了します。
		*/
		virtual void End() = 0;
		/**
			@brief 描画ページのフリップ
			@author 葉迩倭
			@note
			フレームの最後で呼び出してください。
		*/
		virtual void FlipPage() = 0;
		/**
			@brief ポリライン生成
			@author 葉迩倭
			@param List		[in] ポリライン用のデータのリスト
			@param Count	[in] データのリストの数
			@param Src		[in] テクスチャのUV情報（ピクセル単位）
			@param UvIndex	[in] テクスチャのインデックス
			@note
			ポリラインの生成を行います。<BR>
			必ずBeing()/End()間で呼び出して下さい。
		*/
		virtual void DrawPolyLine( const SListData List[], Sint32 Count, const RectF& Src, Sint32 UvIndex = 0 ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief テキストインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Text
{
	/**
		@brief テキストデータ
		@author 葉迩倭
	*/
	class ITextData
		: public Interface
	{
	protected:
		virtual ~ITextData(){}

	public:
		/**
			@brief テキストデータの文字間設定
			@author 葉迩倭
			@param Space		[in] 文字間の余白
			@note
			対象のインデックスに対して文字データの文字間の余白を設定します。
		*/
		virtual void SetFontSpace( const Point2DI& Space ) = 0;
		/**
			@brief テキストデータの文字サイズ設定
			@author 葉迩倭
			@param Size		[in] 文字サイズ
			@note
			対象のインデックスに対して文字データの文字サイズを設定します。
		*/
		virtual void SetDrawFontSize( Sint32 Size ) = 0;
		/**
			@brief テキストデータの文字サイズ設定
			@author 葉迩倭
			@param Size		[in] 文字サイズ
			@note
			対象のインデックスに対して文字データの文字サイズを設定します。
		*/
		virtual void SetDrawFontSize3D( float Size ) = 0;
		/**
			@brief テキストデータの文字サイズ取得
			@author 葉迩倭
			@note
			対象のインデックスに対して文字データの基本文字サイズを取得します。
		*/
		virtual Sint32 GetOriginalFontSize() const = 0;
		/**
			@brief テキストデータの文字サイズ取得
			@author 葉迩倭
			@return 文字のベースサイズ
			@note
			対象のインデックスに対して文字データの基本文字サイズを取得します。<BR>
			ここで取得できるサイズはツール上で生成した時のサイズです。
		*/
		virtual Sint32 GetDrawFontSize() const = 0;
		/**
			@brief テキストデータの縦用か取得
			@author 葉迩倭
			@retval true	縦書きフォント
			@retval false	横書きフォント
			@note
			対象のインデックスに対して文字データの基本文字サイズを取得します。
		*/
		virtual bool IsVerticale() const = 0;
		/**
			@brief テキストデータの描画優先度を設定
			@author 葉迩倭
			@param Priority	[in] 描画優先度
			@note
			テキストの描画時の描画優先度を設定します。<BR>
			内部的にはSimple::ISpriteRendererに対して同じことを行います。
		*/
		virtual void SetPriority( Sint32 Priority ) = 0;
		/**
			@brief テキスト描画用のスプライト設定
			@author 葉迩倭
			@param pSprite	[in] スプライトインターフェイス
			@note
			テキストの描画に使うスプライトを設定します。<BR>
			このメソッドによる設定を行わない場合は内部で保持している<BR>
			スプライトを利用居て描画されます。
		*/
		virtual void SetDrawSprite( Simple::ISpriteRenderer* pSprite ) = 0;
		/**
			@brief テキスト描画用のスプライト設定
			@author 葉迩倭
			@param pSprite	[in] スプライトインターフェイス
			@note
			テキストの描画に使うスプライトを設定します。<BR>
			このメソッドによる設定を行わない場合は内部で保持している<BR>
			スプライトを利用居て描画されます。
		*/
		virtual void SetDrawSprite3D( Simple::ISpriteRenderer3D* pSprite ) = 0;

		/**
			@brief テキストデータの文字描画位置設定
			@author 葉迩倭
			@param Position		[in] 文字描画位置
			@note
			対象のインデックスに対して文字データの文字描画位置を設定します。
		*/
		virtual void SetDrawBasePosition( const Point2DF& Position ) = 0;
		/**
			@brief テキストデータのリセット
			@author 葉迩倭
			@note
			テキストデータをリセットします。
		*/
		virtual void Reset() = 0;
		/**
			@brief テキストデータの描画
			@author 葉迩倭
			@note
			テキストデータ内の描画を一括で行います。
		*/
		virtual void Draw() = 0;
		/**
			@brief テキストデータの文字描画位置設定
			@author 葉迩倭
			@param Rect		[in] シザリング領域
			@note
			対象のインデックスに対して文字データの文字描画位置を設定します。
		*/
		virtual void SetScissorRect( const RectI& Rect ) = 0;
		/**
			@brief テキストデータの文字描画サイズ取得
			@author 葉迩倭
			@param pString		[in] サイズを調べる文字列
			@param Length		[in] 文字数（-1で全部）
			@return 文字描画サイズ
			@note
			対象のインデックスに対して文字の実際に描画した場合のサイズを取得します。
		*/
		virtual Point2DF GetDrawSize( const wchar_t* pString, Sint32 Length = -1 ) const = 0;
		/**
			@brief テキストデータの文字描画サイズ取得
			@author 葉迩倭
			@param pString		[in] サイズを調べる文字列
			@param Length		[in] 文字数（-1で全部）
			@return 文字描画サイズ
			@note
			対象のインデックスに対して文字の実際に描画した場合のサイズを取得します。
		*/
		virtual Kernel::Math::Vector3 GetDrawSize3D( const wchar_t* pString, Sint32 Length ) const = 0;
		/**
			@brief テキストデータの文字描画終了位置取得
			@author 葉迩倭
			@param pString		[in] サイズを調べる文字列
			@param Length		[in] 文字数（-1で全部）
			@return 文字描画終端位置
			@note
			対象のインデックスに対して文字の実際に描画した場合の終端位置を取得します。
		*/
		virtual Point2DF GetDrawEndPosition( const wchar_t* pString, Sint32 Length = -1 ) const = 0;
		/**
			@brief テキストデータの文字描画
			@author 葉迩倭
			@param Position			[in] 描画開始位置
			@param Color			[in] 描画色
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@param IsBasePosition	[in] ベースポジションから描画するかどうかのフラグ
			@return 文字描画終端位置
			@note
			対象のインデックスに対して文字の描画を行います。<BR>
			Text_DrawLeft()と同様に左揃えで描画されます。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual Point2DF DrawDirect( const Point2DF& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief テキストデータの文字描画
			@author 葉迩倭
			@param Position			[in] 描画開始位置
			@param Color			[in] 描画色
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@param IsBasePosition	[in] ベースポジションから描画するかどうかのフラグ
			@return 文字描画終端位置
			@note
			対象のインデックスに対して文字の描画を行います。<BR>
			Text_DrawLeft()と同様に左揃えで描画されます。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual Point2DF DrawRequest( const Point2DF& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief 左揃えテキストデータの文字描画
			@author 葉迩倭
			@param Rect				[in] 描画矩形
			@param Offset			[in] 描画位置のオフセット
			@param Color			[in] 描画色
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@param IsBasePosition	[in] ベースポジションから描画するかどうかのフラグ
			@return 文字描画終端位置
			@note
			対象のインデックスに対して左揃えで文字の描画を行います。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual Point2DF DrawRequestLeft( const RectF& Rect, const Point2DF& Offset, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief 中央揃えテキストデータの文字描画
			@author 葉迩倭
			@param Rect				[in] 描画矩形
			@param Offset			[in] 描画位置のオフセット
			@param Color			[in] 描画色
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@param IsBasePosition	[in] ベースポジションから描画するかどうかのフラグ
			@return 文字描画終端位置
			@note
			対象のインデックスに対して中央揃えで文字の描画を行います。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual Point2DF DrawRequestCenter( const RectF& Rect, const Point2DF& Offset, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief 右揃えテキストデータの文字描画
			@author 葉迩倭
			@param Rect				[in] 描画矩形
			@param Offset			[in] 描画位置のオフセット
			@param Color			[in] 描画色
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@param IsBasePosition	[in] ベースポジションから描画するかどうかのフラグ
			@return 文字描画終端位置
			@note
			対象のインデックスに対して右揃えで文字の描画を行います。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual Point2DF DrawRequestRight( const RectF& Rect, const Point2DF& Offset, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief テキストデータの文字描画
			@author 葉迩倭
			@param Position			[in] 描画位置
			@param Color			[in] 描画色
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@note
			対象のインデックスに対して文字の描画を行います。<BR>
			Text_DrawLeft()と同様に左揃えで描画されます。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual void DrawDirect3D( const Kernel::Math::Vector3& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1 ) = 0;
		/**
			@brief テキストデータの文字描画
			@author 葉迩倭
			@param Position			[in] 描画位置
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@note
			対象のインデックスに対して文字の描画を行います。<BR>
			Text_DrawLeft()と同様に左揃えで描画されます。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual void DrawRequest3D( const Kernel::Math::Vector3& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1 ) = 0;
		/**
			@brief 左揃えテキストデータの文字描画
			@author 葉迩倭
			@param Position			[in] 描画位置
			@param Color			[in] 描画色
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@note
			対象のインデックスに対して左揃えで文字の描画を行います。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual void DrawRequest3DLeft( const Kernel::Math::Vector3& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1 ) = 0;
		/**
			@brief 中央揃えテキストデータの文字描画
			@author 葉迩倭
			@param Position			[in] 描画位置
			@param Color			[in] 描画色
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@note
			対象のインデックスに対して中央揃えで文字の描画を行います。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual void DrawRequest3DCenter( const Kernel::Math::Vector3& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1 ) = 0;
		/**
			@brief 右揃えテキストデータの文字描画
			@author 葉迩倭
			@param Position			[in] 描画位置
			@param Color			[in] 描画色
			@param pString			[in] 描画する文字列
			@param Length			[in] 文字数（-1で全部）
			@note
			対象のインデックスに対して右揃えで文字の描画を行います。<BR>
			IsBasePosition=trueの場合はText_SetDrawBasePositionで設定した場所からかかれます。
		*/
		virtual void DrawRequest3DRight( const Kernel::Math::Vector3& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1 ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief グラフィックマネージャーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
	static const Sint32 RENDER_TARGET_MAX_COUNT	= 4;	///< 描画ターゲットの最大数
	static const Sint32 TEXTURE_STAGE_MAX_COUNT	= 12;	///< テクスチャの同時利用可能の最大数

	/**
		@brief グラフィックAPI
		@author 葉迩倭
		@note
		グラフィックAPI
	*/
	enum eGraphicsAPI
	{
		GRAPHICS_API_DIRECTX_09,
		GRAPHICS_API_DIRECTX_10,
		GRAPHICS_API_DIRECTX_11,
		GRAPHICS_API_UNKNOWN,
	};

	/**
		@brief テクスチャフィルタ
		@author 葉迩倭
		@note
		テクスチャのフィルタ
	*/
	enum eTextureFilter
	{
		TEXTURE_FILTER_NEAREST,
		TEXTURE_FILTER_BILINEAR,
		TEXTURE_FILTER_ANISOTROPIC,
	};

	/**
		@brief テクスチャフォーマット
		@author 葉迩倭
		@note
		テクスチャのフォーマット
	*/
	enum eTextureFormat
	{
		TF_TEXTURE_A8,					///< alpha-only
		TF_TEXTURE_32BIT,				///< A8R8G8B8
		TF_TEXTURE_16BIT,				///< A4R4G4B4
		TF_TEXTURE_DXT,					///< DXT1
		TF_TEXTURE_DXT_ALPHA,			///< DXT5/DXT3

		TF_TARGET_UCHARx4,				///< A8R8G8B8
		TF_TARGET_RGB10BIT,				///< A2R10G10B10
		TF_TARGET_FLOAT32x1,			///< fp32-R
		TF_TARGET_FLOAT32x4,			///< fp32-RGBA
		TF_TARGET_FLOAT16x1,			///< fp16-R
		TF_TARGET_FLOAT16x4,			///< fp16-RGBA
		TF_TARGET_UCHARx4_ALPHA,		///< A8R8G8B8    - alpha blending enable
		TF_TARGET_RGB10BIT_ALPHA,		///< A2R10G10B10 - alpha blending enable
		TF_TARGET_FLOAT32x1_ALPHA,		///< fp32-R      - alpha blending enable
		TF_TARGET_FLOAT32x4_ALPHA,		///< fp32-RGBA   - alpha blending enable
		TF_TARGET_FLOAT16x1_ALPHA,		///< fp16-R      - alpha blending enable
		TF_TARGET_FLOAT16x4_ALPHA,		///< fp16-RGBA   - alpha blending enable

		TF_DEPTH_TARGET,				///< DepthBuffer

		TF_MAX,

		TF_INVALID = TF_MAX,
	};

	/**
		@brief テクスチャ読み込み用パラメーター
		@author 葉迩倭
		@note
		テクスチャの読み込みに使われるパラメーターです
	*/
	struct STextureLoadParameter
	{
		bool IsFromFile;			///< ファイルからそのまま読み込む（他のフラグを全部無視）
		bool IsCompressFormat;		///< 圧縮テクスチャの有無
		bool IsMipmapEnable;		///< ミップマップの有無
		Sint32 SizeDivide;			///< 元のサイズに対して除算する数（2なら256x256を内部的に128x128で生成）
		ColorF ColorKey;			///< カラーキーを利用しない場合は(0,0,0,0)
	};

	/**
		@brief プリミティブ描画種類
		@author 葉迩倭
		@note
		DrawPrimitive時の描画プリミティブの種類
	*/
	enum DrawPrimitiveType
	{
		DP_LINE_LIST,				///< ラインリスト描画
		DP_LINE_STRIP,				///< ラインストリップ描画
		DP_TRIANGLE_LIST,			///< 三角形リスト描画
		DP_TRIANGLE_STRIP,			///< 三角形ストリップ描画
	};

	/**
		@brief デバイス生成用パラメーター
		@author 葉迩倭
		@note
		デバイスを生成するためのパラメータークラスです
	*/
	class SDeviceCreationParameter
	{
	private:
		bool		m_IsFullScreen;			///< フルスクーリン起動の有無
		bool		m_IsWaitVSync;			///< VSync待ちの有無
		Point2DI	m_BackBufferSize;		///< バックバッファサイズ
		HWND		m_WindowHandle;			///< ウィンドウハンドル

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		SDeviceCreationParameter()
			: m_IsFullScreen	( false )
			, m_IsWaitVSync		( true )
			, m_BackBufferSize	( 0, 0 )
			, m_WindowHandle	( 0 )
		{
		}

	public:
		/**
			@brief ウィンドウハンドル設定
			@author 葉迩倭
			@param Handle	[in] ウィンドウハンドル
		*/
		void SetWindowHandle( HWND Handle )
		{
			m_WindowHandle = Handle;
		}

		/**
			@brief 葉迩倭
			@author 葉迩倭
			@param Flag	[in] trueの時VSync待ちする
		*/
		void SetWaitVSync( bool Flag )
		{
			m_IsWaitVSync = Flag;
		}

		/**
			@brief フルスクリーンモード有無設定
			@author 葉迩倭
			@param Flag	[in] trueの時フルスクリーンモードで起動
		*/
		void SetFullScreenMode( bool Flag )
		{
			m_IsFullScreen = Flag;
		}

		/**
			@brief バックバッファのサイズを設定
			@author 葉迩倭
			@param Size	[in] バックバッファのサイズ
		*/
		void SetBackbufferSize( const Point2DI &Size )
		{
			m_BackBufferSize = Size;
		}

		/**
			@brief ウィンドウハンドル取得
			@author 葉迩倭
			@return ウィンドウハンドル
		*/
		HWND GetWindowHandle() const
		{
			return m_WindowHandle;
		}

		/**
			@brief VSync待ちの有無を取得
			@author 葉迩倭
			@return VSync待ちを行うかの有無
		*/
		bool GetWaitVSync() const
		{
			return m_IsWaitVSync;
		}

		/**
			@brief フルスクリーンモードで起動するかを取得
			@author 葉迩倭
			@return フルスクリーンモードで起動するかの有無
		*/
		bool GetFullScreenMode() const
		{
			return m_IsFullScreen;
		}

		/**
			@brief バックバッファのサイズを取得
			@author 葉迩倭
			@return バックバッファのサイズ
		*/
		const Point2DI &GetBackbufferSize() const
		{
			return m_BackBufferSize;
		}
	};

	/**
		@brief 描画管理クラス
		@author 葉迩倭

		描画の読み込み処理を行うためのインターフェイスです。
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		virtual void* GetDevicePointer() = 0;
		/**
			@brief グラフィックAPI取得
			@author 葉迩倭
			@return グラフィックAPIの種類
			@note
			現在のGraphicsManagerが利用しているAPIを取得します。
		*/
		virtual eGraphicsAPI GetGraphicsAPI() = 0;
		/**
			@brief ディスプレイモードの数を取得
			@author 葉迩倭
			@return ディスプレイモードの数
			@note
			アダプターが設定可能なディスプレイモードの数を取得します。<BR>
			ウィンドウモードの場合はサイズに制限はありません。
		*/
		virtual Sint32 GetDisplayModeCount() const = 0;
		/**
			@brief ディスプレイモードを取得
			@author 葉迩倭
			@param Index	[in]
			@return ディスプレイモード
			@note
			Index番目に見つかったディスプレイモードを取得します。
		*/
		virtual Point2DI GetDisplayMode( Sint32 Index ) const = 0;
		/**
			@brief スクリーンモードの切り替え
			@author 葉迩倭
			@param IsFullscreen	[in] スクリーンモードの切り替え
			@note
			スクリーンモードの切り替えを行います。
		*/
		virtual void ChangeScreenMode( bool IsFullscreen ) = 0;
		/**
			@brief 画面描画開始
			@author 葉迩倭
			@note
			レンダリング処理を開始する事をドライバーに通知します。
		*/
		virtual void Begin() = 0;
		/**
			@brief 画面描画終了
			@author 葉迩倭
			@note
			レンダリング処理を終了した事をドライバーに通知します。
		*/
		virtual void End() = 0;
		/**
			@brief ウィンドウにバックバッファの内容を転送
			@author 葉迩倭
			@return falseの時デバイスの復帰不可能なエラー発生
			@note
			バックバッファに対して生成した画面をウィンドウに転送します。
		*/
		virtual bool Present() = 0;
		/**
			@brief 描画ターゲットのクリア
			@author 葉迩倭
			@param IsClearTarget	[in] カラーバッファをクリアするか否か
			@param IsClearDepth		[in] 深度バッファをクリアするか否か
			@param Color			[in] カラーバッファのクリア色
			@return falseの時デバイスの復帰不可能なエラー発生
			@note
			バックバッファと深度バッファをクリアします。
		*/
		virtual void Clear( bool IsClearTarget, bool IsClearDepth, const ColorF& Color ) = 0;
		/**
			@brief シェーダーの対応状況を取得
			@author 葉迩倭
			@retval true	最低でも3.0世代のシェーダーをサポートしている
			@retval false	シェーダー3.0すらサポートしてない
			@note
			現在デバイスがシェーダーに対応しているか取得します。
		*/
		virtual bool IsSupportPixelShader() const = 0;
		/**
			@brief ビューポート取得
			@author 葉迩倭
			@return 現在のビューポート
			@note
			現在デバイスに設定されているビューポートを取得します。
		*/
		virtual RectI GetViewport() const = 0;
		/**
			@brief ビューポート設定
			@author 葉迩倭
			@param Rect	[in] ビューポート
			@note
			現在のデバイスにビューポートを設定します。<BR>
			このサイズはレンダリングターゲットに収まる大きさでなくてはいけません。
		*/
		virtual void SetViewport( const RectI& Rect ) = 0;
		/**
			@brief レンダーステートを復帰
			@author 葉迩倭
			@note
			現在内部的に保持されているステートを再適用します
		*/
		virtual void RestoreRenderState() = 0;
		
		/**
			@brief レンダーステートを生成
			@author 葉迩倭
			@return IRenderStateインターフェイス
			@note
			新規のアクティブなステートの複製を生成します。
		*/
		virtual State::IRenderState* CreateRenderState() = 0;
		/**
			@brief レンダーステートを取得
			@author 葉迩倭
			@return IRenderStateインターフェイス
			@note
			現在アクティブなステートを取得します。
		*/
		virtual State::IRenderState* GetRenderState() = 0;
		/**
			@brief レンダーステートを設定
			@author 葉迩倭
			@param pState	[in] IRenderStateインターフェイス
			@note
			現在アクティブなステートに設定します。
		*/
		virtual void SetRenderState( State::IRenderState* pState ) = 0;
		/**
			@brief レンダーステートをスタックにPush
			@author 葉迩倭
			@note
			ステートの階層を１段Pushします。
		*/
		virtual void PushRenderState() = 0;
		/**
			@brief レンダーステートをスタックからPop
			@author 葉迩倭
			@note
			ステートの階層を１段Popします。
		*/
		virtual void PopRenderState() = 0;
		/**
			@brief レンダーステートをドライバーに定着
			@author 葉迩倭
			@note
			実際にステートの内容をドライバーに定着させます。
		*/
		virtual void UpdateRenderState() = 0;
		/**
			@brief クリップ領域設定
			@author 葉迩倭
			@param ScissorRect	[in] クリップ領域
			@note
			描画時のスクリーン空間でのクリップ領域を設定します。
		*/
		virtual void SetScissorRect( const RectI& ScissorRect ) = 0;

		virtual Kernel::Math::Matrix CreateScreenTransformMatrix() const = 0;

		/**
			@brief Antialias可能テクスチャチェック
			@author 葉迩倭
			@retval true	Antialias可能
			@retval false	Antialias不可能
			@note
			レンダリングターゲットがAntialias可能か調べます。
		*/
		virtual bool IsMultiSampleRenderTargetEnable( eTextureFormat Format ) = 0;
		/**
			@brief 色マスク設定
			@author 葉迩倭
			@param pPlane	[in] クリッピング用平面
			@note
			デバイスにクリッピング用平面をセットします。
		*/
		virtual void SetStateEffectRenderingForWater( bool IsEnable ) = 0;

		/**
			@brief テクスチャチェック
			@author 葉迩倭
			@retval true	可能
			@retval false	不可能
			@note
			レンダリングターゲットが可能か調べます。
		*/
		virtual bool IsRenderTargetEnable( eTextureFormat Format ) = 0;

		/**
			@brief 頂点テクスチャ可能テクスチャチェック
			@author 葉迩倭
			@retval true	頂点テクスチャ可能
			@retval false	頂点テクスチャ不可能
			@note
			レンダリングターゲットが頂点テクスチャ可能か調べます。
		*/
		virtual bool IsVertexTextureEnable( eTextureFormat Format ) = 0;

		/**
			@brief テキストレンダラー生成
			@author 葉迩倭
			@param pFontName	[in] フォント名
			@param FontSize		[in] フォントサイズ
			@param IsBold		[in] 太字On/Off
			@param IsItalic		[in] 斜体On/Off
			@return ITextRendererインターフェイス
			@note
			テキスト描画用のインターフェイスを取得します。
		*/
		virtual Simple::ITextRenderer* CreateTextRenderer( const wchar_t* pFontName, Sint32 FontSize, bool IsBold, bool IsItalic ) = 0;
		/**
			@brief スプライトレンダラー生成
			@author 葉迩倭
			@param SpriteSortMode	[in] ソートのモード
			@return ISpriteRendererインターフェイス
			@note
			2D画面描画用のインターフェイスを取得します。
		*/
		virtual Simple::ISpriteRenderer* CreateSpriteRenderer() = 0;
		/**
			@brief 3Dスプライトレンダラー生成
			@author 葉迩倭
			@return ISpriteRenderer3Dインターフェイス
			@note
			3D画面描画用のインターフェイスを取得します。
		*/
		virtual Simple::ISpriteRenderer3D* CreateSpriteRenderer3D() = 0;
		/**
			@brief ラインレンダラー生成
			@author 葉迩倭
			@return ILineRendererインターフェイス
			@note
			ライン描画用のインターフェイスを取得します。
		*/
		virtual Simple::ILineRenderer* CreateLineRenderer() = 0;
		/**
			@brief トライアングルレンダラー生成
			@author 葉迩倭
			@return ITriangleRendererインターフェイス
			@note
			トライアングル描画用のインターフェイスを取得します。
		*/
		virtual Simple::ITriangleRenderer* CreateTriangleRenderer() = 0;
		/**
			@brief 頂点シェーダー生成
			@author 葉迩倭
			@param pBuffer			[in] リソースのバッファのポインタ
			@param Size				[in] リソースのサイズ
			@param Line				[in] 生成したソースの行
			@param pSourceFile		[in] 生成したソースのファイル名
			@return IShaderインターフェイス
			@note
			コンパイル済み頂点シェーダーからインターフェイスを生成します。
		*/
		virtual Resource::IVertexShader* CreateVertexShader( const void* pBuffer, Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief ピクセルシェーダー生成
			@author 葉迩倭
			@param pBuffer			[in] リソースのバッファのポインタ
			@param Size				[in] リソースのサイズ
			@param Line				[in] 生成したソースの行
			@param pSourceFile		[in] 生成したソースのファイル名
			@return IShaderインターフェイス
			@note
			コンパイル済みピクセルシェーダーからインターフェイスを生成します。
		*/
		virtual Resource::IPixelShader* CreatePixelShader( const void* pBuffer, Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief テクスチャ生成
			@author 葉迩倭
			@param Size				[in] テクスチャのサイズ
			@param IsFloat			[in] 浮動小数点か否か（true=float32x4, false=uint8x4）
			@param IsSystemMemory	[in] システムメモリにバックアップを保持するか否か
			@param Line				[in] 生成したソースの行
			@param pSourceFile		[in] 生成したソースのファイル名
			@return ITextureインターフェイス
			@note
			CPUからアクセス可能な空のテクスチャを生成します。<BR>
			「IsSystemMemory = true」の場合は内部で保持しているバックアップのシステムメモリのアドレスを返します。<BR>
			Unlock()がコールされた時点でVRAMへの転送が行われるようになっています。
		*/
		virtual Resource::ITexture* CreateCpuAccessTexture( const Point2DI& Size, bool IsFloat, bool IsSystemMemory, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief テクスチャ生成
			@author 葉迩倭
			@param pBuffer			[in] リソースのバッファのポインタ
			@param Size				[in] リソースのサイズ
			@param pResourceName	[in] 同一リソース検索用のリソース名
			@param Param			[in] テクスチャ生成用のパラメーター
			@return ITextureインターフェイス
			@note
			画像ファイルからテクスチャインターフェイスを生成します。<BR>
			TGA/BMP/JPG/PNG/DDSファイルを読み込むことができます。
		*/
		virtual Resource::ITexture* CreateTexture( const void* pBuffer, Sint32 Size, const wchar_t* pResourceName, const STextureLoadParameter& Param ) = 0;
		/**
			@brief キューブテクスチャ生成
			@author 葉迩倭
			@param pBuffer			[in] リソースのバッファのポインタ
			@param Size				[in] リソースのサイズ
			@param pResourceName	[in] 同一リソース検索用のリソース名
			@param Param			[in] テクスチャ生成用のパラメーター
			@return ITextureインターフェイス
			@note
			画像ファイルからテクスチャインターフェイスを生成します。<BR>
			BMP/JPG/PNG/DDSファイルを読み込むことができます。<BR>
			可能な限りDDSファイルの利用を推奨します。
		*/
		virtual Resource::ITexture* CreateCubeTexture( const void* pBuffer, Sint32 Size, const wchar_t* pResourceName, const STextureLoadParameter& Param ) = 0;
		/**
			@brief 深度バッファテクスチャ生成
			@author 葉迩倭
			@param Size			[in] リソースのサイズ
			@param DepthFormat	[in] 深度バッファフォーマット
			@param Line			[in] 生成したソースの行
			@param pSourceFile	[in] 生成したソースのファイル名
			@return ITextureインターフェイス
			@note
			深度バッファ用のテクスチャインターフェイスを生成します。
		*/
		virtual Resource::ITexture* CreateDepthTexture( const Point2DI& Size, eTextureFormat DepthFormat, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief 描画ターゲットテクスチャ生成
			@author 葉迩倭
			@param Size			[in] リソースのサイズ
			@param Format		[in] 生成するターゲットのフォーマット
			@param Line			[in] 生成したソースの行
			@param pSourceFile	[in] 生成したソースのファイル名
			@return ITextureインターフェイス
			@note
			描画ターゲット用のテクスチャインターフェイスを生成します。
		*/
		virtual Resource::ITexture* CreateTargetTexture( const Point2DI& Size, eTextureFormat Format, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief マルチサンプリング対応描画ターゲットテクスチャ生成
			@author 葉迩倭
			@param Size			[in] リソースのサイズ
			@param TargetFormat	[in] 生成する描画ターゲットのフォーマット
			@param pTarget		[out] 描画ターゲットインターフェイス格納先
			@param DepthFormat	[in] 生成する深度ターゲットのフォーマット
			@param pDepth		[out] 深度ターゲットインターフェイス格納先
			@param Line			[in] 生成したソースの行
			@param pSourceFile	[in] 生成したソースのファイル名
			@return ITextureインターフェイス
			@note
			描画ターゲット用のテクスチャインターフェイスを生成します。
		*/
		virtual bool CreateRenderTargetWithAntialias( const Point2DI& Size, eTextureFormat TargetFormat, Resource::ITexture*& pTarget, eTextureFormat DepthFormat, Resource::ITexture*& pDepth, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief 頂点レイアウト生成
			@author 葉迩倭
			@param LayoutTable	[in] レイアウトが定義されているテーブル（終端にはStreamNoに-1を入れておいてください）
			@param pData		[in] 頂点シェーダーバイナリ
			@param Size			[in] 頂点シェーダーサイズ
			@param Line			[in] 生成したソースの行
			@param pSourceFile	[in] 生成したソースのファイル名
			@note
			頂点構造体の定義とシェーダーを関連付ける為のインターフェイスを生成します。
		*/
		virtual Resource::IVertexLayout* CreateVertexLayout( const Graphics::Resource::SVertexLayoutTable LayoutTable[], const void* pData, Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief 頂点レイアウト生成
			@author 葉迩倭
			@param LayoutTable	[in] レイアウトが定義されているテーブル（終端にはStreamNoに-1を入れておいてください）
			@param pShader		[in] チェックする頂点フォーマットの入った頂点シェーダー
			@param Line			[in] 生成したソースの行
			@param pSourceFile	[in] 生成したソースのファイル名
			@note
			頂点構造体の定義とシェーダーを関連付ける為のインターフェイスを生成します。
		*/
		virtual Resource::IVertexLayout* CreateVertexLayout( const Resource::SVertexLayoutTable LayoutTable[], Graphics::Resource::IVertexShader* pShader, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief 頂点バッファ生成
			@author 葉迩倭
			@param VertexSize	[in] 頂点の１要素のサイズ
			@param VertexCount	[in] 頂点数
			@param IsDynamic	[in] 動的生成フラグ
			@param pInitialize	[in] バッファ初期化用データ
			@param IsAutoResize	[in] 自動サイズ拡張
			@param Line			[in] 生成したソースの行
			@param pSourceFile	[in] 生成したソースのファイル名
			@return IVertexBufferインターフェイス
			@note
			頂点構造体の実データを格納する為のインターフェイスを生成します。
		*/
		virtual Resource::IVertexBuffer* CreateVertexBuffer( Sint32 VertexSize, Sint32 VertexCount, bool IsDynamic, const void* pInitialize, bool IsAutoResize, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief 頂点インデックス生成
			@author 葉迩倭
			@param Is32Bit		[in] 32Bitのインデックスを利用するか否か
			@param IndexCount	[in] 頂点インデックス数
			@param IsDynamic	[in] 動的生成フラグ
			@param pInitialize	[in] インデックス初期化用データ
			@param IsAutoResize	[in] 自動サイズ拡張
			@param Line			[in] 生成したソースの行
			@param pSourceFile	[in] 生成したソースのファイル名
			@return IIndexBufferインターフェイス
			@note
			頂点構造体の実データを格納する為のインターフェイスを生成します。
		*/
		virtual Resource::IIndexBuffer* CreateIndexBuffer( bool Is32Bit, Sint32 IndexCount, bool IsDynamic, const void* pInitialize, bool IsAutoResize, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief プリミティブ描画
			@author 葉迩倭
			@param Type			[in] 描画タイプ
			@param VertexStart	[in] 頂点の開始位置
			@param VertexCount	[in] 頂点の数
			@note
			設定された情報と引数を元にして描画ターゲットにポリゴンの描画を行います。
		*/
		virtual void DrawPrimitive( DrawPrimitiveType Type, Sint32 VertexStart, Sint32 VertexCount ) = 0;
		/**
			@brief プリミティブ描画
			@author 葉迩倭
			@param Type				[in] 描画タイプ
			@param VertexStart		[in] 頂点の開始位置
			@param VertexCount		[in] 頂点の数
			@param IndexStart		[in] インデックスの開始位置
			@param IndexCount		[in] インデックスの数
			@note
			設定された情報と引数を元にして描画ターゲットにポリゴンの描画を行います。
		*/
		virtual void DrawPrimitiveIndex( DrawPrimitiveType Type, Sint32 VertexStart, Sint32 VertexCount, Sint32 IndexStart, Sint32 IndexCount ) = 0;
		/**
			@brief プリミティブ描画
			@author 葉迩倭
			@param Type			[in] 描画タイプ
			@param VertexStart	[in] 頂点の開始位置
			@param VertexCount	[in] 頂点の数
			@param InstanceCount	[in] インスタンス数
			@note
			設定された情報と引数を元にして描画ターゲットにポリゴンの描画を行います。
		*/
		virtual void DrawPrimitiveInstance( DrawPrimitiveType Type, Sint32 VertexStart, Sint32 VertexCount, Uint32 InstanceCount ) = 0;
		/**
			@brief プリミティブ描画
			@author 葉迩倭
			@param Type				[in] 描画タイプ
			@param VertexStart		[in] 頂点の開始位置
			@param VertexCount		[in] 頂点の数
			@param IndexStart		[in] インデックスの開始位置
			@param IndexCount		[in] インデックスの数
			@param InstanceCount	[in] インスタンス数
			@note
			設定された情報と引数を元にして描画ターゲットにポリゴンの描画を行います。
		*/
		virtual void DrawPrimitiveIndexInstance( DrawPrimitiveType Type, Sint32 VertexStart, Sint32 VertexCount, Sint32 IndexStart, Sint32 IndexCount, Uint32 InstanceCount ) = 0;
		/**
			@brief 描画ターゲット設定
			@author 葉迩倭
			@param pTargetTexture1	[in] 描画用描画ターゲット
			@param pTargetTexture2	[in] 描画用描画ターゲット
			@param pTargetTexture3	[in] 描画用描画ターゲット
			@param pTargetTexture4	[in] 描画用描画ターゲット
			@param pDepthTexture	[in] 描画用深度バッファ
			@param IsAntialias			[in] Antialias(アンチエイリアス)処理をONにするかどうか
			@note
			描画に利用する描画ターゲットテクスチャインターフェイスを設定します。<BR>
			IsAntialiasをONにするにはCreateRenderTargetWithAntialias()で生成したバッファの必要があります。
		*/
		virtual void SetRenderTarget( Resource::ITexture* pTargetTexture1, Resource::ITexture* pTargetTexture2, Resource::ITexture* pTargetTexture3, Resource::ITexture* pTargetTexture4, Resource::ITexture* pDepthTexture, bool IsAntialias ) = 0;
		/**
			@brief 頂点レイアウト設定
			@author 葉迩倭
			@param pVertexLayout	[in] 描画用頂点レイアウト
			@note
			描画に利用する頂点データのレイアウトが定義されたインターフェイスを設定します。
		*/
		virtual void SetVertexLayout( Resource::IVertexLayout* pVertexLayout ) = 0;
		/**
			@brief 頂点バッファ設定
			@author 葉迩倭
			@param pBuffer				[in] 描画用頂点バッファ
			@note
			描画に利用する頂点データのバッファが定義されたインターフェイスを設定します。
		*/
		virtual void SetVertexBuffer( Resource::IVertexBuffer* pBuffer ) = 0;
		/**
			@brief 頂点インデックス設定
			@author 葉迩倭
			@param pBuffer			[in] 描画用頂点インデックス
			@note
			描画に利用する頂点データのインデックスが定義されたインターフェイスを設定します。
		*/
		virtual void SetIndexBuffer( Resource::IIndexBuffer* pBuffer ) = 0;
		/**
			@brief 頂点シェーダー設定
			@author 葉迩倭
			@param pShader	[in] シェーダー
			@note
			デバイスに頂点シェーダーをセットします。
		*/
		virtual void SetVertexShader( Resource::IVertexShader* pShader ) = 0;
		/**
			@brief ピクセルシェーダー設定
			@author 葉迩倭
			@param pShader	[in] シェーダー
			@note
			デバイスにピクセルシェーダーをセットします。
		*/
		virtual void SetPixelShader( Resource::IPixelShader* pShader ) = 0;
		/**
			@brief テクスチャ設定
			@author 葉迩倭
			@param State	[in] ステージ
			@param pTexture	[in] テクスチャ
			@param IsFilter	[in] フィルタON/OFF
			@param IsWrap	[in] ラッピングON/OFF
			@note
			デバイスにテクスチャをセットします。
		*/
		virtual void SetTexture( Uint32 Stage, Resource::ITexture* pTexture, eTextureFilter Filter, bool IsWrap ) = 0;
		/**
			@brief テクスチャ設定
			@author 葉迩倭
			@param State	[in] ステージ
			@param pTexture	[in] テクスチャ
			@note
			デバイスにテクスチャをセットします。
		*/
		virtual void SetVertexTexture( Uint32 Stage, Resource::ITexture* pTexture ) = 0;
		/**
			@brief 描画数を取得
			@author 葉迩倭
			@note
			実際に描画がコールされた回数を取得します。
		*/
		virtual Uint32 GetDrawPrimitiveCount() = 0;

		/**
			@brief 描画ポリゴン数を取得
			@author 葉迩倭
			@note
			実際に描画したポリゴン数を取得します。
		*/
		virtual Uint32 GetDrawPolygonCount() = 0;

		/**
			@brief 画面を画像で保存
			@author 葉迩倭
			@param pFileName	[in] ファイル名
			@note
			現在の画面の内容を画像で保存します。
		*/
		virtual void SaveScreen( const wchar_t* pFileName ) = 0;

		/**
			@brief 描画ターゲット複製
			@author 葉迩倭
			@param pTextureDst	[in] 転送先ターゲットテクスチャ
			@param pTextureSrc	[in] 転送元ターゲットテクスチャ
			@note
			描画ターゲットの内容を別の描画ターゲットに複製します。
		*/
		virtual void MultSampleTargetDownSampling( Resource::ITexture* pTextureDst, Resource::ITexture* pTextureSrc ) = 0;

		/**
			@brief マテリアルリスナーの登録
			@author 葉迩倭
			@param pPluginName	[in] プラグイン名
			@param pListener	[in] リスナー
			@note
			マテリアル読み込み時に検索するマテリアルリスナーを登録します。
		*/
		virtual void RegistMaterialListener( const char* pPluginName, Resource::IMaterialListener* pListener ) = 0;
		/**
			@brief マテリアルリスナーの削除
			@author 葉迩倭
			@param pPluginName	[in] プラグイン名
			@note
			マテリアル読み込み時に検索するマテリアルリスナーを削除します。
		*/
		virtual void UnRegistMaterialListener( const char* pPluginName ) = 0;
		/**
			@brief マテリアルリスナーの取得
			@author 葉迩倭
			@param pPluginName	[in] プラグイン名
			@note
			プラグインに対応したマテリアルリスナーを取得します。
		*/
		virtual Resource::IMaterialListener* GetMaterialListener( const char* pPluginName ) = 0;

		/**
			@brief モデル生成
			@author 葉迩倭
			@param pData		[in] データのポインタ
			@param Size			[in] データのサイズ
			@param pFileName	[in] データ名
			@note
			Amaryllisで作成可能なSMFファイルからモデルデータの生成を行います。
		*/
		virtual Resource::SMF::IModel* CreateModel( const void* pData, Uint32 Size, const wchar_t* pFileName ) = 0;
		/**
			@brief モデル生成
			@author 葉迩倭
			@param pData		[in] データのポインタ
			@param Size			[in] データのサイズ
			@param pFileName	[in] データ名
			@note
			Almeriaで作成可能なSTMファイルからモデルデータの生成を行います。
		*/
		virtual Resource::STM::IModelController* CreateMap( const void* pData, Uint32 Size, const wchar_t* pFileName ) = 0;
		/**
			@brief テキスト生成
			@author 葉迩倭
			@param pData		[in] データのポインタ
			@param Size			[in] データのサイズ
			@param pFileName	[in] データ名
			@param Param		[in] テクスチャ生成用パラメーター
			@param pListener	[in] ファイル読み込みイベントリスナー
			@param pUserSetData	[in] リスナー受渡し用ユーザーポインター
			@note
			Liatrisで作成可能なSFFファイルからテキストデータの生成を行います。
		*/
		virtual Resource::Text::ITextData* CreateText( const void* pData, Uint32 Size, const wchar_t* pFileName, const STextureLoadParameter& Param, Resource::IFileLoadListener* pListener, void* pUserSetData = NULL ) = 0;
		/**
			@brief ローとモーションインターフェイス取得
			@author 葉迩倭
			@param pData		[in] データのポインタ
			@param Size			[in] データのサイズ
			@note
			ルートモーションデータをsafファイルから生成します。
		*/
		virtual Resource::IRootMotion* CreateRootMotion( const void* pData, Uint32 Size ) = 0;

		/**
			@brief プリミティブ生成
			@author 葉迩倭
			@param VertexCount	[in] 頂点数
			@param IndexCount	[in] 頂点インデックス数
			@param Param		[in] プリミティブ用パラメーター
			@note
			プログラム上で簡易なモデルデータの作成を行うためのインターフェイスです。<BR>
			SMFモデルと同じようにボーンやマテリアルが適用できます。
		*/
		virtual Resource::Primitive::IPrimitiveController* CreatePrimitive( Sint32 VertexCount, Sint32 IndexCount, const Resource::Primitive::SParameter& Param ) = 0;
		/**
			@brief 球形状プリミティブ生成
			@author 葉迩倭
			@param Size		[in] 球のサイズ（半径）
			@param Param	[in] プリミティブ用パラメーター
			@note
			Resource::Primitive::IPrimitiveControllerを利用して球形状のプリミティブを生成します。
		*/
		virtual Resource::Primitive::IPrimitiveController* CreatePrimitiveSphere( const Kernel::Math::Vector3& Size, const Resource::Primitive::SParameter& Param ) = 0;
		/**
			@brief 箱形状プリミティブ生成
			@author 葉迩倭
			@param Size		[in] 箱のサイズ（３辺）
			@param Param	[in] プリミティブ用パラメーター
			@note
			Resource::Primitive::IPrimitiveControllerを利用して箱形状のプリミティブを生成します。
		*/
		virtual Resource::Primitive::IPrimitiveController* CreatePrimitiveCube( const Kernel::Math::Vector3& Size, const Resource::Primitive::SParameter& Param ) = 0;
		/**
			@brief カプセル形状プリミティブ生成
			@author 葉迩倭
			@param Radius	[in] カプセルのサイズ（半径）
			@param Length	[in] カプセルの長さ
			@param Param	[in] プリミティブ用パラメーター
			@note
			Resource::Primitive::IPrimitiveControllerを利用してカプセル形状のプリミティブを生成します。
		*/
		virtual Resource::Primitive::IPrimitiveController* CreatePrimitiveCapsule( float Radius, float Length, const Resource::Primitive::SParameter& Param ) = 0;
		/**
			@brief 平面形状プリミティブ生成
			@author 葉迩倭
			@param Size		[in] 平面のサイズ（半径）
			@param Param	[in] プリミティブ用パラメーター
			@note
			Resource::Primitive::IPrimitiveControllerを利用して平面形状のプリミティブを生成します。
		*/
		virtual Resource::Primitive::IPrimitiveController* CreatePrimitivePlane( const Kernel::Math::Vector2& Size, const Resource::Primitive::SParameter& Param ) = 0;
		/**
			@brief 床形状プリミティブ生成
			@author 葉迩倭
			@param Size			[in] 床のサイズ（半径）
			@param CellCount	[in] 床のセル数
			@param Param		[in] プリミティブ用パラメーター
			@note
			Resource::Primitive::IPrimitiveControllerを利用して床形状のプリミティブを生成します。
		*/
		virtual Resource::Primitive::IPrimitiveController* CreatePrimitiveFloor( const Kernel::Math::Vector2& Size, Sint32 CellCount, const Resource::Primitive::SParameter& Param ) = 0;

		/**
			@brief パーティクル生成
			@author 葉迩倭
			@param Count	[in] パーティクル数
			@param Param	[in] パーティクル用パラメーター
			@note
			ビルボードにより表現されるパーティクルの生成を行います。<BR>
			単純なビルボードとしての運用もでき、ソフトパーティクル処理を行う事も出来ます。
		*/
		virtual Resource::Particle::IParticleController* CreateParticle( Sint32 Count, const Resource::Particle::SParameter& Param ) = 0;
		/**
			@brief パーティクル生成
			@author 葉迩倭
			@param Count	[in] パーティクル数
			@param Param	[in] パーティクル用パラメーター
			@note
			ビルボードにより表現されるパーティクルの生成を行います。<BR>
			単純なビルボードとしての運用もでき、ソフトパーティクル処理を行う事も出来ます。
		*/
		virtual Graphics::Resource::Particle::IVolumeParticleController* CreateVolumeParticle( Sint32 Count, const Graphics::Resource::Particle::SParameter& Param ) = 0;
		/**
			@brief パーティクル生成
			@author 葉迩倭
			@param Count	[in] パーティクル数
			@param Param	[in] パーティクル用パラメーター
			@note
			ビルボードにより表現されるパーティクルの生成を行います。<BR>
			単純なビルボードとしての運用もでき、ソフトパーティクル処理を行う事も出来ます。
		*/
		virtual Graphics::Resource::Particle::IEnhancedParticleController* CreateEnhancedParticle( Sint32 Count, const Graphics::Resource::Particle::SParameter& Param ) = 0;
		/**
			@brief スプライト生成
			@author 葉迩倭
			@param Count	[in] スプライト数
			@param Param	[in] スプライト用パラメーター
			@note
			3Dスプライトの生成を行います。<BR>
			3Dスプライトは四角系のみの描画を行う事ができます。
		*/
		virtual Resource::Sprite::ISpriteController* CreateSprite( Sint32 Count, const Resource::Sprite::SParameter& Param ) = 0;
		/**
			@brief ポリライン生成
			@author 葉迩倭
			@param VertexCount	[in] 頂点数
			@param IndexCount	[in] 頂点インデックス数
			@param Param		[in] ポリライン用パラメーター
			@note
			ポリゴンをつなげて太さをもったラインを表現する為のポリラインの生成を行います。
		*/
		virtual Resource::PolyLine::IPolyLineController* CreatePolyLine( Sint32 VertexCount, Sint32 IndexCount, const Resource::PolyLine::SParameter& Param ) = 0;
		/**
			@brief シェーダー定数バッファ生成
			@author 葉迩倭
			@param Size			[in] バッファのサイズ
			@param Line			[in] 生成したソースの行
			@param pSourceFile	[in] 生成したソースのファイル名
			@return IShaderインターフェイス
			@note
			シェーダー定数バッファインターフェイスを生成します。
		*/
		virtual Resource::IShaderConstantBuffer* D3D10_CreateShaderConstantBuffer( Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief シェーダー定数バッファ設定
			@author 葉迩倭
			@param Slot		[in] スロット
			@param pBuffer	[in] バッファ
			@note
			デバイスにシェーダー定数バッファをセットします。
		*/
		virtual void D3D10_SetVertexShaderConstantBuffer( Uint32 Slot, Resource::IShaderConstantBuffer* pBuffer ) = 0;
		/**
			@brief シェーダー定数バッファ設定
			@author 葉迩倭
			@param Slot		[in] スロット
			@param pBuffer	[in] バッファ
			@note
			デバイスにシェーダー定数バッファをセットします。
		*/
		virtual void D3D10_SetGeometryShaderConstantBuffer( Uint32 Slot, Resource::IShaderConstantBuffer* pBuffer ) = 0;
		/**
			@brief シェーダー定数バッファ設定
			@author 葉迩倭
			@param Slot		[in] スロット
			@param pBuffer	[in] バッファ
			@note
			デバイスにシェーダー定数バッファをセットします。
		*/
		virtual void D3D10_SetPixelShaderConstantBuffer( Uint32 Slot, Resource::IShaderConstantBuffer* pBuffer ) = 0;
		/**
			@brief テクスチャ設定
			@author 葉迩倭
			@param State	[in] ステージ
			@param pTexture	[in] テクスチャ
			@note
			デバイスにテクスチャをセットします。
		*/
		virtual void D3D10_SetShadowTexture( Uint32 Stage, Resource::ITexture* pTexture ) = 0;
		/**
			@brief テクスチャ設定
			@author 葉迩倭
			@param pTexture		[in] テクスチャ
			@note
			デバイスにテクスチャをセットします。
		*/
		virtual void D3D10_SetShadowRenderTarget( Resource::ITexture* pTexture ) = 0;
		/**
			@brief ジオメトリシェーダー生成
			@author 葉迩倭
			@param pBuffer			[in] リソースのバッファのポインタ
			@param Size				[in] リソースのサイズ
			@param Line				[in] 生成したソースの行
			@param pSourceFile		[in] 生成したソースのファイル名
			@return IShaderインターフェイス
			@note
			コンパイル済みジオメトリシェーダーからインターフェイスを生成します。
		*/
		virtual Resource::IGeometryShader* D3D10_CreateGeometryShader( const void* pBuffer, Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief ジオメトリシェーダー設定
			@author 葉迩倭
			@param pShader	[in] シェーダー
			@note
			デバイスにジオメトリシェーダーをセットします。
		*/
		virtual void D3D10_SetGeometryShader( Resource::IGeometryShader* pShader ) = 0;
		/**
			@brief シェーダー定数バッファ生成
			@author 葉迩倭
			@param Size			[in] バッファのサイズ
			@param Line			[in] 生成したソースの行
			@param pSourceFile	[in] 生成したソースのファイル名
			@return IShaderインターフェイス
			@note
			シェーダー定数バッファインターフェイスを生成します。
		*/
		virtual Resource::IShaderConstantBuffer* D3D11_CreateShaderConstantBuffer( Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief シェーダー定数バッファ設定
			@author 葉迩倭
			@param Slot		[in] スロット
			@param pBuffer	[in] バッファ
			@note
			デバイスにシェーダー定数バッファをセットします。
		*/
		virtual void D3D11_SetVertexShaderConstantBuffer( Uint32 Slot, Resource::IShaderConstantBuffer* pBuffer ) = 0;
		/**
			@brief シェーダー定数バッファ設定
			@author 葉迩倭
			@param Slot		[in] スロット
			@param pBuffer	[in] バッファ
			@note
			デバイスにシェーダー定数バッファをセットします。
		*/
		virtual void D3D11_SetGeometryShaderConstantBuffer( Uint32 Slot, Resource::IShaderConstantBuffer* pBuffer ) = 0;
		/**
			@brief シェーダー定数バッファ設定
			@author 葉迩倭
			@param Slot		[in] スロット
			@param pBuffer	[in] バッファ
			@note
			デバイスにシェーダー定数バッファをセットします。
		*/
		virtual void D3D11_SetPixelShaderConstantBuffer( Uint32 Slot, Resource::IShaderConstantBuffer* pBuffer ) = 0;
		/**
			@brief テクスチャ設定
			@author 葉迩倭
			@param State	[in] ステージ
			@param pTexture	[in] テクスチャ
			@note
			デバイスにテクスチャをセットします。
		*/
		virtual void D3D11_SetShadowTexture( Uint32 Stage, Resource::ITexture* pTexture ) = 0;
		/**
			@brief テクスチャ設定
			@author 葉迩倭
			@param pTexture		[in] テクスチャ
			@note
			デバイスにテクスチャをセットします。
		*/
		virtual void D3D11_SetShadowRenderTarget( Resource::ITexture* pTexture ) = 0;
		/**
			@brief ジオメトリシェーダー生成
			@author 葉迩倭
			@param pBuffer			[in] リソースのバッファのポインタ
			@param Size				[in] リソースのサイズ
			@param Line				[in] 生成したソースの行
			@param pSourceFile		[in] 生成したソースのファイル名
			@return IShaderインターフェイス
			@note
			コンパイル済みジオメトリシェーダーからインターフェイスを生成します。
		*/
		virtual Resource::IGeometryShader* D3D11_CreateGeometryShader( const void* pBuffer, Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief ジオメトリシェーダー設定
			@author 葉迩倭
			@param pShader	[in] シェーダー
			@note
			デバイスにジオメトリシェーダーをセットします。
		*/
		virtual void D3D11_SetGeometryShader( Resource::IGeometryShader* pShader ) = 0;
		/**
			@brief 頂点シェーダー定数設定
			@author 葉迩倭
			@param Register		[in] レジスタ番号
			@param pVector		[in] ベクトル
			@param Count		[in] ベクトル数
			@note
			デバイスに頂点シェーダー用定数をセットします。
		*/
		virtual void D3D9_SetVertexShaderConstant( Uint32 Register, const Kernel::Math::VectorS* pVector, Uint32 Count ) = 0;
		/**
			@brief ピクセルシェーダー定数設定
			@author 葉迩倭
			@param Register		[in] レジスタ番号
			@param pVector		[in] ベクトル
			@param Count		[in] ベクトル数
			@note
			デバイスにピクセルシェーダー用定数をセットします。
		*/
		virtual void D3D9_SetPixelShaderConstant( Uint32 Register, const Kernel::Math::VectorS* pVector, Uint32 Count ) = 0;
		/**
			@brief 固定グラフィックスパイプラインモード
			@author 葉迩倭
			@param IsEnable		[in] ON/OFF
			@param IsFogEnable	[in] フォグのON/OFF
			@param FogColor		[in] フォグ色
			@note
			DirectX9でのみ利用可能な固定パイプラインモードの設定をします。
		*/
		virtual void D3D9_SetFixedRenderingPiplineMode( bool IsEnable, bool IsFogEnable, const Kernel::Math::VectorS& FogColor ) = 0;
	};
}
}
}

/**
	@file
	@brief タスク制御
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Task
{
	enum eTaskPass
	{
		TaskPass_Main,
		TaskPass_Post,
		TaskPass_Max,
	};

	typedef Kernel::Delegate01<Sint64> TaskExecutor;

	class TaskQueue
	{
	private:
		mutable TaskExecutor	m_Execute;

	public:
		TaskQueue()
		{
		}

		TaskQueue( const TaskExecutor& Execute )
			: m_Execute	( Execute )
		{
		}

		void Set( const TaskExecutor& Execute )
		{
			m_Execute = Execute;
		}

		void Execute( Sint64 DeltaTime ) const
		{
			m_Execute( DeltaTime );
		}
	};

	class ITaskManager
		: public Interface
	{
	public:
		virtual void Clear() = 0;
		virtual void SetProfileEnable( bool IsProfile ) = 0;
		virtual void Start() = 0;
		virtual void End() = 0;
		virtual void PushMasterTask( eTaskPass TaskPass, const TaskQueue& Que, const ColorF& Color ) = 0;
		virtual void PushSlaveTask( eTaskPass TaskPass, const TaskQueue& Que, const ColorF& Color ) = 0;
		virtual void PushSlaveTaskBarrier( eTaskPass TaskPass ) = 0;
		virtual void Execute( Sint64 DeltaTime ) = 0;
		virtual Sint32 GetMaxTaskCount() = 0;
		virtual void DrawTaskExecuteTime( Engine::Graphics::Simple::ISpriteRenderer* pSprite ) = 0;
	};
}
}
}


/**
	@file
	@brief コントロール基底インターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	enum eControlType
	{
		CONTROL_TYPE_DESKTOP,
		CONTROL_TYPE_DIALOG,
		CONTROL_TYPE_WINDOW,
		CONTROL_TYPE_WINDOW_IME,
		CONTROL_TYPE_MENUBAR,
		CONTROL_TYPE_MENUBAR_BUTTON,
		CONTROL_TYPE_MENUBAR_LIST,
		CONTROL_TYPE_SCROLLBAR,
		CONTROL_TYPE_BUTTON,
		CONTROL_TYPE_LISTBOX,
		CONTROL_TYPE_COMBOBOX,
		CONTROL_TYPE_SLIDERBAR,
		CONTROL_TYPE_PROGRESSBAR,
		CONTROL_TYPE_LABEL,
		CONTROL_TYPE_GROUPBOX,
		CONTROL_TYPE_CHECKBOX,
		CONTROL_TYPE_EDITBOX,
		CONTROL_TYPE_TEXTBOX,
	};

	enum eTextAlign
	{
		TEXT_ALIGN_LEFT,
		TEXT_ALIGN_CENTER,
		TEXT_ALIGN_RIGHT,
	};

	enum eControlEdge
	{
		CONTROL_EDGE_NONE,
		CONTROL_EDGE_LINE,
	};

	enum eImeCursorAttribute
	{
		ICA_INPUT,					// 選択されていなく、変換されていない文字。 
		ICA_TARGET_CONVERTED,		// 選択されていて、変換されている文字。 
		ICA_CONVERTED,				// 選択されてなく、変換されている文字。 
		ICA_TARGET_NOTCONVERTED,	// 選択されていて、変換されていない文字。 
		ICA_INPUT_ERROR,			// 無効な文字。 
	};

	enum eControlShapeType
	{
		CONTROL_TYPE_HORIZONTAL,
		CONTROL_TYPE_VERTICAL,
		CONTROL_TYPE_MAX,
	};

	struct DrawArgs
	{
		bool IsForcus;
		bool IsForcusParentWindow;
		bool IsMouseHover;
		bool IsMouseDown;
		Sint32 MouseHoverTime;
		RectI ScissorRect;
		RectI ClientRect;
		RectI ClientDrawRect;
		eControlEdge Edge;
	};

	typedef Kernel::Delegate02<IControl*,const DrawArgs&>	OwnerDrawEvent;
	typedef Kernel::Delegate01<IControl*>					OwnerDeleteEvent;

	class IControl
		: public Interface
	{
	protected:
		virtual ~IControl(){}

	public:
		virtual bool IsShow() = 0;
		virtual void Show() = 0;
		virtual void Hide() = 0;

		virtual void SetControlEdge( eControlEdge Edge ) = 0;

		virtual void SetOwnerDrawEvent( const OwnerDrawEvent& Event ) = 0;
		virtual void SetOwnerDeleteEvent( const OwnerDeleteEvent& Event ) = 0;

		virtual eControlType GetType() const = 0;

		virtual void* GetUserData() = 0;
		virtual void SetUserData( void* pData ) = 0;

		virtual void SetID( Uint32 Id ) = 0;
		virtual Uint32 GetID() const = 0;

		virtual void SetName( const wchar_t* pName ) = 0;
		virtual const wchar_t* GetName() const = 0;

		virtual void SetDockType( bool IsTop, bool IsBottom, bool IsLeft, bool IsRight ) = 0;
		virtual void SetMargin( Sint32 Size ) = 0;
		virtual void SetPosition( const Point2DI& Position ) = 0;
		virtual void SetSize( const Point2DI& Size ) = 0;
		virtual void SetMinSize( const Point2DI& Size ) = 0;
		virtual void SetMaxSize( const Point2DI& Size ) = 0;
	};
}
}
}
}

/**
	@file
	@brief IMEインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct ImeDrawArgs
		: public DrawArgs
	{
		const wchar_t** ppCandidateList;
		const RectI* pCandidateRect;
		Sint32 CandidateListCount;
		Sint32 SelectCandidateIndex;

		RectI L_EdgeRect;
		RectI R_EdgeRect;
		RectI T_EdgeRect;
		RectI B_EdgeRect;
		RectI LT_CornerRect;
		RectI LB_CornerRect;
		RectI RT_CornerRect;
		RectI RB_CornerRect;
	};

	class IIme
		: public IControl
	{
	protected:
		virtual ~IIme(){}

	public:
		virtual void SetPositionAuto( const Point2DI& Position ) = 0;
	};
}
}
}
}

/**
	@file
	@brief エディットボックスインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct EditBoxDrawArgs
		: public DrawArgs
	{
		const wchar_t** ppText;
		const Point2DI* pPosition;
		Sint32 LineMax;
		Sint32 ActiveLine;
		Sint32 ActiveCursor;
		bool IsReadOnly;
		const wchar_t* pImeConvertText;
		const Sint32* pImeConvertCursor;
		const eImeCursorAttribute* pImeConvertTextAttribute;
		Sint32 ImeConvertCursorCount;
	};

	typedef Kernel::Delegate01<IControl*> EditBoxCopyEvent;
	typedef Kernel::Delegate01<IControl*> EditBoxPasteEvent;
	typedef Kernel::Delegate01<IControl*> EditBoxPressEnterEvent;
	typedef Kernel::Delegate03<IControl*,const wchar_t*,Sint32&> EditBoxGetStringLengthEvent;

	class IEditBox
		: public IControl
	{
	protected:
		virtual ~IEditBox(){}

	public:
		virtual void SetCopyEvent( const EditBoxCopyEvent& Event ) = 0;
		virtual void SetPasteEvent( const EditBoxPasteEvent& Event ) = 0;
		virtual void SetPressEnterEvent( const EditBoxPressEnterEvent& Event ) = 0;
		virtual void SetGetStringLengthEvent( const EditBoxGetStringLengthEvent& Event ) = 0;

		virtual void ClearText() = 0;
		virtual void AddText( const wchar_t* pText ) = 0;
		virtual void InsertText( const wchar_t* pText ) = 0;
		virtual void SetText( const wchar_t* pText ) = 0;
		virtual Sint32 GetText( wchar_t* pText, Sint32 Length ) const = 0;

		virtual IScrollBar* GetScrollBar() = 0;
	};
}
}
}
}

/**
	@file
	@brief テキストボックスインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	enum eTextBoxInputType
	{
		TB_INPUT_TYPE_READ_ONLY,
		TB_INPUT_TYPE_NUMBER_ONLY,
		TB_INPUT_TYPE_ASCII_ONLY,
		TB_INPUT_TYPE_ALL,
	};

	struct TextBoxDrawArgs
		: public DrawArgs
	{
		const wchar_t* pText;
		Sint32 ActiveCursor;
		bool IsReadOnly;
		Sint32 OffsetPosition;
		const wchar_t* pImeConvertText;
		const Sint32* pImeConvertCursor;
		const eImeCursorAttribute* pImeConvertTextAttribute;
		Sint32 ImeConvertCursorCount;
	};

	typedef Kernel::Delegate01<IControl*> TextBoxCopyEvent;
	typedef Kernel::Delegate01<IControl*> TextBoxPasteEvent;
	typedef Kernel::Delegate01<IControl*> TextBoxPressEnterEvent;
	typedef Kernel::Delegate03<IControl*,const wchar_t*,Sint32&> TextBoxGetStringLengthEvent;

	class ITextBox
		: public IControl
	{
	protected:
		virtual ~ITextBox(){}

	public:
		virtual void SetCopyEvent( const TextBoxCopyEvent& Event ) = 0;
		virtual void SetPasteEvent( const TextBoxPasteEvent& Event ) = 0;
		virtual void SetPressEnterEvent( const TextBoxPressEnterEvent& Event ) = 0;
		virtual void SetGetStringLengthEvent( const TextBoxGetStringLengthEvent& Event ) = 0;

		virtual void InsertText( const wchar_t* pText ) = 0;
		virtual void SetText( const wchar_t* pText ) = 0;
		virtual Sint32 GetText( wchar_t* pText, Sint32 Length ) const = 0;
	};
}
}
}
}

/**
	@file
	@brief スクロールバーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct ScrollBarDrawArgsData
	{
		bool IsEnable;
		bool IsOver[2];
		RectI Client;
		RectI HandleRect;
		RectI ButtonRect[2];
	};

	struct ScrollBarDrawArgs
		: public DrawArgs
	{
		ScrollBarDrawArgsData DataH;
		ScrollBarDrawArgsData DataV;
	};

	typedef Kernel::Delegate03<IControl*,Sint32,Sint32> ScrollBarChangeEvent;

	class IScrollBar
		: public IControl
	{
	protected:
		virtual ~IScrollBar(){}

	public:
		virtual void SetScrollBarChangeEvent( const ScrollBarChangeEvent& ScrollBarChange ) = 0;
	};
}
}
}
}

/**
	@file
	@brief スライダーバーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct SliderBarDrawArgs
		: public DrawArgs
	{
		eControlShapeType Type;
		float MinValue;
		float MaxValue;
		float Value;
		RectI HandleRect;
		RectI RulerRect;
	};

	typedef Kernel::Delegate03<IControl*,float,float> SliderBarChangeEvent;

	class ISliderBar
		: public IControl
	{
	protected:
		virtual ~ISliderBar(){}

	public:
		virtual void SetSliderBarChangeEvent( const SliderBarChangeEvent& Event ) = 0;

		virtual float GetMinValue() const = 0;
		virtual float GetMaxValue() const = 0;
		virtual float GetValue() const = 0;

		virtual void SetMinValue( float Value ) = 0;
		virtual void SetMaxValue( float Value ) = 0;
		virtual void SetValue( float Value ) = 0;
	};
}
}
}
}

/**
	@file
	@brief プログレスバーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct ProgressBarDrawArgs
		: public DrawArgs
	{
		eControlShapeType Type;
		RectI ProgressRect;
		float Rate;
	};

	class IProgressBar
		: public IControl
	{
	protected:
		virtual ~IProgressBar(){}

	public:
		virtual Sint32 GetMaxValue() const = 0;
		virtual Sint32 GetValue() const = 0;

		virtual void SetMaxValue( Sint32 Value ) = 0;
		virtual void SetValue( Sint32 Value ) = 0;
	};
}
}
}
}

/**
	@file
	@brief チェックボックスインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct CheckBoxDrawArgs
		: public DrawArgs
	{
		eTextAlign TextAlign;
		const wchar_t* pText;
		bool IsCheck;
	};

	typedef Kernel::Delegate02<IControl*,bool> CheckBoxChangeEvent;

	class ICheckBox
		: public IControl
	{
	protected:
		virtual ~ICheckBox(){}

	public:
		virtual void SetCheckBoxChangeEvent( const CheckBoxChangeEvent& Event ) = 0;

		virtual void SetTextAlign( eTextAlign TextAlign ) = 0;

		virtual void SetText( const wchar_t* pText ) = 0;
		virtual void GetText( wchar_t* pText, Sint32 Length ) const = 0;

		virtual void SetChecked( bool IsCheck ) = 0;
		virtual bool GetChecked() const = 0;
	};
}
}
}
}

/**
	@file
	@brief ボタンインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct ButtonDrawArgs
		: public DrawArgs
	{
		eTextAlign TextAlign;
		const wchar_t* pText;
	};

	typedef Kernel::Delegate01<IControl*> ButtonPushEvent;

	class IButton
		: public IControl
	{
	protected:
		virtual ~IButton(){}

	public:
		virtual void SetButtonPushEvent( const ButtonPushEvent& Event ) = 0;

		virtual void SetTextAlign( eTextAlign TextAlign ) = 0;

		virtual void SetText( const wchar_t* pText ) = 0;
		virtual Sint32 GetText( wchar_t* pText, Sint32 Length ) const = 0;
	};
}
}
}
}

/**
	@file
	@brief ラベルインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct LabelDrawArgs
		: public DrawArgs
	{
		eTextAlign TextAlign;
		const wchar_t* pText;
	};

	class ILabel
		: public IControl
	{
	protected:
		virtual ~ILabel(){}

	public:
		virtual void SetTextAlign( eTextAlign TextAlign ) = 0;

		virtual void SetText( const wchar_t* pText ) = 0;
		virtual void GetText( wchar_t* pText, Sint32 Length ) const = 0;
		virtual void SetFloat( float Value ) = 0;
		virtual float GetFloat() const = 0;
		virtual void SetInt( Sint32 Value ) = 0;
		virtual Sint32 GetInt() const = 0;
	};
}
}
}
}

/**
	@file
	@brief グループボックスインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct GroupBoxDrawArgs
		: public DrawArgs
	{
		const wchar_t* pText;
		RectI TitleRect;
	};

	class IGroupBox
		: public IControl
	{
	protected:
		virtual ~IGroupBox(){}

	public:
		virtual void SetText( const wchar_t* pText ) = 0;
		virtual void GetText( wchar_t* pText, Sint32 Length ) const = 0;

		virtual IButton* AddButton( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size ) = 0;
		virtual ICheckBox* AddCheckBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsChecked ) = 0;
		virtual ILabel* AddLabel( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size ) = 0;
		virtual IGroupBox* AddGroupBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight ) = 0;
		virtual IEditBox* AddEditBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsReadOnly, bool IsMultiLine, Sint32 LineHeight ) = 0;
		virtual ISliderBar* AddSliderBar( const Point2DI& Position, const Point2DI& Size, eControlShapeType Type, Sint32 HandleSize ) = 0;
		virtual IProgressBar* AddProgressBar( const Point2DI& Position, const Point2DI& Size, eControlShapeType Type ) = 0;
		virtual IListBox* AddListBox( const Point2DI& Position, const Point2DI& Size, Sint32 ItemHeight, bool IsSort ) = 0;
		virtual IComboBox* AddComboBox( const Point2DI& Position, Sint32 Width, Sint32 ItemHeight, Sint32 DropDownListHeight, bool IsSort ) = 0;
		virtual ITextBox* AddTextBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, eTextBoxInputType InputType ) = 0;
	};
}
}
}
}

/**
	@file
	@brief リストボックスインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct ListBoxDrawArgs
		: public DrawArgs
	{
		Sint32 SelectItem;
		Sint32 MouseHoverItem;
		Sint32 ItemCount;
		RectI* pItemRect;
		const wchar_t** ppItemText;
	};

	typedef Kernel::Delegate03<IControl*,const wchar_t*,Kernel::Object::ReferenceObject*> ListBoxSelectEvent;
	typedef Kernel::Delegate03<IControl*,const wchar_t*,Sint32&> ListBoxGetStringLengthEvent;

	class IListBox
		: public IControl
	{
	protected:
		virtual ~IListBox(){}

	public:
		virtual void SetSelectEvent( const ListBoxSelectEvent& Event ) = 0;
		virtual void SetGetStringLengthEvent( const ListBoxGetStringLengthEvent& Event ) = 0;

		virtual Sint32 AddItem( const wchar_t* pText, Kernel::Object::ReferenceObject* pObject ) = 0;
		virtual void SubItem( const wchar_t* pText, Kernel::Object::ReferenceObject* pObject ) = 0;
		virtual void SubItem( Sint32 Index ) = 0;

		virtual Sint32 GetSelectItem( wchar_t* pText, Sint32 TextSize, Kernel::Object::ReferenceObject*& pObject ) const = 0;
		virtual void SetSelectItem( Sint32 Index ) = 0;
		virtual void SetSelectItem( wchar_t* pText ) = 0;

		virtual IScrollBar* GetScrollBar() = 0;
	};
}
}
}
}

/**
	@file
	@brief コンボボックスインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct ComboBoxDrawArgs
		: public DrawArgs
	{
		const wchar_t* pText;
		RectI ButtonRect;
		RectI DropDownListRect;
		RectI DropDownListDrawRect;
		Sint32 DropDownSelectItem;
		Sint32 DropDownItemCount;
		RectI* pDropDownItemRect;
		const wchar_t** ppDropDownItemText;
		bool IsDropDownOpen;
	};

	typedef Kernel::Delegate03<IControl*,const wchar_t*,Kernel::Object::ReferenceObject*> ComboBoxSelectEvent;
	typedef Kernel::Delegate03<IControl*,const wchar_t*,Sint32&> ComboBoxGetStringLengthEvent;

	class IComboBox
		: public IControl
	{
	protected:
		virtual ~IComboBox(){}

	public:
		virtual void SetSelectEvent( const ComboBoxSelectEvent& Event ) = 0;
		virtual void SetGetStringLengthEvent( const ComboBoxGetStringLengthEvent& Event ) = 0;

		virtual void AddItem( const wchar_t* pText, Kernel::Object::ReferenceObject* pObject ) = 0;
		virtual void SubItem( const wchar_t* pText, Kernel::Object::ReferenceObject* pObject ) = 0;
		virtual void SubItem( Sint32 Index ) = 0;

		virtual Sint32 GetSelectItem( const wchar_t* pText, Sint32 Length, Kernel::Object::ReferenceObject*& pObject ) const = 0;
		virtual void SetSelectItem( Sint32 Index ) = 0;

		virtual IScrollBar* GetScrollBar() = 0;
	};
}
}
}
}

/**
	@file
	@brief メニューボタンインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct MenuButtonDrawArgs
		: public DrawArgs
	{
		eTextAlign TextAlign;
		const wchar_t* pText;
		bool IsPopupMenu;
		bool IsCheckBox;
		bool IsChecked;
	};

	class IMenuButton
		: public IControl
	{
	protected:
		virtual ~IMenuButton(){}

	public:
		virtual void SetText( const wchar_t* pText ) = 0;
		virtual Sint32 GetText( wchar_t* pText, Sint32 Length ) const = 0;

		virtual void SetChecked( bool IsChecked ) = 0;
		virtual bool GetChecked() const = 0;
	};
}
}
}
}

/**
	@file
	@brief スライダーバーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	typedef Kernel::Delegate01<IControl*> MenuClickEvent;

	struct SMenuItem
	{
		wchar_t Text[64];
		Uint32 ID;
		bool IsCheckBox;
		bool IsChecked;
		MenuClickEvent Event;
	};

	struct MenuBarDrawArgs
		: public DrawArgs
	{
	};

	typedef Kernel::Delegate03<IControl*,const wchar_t*,Sint32&> MenuBarGetStringLengthEvent;

	class IMenuBar
		: public IControl
	{
	protected:
		virtual ~IMenuBar(){}

	public:
		virtual void SetGetStringLengthEvent( const MenuBarGetStringLengthEvent& Event ) = 0;
		virtual IMenuButton* SearchMenuButtonByID( Uint32 TargetID ) = 0;
		virtual bool AppendRootMenu( const SMenuItem& Item ) = 0;
		virtual bool AppendSubMenu( Uint32 TargetID, const SMenuItem& Item ) = 0;
		virtual bool DeleteMenu( Uint32 TargetID ) = 0;
	};
}
}
}
}

/**
	@file
	@brief ウィンドウインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct WindowDrawArgs
		: public DrawArgs
	{
		const wchar_t* pTitle;
		bool IsMouseOnWindow;
		RectI TitleBarRect;
		RectI CloseButtonRect;
		RectI L_EdgeRect;
		RectI R_EdgeRect;
		RectI T_EdgeRect;
		RectI B_EdgeRect;
		RectI LT_CornerRect;
		RectI LB_CornerRect;
		RectI RT_CornerRect;
		RectI RB_CornerRect;
	};

	typedef Kernel::Delegate02<IControl*,bool&> WindowCloseEvent;

	class IWindow
		: public IControl
	{
	protected:
		virtual ~IWindow(){}

	public:
		virtual void SetTitle( const wchar_t* pTitle ) = 0;
		virtual void GetTitle( wchar_t* pTitle, Sint32 Length ) const = 0;
		virtual void SetCloseEvent( const WindowCloseEvent& Event ) = 0;

		virtual IButton* AddButton( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size ) = 0;
		virtual ICheckBox* AddCheckBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsChecked ) = 0;
		virtual ILabel* AddLabel( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size ) = 0;
		virtual IGroupBox* AddGroupBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight ) = 0;
		virtual IEditBox* AddEditBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsReadOnly, bool IsMultiLine, Sint32 LineHeight ) = 0;
		virtual ISliderBar* AddSliderBar( const Point2DI& Position, const Point2DI& Size, eControlShapeType Type, Sint32 HandleSize ) = 0;
		virtual IProgressBar* AddProgressBar( const Point2DI& Position, const Point2DI& Size, eControlShapeType Type ) = 0;
		virtual IListBox* AddListBox( const Point2DI& Position, const Point2DI& Size, Sint32 ItemHeight, bool IsSort ) = 0;
		virtual IComboBox* AddComboBox( const Point2DI& Position, Sint32 Width, Sint32 ItemHeight, Sint32 DropDownListHeight, bool IsSort ) = 0;
		virtual ITextBox* AddTextBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, eTextBoxInputType InputType ) = 0;
	};
}
}
}
}

/**
	@file
	@brief ダイアログインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct DialogDrawArgs
		: public DrawArgs
	{
		const wchar_t* pTitle;
		Sint32 BlinkTime;
		RectI TitleBarRect;
		RectI CloseButtonRect;
		RectI L_EdgeRect;
		RectI R_EdgeRect;
		RectI T_EdgeRect;
		RectI B_EdgeRect;
		RectI LT_CornerRect;
		RectI LB_CornerRect;
		RectI RT_CornerRect;
		RectI RB_CornerRect;
	};

	typedef Kernel::Delegate02<IControl*,bool&> DialogCloseEvent;

	class IDialog
		: public IControl
	{
	protected:
		virtual ~IDialog(){}

	public:
		virtual void SetTitle( const wchar_t* pTitle ) = 0;
		virtual void GetTitle( wchar_t* pTitle, Sint32 Length ) const = 0;
		virtual void Close() = 0;

		virtual IButton* AddButton( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size ) = 0;
		virtual ICheckBox* AddCheckBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsChecked ) = 0;
		virtual ILabel* AddLabel( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size ) = 0;
		virtual IGroupBox* AddGroupBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight ) = 0;
		virtual IEditBox* AddEditBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsReadOnly, bool IsMultiLine, Sint32 LineHeight ) = 0;
		virtual ISliderBar* AddSliderBar( const Point2DI& Position, const Point2DI& Size, eControlShapeType Type, Sint32 HandleSize ) = 0;
		virtual IProgressBar* AddProgressBar( const Point2DI& Position, const Point2DI& Size, eControlShapeType Type ) = 0;
		virtual IListBox* AddListBox( const Point2DI& Position, const Point2DI& Size, Sint32 ItemHeight, bool IsSort ) = 0;
		virtual IComboBox* AddComboBox( const Point2DI& Position, Sint32 Width, Sint32 ItemHeight, Sint32 DropDownListHeight, bool IsSort ) = 0;
		virtual ITextBox* AddTextBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, eTextBoxInputType InputType ) = 0;
	};
}
}
}
}

/**
	@file
	@brief GUIマネージャーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
	enum eMouseCursorState
	{
		MCS_NORMAL,
		MCS_BEAM,
		MCS_DRAG,
		MCS_ARROW_L_R,
		MCS_ARROW_T_B,
		MCS_ARROW_LT_RB,
		MCS_ARROW_LB_RT,
	};

	enum eEventMessage
	{
		EM_NULL,

		EM_MOUSE_L_DOWN,
		EM_MOUSE_R_DOWN,
		EM_MOUSE_M_DOWN,
		EM_MOUSE_L_UP,
		EM_MOUSE_R_UP,
		EM_MOUSE_M_UP,
		EM_MOUSE_L_DOUBLE_CLICK,
		EM_MOUSE_R_DOUBLE_CLICK,
		EM_MOUSE_M_DOUBLE_CLICK,
		EM_MOUSE_MOVE,

		EM_FORCUS_BEGIN,
		EM_FORCUS_KEY_DOWN,
		EM_FORCUS_KEY_UP,
		EM_FORCUS_CHAR,
		EM_FORCUS_END,

		EM_IME_BEGIN,
		EM_IME_COMPOSITION_START,
		EM_IME_COMPOSITION_END,
		EM_IME_COMPOSITION,
		EM_IME_CANDIDATE_OPEN,
		EM_IME_CANDIDATE_CLOSE,
		EM_IME_CANDIDATE_UPDATE,
		EM_IME_END,
	};

	struct EventArgs
	{
	};

	struct MouseEventArgs
		: public EventArgs
	{
		bool IsAlt;
		bool IsShift;
		bool IsControl;
		bool IsLButton;
		bool IsRButton;
		bool IsMButton;
		Point2DI Position;
	};

	struct MouseMoveEventArgs
		: public MouseEventArgs
	{
		Point2DI Move;
	};

	struct KeyEventArgs
		: public EventArgs
	{
		bool IsAlt;
		bool IsShift;
		bool IsControl;
		Uint64 VirtualKey;
	};

	struct CharEventArgs
		: public EventArgs
	{
		wchar_t Chara;
	};

	struct ImeEventArgs
		: public EventArgs
	{
		bool IsCOMPATTR;			///< 編集文字列のアトリビュートが取得された、または最新化された 
		bool IsCOMPCLAUSE;			///< 編集文字列の文節情報が取得された、または最新化された 
		bool IsCOMPREADATTR;		///< 現在の編集のリーディング文字列が取得された、または最新化された 
		bool IsCOMPREADCLAUSE;		///< 編集文字列のリーディング文字列の文節情報が取得された、または最新化された 
		bool IsCOMPREADSTR;			///< 現在の編集のリーディング文字列が取得された、または最新化された 
		bool IsCOMPSTR;				///< 現在の編集文字列が取得された、または最新化された 
		bool IsCURSORPOS;			///< 編集文字列のカーソル位置が取得した、または最新化された 
		bool IsDELTASTART;			///< 編集文字列の変化の開始位置が取得された、または最新化された 
		bool IsRESULTCLAUSE;		///< 確定文字列の文節情報が取得された、または最新化された 
		bool IsRESULTREADCLAUSE;	///< リーディング文字列の文節情報が取得された、または最新化された 
		bool IsRESULTREADSTR;		///< リーディング文字列を取得した、または最新化された 
		bool IsRESULTSTR;			///< 確定文字列が取得された、または最新化された
	};

	typedef Kernel::Delegate01<const MouseMoveEventArgs&> DesktopMouseDragEvent;
	typedef Kernel::Delegate01<const MouseMoveEventArgs&> DesktopMouseMoveEvent;
	typedef Kernel::Delegate01<const MouseEventArgs&> DesktopMouseDownEvent;
	typedef Kernel::Delegate01<const MouseEventArgs&> DesktopMouseUpEvent;
	typedef Kernel::Delegate01<const eMouseCursorState&> MouseCursorSettingEvent;

	/**
		@brief GUI管理クラス
		@author 葉迩倭

		GUIの処理を行うためのインターフェイスです。
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		virtual bool OnEvent( eEventMessage Message, const EventArgs& Args ) = 0;
		virtual bool EventByWindowMessage( Uint32 Message, Uint64 wParam, Uint64 lParam ) = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

		virtual const wchar_t* GetActiveControlName() const = 0;
		virtual Uint32 GetActiveControlID() const = 0;
		virtual const wchar_t* GetForcusWindowName() const = 0;
		virtual Uint32 GetForcusWindowID() const = 0;

		virtual bool IsForcusDesktop() = 0;
		virtual void CreateMenuBar( Sint32 TextHeight, bool IsAutoErase ) = 0;
		virtual Control::IMenuBar* GetMenuBar() = 0;
		virtual void CreateIME( Sint32 WindowWidth, Sint32 EdgeSize, Sint32 ItemHeight, Sint32 PageItemCount ) = 0;
		virtual Control::IIme* GetIME() = 0;
		virtual Control::IDialog* OpenDialog( const wchar_t* pTitleName, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Sint32 EdgeSize, bool IsFixed ) = 0;
		virtual Control::IWindow* AddWindow( const wchar_t* pTitleName, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Sint32 EdgeSize, bool IsFixed ) = 0;

		virtual void SetDesktopMouseDragEvent( const DesktopMouseDragEvent& Event ) = 0;
		virtual void SetDesktopMouseDownEvent( const DesktopMouseDownEvent& Event ) = 0;
		virtual void SetDesktopMouseUpEvent( const DesktopMouseUpEvent& Event ) = 0;
		virtual void SetDesktopMouseMoveEvent( const DesktopMouseMoveEvent& Event ) = 0;
		virtual void SetMouseCursorSettingEvent( const MouseCursorSettingEvent& Event ) = 0;
	};
}
}
}

/**
	@file
	@brief GUIマネージャーインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
	/**
		@brief GUI管理クラス
		@author 葉迩倭

		GUIの処理を行うためのインターフェイスです。
	*/
	class IHelper
		: public Interface
	{
	protected:
		virtual ~IHelper(){}

	public:
		virtual void CreateMenuBar( Sint32 TextHeight, bool IsAutoErase ) = 0;
		virtual Engine::GUI::Control::IMenuBar* GetMenuBar() = 0;

		virtual Engine::GUI::Control::IControl* GetControlByID( Uint32 ControlId ) = 0;
		virtual void DeleteControlByID( Uint32 ControlId ) = 0;

		virtual Engine::GUI::Control::IDialog* OpenDialog( const wchar_t* pTitleName, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Sint32 EdgeSize, bool IsFixed, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IWindow* AddWindow( const wchar_t* pTitleName, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Sint32 EdgeSize, bool IsFixed, Uint32 ControlId ) = 0;

		virtual Engine::GUI::Control::IButton* AddButton( Engine::GUI::Control::IWindow* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ICheckBox* AddCheckBox( Engine::GUI::Control::IWindow* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsChecked, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ILabel* AddLabel( Engine::GUI::Control::IWindow* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IGroupBox* AddGroupBox( Engine::GUI::Control::IWindow* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IEditBox* AddEditBox( Engine::GUI::Control::IWindow* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsReadOnly, bool IsMultiLine, Sint32 LineHeight, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ISliderBar* AddSliderBar( Engine::GUI::Control::IWindow* pTarget, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eControlShapeType Type, Sint32 HandleSize, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IProgressBar* AddProgressBar( Engine::GUI::Control::IWindow* pTarget, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eControlShapeType Type, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IListBox* AddListBox( Engine::GUI::Control::IWindow* pTarget, const Point2DI& Position, const Point2DI& Size, Sint32 ItemHeight, bool IsSort, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IComboBox* AddComboBox( Engine::GUI::Control::IWindow* pTarget, const Point2DI& Position, Sint32 Width, Sint32 ItemHeight, Sint32 DropDownListHeight, bool IsSort, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ITextBox* AddTextBox( Engine::GUI::Control::IWindow* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eTextBoxInputType InputType, Uint32 ControlId ) = 0;

		virtual Engine::GUI::Control::IButton* AddButton( Engine::GUI::Control::IGroupBox* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ICheckBox* AddCheckBox( Engine::GUI::Control::IGroupBox* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsChecked, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ILabel* AddLabel( Engine::GUI::Control::IGroupBox* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IGroupBox* AddGroupBox( Engine::GUI::Control::IGroupBox* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IEditBox* AddEditBox( Engine::GUI::Control::IGroupBox* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsReadOnly, bool IsMultiLine, Sint32 LineHeight, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ISliderBar* AddSliderBar( Engine::GUI::Control::IGroupBox* pTarget, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eControlShapeType Type, Sint32 HandleSize, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IProgressBar* AddProgressBar( Engine::GUI::Control::IGroupBox* pTarget, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eControlShapeType Type, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IListBox* AddListBox( Engine::GUI::Control::IGroupBox* pTarget, const Point2DI& Position, const Point2DI& Size, Sint32 ItemHeight, bool IsSort, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IComboBox* AddComboBox( Engine::GUI::Control::IGroupBox* pTarget, const Point2DI& Position, Sint32 Width, Sint32 ItemHeight, Sint32 DropDownListHeight, bool IsSort, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ITextBox* AddTextBox( Engine::GUI::Control::IGroupBox* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eTextBoxInputType InputType, Uint32 ControlId ) = 0;

		virtual Engine::GUI::Control::IButton* AddButton( Engine::GUI::Control::IDialog* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ICheckBox* AddCheckBox( Engine::GUI::Control::IDialog* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsChecked, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ILabel* AddLabel( Engine::GUI::Control::IDialog* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IGroupBox* AddGroupBox( Engine::GUI::Control::IDialog* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IEditBox* AddEditBox( Engine::GUI::Control::IDialog* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsReadOnly, bool IsMultiLine, Sint32 LineHeight, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ISliderBar* AddSliderBar( Engine::GUI::Control::IDialog* pTarget, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eControlShapeType Type, Sint32 HandleSize, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IProgressBar* AddProgressBar( Engine::GUI::Control::IDialog* pTarget, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eControlShapeType Type, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IListBox* AddListBox( Engine::GUI::Control::IDialog* pTarget, const Point2DI& Position, const Point2DI& Size, Sint32 ItemHeight, bool IsSort, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IComboBox* AddComboBox( Engine::GUI::Control::IDialog* pTarget, const Point2DI& Position, Sint32 Width, Sint32 ItemHeight, Sint32 DropDownListHeight, bool IsSort, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ITextBox* AddTextBox( Engine::GUI::Control::IDialog* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eTextBoxInputType InputType, Uint32 ControlId ) = 0;
	};
}
}
}

/**
	@file
	@brief UDP接続用
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Network
{
namespace UDP
{
	/**
		@brief UDP接続管理クラス
		@author 葉迩倭

		UDP通信を統一して扱うためのインターフェイスです。
	*/
	class IConnect
		: public Interface
	{
	protected:
		virtual ~IConnect(){}

	public:
		/**
			@brief データ送信
			@author 葉迩倭
			@param pData	[in] 送信するデータ
			@param Size		[in] データのbyte数
			@retval true	成功
			@retval false	失敗
			@note
			データを接続先に送信します。
		*/
		virtual bool Send( const void* pData, Sint32 Size ) = 0;
		/**
			@brief データ受信
			@author 葉迩倭
			@param pData	[in] 受信するデータ
			@param Size		[in] データのbyte数
			@retval true	成功
			@retval false	失敗
			@note
			データを接続先から受信します。
		*/
		virtual bool Recv( void* pData, Sint32 Size ) = 0;
	};
}
}
}
}

/**
	@file
	@brief TCP通信用クライアント
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Network
{
namespace TCP
{
	/**
		@brief TCP通信管理クラス
		@author 葉迩倭

		TCP通信のクライアント処理を統一して扱うためのインターフェイスです。
	*/
	class IClient
		: public Interface
	{
	protected:
		virtual ~IClient(){}

	public:
		/**
			@brief データ送信
			@author 葉迩倭
			@param pData	[in] 送信するデータ
			@param Size		[in] データのbyte数
			@retval true	成功
			@retval false	失敗
			@note
			データを接続先に送信します。
		*/
		virtual bool Send( const void* pData, Sint32 Size ) = 0;
		/**
			@brief データ受信
			@author 葉迩倭
			@param pData	[in] 受信するデータ
			@param Size		[in] データのbyte数
			@retval true	成功
			@retval false	失敗
			@note
			データを接続先から受信します。
		*/
		virtual bool Recv( void* pData, Sint32 Size ) = 0;
	};
}
}
}
}

/**
	@file
	@brief TCP接続用サーバー
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Network
{
namespace TCP
{
	/**
		@brief サーバーイベントのレシーバー
		@author 葉迩倭
		@note
		サーバーイベント時のコールバックを取得する為のリスナーインターフェイス
	*/
	class IServerEventReceiver
	{
	protected:
		virtual ~IServerEventReceiver(){}

	public:
		/**
			@brief 接続時コールバックイベント
			@author 葉迩倭
			@param pClient	[in] 接続クライアント
			@note
			クライアントからの接続が行われた時にコールバックされてきます。
		*/
		virtual void OnConnect( Engine::Network::TCP::IClientOfServer* pClient ) = 0;
		/**
			@brief 切断時コールバックイベント
			@author 葉迩倭
			@param pClient	[in] 切断クライアント
			@note
			クライアントからの切断が行われた時にコールバックされてきます。
		*/
		virtual void OnDisconnect( Engine::Network::TCP::IClientOfServer* pClient ) = 0;
		/**
			@brief アイドル時コールバックイベント
			@author 葉迩倭
			@param pSender	[in] クライアントへの送信用インターフェイス
			@note
			アイドル時のコールバックされてきます。
		*/
		virtual bool OnIdle( Engine::Network::TCP::IServerSender* pSender ) = 0;
		/**
			@brief 受信時コールバックイベント
			@author 葉迩倭
			@param pReciver	[in] クライアントへの受信用インターフェイス
			@note
			クライアントからの受信時にコールバックされてきます。
		*/
		virtual bool OnRecv( Engine::Network::TCP::IServerReciver* pReciver ) = 0;
	};

	/**
		@brief サーバー側のイベントリスナークラス生成
		@author 葉迩倭
		@return クライアントクラス
		@note
		サーバー側で保持しておくリスナーイベント付きのクラアントクラスの<BR>
		生成を行うためのテンプレート関数です。
	*/
	template < typename T >
	IServerEventReceiver* CreateReceiverFactory( IManager* pManager )
	{
		return new T( pManager );
	}

	typedef IServerEventReceiver* (*RECEIVER_FACTORY_PROC)( IManager* pManager );

	/**
		@brief TCP通信管理クラス
		@author 葉迩倭
		@note
		TCP通信のサーバー処理を統一して扱うためのインターフェイスです。
	*/
	class IServer
		: public Interface
	{
	protected:
		virtual ~IServer(){}

	public:
		/**
			@brief サーバー処理起動
			@author 葉迩倭
			@param pFactory	[in] サーバーへの接続時にクライアントクラスを生成する為のファクトリー関数
			@retval true	成功
			@retval false	失敗
			@note
			サーバーとしての処理を開始します。
		*/
		virtual bool Start( RECEIVER_FACTORY_PROC pFactory ) = 0;
		/**
			@brief 全クライアントに送信
			@author 葉迩倭
			@param pData	[in] 送信するデータ
			@param Size		[in] データサイズ
			@retval true	成功
			@retval false	失敗
			@note
			全てのクライアントに対してデータの送信を行います。
		*/
		virtual bool SendToAllClient( const void* pData, Sint32 Size ) = 0;
	};
}
}
}
}

/**
	@file
	@brief TCP通信用サーバー接続クライアント
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Network
{
namespace TCP
{
	/**
		@brief サーバー受信用インターフェイス
		@author 葉迩倭
		@note
		サーバーがクラアントからデータを受信する場合に利用される
	*/
	class IServerReciver
	{
	protected:
		virtual ~IServerReciver(){}

	public:
		/**
			@brief ホスト情報取得
			@author 葉迩倭
			@param Info	[out] 接続先のホスト情報を取得
			@note
			接続先のホスト情報を取得できます。
		*/
		virtual void GetHostInfo( SHostInfo& Info ) const = 0;
		/**
			@brief データ受信
			@author 葉迩倭
			@param pData	[in] 受信するデータ
			@param Size		[in] データのbyte数
			@retval true	成功
			@retval false	失敗
			@note
			データを接続先から受信します。
		*/
		virtual bool Recv( void* pData, Sint32 Size ) = 0;
	};

	/**
		@brief サーバー送信用インターフェイス
		@author 葉迩倭
		@note
		サーバーがクラアントにデータを送信する場合に利用される
	*/
	class IServerSender
	{
	protected:
		virtual ~IServerSender(){}

	public:
		/**
			@brief ホスト情報取得
			@author 葉迩倭
			@param Info	[out] 接続先のホスト情報を取得
			@note
			接続先のホスト情報を取得できます。
		*/
		virtual void GetHostInfo( SHostInfo& Info ) const = 0;
		/**
			@brief データ送信
			@author 葉迩倭
			@param pData	[in] 送信するデータ
			@param Size		[in] データのbyte数
			@retval true	成功
			@retval false	失敗
			@note
			データを接続先に送信します。
		*/
		virtual bool Send( const void* pData, Sint32 Size ) = 0;
	};

	/**
		@brief TCP通信サーバー用クライアント管理クラス
		@author 葉迩倭
		@note
		TCP通信のサーバー側のクライアント管理を行うためのインターフェイス。
	*/
	class IClientOfServer
		: public Interface
	{
	protected:
		virtual ~IClientOfServer(){}

	public:
		/**
			@brief ホスト情報取得
			@author 葉迩倭
			@param Info	[out] 接続先のホスト情報を取得
			@note
			接続先のホスト情報を取得できます。
		*/
		virtual void GetHostInfo( SHostInfo& Info ) const = 0;
	};
}
}
}
}

/**
	@file
	@brief ネットワークマネージャー
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Network
{
	/**
		@brief ネットワーク管理クラス
		@author 葉迩倭

		ネットワーク処理を統一して扱うためのインターフェイスです。
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		/**
			@brief 送信用メモリ確保
			@author 葉迩倭
			@return メモリアドレス
			@note
			送信で利用する為のメモリを取得します。<BR>
			送信後に自動的にメモリは解放されます。
		*/
		virtual void* GetDataSendMemory( Uint32 Size ) const = 0;
		/**
			@brief 最終エラー取得
			@author 葉迩倭
			@return エラーメッセージ
			@note
			最終的に発生したエラーを取得します。
		*/
		virtual const wchar_t* GetLastError() const = 0;
		/**
			@brief ホスト情報取得
			@author 葉迩倭
			@param Info	[out] 自分のホスト情報を取得
			@note
			自分のホスト情報を取得できます。
		*/
		virtual void GetHostInfo( SHostInfo& Info ) const = 0;
		/**
			@brief サーバー生成
			@author 葉迩倭
			@param Port			[in] ポート
			@param ConnectMax	[in] 接続最大数
			@note
			TCP接続のサーバーインターフェイスを生成します。
		*/
		virtual TCP::IServer* CreateServer( Uint16 Port, Uint32 ConnectMax ) = 0;
		/**
			@brief TCP接続クライアント生成
			@author 葉迩倭
			@param pTargetHost	[in] 対象のホストまたはIPアドレス
			@param TargetPort	[in] 対象のホストのポート
			@note
			TCP接続のクライアントインターフェイスを生成します。
		*/
		virtual TCP::IClient* ConnectByTCP( const char* pTargetHost, Uint16 TargetPort ) = 0;
		/**
			@brief UDP接続生成
			@author 葉迩倭
			@param pTargetHost	[in] 対象のホストまたはIPアドレス
			@param TargetPort	[in] 対象のホストのポート
			@note
			UDP接続を行います。<BR>
			UDPにはサーバーやクライアントの概念がないので<BR>
			双方で作成して自前で管理する必要があります。
		*/
		virtual UDP::IConnect* ConnectByUDP( const char* pTargetHost, Uint16 TargetPort ) = 0;
	};
}
}
}

/**
	@file
	@brief メモリ常駐サウンド
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Sound
{
namespace Resource
{
	/**
		@brief サウンド管理クラス
		@author 葉迩倭
		@note
		メモリ常駐型のサウンドの処理を行うクラスです。<BR>
		未圧縮Waveのみのオンメモリ多重再生に対応しています。<BR>
		また3Dサウンドの利用も可能で、効果音としての用途を想定しています。
	*/
	class IStaticSound
		: public Interface
	{
	protected:
		virtual ~IStaticSound(){}

	public:
		/**
			@brief 再生
			@author 葉迩倭
			@param Layer	[in] レイヤー番号（-1指定で全レイヤーに対して）
			@param IsLoop	[in] ループ有無フラグ
			@note
			読み込んだサウンドデータの再生を開始します。<BR>
			ループの有無を指定できます。
		*/
		virtual void Play( Sint32 Layer, bool IsLoop = false ) = 0;

		/**
			@brief 停止
			@author 葉迩倭
			@param Layer	[in] レイヤー番号（-1指定で全レイヤーに対して）
			@note
			再生中のサウンドを停止します。
		*/
		virtual void Stop( Sint32 Layer ) = 0;

		/**
			@brief 一時停止/解除
			@author 葉迩倭
			@param Layer	[in] レイヤー番号（-1指定で全レイヤーに対して）
			@note
			再生中のサウンドを一時停止、<BR>
			一時停止中のサウンドを再生します。
		*/
		virtual void Pause( Sint32 Layer ) = 0;

		/**
			@brief 一時停止チェック
			@author 葉迩倭
			@param Layer	[in] レイヤー番号
			@retval false	一時停止していない
			@retval true	一時停止している
			@note
			現在一時停止のサウンドかどうか調べます。
		*/
		virtual bool IsPause( Sint32 Layer ) const = 0;

		/**
			@brief 再生チェック
			@author 葉迩倭
			@param Layer	[in] レイヤー番号
			@retval false	再生していない
			@retval true	再生している
			@note
			現在再生中のサウンドかどうか調べます。
		*/
		virtual bool IsPlay( Sint32 Layer ) const = 0;

		/**
			@brief ボリューム変更
			@author 葉迩倭
			@param Layer	[in] レイヤー番号（-1指定で全レイヤーに対して）
			@param Volume	[in] ボリューム（0～100%）
			@note
			ボリュームの変更を行います。
		*/
		virtual void SetVolume( Sint32 Layer, float Volume ) = 0;

		/**
			@brief 3Dサウンドの位置設定
			@author 葉迩倭
			@param Layer	[in] レイヤー番号（-1指定で全レイヤーに対して）
			@param Position	[in] 3D空間上の位置
			@note
			3Dサウンド時のワールドの位置を設定します。
		*/
		virtual void SetPosition( Sint32 Layer, const Kernel::Math::VectorS& Position ) = 0;
	};
}
}
}
}

/**
	@file
	@brief ストリームサウンド
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Sound
{
namespace Resource
{
	static const float PLAY_TIME_AUTO = -1.0f;	///< 再生時間自動設定

	/**
		@brief ストリームサウンド再生パラメーター
		@author 葉迩倭
		@note
		ストリームサウンドの再生を行うためのテーブルデータです。
	*/
	struct SPlayBlock
	{
		Sint32 LoopCount;		///< このテーブルのループ数（-1で無限ループ）
		float StartTime;		///< 再生開始位置（秒指定）（PLAY_TIME_AUTO指定で最初から）
		float EndTime;			///< 再生終了位置（秒指定）（PLAY_TIME_AUTO指定で最後まで）
	};

	/**
		@brief ストリームサウンド管理クラス
		@author 葉迩倭
		@note
		ストリームサウンドの処理を行うクラスです。<BR>
		未圧縮Wave/圧縮Wave/OggVorbisの再生に対応しています。<BR>
		BGMや音声の再生用途を想定しています。
	*/
	class IStreamSound
		: public Interface
	{
	protected:
		virtual ~IStreamSound(){}

	public:
		/**
			@brief 再生
			@author 葉迩倭
			@param pTbl			[in] 再生テーブル
			@param Count		[in] 再生テーブル数
			@note
			読み込んだサウンドデータの再生を開始します。<BR>
			再生テーブルの定義にそって再生されていきます。
		*/
		virtual void Play( const SPlayBlock* pTbl, Sint32 Count ) = 0;

		/**
			@brief 再生
			@author 葉迩倭
			@param LoopCount	[in] ループ数(-1で無限)
			@note
			読み込んだサウンドデータの再生を開始します。
		*/
		virtual void Play( Sint32 LoopCount = 0 ) = 0;

		/**
			@brief 停止
			@author 葉迩倭
			@note
			再生中のサウンドを停止します。
		*/
		virtual void Stop() = 0;

		/**
			@brief 一時停止/解除
			@author 葉迩倭
			@note
			再生中のサウンドを一時停止、<BR>
			一時停止中のサウンドを再生します。
		*/
		virtual void Pause() = 0;

		/**
			@brief 再生チェック
			@author 葉迩倭
			@retval true	再生している
			@retval false	再生していない
			@note
			現在再生中のサウンドかどうか調べます。
		*/
		virtual bool IsPlay() const = 0;

		/**
			@brief ボリューム変更
			@author 葉迩倭
			@param Volume	[in] ボリューム（0～100）
			@note
			ボリュームの変更を行います。
		*/
		virtual void SetVolume( float Volume ) = 0;

		/**
			@brief フェードイン
			@author 葉迩倭
			@param Second	[in] 秒単位での時間
			@param Volume	[in] ターゲットのボリューム
			@note
			フェードイン処理を行います
		*/
		virtual void FadeIn( float Second, float Volume = 100.0f ) = 0;

		/**
			@brief フェードアウト
			@author 葉迩倭
			@param Second	[in] 秒単位での時間
			@note
			フェードアウト処理を行います
		*/
		virtual void FadeOut( float Second ) = 0;
	};
}
}
}
}
/**
	@file
	@brief サウンドマネージャー
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Sound
{
	/**
		@brief サウンドデバイス管理クラス
		@author 葉迩倭
		@note
		サウンド処理を統一して扱うためのインターフェイスです。
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		/**
			@brief ストリームサウンドの生成
			@author 葉迩倭
			@param pFile		[in] 再生するファイル
			@param pPluginName	[in] 利用するプラグイン名
			@param IsMemoryCopy	[in] 内部でメモリをコピーしてもっておくかどうか
			@return IStreamSoundインターフェイス
			@note
			おもにBGMで使うファイルストリーム再生用のインターフェイスを生成します。<BR>
			指定したプラグインを使ってリアルタイムにデコードしながら再生を行います。<BR>
			圧縮音声ファイルを直接再生できるのでメモリ的には有利ですがデコードでCPUを使うので<BR>
			多量の再生を同時に行う場合は注意が必要です。
		*/
		virtual Resource::IStreamSound* CreateStreamSound( File::IFile* pFile, const wchar_t *pPluginName, bool IsMemoryCopy = true ) = 0;

		/**
			@brief ストリームサウンドの生成
			@author 葉迩倭
			@param pFileName	[in] ファイル名
			@param pData		[in] Waveファイルのデータ
			@param Size			[in] Waveファイルのデータサイズ
			@param pPluginName	[in] 利用するプラグイン名
			@param IsMemoryCopy	[in] 内部でメモリをコピーしてもっておくかどうか
			@return IStreamSoundインターフェイス
			@note
			おもにBGMで使うファイルストリーム再生用のインターフェイスを生成します。<BR>
			指定したプラグインを使ってリアルタイムにデコードしながら再生を行います。<BR>
			圧縮音声ファイルを直接再生できるのでメモリ的には有利ですがデコードでCPUを使うので<BR>
			多量の再生を同時に行う場合は注意が必要です。
		*/
		virtual Resource::IStreamSound* CreateStreamSound( const wchar_t* pFileName, const void* pData, Uint32 Size, const wchar_t *pPluginName, bool IsMemoryCopy ) = 0;

		/**
			@brief スタティックサウンドの生成
			@author 葉迩倭
			@param pFileName	[in] ファイル名
			@param pData		[in] Waveファイルのデータ
			@param Size			[in] Waveファイルのデータサイズ
			@param LayerCount	[in] 同時再生用レイヤーの数
			@param Is3DSound	[in] 3Dサウンドとして生成するかどうか
			@return IStaticSoundインターフェイス
			@note
			おもに効果音で使う常駐のwaveファイルのインターフェイスを生成します。<BR>
			同一バッファを使った複数同時再生や3Dサウンドなどの機能を持っています。<BR>
			デコード済みの生waveファイルしか扱えないので大きなファイルはメモリを圧迫しますが、<BR>
			デコードの負荷がないのでSEのように数が多くサイズの小さい音に向いています。
		*/
		virtual Resource::IStaticSound* CreateStaticSound( const wchar_t* pFileName, const void* pData, Uint32 Size, Sint32 LayerCount, bool Is3DSound ) = 0;

		/**
			@brief プラグインディレクトリ設定
			@author 葉迩倭
			@param pPath	[in] プラグインディレクトリのパス
			@note
			ストリーム再生に利用するプラグインの検索ディレクトリを設定します
		*/
		virtual void SetPluginDirectory( const wchar_t* pPath ) = 0;

		/**
			@brief リスナーの位置を設定
			@author 葉迩倭
			@param Position	[in] リスナーの位置
			@note
			3Dサウンドのリスナーの位置を設定します。
		*/
		virtual void SetListenerPosition( const Kernel::Math::VectorS& Position ) = 0;

		/**
			@brief リスナーの方向を設定
			@author 葉迩倭
			@param Front	[in] リスナーの前方向
			@param Up		[in] リスナーの上方向
			@note
			3Dサウンドのリスナーの方向を設定します。
		*/
		virtual void SetListenerDirection( const Kernel::Math::VectorS& Front, const Kernel::Math::VectorS& Up ) = 0;

		/**
			@brief サウンドの処理を更新する
			@author 葉迩倭
			@note
			3Dサウンドに関する再計算を行います。
		*/
		virtual void Update() = 0;
	};
}
}
}

/**
	@file
	@brief マウス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Input
{
	/**
		@brief マウス管理インターフェイス
		@author 葉迩倭
		@note
		マウスを扱うためのインターフェイスです。
	*/
	class IMouse
		: public Interface
	{
	protected:
		virtual ~IMouse(){}

	public:
		/**
			@brief マウスのX座標取得
			@author 葉迩倭
			@return X座標
			@note
			マウスポインターのスクリーン座標上のX座標を取得します。
		*/
		virtual Sint32 GetPositionX() const = 0;

		/**
			@brief マウスのY座標取得
			@author 葉迩倭
			@return Y座標
			@note
			マウスポインターのスクリーン座標上のY座標を取得します。
		*/
		virtual Sint32 GetPositionY() const = 0;

		/**
			@brief マウスのX移動量取得
			@author 葉迩倭
			@return X移動量
			@note
			マウスポインターのスクリーン上のX移動量を取得します。
		*/
		virtual Sint32 GetMoveX() const = 0;

		/**
			@brief マウスのY移動量取得
			@author 葉迩倭
			@return Y移動量
			@note
			マウスポインターのスクリーン上のY移動量を取得します。
		*/
		virtual Sint32 GetMoveY() const = 0;

		/**
			@brief マウスの左クリック状態取得
			@author 葉迩倭
			@retval false	左ボタンは押されていない
			@retval true	左ボタンは押されている
			@note
			マウスの左ボタンの状態を取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual bool GetClickL() const = 0;

		/**
			@brief マウスの右クリック状態取得
			@author 葉迩倭
			@retval false	右ボタンは押されていない
			@retval true	右ボタンは押されている
			@note
			マウスの右ボタンの状態を取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual bool GetClickR() const = 0;

		/**
			@brief マウスのホイールクリック状態取得
			@author 葉迩倭
			@retval false	ホイールボタンは押されていない
			@retval true	ホイールボタンは押されている
			@note
			マウスのホイールボタンの状態を取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual bool GetClickW() const = 0;

		/**
			@brief マウスの左ボタン状態取得
			@author 葉迩倭
			@return		左ボタンの状態
			@note
			マウスの左ボタンの詳細な情報を取得します。
		*/
		virtual eButtonState GetStateL() const = 0;

		/**
			@brief マウスの右ボタン状態取得
			@author 葉迩倭
			@return		右ボタンの状態
			@note
			マウスの右ボタンの詳細な情報を取得します。
		*/
		virtual eButtonState	GetStateR() const = 0;

		/**
			@brief マウスのホイールボタン状態取得
			@author 葉迩倭
			@return		ホイールボタンの状態
			@note
			マウスのホイールボタンの詳細な情報を取得します。
		*/
		virtual eButtonState	GetStateW() const = 0;

		/**
			@brief マウスのホイール回転量取得
			@author 葉迩倭
			@return		ホイール回転量
			@note
			マウスのホイール回転量を取得します。
		*/
		virtual float GetWheelRotate() const = 0;

		/**
			@brief マウスの位置を設定
			@author 葉迩倭
			@param Pos	[in] スクリーン座標
			@note
			マウスの位置を任意の場所に設定します。
		*/
		virtual void SetPosition( Point2DI& Pos ) = 0;
	};
}
}
}

/**
	@file
	@brief キーボード
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Input
{
	/**
		@brief キーボード管理インターフェイス
		@author 葉迩倭
		@note
		キーボードを扱うためのインターフェイスです。
	*/
	class IKeyboard
		: public Interface
	{
	protected:
		virtual ~IKeyboard(){}

	public:
		/**
			@brief キー入力バッファフラッシュ
			@author 葉迩倭
			@note
			キー入力バッファに蓄積した入力バッファをクリアします。
		*/
		virtual void ClearKeyBuffer() = 0;

		/**
			@brief キー入力バッファからデータ取得
			@author 葉迩倭
			@return 入力されたキーのキーコード
			@note
			キー入力バッファに蓄積されたデータを取り出します。<BR>
			押されたキーを全て取り出す時はwhile()文等で処理してください。
		*/
		virtual eKeyCode GetKeyBuffer() = 0;

		/**
			@brief キーが押されているかチェックする
			@author 葉迩倭
			@retval false	押されていない
			@retval true	押されている
			@note
			指定されたキーが現在押されているかチェックします。<BR>
			純粋にキーのON/OFFのみ取得できます。
		*/
		virtual bool GetKeyData( eKeyCode Key ) const = 0;
	};
}
}
}

/**
	@file
	@brief ジョイスティック
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Input
{
	/**
		@brief ジョイスティック管理インターフェイス
		@author 葉迩倭
		@note
		ジョイスティックを扱うためのインターフェイスです。
	*/
	class IJoystick
		: public Interface
	{
	protected:
		virtual ~IJoystick(){}

	public:
		/**
			@brief 軸を直接取得
			@author 葉迩倭
			@param AxisNo	[in] 物理的な軸の番号
			@retval true	押している
			@retval false	押していない
			@note
			直接軸の状態を取得します。
		*/
		virtual float GetAxisDirect( Uint32 AxisNo ) const = 0;

		/**
			@brief ボタンを直接取得
			@author 葉迩倭
			@param ButtonNo	[in] 物理的なボタンの番号
			@retval true	押している
			@retval false	押していない
			@note
			直接ボタンの状態を取得します。
		*/
		virtual bool GetButtonDirect( Uint32 ButtonNo ) const = 0;

		/**
			@brief 仮想ボタンの入力レベルを取得
			@author 葉迩倭
			@param Button	[in] 仮想ボタンの番号
			@note
			仮想ボタンの入力レベルを0.0～1.0で取得します。<BR>
			通常のボタンの場合は0.0(押していない)か1.0(押している)になり<BR>
			アナログスティックの場合はそれぞれの方向で値が取得されます。
		*/
		virtual float GetVirtualButton( Uint32 Button ) const = 0;

		/**
			@brief 仮想ボタンの状態を取得
			@author 葉迩倭
			@param Button	[in] 仮想ボタンの番号
			@return ボタンの状態
			@note
			仮想ボタンの状態を調べます。
		*/
		virtual eButtonState GetVirtualButtonState( Uint32 Button ) const = 0;

		/**
			@brief 入力しているかチェック
			@author 葉迩倭
			@retval true	一切の入力をしていない
			@retval false	なんらかの入力をしている
			@note
			なんらかの入力をしているか調べます。
		*/
		virtual bool IsFree() const = 0;
	};
}
}
}

/**
	@file
	@brief 入力簡易操作コントローラー
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Input
{
	/**
		@brief コントローラーのボタン
		@author 葉迩倭
		@note
		コントローラーのボタンの定義。
	*/
	enum eControllerButton
	{
		CONTROLLER_BUTTON_01,				///< ボタン 1
		CONTROLLER_BUTTON_02,				///< ボタン 2
		CONTROLLER_BUTTON_03,				///< ボタン 3
		CONTROLLER_BUTTON_04,				///< ボタン 4
		CONTROLLER_BUTTON_05,				///< ボタン 5
		CONTROLLER_BUTTON_06,				///< ボタン 6
		CONTROLLER_BUTTON_07,				///< ボタン 7
		CONTROLLER_BUTTON_08,				///< ボタン 8
		CONTROLLER_BUTTON_09,				///< ボタン 9
		CONTROLLER_BUTTON_10,				///< ボタン10
		CONTROLLER_BUTTON_11,				///< ボタン11
		CONTROLLER_BUTTON_12,				///< ボタン12
		CONTROLLER_BUTTON_13,				///< ボタン13
		CONTROLLER_BUTTON_14,				///< ボタン14
		CONTROLLER_BUTTON_15,				///< ボタン15
		CONTROLLER_BUTTON_16,				///< ボタン16
		CONTROLLER_AXIS_01_MINUIS,			///< 軸1マイナス方向
		CONTROLLER_AXIS_01_PLUS,			///< 軸1プラス方向
		CONTROLLER_AXIS_02_MINUIS,			///< 軸2マイナス方向
		CONTROLLER_AXIS_02_PLUS,			///< 軸2プラス方向
		CONTROLLER_AXIS_03_MINUIS,			///< 軸3マイナス方向
		CONTROLLER_AXIS_03_PLUS,			///< 軸3プラス方向
		CONTROLLER_AXIS_04_MINUIS,			///< 軸4マイナス方向
		CONTROLLER_AXIS_04_PLUS,			///< 軸4プラス方向
		CONTROLLER_AXIS_05_MINUIS,			///< 軸5マイナス方向
		CONTROLLER_AXIS_05_PLUS,			///< 軸5プラス方向
		CONTROLLER_AXIS_06_MINUIS,			///< 軸6マイナス方向
		CONTROLLER_AXIS_06_PLUS,			///< 軸6プラス方向
		CONTROLLER_AXIS_07_MINUIS,			///< 軸7マイナス方向
		CONTROLLER_AXIS_07_PLUS,			///< 軸7プラス方向
		CONTROLLER_AXIS_08_MINUIS,			///< 軸8マイナス方向
		CONTROLLER_AXIS_08_PLUS,			///< 軸8プラス方向
		CONTROLLER_MAX,
	};

	/**
		@brief 入力デバイス簡易操作クラス
		@author 葉迩倭
		@note
		キーボードとパッドを統一して扱うためのインターフェイスです。
	*/
	class IInputController
		: public Interface
	{
	protected:
		virtual ~IInputController(){}

	public:
		/**
			@brief キーリピート設定
			@author 葉迩倭
			@param RepeatStart		[in] リピート開始までのフレーム数
			@param RepeatInterval	[in] リピートの間隔フレーム数
			@note
			入力コントローラーの押しっぱなし時のキーリピートの設定を行います。
		*/
		virtual void SetRepeatParameter( Sint32 RepeatStart, Sint32 RepeatInterval ) = 0;

		/**
			@brief キーリピート設定
			@author 葉迩倭
			@param Button			[in] コントローラーのボタン
			@param RepeatStart		[in] リピート開始までのフレーム数
			@param RepeatInterval	[in] リピートの間隔フレーム数
			@note
			入力コントローラーの押しっぱなし時のキーリピートの設定を行います。<BR>
			このメソッドで個別に設定を行わない場合はSetRepeatParameter()での設定が利用されます。
		*/
		virtual void SetButtonRepeatParameter( eControllerButton Button, Sint32 RepeatStart, Sint32 RepeatInterval ) = 0;

		/**
			@brief 仮想ボタンのアタッチ
			@author 葉迩倭
			@param Button			[in] コントローラーのボタン
			@param VirtualButton	[in] アタッチする仮想キー
			@note
			ゲームパッドの仮想ボタンを入力コントローラーのボタンにアタッチします。
		*/
		virtual void AttachGamepadVirtualButton( eControllerButton Button, Uint32 VirtualButton ) = 0;

		/**
			@brief キーボードのアタッチ
			@author 葉迩倭
			@param Button			[in] コントローラーのボタン
			@param KeyCode			[in] アタッチするキー
			@note
			キーボードのキーを入力コントローラーのボタンにアタッチします。
		*/
		virtual void AttachKeyboard( eControllerButton Button, eKeyCode KeyCode ) = 0;

		/**
			@brief 仮想ボタンのアタッチ解除
			@author 葉迩倭
			@param Button			[in] コントローラーのボタン
			@param VirtualButton	[in] アタッチ解除する仮想キー
			@note
			ゲームパッドの仮想ボタンを入力コントローラーのボタンのアタッチ解除します。
		*/
		virtual void DetachGamepadVirtualButton( eControllerButton Button, Uint32 VirtualButton ) = 0;

		/**
			@brief キーボードのアタッチ解除
			@author 葉迩倭
			@param Button			[in] コントローラーのボタン
			@param KeyCode			[in] アタッチ解除するキー
			@note
			キーボードのキーを入力コントローラーのボタンのアタッチ解除します。
		*/
		virtual void DetachKeyboard( eControllerButton Button, eKeyCode KeyCode ) = 0;

		/**
			@brief フリー状態かを取得
			@author 葉迩倭
			@param Button			[in] コントローラーのボタン
			@retval true	押していない
			@retval false	押している
			@note
			指定ボタンが押しっぱなしの状態かどうかを取得します。
		*/
		virtual bool IsFree( eControllerButton Button ) const = 0;

		/**
			@brief 離した瞬間かを取得
			@author 葉迩倭
			@param Button			[in] コントローラーのボタン
			@retval true	このフレームで押された
			@retval false	押されてない
			@note
			指定ボタンがいまのフレームで押されたかを取得します。
		*/
		virtual bool IsPull( eControllerButton Button ) const = 0;

		/**
			@brief 押した瞬間かを取得
			@author 葉迩倭
			@param Button			[in] コントローラーのボタン
			@retval true	このフレームで押された
			@retval false	押されてない
			@note
			指定ボタンがいまのフレームで押されたかを取得します。
		*/
		virtual bool IsPush( eControllerButton Button ) const = 0;

		/**
			@brief ホールド状態かを取得
			@author 葉迩倭
			@param Button			[in] コントローラーのボタン
			@retval true	押しっぱなし
			@retval false	押していない
			@note
			指定ボタンが押しっぱなしの状態かどうかを取得します。
		*/
		virtual bool IsHold( eControllerButton Button ) const = 0;

		/**
			@brief 入力値を取得
			@author 葉迩倭
			@param Button			[in] コントローラーのボタン
			@note
			指定ボタンの入力値をアナログで取得します。<BR>
			値は0.0から1.0の値で取得できます。<BR>
			ボタンとしての扱いなので軸もそれぞれの方向に対して0.0～1.0で取得されます。
		*/
		virtual float GetPower( eControllerButton Button ) const = 0;
	};
}
}
}

/**
	@file
	@brief 入力デバイスマネージャー
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Input
{
	/**
		@brief 入力デバイス管理クラス
		@author 葉迩倭
		@note
		入力デバイス関係のマネージャー
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		/**
			@brief 入力情報更新
			@author 葉迩倭
			@note
			入力情報から最新の状態へ更新します。<BR>
			必ず１フレームに１回呼ぶようにして下さい。
		*/
		virtual void Update() = 0;

		/**
			@brief ジョイスティック数取得
			@author 葉迩倭
			@return ジョイスティック数
			@note
			利用可能なジョイスティックの数を取得します
		*/
		virtual Sint32 GetJoystickCount() const = 0;

		/**
			@brief ジョイスティック番号取得
			@author 葉迩倭
			@param GuidInstance		[in] インスタンス
			@param GuidProduct		[in] プロダクト
			@return ジョイスティック番号
			@note
			GUIDが一致するジョイスティックの番号を返します。<BR>
			なければ-1になります。
		*/
		virtual Sint32 GetJoystickIndex( const GUID& GuidInstance, const GUID& GuidProduct ) const = 0;

		/**
			@brief ジョイスティック用インターフェイス取得
			@author 葉迩倭
			@param No	[in] ジョイスティック番号
			@return IJoystickインターフェイス
			@note
			ジョイスティック操作用のインターフェイスを取得します
		*/
		virtual IJoystick* GetJoystick( Sint32 No ) = 0;

		/**
			@brief キーボード用インターフェイス取得
			@author 葉迩倭
			@return IKeyboardインターフェイス
			@note
			キーボード操作用のインターフェイスを取得します
		*/
		virtual IKeyboard* GetKeyboard() = 0;

		/**
			@brief マウス用インターフェイス取得
			@author 葉迩倭
			@return IMouseインターフェイス
			@note
			マウス操作用のインターフェイスを取得します
		*/
		virtual IMouse* GetMouse() = 0;

		/**
			@brief 入力制御用インターフェイス取得
			@author 葉迩倭
			@param No		[in] 入力に使うジョイスティックの番号
			@return IInputControllerインターフェイス
			@note
			入力制御操作用のインターフェイスを取得します
		*/
		virtual IInputController* CreateInputController( Sint32 No ) = 0;
	};
}
}
}

/**
	@file
	@brief ボディインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief ボディ
		@author 葉迩倭
	*/
	class IBody
		: public Interface
	{
	protected:
		virtual ~IBody(){}

	public:
		/**
			@brief 内部データの取得
			@author 葉迩倭
			@return 内部データ
			@note
			内部で利用している特殊なデータを取得します。<BR>
			これをユーザーが利用する事はありません。
		*/
		virtual void* GetInstance() = 0;
		/**
			@brief ボディタイプ取得
			@author 葉迩倭
			@return ボディタイプ
			@note
			ボディのタイプを取得します。
		*/
		virtual eBodyType GetBodyType() = 0;
		/**
			@brief ユーザーポインター取得
			@author 葉迩倭
			@return ユーザーが設定したポインター
			@note
			ユーザーが設定したポインターを取得します。
		*/
		virtual void* GetUserData() = 0;
		/**
			@brief ユーザーポインター設定
			@author 葉迩倭
			@param pData	[in] ユーザー定義のポインター
			@note
			ユーザー定義のポインターを設定します。
		*/
		virtual void SetUserData( void* pData ) = 0;
		/**
			@brief デバッグ用形状データ生成
			@author 葉迩倭
			@param Color	[in] 形状の色
			@note
			デバッグ描画で利用する形状データを生成します。
		*/
		virtual void CreateDebugShape( const ColorF& Color ) = 0;
		/**
			@brief 接触ボディ数取得
			@author 葉迩倭
			@return 接触ボディ数
			@note
			接触しているボディの数を取得します。
		*/
		virtual Uint32 GetContactCount() = 0;
		/**
			@brief 接触ボディ取得
			@author 葉迩倭
			@param Index	[in] 接触ボディのインデックス
			@return 接触しているボディの情報
			@note
			接触しているボディのインデックスを取得します。
		*/
		virtual const SContactInfo& GetContactBody( Uint32 Index ) = 0;
		/**
			@brief 接触時コールバックイベント設定
			@author 葉迩倭
			@param Event	[in] 接触時コールバックイベント
			@note
			接触時のコールバックイベントを設定します。
		*/
		virtual void SetContactEvent( const Kernel::Delegate02<Body::IBody*, const SContactInfo&>& Event ) = 0;
		/**
			@brief ワールド行列取得
			@author 葉迩倭
			@return ワールド行列
			@note
			ボディのワールド行列を取得します。
		*/
		virtual const Kernel::Math::Matrix& GetWorldMatrix() const = 0;
		/**
			@brief ダイナミクス用マネージャー取得
			@author 少佐
			@return ダイナミクス用マネージャー
			@note
			ダイナミクス用マネージャーを取得します。
		*/
		virtual IManager* GetManager() = 0;
	};
}
}
}
}
/**
	@file
	@brief 球
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	class IDynamicsBody
		: public IBody
	{
	protected:
		virtual ~IDynamicsBody(){}

	public:
		/**
			@brief 接触応答設定
			@author 葉迩倭
			@note
			接触時の応答を無効にします。<BR>
			応答がないボディはコリジョンの反応はしますが<BR>
			ぶつかった時の物理シミュレーションが行われません。
		*/
		virtual void SetNoContactResponseObject() = 0;

		/**
			@brief キネマティクス設定
			@author 葉迩倭
			@note
			キネマティクスオブジェクト化します。
		*/
		virtual void SetKinematicsObject() = 0;

		/**
			@brief 状態リセット
			@author 葉迩倭
			@param Position	[in] 位置
			@param Rotation	[in] 角度
			@note
			物理シミュレーション状態をリセットします。
		*/
		virtual void ResetAll( const Kernel::Math::VectorS& Position, const Kernel::Math::VectorS& Rotation ) = 0;
		/**
			@brief 位置直接設定
			@author 葉迩倭
			@param Position	[in] 位置
			@note
			ワールド座標を直接指定して位置を移動します。
		*/
		virtual void SetPosition( const Kernel::Math::VectorS& Position ) = 0;
		/**
			@brief 移動速度設定
			@author 葉迩倭
			@param Velocity	[in] 移動速度
			@note
			通常ApplｙForceで力を与えた結果としてVelocityが求まりますが<BR>
			それを無視して直接ボディに速度を与えられます。
		*/
		virtual void SetLinearVelocity( const Kernel::Math::VectorS& Velocity ) = 0;
		/**
			@brief 回転速度設定
			@author 葉迩倭
			@param Velocity	[in] 回転速度
			@note
			通常ApplｙForceで力を与えた結果としてVelocityが求まりますが<BR>
			それを無視して直接ボディに速度を与えられます。
		*/
		virtual void SetAngularVelocity( const Kernel::Math::VectorS& Velocity ) = 0;
		/**
			@brief 移動速度係数設定
			@author 葉迩倭
			@param Factor	[in] 係数
			@note
			移動速度のVelocityに対して乗算する係数を設定します。<BR>
			たとえばz=0.0にするとXY平面上での移動しかしなくなります。
		*/
		virtual void SetLinearFactor( const Kernel::Math::VectorS& Factor ) = 0;
		/**
			@brief 回転速度係数設定
			@author 葉迩倭
			@param Factor	[in] 係数
			@note
			回転速度のVelocityに対して乗算する係数を設定します。<BR>
			たとえばxy=0.0にするとz軸上での回転しかしなくなります。
		*/
		virtual void SetAngularFactor( const Kernel::Math::VectorS& Factor ) = 0;
		/**
			@brief 移動速度取得
			@author 葉迩倭
			@param 移動速度
			@note
			シミュレーション後の移動の速度を取得します。
		*/
		virtual Kernel::Math::VectorS GetLinearVelocity() const = 0;
		/**
			@brief 回転速度取得
			@author 葉迩倭
			@param 回転速度
			@note
			シミュレーション後の回転の速度を取得します。
		*/
		virtual Kernel::Math::VectorS GetAngularVelocity() const = 0;
		/**
			@brief 移動速度係数取得
			@author 葉迩倭
			@param 移動速度係数
			@note
			シミュレーション後の移動の速度への係数を取得します。
		*/
		virtual Kernel::Math::VectorS GetLinearFactor() const = 0;
		/**
			@brief 回転速度係数取得
			@author 葉迩倭
			@param 回転速度係数
			@note
			シミュレーション後の回転の速度への係数を取得します。
		*/
		virtual Kernel::Math::VectorS GetAngularFactor() const = 0;
		/**
			@brief 反射率設定
			@author 葉迩倭
			@param Value	[in] 反射率
			@note
			ボディの反射率を設定します。
		*/
		virtual void SetRestitution( float Value ) = 0;
		/**
			@brief 反射率取得
			@author 葉迩倭
			@return 反射率
			@note
			ボディの反射率を取得します。
		*/
		virtual float GetRestitution() const = 0;
		/**
			@brief 摩擦係数設定
			@author 葉迩倭
			@param Value	[in] 摩擦係数
			@note
			ボディの摩擦係数を設定します。
		*/
		virtual void SetFriction( float Value ) = 0;
		/**
			@brief 摩擦係数取得
			@author 葉迩倭
			@return 摩擦係数
			@note
			ボディの摩擦係数を取得します。
		*/
		virtual float GetFriction() const = 0;
		/**
			@brief 重力設定
			@author 少佐
			@param Gravity	[in] 重力
			@note
			ボディにかかる重力を設定します。
		*/
		virtual void SetGravity( const Kernel::Math::VectorS& Gravity ) = 0;
		/**
			@brief 重力取得
			@author 少佐
			@return 重力
			@note
			ボディにかかる重力を取得します。
		*/
		virtual Kernel::Math::VectorS GetGravity() = 0;
		/**
			@brief ボディに力を加える
			@author 葉迩倭
			@param Force	[in] 力
			@param Position	[in] 力を加える位置
			@note
			ボディに力を加えて物理シミュレーションで動かします。
		*/
		virtual void ApplyForce( const Kernel::Math::VectorS& Force, const Kernel::Math::VectorS& Position ) = 0;
		/**
			@brief 回転力取得
			@author 少佐
			@return 回転力
			@note
			ボディに重心にかかっている回転力を取得します。
		*/
		virtual Kernel::Math::VectorS GetTotalTorque() = 0;
		/**
			@brief 力取得
			@author 少佐
			@return 力
			@note
			ボディに重心にかかっている力を取得します。
		*/
		virtual Kernel::Math::VectorS GetTotalForce() = 0;
		/**
			@brief ボディに力を加える
			@author 少佐
			@param Torque	[in] 力
			@note
			ボディに重心に回転力を加えて物理シミュレーションで動かします。
		*/
		virtual void ApplyTorque( const Kernel::Math::VectorS & Torque ) = 0;
		/**
			@brief ボディに力を加える
			@author 少佐
			@param Force	[in] 力
			@note
			ボディに重心に力を加えて物理シミュレーションで動かします。
		*/
		virtual void ApplyCentralForce( const Kernel::Math::VectorS & Force ) = 0;
		/**
			@brief 最大落下速度設定
			@author 葉迩倭
			@param Speed	[in] 落下速度
			@note
			最大落下速度を設定します。<BR>
			-1を指定すると重力により無限に加速していきます。
		*/
		virtual void SetMaxFalloffSpeed( float Speed ) = 0;
		/**
			@brief 最大移動速度設定
			@param Speed	[in] 移動速度
			@note
			最大移動速度を設定します。<BR>
			指定は１秒間の移動速度になります。
		*/
		virtual void SetMaxMoveSpeed( float Speed ) = 0;
		/**
			@brief 減衰設定
			@author 葉迩倭
			@param Linear		[in] 移動減衰
			@param Angulate	[in] 回転減衰
			@note
			物理シミュレーション時の減衰を設定します。
		*/
		virtual void SetDamping( float Linear, float Angulate ) = 0;
	};
}
}
}
}
/**
	@file
	@brief 複合ボディインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief 複合ボディ
		@author 葉迩倭
	*/
	class ICompound
		: public IDynamicsBody
	{
	protected:
		virtual ~ICompound(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief メッシュボディインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief メッシュボディ
		@author 葉迩倭
	*/
	class ITriMesh
		: public IDynamicsBody
	{
	protected:
		virtual ~ITriMesh(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief 無限平面インターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief 無限平面
		@author 葉迩倭
	*/
	class IPlane
		: public IDynamicsBody
	{
	protected:
		virtual ~IPlane(){}

	public:
		/**
			@brief 摩擦係数設定
			@author 葉迩倭
			@param Value	[in] 摩擦係数
			@note
			ボディの摩擦係数を設定します。
		*/
		virtual void SetRestitution( float Value ) = 0;
		/**
			@brief 摩擦係数取得
			@author 葉迩倭
			@return 摩擦係数
			@note
			ボディの摩擦係数を取得します。
		*/
		virtual float GetRestitution() const = 0;
		/**
			@brief 反射率設定
			@author 葉迩倭
			@param Value	[in] 反射率
			@note
			ボディの反射率を設定します。
		*/
		virtual void SetFriction( float Value ) = 0;
		/**
			@brief 反射率取得
			@author 葉迩倭
			@return 反射率
			@note
			ボディの反射率を取得します。
		*/
		virtual float GetFriction() const = 0;
	};
}
}
}
}

/**
	@file
	@brief 箱ボディインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief 箱ボディ
		@author 葉迩倭
	*/
	class IBox
		: public IDynamicsBody
	{
	protected:
		virtual ~IBox(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief カプセルボディインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief カプセルボディ
		@author 葉迩倭
	*/
	class ICapsule
		: public IDynamicsBody
	{
	protected:
		virtual ~ICapsule(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief キャラクタクラス
	@author 少佐
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief キャラクタクラス
		@author 少佐
		@note
		キャラクタクラス
	*/
	class ICharaProxy
		: public IDynamicsBody
	{
	protected:
		virtual ~ICharaProxy(){}

	public:
	
		/**
			@brief 接地チェック
			@author 少佐
			@note
			ボディが地面に設置しているかどうかをチェックします。<BR>
			落下時の着地の反動でわずかに浮いたりするので<BR>
			タイミングを図るなどの工夫が必要な場合があります。
		*/
		virtual bool IsFitGround() const = 0;
		/**
			@brief 接地面の法線取得
			@author 少佐
			@return 接地箇所の法線
			@note
			接地している箇所の法線を取得します。
		*/
		virtual const Kernel::Math::VectorS& GetGroundNormal() = 0;
		/**
			@brief 拘束取得
			@author 少佐
			@return 拘束されているか？
			@note
			接地等、他のオブジェクトに拘束されているかを取得します。
		*/
		virtual bool IsConstraint() = 0;
		/**
			@brief 拘束速度取得
			@author 少佐
			@return 拘束している物体の速度
			@note
			拘束している物体の速度を取得します。<BR>
			動く床等の場合、この速さと物体に加えないと床とずれることになります。
		*/
		virtual Kernel::Math::VectorS GetConstraintVelocity() = 0;
		/**
			@brief 更新イベント設定
			@author 少佐
			@param Event			[in] 更新イベント
			@note
			毎フレームごとの移動回転などの更新処理を行う関数を設定します。<BR>
			Delegateの「ICharaProxy*」は更新する対象のキャラクタクラスです。
		*/
		virtual void SetPreUpdateEvent( const Kernel::Delegate01<ICharaProxy*>& Event ) = 0;
		/**
			@brief 解放イベント設定
			@author 少佐
			@param Event			[in] 解放イベント
			@note
			クラスが削除されるときに実行される関数を設定ます。<BR>
			Delegateの「ICharaProxy*」は削除される対象のキャラクタクラスです。
		*/
		virtual void SetReleaseEvent( const Kernel::Delegate01<ICharaProxy*>& Event ) = 0;
		/**
			@brief 接地イベント設定
			@author 少佐
			@param Event			[in] 接地イベント
			@note
			何か物体と衝突したときに、それを接地として扱うかどうかを指定する関数を設定します。<BR>
			Delegateの「ICharaProxy*」は接地する対象のキャラクタクラスです。<BR>
			「IBody*」は衝突したボディクラスです。<BR>
			「const Kernel::Math::VectorS&」は衝突した部分の法線です。<BR>
			「bool&」にtrueを代入すると接地したことになります。
		*/
		virtual void SetFitGroundEvent( const Kernel::Delegate04<ICharaProxy*, IBody*, const Kernel::Math::VectorS&, bool&>& Event ) = 0;
		/**
			@brief 接地面の法線設定イベント設定
			@author 少佐
			@param Event			[in] 接地面の法線設定イベント
			@note
			何か物体と衝突したときに、接地面の法線をどう扱うかを設定する関数を設定します。<BR>
			Delegateの「ICharaProxy*」は接地する対象のキャラクタクラスです。<BR>
			「IBody*」は衝突したボディクラスです。<BR>
			「const Kernel::Math::VectorS&」は衝突した部分の法線です。<BR>
			「Kernel::Math::VectorS&」に接地面を代入します。
		*/
		virtual void SetSetGroundNormalEvent( const Kernel::Delegate04<ICharaProxy*, IBody*, const Kernel::Math::VectorS&, Kernel::Math::VectorS&>& Event ) = 0;
		/**
			@brief ワールド行列設定
			@author 少佐
			@param mat		[in] ワールド行列
			@note
			ボディのワールド行列を設定します。
		*/
		virtual void SetWorldMatrix( const Kernel::Math::Matrix& mat ) = 0;
		/**
			@brief 位置取得
			@author 少佐
			@return 位置
			@note
			ワールド座標を取得します。
		*/
		virtual Kernel::Math::VectorS GetPosition() = 0;
		/**
			@brief 作動
			@author 少佐
			@note
			速度、回転などを変更した後に実行します。
		*/
		virtual void Activate() = 0;
		/**
			@brief 半径取得
			@author 少佐
			@return 半径
			@note
			球、カプセルの半径を取得します。
		*/
		virtual float GetRadius() = 0;
		/**
			@brief 長さ取得
			@author 少佐
			@return 半径
			@note
			カプセルの長さを取得します。
		*/
		virtual float GetLength() = 0;

		/**
			@brief ユーザーポインター取得
			@author 少佐
			@return ユーザーが設定したポインター
			@note
			ユーザーが設定したポインターを取得します。<BR>
			Get/SetUserDataとは別のポインタを使用しています。
		*/
		virtual void* GetUserCharaData() = 0;

		/**
			@brief ユーザーポインター設定
			@author 少佐
			@param pData	[in] ユーザー定義のポインター
			@note
			ユーザー定義のポインターを設定します。<BR>
			Get/SetUserDataとは別のポインタを使用しています。
		*/
		virtual void SetUserCharaData( void* pData ) = 0;
	};
}
}
}
}

/**
	@file
	@brief 簡易キャラクタクラス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief 簡易キャラクタクラス
		@author 葉迩倭
		@note
		簡易キャラクタ
	*/
	class ICharaProxySimple
		: public IBody
	{
	protected:
		virtual ~ICharaProxySimple(){}

	public:
		/**
			@brief 接地チェック
			@author 葉迩倭
			@note
			ボディが地面に設置しているかどうかをチェックします。<BR>
			落下時の着地の反動でわずかに浮いたりするので<BR>
			タイミングを図るなどの工夫が必要な場合があります。
		*/
		virtual bool IsFitGround() const = 0;
		/**
			@brief 接地面の法線取得
			@author 葉迩倭
			@return 接地箇所の法線
			@note
			接地している箇所の法線を取得します。
		*/
		virtual const Kernel::Math::VectorS& GetGroundNormal() = 0;
		/**
			@brief ジャンプ処理
			@author 葉迩倭
			@param Value	[in] ジャンプ力
			@note
			ボディに上向き（ｙ＋）に力を加えてジャンプの処理を行います。
		*/
		virtual void Jump( float Value ) = 0;
		/**
			@brief 移動
			@author 葉迩倭
			@note
			ボディをXZ平面上で移動させるようにします。<BR>
			坂などによる移動量の補正は自動で行われますので<BR>
			最終的には指定したベクトルの
		*/
		virtual void MoveXZ( const Kernel::Math::VectorS& Move ) = 0;
		/**
			@brief 最大落下速度設定
			@author 葉迩倭
			@param Speed	[in] 落下速度
			@note
			最大落下速度を設定します。<BR>
			-1を指定すると重力により無限に加速していきます。
		*/
		virtual void SetMaxFalloffSpeed( float Speed ) = 0;
		/**
			@brief 最大移動速度設定
			@param Speed	[in] 移動速度
			@note
			最大移動速度を設定します。<BR>
			指定は１秒間の移動速度になります。
		*/
		virtual void SetMaxMoveSpeed( float Speed ) = 0;
		/**
			@brief 位置直接設定
			@author 葉迩倭
			@param Position	[in] 位置
			@note
			ワールド座標を直接指定して位置を移動します。
		*/
		virtual void SetPosition( const Kernel::Math::VectorS& Position ) = 0;
		/**
			@brief 重力設定
			@author 少佐
			@param Gravity	[in] 重力
			@note
			ボディにかかる重力を設定します。
		*/
		virtual void SetGravity( const Kernel::Math::VectorS& Gravity ) = 0;
		/**
			@brief 重力取得
			@author 少佐
			@return 重力
			@note
			ボディにかかる重力を取得します。
		*/
		virtual Kernel::Math::VectorS GetGravity() = 0;
	};
}
}
}
}

/**
	@file
	@brief 球ボディインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief 球ボディ
		@author 葉迩倭
	*/
	class ISphere
		: public IDynamicsBody
	{
	protected:
		virtual ~ISphere(){}

	public:
	};
}
}
}
}
/**
	@file
	@brief トリガーボックスインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief トリガーボックス
		@author 葉迩倭
	*/
	class ITriggerBox
		: public IBody
	{
	protected:
		virtual ~ITriggerBox(){}

	public:
		/**
			@brief トリガーボックスに名前を設定
			@author 葉迩倭
			@param pName	[in] 名前
			@note
			トリガーボックスに対して名前を設定します。
		*/
		virtual void SetName( const char* pName ) = 0;
		/**
			@brief トリガーボックスの名前を取得
			@author 葉迩倭
			@return 名前
			@note
			トリガーボックスから名前を取得します。
		*/
		virtual const char* GetName() = 0;
		/**
			@brief トリガーボックスの名前チェック
			@author 葉迩倭
			@param pName	[in] 名前
			@retval true	同一名称である
			@retval false	同一名称ではない
			@note
			トリガーボックスが指定された名称かどうかチェックします。
		*/
		virtual bool IsName( const char* pName ) = 0;
	};
}
}
}
}

/**
	@file
	@brief ソフトボディ
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	class ISoftBody
		: public IBody
	{
	protected:
		virtual ~ISoftBody(){}

	public:
	};
}
}
}
}
/**
	@file
	@brief ロープボディインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief ロープボディ
		@author 葉迩倭
	*/
	class IRope
		: public ISoftBody
	{
	protected:
		virtual ~IRope(){}

	public:
		virtual void ConnentFrom( Body::IBody* pBody ) = 0;
		virtual void ConnentTo( Body::IBody* pBody ) = 0;
		virtual void DrawDebugShape( Engine::Graphics::Simple::ILineRenderer* pLine ) = 0;
	};
}
}
}
}

/**
	@file
	@brief 衝突判定
	@author 少佐
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	class ICollisionBody
		: public IBody
	{
	protected:
		virtual ~ICollisionBody(){}

	public:
		/**
			@brief ワールド行列設定
			@author 少佐
			@param mat		[in] ワールド行列
			@note
			ボディのワールド行列を設定します。
		*/
		virtual void SetWorldMatrix( const Kernel::Math::Matrix& mat ) = 0;
		/**
			@brief 位置直接設定
			@author 少佐
			@param Position	[in] 位置
			@note
			ワールド座標を直接指定して位置を移動します。
		*/
		virtual void SetPosition( const Kernel::Math::VectorS& Position ) = 0;
		/**
			@brief 衝突判定
			@author 少佐
			@param value		[in] 有効かどうか
			@note
			衝突判定が有効かどうか設定します。
		*/
		virtual void SetHit( bool value ) = 0;

		/**
			@brief 衝突判定
			@author 少佐
			@return value		有効かどうか
			@note
			衝突判定が有効かどうか取得します。
		*/
		virtual bool GetHit() = 0;
	};
}
}
}
}
/**
	@file
	@brief 衝突判定用カプセルボディインターフェイス
	@author 少佐
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief 衝突判定用カプセルボディ
		@author 少佐
	*/
	class ICollisionCapsule
		: public ICollisionBody
	{
	protected:
		virtual ~ICollisionCapsule(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief 衝突判定用球ボディインターフェイス
	@author 少佐
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief 衝突判定用球ボディ
		@author 少佐
	*/
	class ICollisionSphere
		: public ICollisionBody
	{
	protected:
		virtual ~ICollisionSphere(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief 衝突判定用箱ボディインターフェイス
	@author 少佐
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief 衝突判定用箱ボディ
		@author 少佐
	*/
	class ICollisionBox
		: public ICollisionBody
	{
	protected:
		virtual ~ICollisionBox(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief 衝突判定用メッシュボディインターフェイス
	@author 少佐
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief 衝突判定用メッシュボディ
		@author 少佐
	*/
	class ICollisionTriMesh
		: public ICollisionBody
	{
	protected:
		virtual ~ICollisionTriMesh(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief ジョイント
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Joint
{
	/**
		@brief ジョイントインターフェイス
		@author 葉迩倭
	*/
	class IJoint
		: public Interface
	{
	protected:
		virtual ~IJoint(){}

	public:
		virtual float GetAppliedImpulse() const = 0;
	};
}
}
}
}

/**
	@file
	@brief ヒンジジョイント
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Joint
{
	/**
		@brief ヒンジジョイントインターフェイス
		@author 葉迩倭
	*/
	class IHingeJoint
		: public IJoint
	{
	protected:
		virtual ~IHingeJoint(){}

	public:
		virtual void SetAngularOnly( bool IsAngularOnly ) = 0;
		virtual void EnableAngularMotor( bool IsMotor, float TargetVelocity, float MaxMotorImpulse ) = 0;
		virtual void EnableMotor( bool IsMotor ) = 0;
		virtual void SetMaxMotorImpulse( float MaxMotorImpulse ) = 0;
		virtual void SetMotorTarget( const Kernel::Math::Quaternion& AinB, float DeltaTime ) = 0;
		virtual void SetMotorTarget( float TargetAngle, float DeltaTime ) = 0;
		virtual void SetLimit( float Low, float High, float Softness = 0.9f, float BiasFactor = 0.3f, float RelaxationFactor = 1.0f ) = 0;
		virtual void SetAxis( const Kernel::Math::VectorS& AxisInA ) = 0;
	};
}
}
}
}

/**
	@file
	@brief スライダージョイント
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Joint
{
	/**
		@brief スライダージョイントインターフェイス
		@author 葉迩倭
	*/
	class ISliderJoint
		: public IJoint
	{
	protected:
		virtual ~ISliderJoint(){}

	public:
		/**
			@brief 移動下限設定
			@author 葉迩倭
			@param Value	[in] 移動下限値
			@note
			スライダーの移動量の下限
		*/
		virtual void SetLowerLinLimit( float Value ) = 0;
		/**
			@brief 移動上限設定
			@author 葉迩倭
			@param Value	[in] 移動上限値
			@note
			スライダーの移動量の上限
		*/
		virtual void SetUpperLinLimit( float Value ) = 0;
		/**
			@brief 回転下限設定
			@author 葉迩倭
			@param Value	[in] 回転角度下限
			@note
			スライダーの回転角度の下限
		*/
		virtual void SetLowerAngLimit( float Value ) = 0;
		/**
			@brief 回転上限設定
			@author 葉迩倭
			@param Value	[in] 回転角度上限
			@note
			スライダーの回転角度の上限
		*/
		virtual void SetUpperAngLimit( float Value ) = 0;
		/**
			@brief モーターのON/OFF設定
			@author 葉迩倭
			@param IsEnable	[in] ON/OFF
			@note
			モーターによる駆動のON/OFF設定
		*/
		virtual void SetPoweredLinMotor( bool IsEnable ) = 0;
		/**
			@brief モーターの最大トルク設定
			@author 葉迩倭
			@param Value	[in] トルク値
			@note
			モーターの最大トルク設定
		*/
		virtual void SetMaxLinMotorForce( float Value ) = 0;
		/**
			@brief モーターの加速度設定
			@author 葉迩倭
			@param Value	[in] 加速度
			@note
			モーターの加速度設定
		*/
		virtual void SetTargetLinMotorVelocity( float Value ) = 0;

		virtual float GetSoftnessDirLin() = 0;
		virtual float GetRestitutionDirLin() = 0;
		virtual float GetDampingDirLin() = 0;
		virtual float GetSoftnessDirAng() = 0;
		virtual float GetRestitutionDirAng() = 0;
		virtual float GetDampingDirAng() = 0;
		virtual float GetSoftnessLimLin() = 0;
		virtual float GetRestitutionLimLin() = 0;
		virtual float GetDampingLimLin() = 0;
		virtual float GetSoftnessLimAng() = 0;
		virtual float GetRestitutionLimAng() = 0;
		virtual float GetDampingLimAng() = 0;
		virtual float GetSoftnessOrthoLin() = 0;
		virtual float GetRestitutionOrthoLin() = 0;
		virtual float GetDampingOrthoLin() = 0;
		virtual float GetSoftnessOrthoAng() = 0;
		virtual float GetRestitutionOrthoAng() = 0;
		virtual float GetDampingOrthoAng() = 0;
	};
}
}
}
}

/**
	@file
	@brief ポイントジョイント
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Joint
{
	/**
		@brief ポイントジョイントインターフェイス
		@author 葉迩倭
	*/
	class IPointJoint
		: public IJoint
	{
	protected:
		virtual ~IPointJoint(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief スライダージョイント
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Joint
{
	enum eDofSpringJoint
	{
		JOINT_DOF_TRANSLATION_X,	// 0 : translation X
		JOINT_DOF_TRANSLATION_Y,	// 1 : translation Y
		JOINT_DOF_TRANSLATION_Z,	// 2 : translation Z
		JOINT_DOF_ROTATION_X,		// 3 : rotation X (3rd Euler rotational around new position of X axis, range [-PI+epsilon, PI-epsilon] )
		JOINT_DOF_ROTATION_Y,		// 4 : rotation Y (2nd Euler rotational around new position of Y axis, range [-PI/2+epsilon, PI/2-epsilon] )
		JOINT_DOF_ROTATION_Z,		// 5 : rotation Z (1st Euler rotational around Z axis, range [-PI+epsilon, PI-epsilon] )
		JOINT_DOF_MAX,
	};

	/**
		@brief スライダージョイントインターフェイス
		@author 葉迩倭
	*/
	class IDofSpringJoint
		: public IJoint
	{
	protected:
		virtual ~IDofSpringJoint(){}

	public:
		virtual void EnableSpring( Sint32 Index, bool IsEnable ) = 0;
		virtual void SetStiffness( Sint32 Index, float Stiffness ) = 0;
		virtual void SetDamping( Sint32 Index, float Damping ) = 0;
		virtual void SetEquilibriumPoint() = 0; // set the current constraint position/orientation as an equilibrium point for all DOF
		virtual void SetEquilibriumPoint( Sint32 Index ) = 0;  // set the current constraint position/orientation as an equilibrium point for given DOF
		virtual void SetLimit( Sint32 Index, float Low, float Hi ) = 0;
		virtual void SetLinearLowerLimit( const Kernel::Math::Vector3& LinearLower ) = 0;
		virtual void SetLinearUpperLimit( const Kernel::Math::Vector3& LinearUpper ) = 0;
		virtual void SetAngularLowerLimit( const Kernel::Math::Vector3& AngularLower ) = 0;
		virtual void SetAngularUpperLimit( const Kernel::Math::Vector3& AngularUpper ) = 0;
	};
}
}
}
}

/**
	@file
	@brief ダイナミクス用マネージャー
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
	/**
		@brief コリジョン用球
		@author 葉迩倭
	*/
	struct CollisionSphere
	{
		float Radius;
	};
	/**
		@brief コリジョン用箱
		@author 葉迩倭
	*/
	struct CollisionBox
	{
		float AxisX;
		float AxisY;
		float AxisZ;
	};
	/**
		@brief コリジョン用カプセル
		@author 葉迩倭
	*/
	struct CollisionCapsule
	{
		float Radius;
		float Length;
	};

	/**
		@brief メッシュ生成用
		@author 葉迩倭
	*/
	struct SMeshCreateInfo
	{
		Uint32 VertexCount;							///< 頂点数
		Uint32 IndexCount;							///< インデックス数
		const Kernel::Math::Vector3* pVertexTable;	///< 頂点データテーブル
		const Uint32* pIndexTable;					///< インデックスデータテーブル
	};

	/**
		@brief ジョイント用初期状態
		@author 葉迩倭
	*/
	struct SJointLocalTransform
	{
		Kernel::Math::VectorS Position;		///< 位置
		Kernel::Math::VectorS Rotation;		///< 回転角度（ＺＹＸ）
	};

	/**
		@brief ダイナミクス用インターフェイス
		@author 葉迩倭
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		/**
			@brief レイキャスト
			@author 葉迩倭
			@param RayFrom		[in] レイの始点
			@param RayTo		[in] レイの終点
			@param HitPosition	[out] レイの衝突位置
			@param HitNormal	[out] レイの衝突法線
			@param pHitBody		[out] 衝突ボディ
			@param Group		[in] レイのコリジョングループ
			@param Mask			[in] レイのコリジョンマスク
			@note
			物理ワールドに対してレイキャストを行います。
		*/
		virtual bool RayCast( const Kernel::Math::VectorS& RayFrom, const Kernel::Math::VectorS& RayTo, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal, Body::IBody*& pHitBody, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief コリジョン判定
			@author 葉迩倭
			@param Shape		[in] 判定する形状
			@param MoveFrom		[in] 移動開始座標
			@param MoveTo		[in] 移動終了座標
			@param HitPosition	[out] レイの衝突位置
			@param HitNormal	[out] レイの衝突法線
			@param pHitBody		[out] 衝突ボディ
			@param Group		[in] レイのコリジョングループ
			@param Mask			[in] レイのコリジョンマスク
			@note
			物理ワールドに対してコリジョン判定を行います。
		*/
		virtual bool SweepTestSingle( const CollisionSphere& Shape, const Kernel::Math::VectorS& MoveFrom, const Kernel::Math::VectorS& MoveTo, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal, Body::IBody*& pHitBody, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief コリジョン判定
			@author 葉迩倭
			@param Shape		[in] 判定する形状
			@param MoveFrom		[in] 移動開始座標
			@param MoveTo		[in] 移動終了座標
			@param Rotate		[in] XYZ回転角度
			@param HitPosition	[out] レイの衝突位置
			@param HitNormal	[out] レイの衝突法線
			@param pHitBody		[out] 衝突ボディ
			@param Group		[in] レイのコリジョングループ
			@param Mask			[in] レイのコリジョンマスク
			@note
			物理ワールドに対してコリジョン判定を行います。
		*/
		virtual bool SweepTestSingle( const CollisionBox& Shape, const Kernel::Math::VectorS& MoveFrom, const Kernel::Math::VectorS& MoveTo, const Kernel::Math::VectorS& Rotate, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal, Body::IBody*& pHitBody, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief コリジョン判定
			@author 葉迩倭
			@param Shape		[in] 判定する形状
			@param MoveFrom		[in] 移動開始座標
			@param MoveTo		[in] 移動終了座標
			@param Rotate		[in] XYZ回転角度
			@param HitPosition	[out] レイの衝突位置
			@param HitNormal	[out] レイの衝突法線
			@param pHitBody		[out] 衝突ボディ
			@param Group		[in] レイのコリジョングループ
			@param Mask			[in] レイのコリジョンマスク
			@note
			物理ワールドに対してコリジョン判定を行います。
		*/
		virtual bool SweepTestSingle( const CollisionCapsule& Shape, const Kernel::Math::VectorS& MoveFrom, const Kernel::Math::VectorS& MoveTo, const Kernel::Math::VectorS& Rotate, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal, Body::IBody*& pHitBody, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;

		/**
			@brief コリジョン判定
			@author 葉迩倭
			@param SrcShape		[in] 判定する形状１
			@param SrcMoveFrom	[in] 形状１の移動開始座標
			@param SrcMoveTo	[in] 形状１の移動終了座標
			@param SrcRotate	[in] 形状１のXYZ回転角度
			@param DstShape		[in] 判定する形状２
			@param DstPosition	[in] 形状２の位置
			@param DstRotation	[in] 形状２のXYZ回転角度
			@param HitPosition	[out] レイの衝突位置
			@param HitNormal	[out] レイの衝突法線
			@note
			形状同士のコリジョン判定を行います。
		*/
		virtual bool SingleCollision( const CollisionSphere& SrcShape, const Kernel::Math::VectorS& SrcMoveFrom, const Kernel::Math::VectorS& SrcMoveTo, const Kernel::Math::VectorS& SrcRotate, const CollisionSphere& DstShape, const Kernel::Math::VectorS& DstPosition, const Kernel::Math::VectorS& DstRotation, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal ) = 0;
		/**
			@brief コリジョン判定
			@author 葉迩倭
			@param SrcShape		[in] 判定する形状１
			@param SrcMoveFrom	[in] 形状１の移動開始座標
			@param SrcMoveTo	[in] 形状１の移動終了座標
			@param SrcRotate	[in] 形状１のXYZ回転角度
			@param DstShape		[in] 判定する形状２
			@param DstPosition	[in] 形状２の位置
			@param DstRotation	[in] 形状２のXYZ回転角度
			@param HitPosition	[out] レイの衝突位置
			@param HitNormal	[out] レイの衝突法線
			@note
			形状同士のコリジョン判定を行います。
		*/
		virtual bool SingleCollision( const CollisionSphere& SrcShape, const Kernel::Math::VectorS& SrcMoveFrom, const Kernel::Math::VectorS& SrcMoveTo, const Kernel::Math::VectorS& SrcRotate, const CollisionBox& DstShape, const Kernel::Math::VectorS& DstPosition, const Kernel::Math::VectorS& DstRotation, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal ) = 0;
		/**
			@brief コリジョン判定
			@author 葉迩倭
			@param SrcShape		[in] 判定する形状１
			@param SrcMoveFrom	[in] 形状１の移動開始座標
			@param SrcMoveTo	[in] 形状１の移動終了座標
			@param SrcRotate	[in] 形状１のXYZ回転角度
			@param DstShape		[in] 判定する形状２
			@param DstPosition	[in] 形状２の位置
			@param DstRotation	[in] 形状２のXYZ回転角度
			@param HitPosition	[out] レイの衝突位置
			@param HitNormal	[out] レイの衝突法線
			@note
			形状同士のコリジョン判定を行います。
		*/
		virtual bool SingleCollision( const CollisionSphere& SrcShape, const Kernel::Math::VectorS& SrcMoveFrom, const Kernel::Math::VectorS& SrcMoveTo, const Kernel::Math::VectorS& SrcRotate, const CollisionCapsule& DstShape, const Kernel::Math::VectorS& DstPosition, const Kernel::Math::VectorS& DstRotation, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal ) = 0;
		/**
			@brief コリジョン判定
			@author 葉迩倭
			@param SrcShape		[in] 判定する形状１
			@param SrcMoveFrom	[in] 形状１の移動開始座標
			@param SrcMoveTo	[in] 形状１の移動終了座標
			@param SrcRotate	[in] 形状１のXYZ回転角度
			@param DstShape		[in] 判定する形状２
			@param DstPosition	[in] 形状２の位置
			@param DstRotation	[in] 形状２のXYZ回転角度
			@param HitPosition	[out] レイの衝突位置
			@param HitNormal	[out] レイの衝突法線
			@note
			形状同士のコリジョン判定を行います。
		*/
		virtual bool SingleCollision( const CollisionBox& SrcShape, const Kernel::Math::VectorS& SrcMoveFrom, const Kernel::Math::VectorS& SrcMoveTo, const Kernel::Math::VectorS& SrcRotate, const CollisionBox& DstShape, const Kernel::Math::VectorS& DstPosition, const Kernel::Math::VectorS& DstRotation, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal ) = 0;
		/**
			@brief コリジョン判定
			@author 葉迩倭
			@param SrcShape		[in] 判定する形状１
			@param SrcMoveFrom	[in] 形状１の移動開始座標
			@param SrcMoveTo	[in] 形状１の移動終了座標
			@param SrcRotate	[in] 形状１のXYZ回転角度
			@param DstShape		[in] 判定する形状２
			@param DstPosition	[in] 形状２の位置
			@param DstRotation	[in] 形状２のXYZ回転角度
			@param HitPosition	[out] レイの衝突位置
			@param HitNormal	[out] レイの衝突法線
			@note
			形状同士のコリジョン判定を行います。
		*/
		virtual bool SingleCollision( const CollisionBox& SrcShape, const Kernel::Math::VectorS& SrcMoveFrom, const Kernel::Math::VectorS& SrcMoveTo, const Kernel::Math::VectorS& SrcRotate, const CollisionCapsule& DstShape, const Kernel::Math::VectorS& DstPosition, const Kernel::Math::VectorS& DstRotation, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal ) = 0;
		/**
			@brief コリジョン判定
			@author 葉迩倭
			@param SrcShape		[in] 判定する形状１
			@param SrcMoveFrom	[in] 形状１の移動開始座標
			@param SrcMoveTo	[in] 形状１の移動終了座標
			@param SrcRotate	[in] 形状１のXYZ回転角度
			@param DstShape		[in] 判定する形状２
			@param DstPosition	[in] 形状２の位置
			@param DstRotation	[in] 形状２のXYZ回転角度
			@param HitPosition	[out] レイの衝突位置
			@param HitNormal	[out] レイの衝突法線
			@note
			形状同士のコリジョン判定を行います。
		*/
		virtual bool SingleCollision( const CollisionCapsule& SrcShape, const Kernel::Math::VectorS& SrcMoveFrom, const Kernel::Math::VectorS& SrcMoveTo, const Kernel::Math::VectorS& SrcRotate, const CollisionCapsule& DstShape, const Kernel::Math::VectorS& DstPosition, const Kernel::Math::VectorS& DstRotation, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal ) = 0;

		/**
			@brief 重力取得
			@author 少佐
			@return 重力
			@note
			シミュレーションワールドの重力を取得します。
		*/
		virtual Kernel::Math::VectorS GetGravity() = 0;

		/**
			@brief 重力設定
			@author 葉迩倭
			@param Gravity	[in] 重力
			@note
			シミュレーションワールドの重力を設定します。
		*/
		virtual void SetGravity( const Kernel::Math::VectorS& Gravity ) = 0;
		/**
			@brief 物理シミュレーションのステップパラメーター設定
			@author 葉迩倭
			@param StepTime	[in] １シミュレーションステップの時間（秒指定）
			@param Iteration	[in] １シミュレーションの処理回数
			@note
			シミュレーション時の分解能を設定します。<BR>
			Iterationが大きくなるほどコリジョンの抜け等が減り安定しますが、<BR>
			その分処理が重くなっていきます。
		*/
		virtual void SetStepSimulationParameteer( float StepTime, Uint32 Iteration ) = 0;
		/**
			@brief 物理シミュレーションのステップ
			@author 葉迩倭
			@param StepTimeScale	[in] 更新時間倍率
			@note
			実際のシミュレーションの実行
		*/
		virtual void StepSimulation( float StepTimeScale = 1.0f ) = 0;
		/**
			@brief 衝突ポイントを更新
			@author 葉迩倭
			@note
			衝突のポイントのリストを更新
		*/
		virtual void EndSimulation() = 0;
		/**
			@brief デバッグ用オブジェ描画
			@author 葉迩倭
			@param pLine		[in] ラインレンダラー
			@param pTriangle	[in] ポリゴンレンダラー
			@param pCamera		[in] 描画に使うカメラ
			@note
			デバッグ用の簡易シェイプの描画を行います。
		*/
		virtual void DrawDebugShape( Graphics::Simple::ILineRenderer* pLine, Graphics::Simple::ITriangleRenderer* pTriangle, const Kernel::Math::Matrix* pCamera ) = 0;
		/**
			@brief デバッグ用接触点描画
			@author 葉迩倭
			@param pLineRenderer	[in] ラインレンダラー
			@param Lenfth			[in] 接触点の法線の長さ
			@note
			デバッグ用の接触点の描画を行います。
		*/
		virtual void DrawDebugContactPoint( Graphics::Simple::ILineRenderer* pLineRenderer, float Lenfth ) = 0;

		/**
			@brief 複合ボディ生成
			@author 葉迩倭
			@param pCompoundTbl		[in] ボディのテーブル
			@param CompoundCount	[in] ボディの数1
			@param Mass			[in] 質量
			@param InitPosition		[in] 初期位置
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			複数のボディを組み合わせた複合ボディを作成します。
		*/
		virtual Body::ICompound* CreateCompound( const Body::CompoundShape* pCompoundTbl[], Uint32 CompoundCount, float Mass, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief 床生成
			@author 葉迩倭
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			無限平面の床のボディを作成します。<BR>
			このボディに対する物理シミュレーションは無効です。
		*/
		virtual Body::IPlane* CreateFloor( Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief 球生成
			@author 葉迩倭
			@param Radius			[in] 球の半径
			@param Mass			[in] 質量
			@param InitPosition		[in] 初期位置
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			球状のボディを作成します。
		*/
		virtual Body::ISphere* CreateSphere( float Radius, float Mass, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief カプセル生成
			@author 葉迩倭
			@param Length			[in] カプセルの長さ
			@param Radius			[in] カプセルの半径
			@param Mass			[in] 質量
			@param InitPosition		[in] 初期位置
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			カプセル状のボディを作成します。
		*/
		virtual Body::ICapsule* CreateCapsule( float Length, float Radius, float Mass, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief ボックス生成
			@author 葉迩倭
			@param Size				[in] 箱のサイズ（３辺）
			@param Mass			[in] 質量
			@param InitPosition		[in] 初期位置
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			箱状のボディを作成します。
		*/
		virtual Body::IBox* CreateBox( const Kernel::Math::VectorS& Size, float Mass, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief メッシュ生成
			@author 葉迩倭
			@param Mass				[in] 質量
			@param Info				[in] メッシュ情報
			@param InitPosition		[in] 初期位置
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			メッシュ形状のボディを作成します。
		*/
		virtual Body::ITriMesh* CreateTriMesh( float Mass, const SMeshCreateInfo& Info, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief メッシュ生成
			@author 葉迩倭
			@param Mass				[in] 質量
			@param pInfo			[in] メッシュ情報テーブル
			@param InfoCount		[in] メッシュ情報テーブル数
			@param InitPosition		[in] 初期位置
			@param Inertia			[in] 慣性
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			メッシュ形状のボディを作成します。
		*/
		virtual Body::ITriMesh* CreateTriMesh( float Mass, const SMeshCreateInfo* pInfo, Uint32 InfoCount, const Kernel::Math::VectorS& InitPosition, const Kernel::Math::VectorS& Inertia, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief マップ用メッシュ生成
			@author 葉迩倭
			@param Info				[in] メッシュ情報
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			マップ用のメッシュ形状のボディを作成します。<BR>
			このボディは物理シミュレーションは無効です。
		*/
		virtual Body::ITriMesh* CreateTriMeshForMap( const SMeshCreateInfo& Info, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief マップ用メッシュ生成
			@author 葉迩倭
			@param pInfo			[in] メッシュ情報テーブル
			@param InfoCount		[in] メッシュ情報テーブル数
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			マップ用のメッシュ形状のボディを作成します。<BR>
			このボディは物理シミュレーションは無効です。
		*/
		virtual Body::ITriMesh* CreateTriMeshForMap( const SMeshCreateInfo* pInfo, Uint32 InfoCount, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;

		/**
			@brief キャラクター用プロキシー生成
			@author 少佐
			@param Mass				[in] 質量
			@param Length			[in] カプセルの長さ
			@param Radius			[in] カプセルの半径
			@param InitPosition		[in] 初期位置
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			キャラクター操作用の特殊なカプセル形状のボディを作成します。<BR>
			Delegateにより、関数を設定することによってキャラクター用の動作を実現します。
		*/
		virtual Body::ICharaProxy* CreateCharaProxy( float Mass, float Length, float Radius, const Kernel::Math::VectorS& InitPosition, Uint16 Group= 0xFFFF, Uint16 Mask= 0xFFFF ) = 0;
		/**
			@brief キャラクター用プロキシー生成
			@author 少佐
			@param Mass				[in] 質量
			@param Radius			[in] 球の半径
			@param InitPosition		[in] 初期位置
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			キャラクター操作用の特殊な球形状のボディを作成します。<BR>
			Delegateにより、関数を設定することによってキャラクター用の動作を実現します。
		*/
		virtual Body::ICharaProxy* CreateCharaProxy( float Mass, float Radius, const Kernel::Math::VectorS& InitPosition, Uint16 Group= 0xFFFF, Uint16 Mask= 0xFFFF ) = 0;
		/**
			@brief 簡易キャラクター用プロキシー生成
			@author 葉迩倭
			@param Length			[in] カプセルの長さ
			@param Radius			[in] カプセルの半径
			@param InitPosition		[in] 初期位置
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			キャラクター操作用の特殊なカプセル形状のボディを作成します。<BR>
			基本的に物理シミュレーションに則って動きますが坂の滑り方や<BR>
			摩擦の処理が特殊なものになっています。
		*/
		virtual Body::ICharaProxySimple* CreateCharaProxySimple( float Length, float Radius, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief 簡易キャラクター用プロキシー生成
			@author 葉迩倭
			@param Radius			[in] 球の半径
			@param InitPosition		[in] 初期位置
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			キャラクター操作用の特殊な球形状のボディを作成します。<BR>
			基本的に物理シミュレーションに則って動きますが坂の滑り方や<BR>
			摩擦の処理が特殊なものになっています。
		*/
		virtual Body::ICharaProxySimple* CreateCharaProxySimple( float Radius, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief トリガーボックスの生成
			@author 葉迩倭
			@param Size				[in] 箱のサイズ（３辺）
			@param InitPosition		[in] 初期位置
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			イベント用の箱状のボディを作成します。<BR>
			何かがここに入った時にイベントを起こすなどの処理のために使います。
		*/
		virtual Body::ITriggerBox* CreateTriggerBox( const Kernel::Math::VectorS& Size, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;

		/**
			@brief ロープの生成
			@author 葉迩倭
			@param From				[in] 始点
			@param To				[in] 終点
			@param Count			[in] ノードの数
			@param Mass				[in] 質量
			@param IsLockFrom		[in] From部分を固定
			@param IsLockTo			[in] To部分を固定
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			ロープ状のソフトボディを生成します。
		*/
		virtual Body::IRope* CreateRope( const Kernel::Math::VectorS& From, const Kernel::Math::VectorS& To, Sint32 Count, float Mass, bool IsLockFrom, bool IsLockTo, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;

		/**
			@brief スライダージョイントの生成
			@author 葉迩倭
			@param pBody0		[in] 接続元のボディ
			@param pBody1		[in] 接続先のボディ
			@param Transform0	[in] 接続元の初期状態
			@param Transform1	[in] 接続先の初期状態
			@note
			１軸回転、１軸移動のスライダー式のジョイントを作成します。<BR>
			２つのボディをスライダーで接続する場合に利用します。
		*/
		virtual Joint::ISliderJoint* CreateSliderJoint( Body::IBody* pBody0, Body::IBody* pBody1, const SJointLocalTransform& Transform0, const SJointLocalTransform& Transform1 ) = 0;
		/**
			@brief ヒンジジョイントの生成
			@author 葉迩倭
			@param pBody0		[in] 接続元のボディ
			@param pBody1		[in] 接続先のボディ
			@param Transform0	[in] 接続元の初期状態
			@param Transform1	[in] 接続先の初期状態
			@note
			１軸回転のヒンジ式のジョイントを作成します。<BR>
			２つのボディをヒンジで接続する場合に利用します。
		*/
		virtual Joint::IHingeJoint* CreateHingeJoint( Body::IBody* pBody0, Body::IBody* pBody1, const SJointLocalTransform& Transform0, const SJointLocalTransform& Transform1 ) = 0;
		/**
			@brief ポイントジョイントの生成
			@author 葉迩倭
			@param pBody0		[in] 接続元のボディ
			@param pBody1		[in] 接続先のボディ
			@param Pivot0		[in] 接続元の接続場所
			@param Pivot1		[in] 接続先の接続場所
			@note
			３軸回転のポイント式のジョイントを作成します。<BR>
			２つのボディをポイントで接続する場合に利用します。
		*/
		virtual Joint::IPointJoint* CreatePointJoint( Body::IBody* pBody0, Body::IBody* pBody1, const Kernel::Math::VectorS& Pivot0, const Kernel::Math::VectorS& Pivot1 ) = 0;

		virtual Joint::IDofSpringJoint* CreateDofSpringJoint( Body::IBody* pBody0, Body::IBody* pBody1, const Kernel::Math::VectorS& Pivot0, const Kernel::Math::VectorS& Pivot1 ) = 0;

		/**
			@brief 衝突判定球生成
			@author 少佐
			@param Radius			[in] 球の半径
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			衝突判定用球状のボディを作成します。
		*/
		virtual Body::ICollisionSphere* CreateCollisionSphere( float Radius, Uint16 Group, Uint16 Mask ) = 0;
	
		/**
			@brief 衝突判定カプセル生成
			@author 少佐
			@param Length			[in] カプセルの長さ
			@param Radius			[in] カプセルの半径
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			衝突判定用カプセル状のボディを作成します。
		*/
		virtual Body::ICollisionCapsule* CreateCollisionCapsule( float Length, float Radius, Uint16 Group, Uint16 Mask ) = 0;
		/**
			@brief 衝突判定ボックス生成
			@author 少佐
			@param Size				[in] 箱のサイズ（３辺）
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			衝突判定用箱状のボディを作成します。
		*/
		virtual Body::ICollisionBox* CreateCollisionBox( const Kernel::Math::VectorS& Size, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief 衝突判定メッシュ生成
			@author 少佐
			@param Info				[in] メッシュ情報
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			衝突判定用メッシュ形状のボディを作成します。
		*/
		virtual Body::ICollisionTriMesh* CreateCollisionTriMesh( const SMeshCreateInfo& Info, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief 衝突判定メッシュ生成
			@author 少佐
			@param pInfo			[in] メッシュ情報テーブル
			@param InfoCount		[in] メッシュ情報テーブル数
			@param Group			[in] コリジョンのグループ（自分のグループ）
			@param Mask				[in] コリジョンのマスク（接触対象のマスク）
			@note
			衝突判定用メッシュ形状のボディを作成します。
		*/
		virtual Body::ICollisionTriMesh* CreateCollisionTriMesh( const SMeshCreateInfo* pInfo, Uint32 InfoCount, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
	};
}
}
}

/**
	@file
	@brief 標準実装マテリアル
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Renderer
{
namespace Standard
{
namespace Material
{
namespace Standard
{
	/**
		@brief 標準実装用マテリアルテクスチャステージ
		@author 葉迩倭
	*/
	enum eTextureStage
	{
		TEXTURE_STAGE_COLOR,			///< 拡散反射
		TEXTURE_STAGE_EMISSIVE,			///< 自己発光
		TEXTURE_STAGE_ENVIRONMENT,		///< 環境マップ（キューブマップ）
		TEXTURE_STAGE_SPECULAR,			///< 鏡面反射
		TEXTURE_STAGE_NORMAL,			///< 法線マップ
		TEXTURE_STAGE_HEIGHT,			///< 視差マップ用高さマップ
		TEXTURE_STAGE_LIGHT_LOOKUP,		///< ライト参照テクスチャ
		TEXTURE_STAGE_MAX,
	};

	/**
		@brief 標準実装マテリアル
		@author 葉迩倭
	*/
	class IMaterial
		: public Engine::Graphics::Resource::IMaterialPlugin
	{
	protected:
		virtual ~IMaterial() {}

	public:
		/**
			@brief ライティングの有無を設定
			@author 葉迩倭
			@param Enable	[in] ライティング利用時はtrue
			@note
			マテリアルに対してライトの処理のON/OFFを設定します。
		*/
		virtual void SetLightEnable( bool Enable ) = 0;
		/**
			@brief ライティングの有無を取得
			@author 葉迩倭
			@retval true	ライトあり
			@retval false	ライトなし
			@note
			ライティングを行うかどうかを取得します。
		*/
		virtual bool IsLightEnable() const = 0;

		/**
			@brief 自己発光の有無を設定
			@author 葉迩倭
			@param Enable	[in] 自己発光利用時はtrue
			@note
			マテリアルに対して自己発光の処理のON/OFFを設定します。
		*/
		virtual void SetEmissiveEnable( bool Enable ) = 0;
		/**
			@brief 自己発光の有無を取得
			@author 葉迩倭
			@retval true	自己発光あり
			@retval false	自己発光なし
			@note
			自己発光を行うかどうかを取得します。
		*/
		virtual bool IsEmissiveEnable() const = 0;

		/**
			@brief 鏡面反射の有無を設定
			@author 葉迩倭
			@param Enable	[in] 鏡面反射利用時はtrue
			@note
			マテリアルに対して鏡面反射の処理のON/OFFを設定します。
		*/
		virtual void SetSpecularEnable( bool Enable ) = 0;
		/**
			@brief 鏡面反射の有無を取得
			@author 葉迩倭
			@retval true	鏡面反射あり
			@retval false	鏡面反射なし
			@note
			鏡面反射を行うかどうかを取得します。
		*/
		virtual bool IsSpecularEnable() const = 0;

		/**
			@brief ライトの種類を設定
			@author 葉迩倭
			@param Value	[in] 種類
			@note
			ライトの種類を設定します。
		*/
		virtual void SetLightType( Sint32 Type ) = 0;
		/**
			@brief ライトの種類を取得
			@author 葉迩倭
			@return	ライトの種類
			@note
			適用するライトの種類を取得します。
		*/
		virtual Sint32 GetLightType() const = 0;

		/**
			@brief ソート用のレイヤーを設定
			@author 葉迩倭
			@param Value	[in] ソート値
			@note
			ソート時の基準値を設定します。
		*/
		virtual void SetSortKey( Uint32 Value ) = 0;
		/**
			@brief ソー用のキーを取得
			@author 葉迩倭
			@return ソート用のキー
			@note
			ソートに利用するキーを取得します。
		*/
		virtual Uint32 GetSortKey() const = 0;

		/**
			@brief マルチポリゴン用レイヤーを設定
			@author 葉迩倭
			@param Value	[in] レイヤー
			@note
			マルチポリゴン用のレイヤー設定します。
		*/
		virtual void SetMultiPolygonLayer( Uint32 Value ) = 0;
		/**
			@brief マルチポリゴン用レイヤーを取得
			@author 葉迩倭
			@return マルチポリゴン用レイヤー
			@note
			マルチポリゴン用のレイヤーを取得します。
		*/
		virtual Uint32 GetMultiPolygonLayer() const = 0;

		/**
			@brief シャドウマップの挙動を設定
			@author 葉迩倭
			@param Value	[in] 挙動
			@note
			シャドウマップ処理時の挙動を設定します。
		*/
		virtual void SetShadowMapType( Uint32 Value ) = 0;
		/**
			@brief シャドウマップの挙動を取得
			@author 葉迩倭
			@return シャドウマップの挙動
			@note
			シャドウマップ時の挙動を取得します。
		*/
		virtual Uint32 GetShadowMapType() const = 0;

		/**
			@brief レンダリング用レイヤーを設定
			@author 葉迩倭
			@param Value	[in] レイヤー
			@note
			レンダリング用のレイヤーを設定します。
		*/
		virtual void SetRenderingLayer( Uint32 Value ) = 0;
		/**
			@brief 描画用レイヤーを取得
			@author 葉迩倭
			@return 描画用レイヤー
			@note
			描画用のレイヤーを取得します。
		*/
		virtual Uint32 GetRenderingLayer() const = 0;

		/**
			@brief テクスチャのUVオフセットを設定
			@author 葉迩倭
			@param Offset	[in] テクスチャのUVオフセット
			@note
			マテリアルに対してテクスチャのUVオフセットを設定します。
		*/
		virtual void SetTextureOffset( const Kernel::Math::Vector2& Offset ) = 0;
		/**
			@brief テクスチャのUVオフセットを取得
			@author 葉迩倭
			@return テクスチャのUVオフセット
			@note
			マテリアルからテクスチャのUVオフセットを取得します。
		*/
		virtual const Kernel::Math::Vector2& GetTextureOffset() const = 0;

		/**
			@brief 拡散反射の色を設定
			@author 葉迩倭
			@param Diffuse	[in] 拡散反射の色
			@note
			マテリアルに対して拡散反射の色を設定します。
		*/
		virtual void SetDiffuse( const Kernel::Math::VectorS& Diffuse ) = 0;
		/**
			@brief 拡散反射の色を取得
			@author 葉迩倭
			@return 拡散反射色
			@note
			拡散反射の色を取得します。
		*/
		virtual const Kernel::Math::VectorS& GetDiffuse() const = 0;

		/**
			@brief 自己発光の色を設定
			@author 葉迩倭
			@param Emissive	[in] 自己発光の色
			@note
			マテリアルに対して自己発光の色を設定します。
		*/
		virtual void SetEmissive( const Kernel::Math::VectorS& Emissive ) = 0;
		/**
			@brief 自己発光の色を取得
			@author 葉迩倭
			@return 自己発光色
			@note
			自己発光の色を取得します。
		*/
		virtual const Kernel::Math::VectorS& GetEmissive() const = 0;

		/**
			@brief 鏡面反射の色を設定
			@author 葉迩倭
			@param Specular	[in] 鏡面反射の色
			@note
			マテリアルに対して鏡面反射の色を設定します。
		*/
		virtual void SetSpecular( const Kernel::Math::VectorS& Specular ) = 0;
		/**
			@brief 鏡面反射の色を取得
			@author 葉迩倭
			@return 鏡面反射色
			@note
			鏡面反射の色を取得します。
		*/
		virtual const Kernel::Math::VectorS& GetSpecular() const = 0;

		/**
			@brief 鏡面反射のバイアスを設定
			@author 葉迩倭
			@param Value	[in] 鏡面反射のバイアス値
			@note
			鏡面反射の計算時のバイアス値を設定します。<BR>
			鏡面反射は以下の式で求められます。<BR>
			Result = Bias + (Scale * pow( Pow ))
		*/
		virtual void SetSpecularBias( float Value ) = 0;
		/**
			@brief 鏡面反射のバイアスを取得
			@author 葉迩倭
			@return バイアス値
			@note
			鏡面反射のバイアス値を取得します。
		*/
		virtual float GetSpecularBias() const = 0;

		/**
			@brief 鏡面反射のスケールを設定
			@author 葉迩倭
			@param Value	[in] 鏡面反射のスケール値
			@note
			鏡面反射の計算時のスケール値を設定します。<BR>
			鏡面反射は以下の式で求められます。<BR>
			Result = Bias + (Scale * pow( Pow ))
		*/
		virtual void SetSpecularScale( float Value ) = 0;
		/**
			@brief 鏡面反射のスケールを取得
			@author 葉迩倭
			@return スケール値
			@note
			鏡面反射のスケール値を取得します。
		*/
		virtual float GetSpecularScale() const = 0;

		/**
			@brief 鏡面反射の係数を設定
			@author 葉迩倭
			@param Value	[in] 鏡面反射の係数値
			@note
			鏡面反射の計算時の係数値を設定します。<BR>
			鏡面反射は以下の式で求められます。<BR>
			Result = Bias + (Scale * pow( Pow ))
		*/
		virtual void SetSpecularPow( float Value ) = 0;
		/**
			@brief 鏡面反射の係数を取得
			@author 葉迩倭
			@return 係数値
			@note
			鏡面反射の係数値を取得します。
		*/
		virtual float GetSpecularPow() const = 0;

		/**
			@brief 法線マップのスケール値を設定
			@author 葉迩倭
			@param Value	[in] 法線マップのスケール値（大きいほど凹凸がはっきりする）
			@note
			法線マップの法線に対してのスケール値を設定します。
		*/
		virtual void SetNormalScale( float Value ) = 0;
		/**
			@brief 法線マップのスケール値を取得
			@author 葉迩倭
			@return スケール値
			@note
			法線マップの法線に対してのスケール値を取得します。
		*/
		virtual float GetNormalScale() const = 0;

		/**
			@brief 視差マップ時の最少サンプル数を設定
			@author 葉迩倭
			@param Value	[in] 視差マップの最少サンプル数
			@note
			視差マップ時の最少のサンプル数を設定します。
		*/
		virtual void SetParallaxMinSample( Sint32 Value ) = 0;
		/**
			@brief 視差マップ時の最少サンプル数を取得
			@author 葉迩倭
			@return 視差マップの最少サンプル数
			@note
			視差マップ時の最少サンプル数を取得します。
		*/
		virtual Sint32 GetParallaxMinSample() = 0;

		/**
			@brief 視差マップ時の最大サンプル数を設定
			@author 葉迩倭
			@param Value	[in] 視差マップの最大サンプル数
			@note
			視差マップ時の最大のサンプル数を設定します。
		*/
		virtual void SetParallaxMaxSample( Sint32 Value ) = 0;
		/**
			@brief 視差マップ時の最大サンプル数を取得
			@author 葉迩倭
			@return 視差マップの最大サンプル数
			@note
			視差マップ時の最大サンプル数を取得します。
		*/
		virtual Sint32 GetParallaxMaxSample() const = 0;

		/**
			@brief 視差マップの高さを設定
			@author 葉迩倭
			@param Value	[in] 視差マップの高さ値
			@note
			視差マップ時の高さを設定します。<BR>
			高くするほど凹凸がはっきりしますが<BR>
			サンプル数が少ないと汚くなります。
		*/
		virtual void SetParallaxHeight( float Value ) = 0;
		/**
			@brief 視差マップの高さを取得
			@author 葉迩倭
			@return 視差マップの高さ
			@note
			視差マップ時の高さを取得します。
		*/
		virtual float GetParallaxHeight() const = 0;
	};
}
}
}
}
}
}
/**
	@file
	@brief 標準実装マテリアル
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Renderer
{
namespace Standard
{
namespace Material
{
namespace Water
{
	/**
		@brief 標準実装用マテリアルテクスチャステージ
		@author 葉迩倭
	*/
	enum eTextureStage
	{
		TEXTURE_STAGE_ENVIRONMENT,		///< 環境マップ（キューブマップ）
		TEXTURE_STAGE_NORMAL_A,			///< 法線マップ
		TEXTURE_STAGE_NORMAL_B,			///< 法線マップ
		TEXTURE_STAGE_MAX,
	};

	/**
		@brief 標準実装マテリアル
		@author 葉迩倭
	*/
	class IMaterial
		: public Engine::Graphics::Resource::IMaterialPlugin
	{
	protected:
		virtual ~IMaterial() {}

	public:
		/**
			@brief 拡散反射の色を設定
			@author 葉迩倭
			@param Diffuse	[in] 拡散反射の色
			@note
			マテリアルに対して拡散反射の色を設定します。
		*/
		virtual void SetDiffuse( const Kernel::Math::VectorS& Diffuse ) = 0;
		/**
			@brief 拡散反射の色を取得
			@author 葉迩倭
			@return 拡散反射色
			@note
			拡散反射の色を取得します。
		*/
		virtual const Kernel::Math::VectorS& GetDiffuse() const = 0;

		/**
			@brief 鏡面反射の色を設定
			@author 葉迩倭
			@param Specular	[in] 鏡面反射の色
			@note
			マテリアルに対して鏡面反射の色を設定します。
		*/
		virtual void SetSpecular( const Kernel::Math::VectorS& Specular ) = 0;
		/**
			@brief 鏡面反射の色を取得
			@author 葉迩倭
			@return 鏡面反射色
			@note
			鏡面反射の色を取得します。
		*/
		virtual const Kernel::Math::VectorS& GetSpecular() const = 0;

		/**
			@brief 鏡面反射のバイアスを設定
			@author 葉迩倭
			@param Value	[in] 鏡面反射のバイアス値
			@note
			鏡面反射の計算時のバイアス値を設定します。<BR>
			鏡面反射は以下の式で求められます。<BR>
			Result = Bias + (Scale * pow( Pow ))
		*/
		virtual void SetSpecularBias( float Value ) = 0;
		/**
			@brief 鏡面反射のバイアスを取得
			@author 葉迩倭
			@return バイアス値
			@note
			鏡面反射のバイアス値を取得します。
		*/
		virtual float GetSpecularBias() const = 0;

		/**
			@brief 鏡面反射のスケールを設定
			@author 葉迩倭
			@param Value	[in] 鏡面反射のスケール値
			@note
			鏡面反射の計算時のスケール値を設定します。<BR>
			鏡面反射は以下の式で求められます。<BR>
			Result = Bias + (Scale * pow( Pow ))
		*/
		virtual void SetSpecularScale( float Value ) = 0;

		/**
			@brief 鏡面反射のスケールを取得
			@author 葉迩倭
			@return スケール値
			@note
			鏡面反射のスケール値を取得します。
		*/
		virtual float GetSpecularScale() const = 0;

		/**
			@brief 鏡面反射の係数を設定
			@author 葉迩倭
			@param Value	[in] 鏡面反射の係数値
			@note
			鏡面反射の計算時の係数値を設定します。<BR>
			鏡面反射は以下の式で求められます。<BR>
			Result = Bias + (Scale * pow( Pow ))
		*/
		virtual void SetSpecularPow( float Value ) = 0;
		/**
			@brief 鏡面反射の係数を取得
			@author 葉迩倭
			@return 係数値
			@note
			鏡面反射の係数値を取得します。
		*/
		virtual float GetSpecularPow() const = 0;

		/**
			@brief 法線マップのスケール値を設定
			@author 葉迩倭
			@param Value	[in] 法線マップのスケール値（大きいほど凹凸がはっきりする）
			@note
			法線マップの法線に対してのスケール値を設定します。
		*/
		virtual void SetNormalScaleA( float Value ) = 0;
		/**
			@brief 法線マップのスケール値を取得
			@author 葉迩倭
			@return スケール値
			@note
			法線マップの法線に対してのスケール値を取得します。
		*/
		virtual float GetNormalScaleA() const = 0;

		/**
			@brief 法線マップのスケール値を設定
			@author 葉迩倭
			@param Value	[in] 法線マップのスケール値（大きいほど凹凸がはっきりする）
			@note
			法線マップの法線に対してのスケール値を設定します。
		*/
		virtual void SetNormalScaleB( float Value ) = 0;
		/**
			@brief 法線マップのスケール値を取得
			@author 葉迩倭
			@return スケール値
			@note
			法線マップの法線に対してのスケール値を取得します。
		*/
		virtual float GetNormalScaleB() const = 0;

		/**
			@brief 法線マップのスケール値を設定
			@author 葉迩倭
			@param Value	[in] 法線マップのスケール値（大きいほど凹凸がはっきりする）
			@note
			法線マップの法線に対してのスケール値を設定します。
		*/
		virtual void SetReflectRate( float Value ) = 0;
		/**
			@brief 法線マップのスケール値を取得
			@author 葉迩倭
			@return スケール値
			@note
			法線マップの法線に対してのスケール値を取得します。
		*/
		virtual float GetReflectRate() const = 0;
	};
}
}
}
}
}
}

/**
	@file
	@brief 標準実装レンダラー
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Renderer
{
namespace Standard
{

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef Uint32 POINTLIGHT_HANDLE;		///< ポイントライトのハンドル

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------


/**
	@brief ビューのタイプ
	@author 葉迩倭
*/
enum eViewType
{
	VIEW_TYPE_01,		///< １つ目のビュー
	VIEW_TYPE_02,		///< ２つ目のビュー
	VIEW_TYPE_03,		///< ３つ目のビュー
	VIEW_TYPE_04,		///< ４つ目のビュー
	VIEW_TYPE_05,		///< ５つ目のビュー
	VIEW_TYPE_06,		///< ６つ目のビュー
	VIEW_TYPE_07,		///< ７つ目のビュー
	VIEW_TYPE_08,		///< ８つ目のビュー

	VIEW_TYPE_MAX,
};

/**
	@brief 平行光源のタイプ
	@author 葉迩倭
*/
enum eDirectionLight
{
	DIRECTION_LIGHT_MAIN,	///< メインの平行光源
	DIRECTION_LIGHT_SUB1,	///< サブ１
	DIRECTION_LIGHT_SUB2,	///< サブ２
	DIRECTION_LIGHT_SUB3,	///< サブ３

	DIRECTION_LIGHT_MAX,
};

/**
	@brief シャドウマップの種類
	@author 葉迩倭
*/
enum eShadowMapType
{
	SHADOW_MAP_DISABLE,		///< なし
	SHADOW_MAP_STANDARD,	///< シャドウマップ
	SHADOW_MAP_SOFT,		///< 3x3サンプルPCFによるソフトシャドウ

	SHADOW_MAP_MAX,
};

/**
	@brief マテリアルの種類
	@author 葉迩倭
*/
enum eMaterialType
{
	MATERIAL_TYPE_STANDARD,
	MATERIAL_TYPE_WATER,

	MATERIAL_TYPE_MAX,
};

/**
	@brief レンダリング対象のレイヤー
	@author 葉迩倭
*/
enum eRenderingLayer
{
	RENDERING_LAYER_BACKGROUND,
	RENDERING_LAYER_DEFAULT,
	RENDERING_LAYER_AFTER_WATER,
	RENDERING_LAYER_AFTER_PARTICLE,

	RENDERING_LAYER_MAX,
};

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
/**
	@brief ポイントライト
	@author 葉迩倭
*/
struct SPointLight
{
	Kernel::Math::Vector4 Position;		///< ポイントライトの位置
	Kernel::Math::Vector4 Color;		///< ポイントライトの色
	float Distance;						///< ポイントライトの影響距離
};

/**
	@brief マテリアル操作用オプション
	@author 葉迩倭
*/
struct SMaterialOption
{
public:
	bool IsEmissiveMap;
	bool IsEnvironmentMap;
	bool IsSpecularMap;
	bool IsNormalMap;
	bool IsParallaxMap;
	bool IsLookUpMap;
	bool IsScattering;
	bool IsFog;

public:
	SMaterialOption()
		: IsEmissiveMap		( true )
		, IsEnvironmentMap	( true )
		, IsSpecularMap		( true )
		, IsNormalMap		( true )
		, IsParallaxMap		( true )
		, IsLookUpMap		( true )
		, IsScattering		( true )
		, IsFog				( true )
	{
	}
};

/**
	@brief レンダラーセッティング用パラメーター
	@author 葉迩倭
*/
struct SParameter
{
	bool IsHighQuality;					///< 高品質レンダリングを行う
	bool IsFog;							///< フォグの有無
	bool IsScattering;					///< 屋外散乱光の有無
	bool IsDepthOfField;				///< 被写界深度の有無
	bool IsHighDynamicRange;			///< HDRレンダリングの有無
	bool IsSoftParticle;				///< ソフトパーティクルの有無
	bool IsMotionBlur;					///< モーションブラーの有無
	bool IsAmbientOcclusion;			///< アンビエント隠蔽
	bool IsWaterInside;					///< 水中演出
	bool IsWaterDepthFog;				///< 水中高さフォグ
	bool IsDynamicReflectionMap;		///< 動的反射マップ利用
	bool IsWaterVertexAnimation;		///< 水面頂点アニメーション
	bool IsFrontFaceShadow;				///< 裏面シャドウマップ
	eShadowMapType ShadowType;			///< シャドウマップの種類

public:
	SParameter()
		: IsHighQuality					( false )
		, IsFog							( false )
		, IsScattering					( false )
		, IsDepthOfField				( false )
		, IsHighDynamicRange			( false )
		, IsSoftParticle				( false )
		, IsMotionBlur					( false )
		, IsAmbientOcclusion			( false )
		, IsWaterInside					( false )
		, IsWaterDepthFog				( false )
		, IsDynamicReflectionMap		( false )
		, IsWaterVertexAnimation		( false )
		, IsFrontFaceShadow				( false )
		, ShadowType					( SHADOW_MAP_DISABLE )
	{
	}
};

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
/**
	@brief レンダラーインターフェイス
	@author 葉迩倭
	@note
	Selene内部で標準の実装として持っているレンダラーです。<BR>
	より詳細な制御をするために自前でレンダラーを用意することも可能です。
*/
class IRenderer
	: public Interface
{
protected:
	virtual ~IRenderer() {}

public:
	/**
		@brief 描画オブジェクトの全解放
		@author 葉迩倭
		@note
		描画オブジェクト全解放。
	*/
	virtual void DestroyAllResource() = 0;

	/**
		@brief 描画オブジェクトの事前シェーダー生成
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@param Option		[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトに対して事前にシェーダーの生成を行います。<BR>
		通常はAddDrawObject()時に行われますが事前に行っておく事で登録のコストを減らせます。
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::SMF::IModelController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの事前シェーダー生成
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@param Option		[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトに対して事前にシェーダーの生成を行います。<BR>
		通常はAddDrawObject()時に行われますが事前に行っておく事で登録のコストを減らせます。
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::STM::IModelController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの事前シェーダー生成
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@param Option		[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトに対して事前にシェーダーの生成を行います。<BR>
		通常はAddDrawObject()時に行われますが事前に行っておく事で登録のコストを減らせます。
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::Particle::IParticleController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの事前シェーダー生成
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@param Option		[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトに対して事前にシェーダーの生成を行います。<BR>
		通常はAddDrawObject()時に行われますが事前に行っておく事で登録のコストを減らせます。
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::Particle::IVolumeParticleController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの事前シェーダー生成
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@param Option		[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトに対して事前にシェーダーの生成を行います。<BR>
		通常はAddDrawObject()時に行われますが事前に行っておく事で登録のコストを減らせます。
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::Particle::IEnhancedParticleController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの事前シェーダー生成
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@param Option		[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトに対して事前にシェーダーの生成を行います。<BR>
		通常はAddDrawObject()時に行われますが事前に行っておく事で登録のコストを減らせます。
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::Primitive::IPrimitiveController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの事前シェーダー生成
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@param Option		[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトに対して事前にシェーダーの生成を行います。<BR>
		通常はAddDrawObject()時に行われますが事前に行っておく事で登録のコストを減らせます。
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::Sprite::ISpriteController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの事前シェーダー生成
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@param Option		[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトに対して事前にシェーダーの生成を行います。<BR>
		通常はAddDrawObject()時に行われますが事前に行っておく事で登録のコストを減らせます。
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::PolyLine::IPolyLineController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの追加
		@author 葉迩倭
		@param pDrawObject		[in] 描画オブジェクト
		@param IsShaderBuild	[in] 登録時にシェーダーのビルドを一緒に行うかどうか
		@param Option			[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトを登録してレンダリングリストに追加します。
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::SMF::IModelController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの破棄
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@note
		登録されている描画オブジェクトを破棄します。
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::SMF::IModelController* pDrawObject ) = 0;

	/**
		@brief 描画オブジェクトの追加
		@author 葉迩倭
		@param pDrawObject		[in] 描画オブジェクト
		@param IsShaderBuild	[in] 登録時にシェーダーのビルドを一緒に行うかどうか
		@param Option			[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトを登録してレンダリングリストに追加します。
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::STM::IModelController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの破棄
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@note
		登録されている描画オブジェクトを破棄します。
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::STM::IModelController* pDrawObject ) = 0;

	/**
		@brief 描画オブジェクトの追加
		@author 葉迩倭
		@param pDrawObject		[in] 描画オブジェクト
		@param IsShaderBuild	[in] 登録時にシェーダーのビルドを一緒に行うかどうか
		@param Option			[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトを登録してレンダリングリストに追加します。
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::Particle::IParticleController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの破棄
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@note
		登録されている描画オブジェクトを破棄します。
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::Particle::IParticleController* pDrawObject ) = 0;

	/**
		@brief 描画オブジェクトの追加
		@author 葉迩倭
		@param pDrawObject		[in] 描画オブジェクト
		@param IsShaderBuild	[in] 登録時にシェーダーのビルドを一緒に行うかどうか
		@param Option			[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトを登録してレンダリングリストに追加します。
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::Particle::IVolumeParticleController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの破棄
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@note
		登録されている描画オブジェクトを破棄します。
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::Particle::IVolumeParticleController* pDrawObject ) = 0;

	/**
		@brief 描画オブジェクトの追加
		@author 葉迩倭
		@param pDrawObject		[in] 描画オブジェクト
		@param IsShaderBuild	[in] 登録時にシェーダーのビルドを一緒に行うかどうか
		@param Option			[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトを登録してレンダリングリストに追加します。
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::Particle::IEnhancedParticleController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの破棄
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@note
		登録されている描画オブジェクトを破棄します。
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::Particle::IEnhancedParticleController* pDrawObject ) = 0;

	/**
		@brief 描画オブジェクトの追加
		@author 葉迩倭
		@param pDrawObject		[in] 描画オブジェクト
		@param IsShaderBuild	[in] 登録時にシェーダーのビルドを一緒に行うかどうか
		@param Option			[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトを登録してレンダリングリストに追加します。
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::Primitive::IPrimitiveController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの破棄
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@note
		登録されている描画オブジェクトを破棄します。
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::Primitive::IPrimitiveController* pDrawObject ) = 0;

	/**
		@brief 描画オブジェクトの追加
		@author 葉迩倭
		@param pDrawObject		[in] 描画オブジェクト
		@param IsShaderBuild	[in] 登録時にシェーダーのビルドを一緒に行うかどうか
		@param Option			[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトを登録してレンダリングリストに追加します。
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::Sprite::ISpriteController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの破棄
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@note
		登録されている描画オブジェクトを破棄します。
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::Sprite::ISpriteController* pDrawObject ) = 0;

	/**
		@brief 描画オブジェクトの追加
		@author 葉迩倭
		@param pDrawObject		[in] 描画オブジェクト
		@param IsShaderBuild	[in] 登録時にシェーダーのビルドを一緒に行うかどうか
		@param Option			[in] マテリアルシェーダー用オプション
		@note
		描画オブジェクトを登録してレンダリングリストに追加します。
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::PolyLine::IPolyLineController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief 描画オブジェクトの破棄
		@author 葉迩倭
		@param pDrawObject	[in] 描画オブジェクト
		@note
		登録されている描画オブジェクトを破棄します。
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::PolyLine::IPolyLineController* pDrawObject ) = 0;

	/**
		@brief ビューの表示の有無
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@note
		ビューの表示が必要かどうかを取得します。<BR>
		表示をfalseにした場合でもIsViewRendering()がtrueであれば<BR>
		レンダリング処理は行われます。<BR>
		コレはレンダリング後の画像をユーザーが自前で処理する場合に利用できます。
	*/
	virtual bool IsViewDraw( eViewType ViewIndex ) = 0;

	/**
		@brief ビューの描画の有無
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@note
		ビューの描画が必要かどうかを取得します。<BR>
		これがfalseの場合はレンダリング処理自体が行われません。
	*/
	virtual bool IsViewRendering( eViewType ViewIndex ) = 0;

	/**
		@brief レンダリングの有無設定
		@author 葉迩倭
		@param IsRenderingEnable	[in] レンダリング有無
		@note
		レンダリングの有無を設定します。
	*/
	virtual void SetRenderingEnable( bool IsRenderingEnable ) = 0;

	/**
		@brief コマンドの生成
		@author 葉迩倭
		@param CameraTbl	[in] ビューの数分のカメラ
		@note
		描画用のコマンドを生成します。<BR>
		DrawRenderingCommand()と並列に呼び出せるようになっています。
	*/
	virtual void CreateRenderingCommandSerial( const Kernel::Math::Camera CameraTbl[] ) = 0;

	/**
		@brief コマンドの描画
		@author 葉迩倭
		@note
		生成してあるコマンドを実際に描画します。
	*/
	virtual void DrawRenderingCommand() = 0;

	/**
		@brief コマンドのフリップ
		@author 葉迩倭
		@note
		ダブルバッファになっている描画コマンドをフリップします。<BR>
		フレームの最後で呼び出すようにして下さい。
	*/
	virtual void EndFrame() = 0;

	/**
		@brief シンプルなレンダリング処理
		@author 葉迩倭
		@param CameraTbl	[in] ビューの数分のカメラ
		@note
		描画のコマンド生成から後処理までを一括で行うためのシンプルなメソッドです。
	*/
	virtual void SimpleRendering( const Kernel::Math::Camera CameraTbl[] ) = 0;

	/**
		@brief 水面アニメーション用高さテクスチャ設定
		@author 葉迩倭
		@param pTexHeightA		[in] 高さテクスチャ１
		@param pTexHeightB		[in] 高さテクスチャ２
		@note
		水面アニメーション用の高さテクスチャを設定します。
	*/
	virtual void SetWaterHeightTexture( Engine::Graphics::Resource::ITexture* pTexHeightA, Engine::Graphics::Resource::ITexture* pTexHeightB ) = 0;

	/**
		@brief 初期化
		@author 葉迩倭
		@param Parameter			[in] レンダラー用パラメーター
		@param CommandBufferBytes	[in] コマンド用バッファのサイズ
		@note
		レンダラーの初期化を行います。
	*/
	virtual bool Initialize( const SParameter& Parameter, Uint32 CommandBufferBytes = 16 * 1024 ) = 0;

	/**
		@brief 初期化
		@author 葉迩倭
		@param Parameter			[in] レンダラー用パラメーター
		@param Option				[in] マテリアル操作用オプション
		@param CommandBufferBytes	[in] コマンド用バッファのサイズ
		@note
		レンダラーの初期化を行います。
	*/
	virtual bool Initialize( const SParameter& Parameter, const SMaterialOption& Option, Uint32 CommandBufferBytes = 16 * 1024 ) = 0;

	/**
		@brief マテリアル操作用オプション変更
		@author 葉迩倭
		@param Option				[in] マテリアル操作用オプション
		@note
		マテリアル操作用オプションの変更をします。
	*/
	virtual void ChangeMaterialOption( const SMaterialOption& Option ) = 0;

	/**
		@brief マテリアル操作用オプション取得
		@author 葉迩倭
		@return マテリアル操作用オプション
		@note
		マテリアル操作用オプションの取得をします。
	*/
	virtual const SMaterialOption& GetMaterialOption() = 0;

	/**
		@brief パラメーター変更
		@author 葉迩倭
		@param Parameter	[in] レンダラー用パラメーター
		@note
		レンダラーのパラメーターを参考にリセットをかけます。<BR>
		レンダラーのパラメーターを変更したい場合に利用します。
	*/
	virtual void Reset( const SParameter& Parameter ) = 0;

	/**
		@brief ビューの生成
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param ViewRect		[in] ビューの表示先矩形（＝サイズ）
		@param IsClear		[in] ビューをクリアの有無
		@param ClearColor	[in] ビューのクリア色
		@param IsAntiAlias	[in] アンチエイリアスの有無
		@note
		レンダラーに対してビューの生成を行います。<BR>
		ビューはカメラと対になるものでビューを複数用意することで<BR>
		バックミラーや分割ウィンドウのようなものを表現することが出来ます。
	*/
	virtual void CreateView( eViewType ViewIndex, const RectI& ViewRect, bool IsClear, const ColorF& ClearColor, bool IsAntiAlias = false ) = 0;

	/**
		@brief ビューの生成
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param ViewRect		[in] ビューの表示先矩形
		@param Size			[in] ビューのサイズ
		@param IsClear		[in] ビューをクリアの有無
		@param ClearColor	[in] ビューのクリア色
		@param IsAntiAlias	[in] アンチエイリアスの有無
		@note
		レンダラーに対してビューの生成を行います。<BR>
		ビューはカメラと対になるものでビューを複数用意することで<BR>
		バックミラーや分割ウィンドウのようなものを表現することが出来ます。
	*/
	virtual void CreateView( eViewType ViewIndex, const RectI& ViewRect, const Point2DI& Size, bool IsClear, const ColorF& ClearColor, bool IsAntiAlias = false ) = 0;

	/**
		@brief ビューの削除
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@note
		レンダラーに対してビューの削除を行います。
	*/
	virtual void DeleteView( eViewType ViewIndex ) = 0;

	/**
		@brief ビューの表示先矩形取得
		@author 少佐
		@param ViewIndex	[in] ビューのインデックス
		@return ビューの表示先矩形
		@note
		ビューの表示先矩形を取得します。
	*/
	virtual const RectI& GetViewRect( eViewType ViewIndex ) = 0;

	/**
		@brief ビューの描画後のテクスチャを取得
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param pTexture		[in] 描画後のテクスチャ
		@note
		ビューのレンダリング処理後のテクスチャを取得します。<BR>
		このテクスチャはレンダリングターゲットなので<BR>
		レンダラーの描画を行っている最中は舞フレーム更新されます。
	*/
	virtual void GetViewRenderTargetTexture( eViewType ViewIndex, Engine::Graphics::Resource::ITexture*& pTexture ) = 0;

	/**
		@brief ビューの水中設定
		@author 葉迩倭
		@param ViewIndex		[in] ビューのインデックス
		@param IsWaterInside	[in] 水中の有無
		@note
		ビューに対して水中に入っているかを設定します。<BR>
		水中に入っている場合は水中シェーダーでポストエフェクトがかかります。
	*/
	virtual void SetCameraIsWaterInside( eViewType ViewIndex, bool IsWaterInside ) = 0;

	/**
		@brief ビューのリフレクション有無設定
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param IsReflection	[in] 描画の有無
		@param Plane		[in] 反射平面
		@note
		ビューに対して反射描画の有無を設定します。<BR>
		指定したビューを反射用の画像生成に使うようになります。
	*/
	virtual void SetViewReflectionMode( eViewType ViewIndex, bool IsReflection, const Kernel::Math::VectorS Point[] ) = 0;

	/**
		@brief ビューのリフレクションテクスチャ設定
		@author 葉迩倭
		@param ViewIndex		[in] ビューのインデックス
		@param pReflectTexture	[in] 反射用テクスチャ
		@note
		ビューに対して反射描画用のテクスチャを設定します。
	*/
	virtual void SetViewReflectionTexture( eViewType ViewIndex, Engine::Graphics::Resource::ITexture* pReflectTexture ) = 0;

	/**
		@brief ビューの表示有無設定
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param IsDrawEnable	[in] 描画の有無
		@note
		ビューに対して表示の有無を設定します。<BR>
		ビューの生成と削除はコストがかかるので表示の切り替えに関しては<BR>
		事前にビューを生成しておきこのメソッドによる切り替えを推奨します。
	*/
	virtual void SetViewDrawEnable( eViewType ViewIndex, bool IsDrawEnable ) = 0;

	/**
		@brief ビューのレンダリング有無設定
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param IsRendering	[in] 描画の有無
		@note
		ビューに対して描画の有無を設定します。<BR>
		ビューの生成と削除はコストがかかるので表示の切り替えに関しては<BR>
		事前にビューを生成しておきこのメソッドによる切り替えを推奨します。
	*/
	virtual void SetViewRenderingEnable( eViewType ViewIndex, bool IsRendering ) = 0;

	/**
		@brief ビューのエフェクト設定
		@author 葉迩倭
		@param ViewIndex			[in] ビューのインデックス
		@param IsMotionBlur			[in] モーションブラーの有無
		@param IsAmbientOcclusion	[in] アンビエント隠蔽の有無
		@param IsDepthOfField		[in] 被写界深度の有無
		@param IsShadowMap			[in] シャドウマップの有無
		@note
		ビューに対してポストエフェクトの有無を設定します。<BR>
		レンダラーの生成時に有効にされたエフェクトで無い場合は<BR>
		このメソッドでtrueにしても有効になりません。
	*/
	virtual void SetViewEffect( eViewType ViewIndex, bool IsMotionBlur, bool IsAmbientOcclusion, bool IsDepthOfField, bool IsShadowMap ) = 0;

	/**
		@brief 画面クリア後イベント
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param Callback		[in] イベント
		@note
		画面クリア後に呼び出されるコールバックを登録します。
	*/
	virtual void SetCallbackEvent_AfterClear( eViewType ViewIndex, const Kernel::Delegate00& Callback ) = 0;

	/**
		@brief 不透明モデル描画前イベント
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param Callback		[in] イベント
		@note
		不透明モデル描画前に呼び出されるコールバックを登録します。
	*/
	virtual void SetCallbackEvent_BeforeModelDraw( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief 不透明モデル描画後イベント
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param Callback		[in] イベント
		@note
		不透明モデル描画後に呼び出されるコールバックを登録します。
	*/
	virtual void SetCallbackEvent_AfterModelDraw( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief 水面描画前イベント
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param Callback		[in] イベント
		@note
		水面描画前に呼び出されるコールバックを登録します。
	*/
	virtual void SetCallbackEvent_BeforeWaterDraw( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief 半透明描画前イベント
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param Callback		[in] イベント
		@note
		半透明描画前に呼び出されるコールバックを登録します。
	*/
	virtual void SetCallbackEvent_BeforeBlendModelDraw( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief 半透明描画後イベント
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param Callback		[in] イベント
		@note
		半透明描画後に呼び出されるコールバックを登録します。
	*/
	virtual void SetCallbackEvent_AfterBlendModelDraw( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief ポストエフェクト前イベント
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param Callback		[in] イベント
		@note
		ポストエフェクト描画前に呼び出されるコールバックを登録します。
	*/
	virtual void SetCallbackEvent_BeforePostEffect( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief ポストエフェクト後イベント
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param Callback		[in] イベント
		@note
		ポストエフェクト描画後に呼び出されるコールバックを登録します。
	*/
	virtual void SetCallbackEvent_AfterPostEffect( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief 3Dテキスト描画用イベント
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param Callback		[in] イベント
		@note
		3Dテキストを描画する際に呼び出されるコールバックを登録します。
	*/
	virtual void SetCallbackEvent_OnDrawText3D( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief モーションブラーパラメーター設定
		@author 葉迩倭
		@param Power	[in] モーションブラーの強度
		@note
		モーションブラー描画に関するパラメーターの設定を行います。
	*/
	virtual void SetParameter_MotionBlurPower( float Power ) = 0;

	/**
		@brief ソフトパーティクルパラメーター設定
		@author 葉迩倭
		@param Distance	[in] ブレンドさせる距離
		@note
		ソフトパーティクル描画に関するパラメーターの設定を行います。
	*/
	virtual void SetParameter_SoftParticleDistance( float Distance ) = 0;

	/**
		@brief 被写界深度パラメーター設定
		@author 葉迩倭
		@param NearEnd		[in] 手前のぼかし完了位置
		@param NearStart	[in] 手前のぼかし開始位置
		@param FarStart		[in] 奥のぼかし開始位置
		@param FarEnd		[in] 奥のぼかし完了位置
		@note
		被写界深度に関するパラメーターの設定を行います。
	*/
	virtual void SetParameter_DepthOfField( float NearEnd, float NearStart, float FarStart, float FarEnd ) = 0;

	/**
		@brief フォグパラメーター設定
		@author 葉迩倭
		@param Near		[in] フォグの始点
		@param Far		[in] フォグの終点
		@param Color	[in] フォグの色
		@note
		フォグに関するパラメーターの設定を行います。
	*/
	virtual void SetParameter_Fog( float Near, float Far, const Kernel::Math::VectorS& Color ) = 0;

	/**
		@brief 屋外散乱光パラメーター設定
		@author 葉迩倭
		@param SunDirection	[in] フォーカスのカメラからの距離
		@param vSunColor	[in] ぼかすレンジ
		@param Rayleigh		[in] レイリー散乱
		@param Mie			[in] ミー散乱
		@param G			[in] HenyeyGreensteinパラメーター
		@param Range		[in] 太陽までの距離（仮想距離）
		@note
		屋外散乱光に関するパラメーターの設定を行います。
	*/
	virtual void SetParameter_Scattering( const Kernel::Math::VectorS& SunDirection, const Kernel::Math::VectorS& vSunColor, const Kernel::Math::VectorS& Rayleigh, const Kernel::Math::VectorS& Mie, float G, float Range ) = 0;

	/**
		@brief アンビエント隠蔽パラメーター設定
		@author 葉迩倭
		@param Radius			[in] レイの半径
		@param Contrast			[in] 隠蔽箇所の濃さ
		@param Attenuation		[in] 隠蔽の減衰率
		@param DistanceLimit	[in] 適用する距離の限界値
		@param StepCount		[in] レイのステップ数
		@param DirectionCount	[in] レイの数
		@param BlurRadius		[in] ぼかしの半径
		@note
		アンビエント隠蔽に関するパラメーターの設定を行います。
	*/
	virtual void SetParameter_AmbientOcclusion( float Radius, float Contrast, float Attenuation, float DistanceLimit, Sint32 StepCount, Sint32 DirectionCount, Sint32 BlurRadius ) = 0;

	/**
		@brief ライト用パラメーター設定
		@author 葉迩倭
		@param Position				[in] ライトの位置
		@param Target				[in] ライトのターゲット位置
		@param Color				[in] ライトの色
		@param Earth				[in] 半球の地面の色
		@param Sky					[in] 半球の空の色
		@param ShadowMapDistance	[in] シャドウマップの有効距離
		@param ShadowPower			[in] シャドウの強さ
		@param ShadowBias			[in] シャドウのバイアス
		@note
		シーン全体にかかるグローバルライトの設定をします。<BR>
		PositionからTargetを見るような平行光源とEarth/Skyを使った半球ライトを定義します。
	*/
	virtual void SetParameter_MainLight( const Kernel::Math::VectorS& Position, const Kernel::Math::VectorS& Target, const Kernel::Math::VectorS& Color, const Kernel::Math::VectorS& Earth, const Kernel::Math::VectorS& Sky, float ShadowMapDistance = 100.0f, float ShadowPower = 0.0f, float ShadowBias = 0.0f ) = 0;

	/**
		@brief ライト用パラメーター設定
		@author 葉迩倭
		@param LightNo		[in] ライト番号 (0,1,2)
		@param Position		[in] ライトの位置
		@param Target		[in] ライトのターゲット位置
		@param Color		[in] ライトの色
		@note
		シーン全体にかかるグローバルなサブのライトの設定をします。<BR>
		PositionからTargetを見るような平行光源を最大３本設定できます。
	*/
	virtual void SetParameter_SubLight( Sint32 LightNo, const Kernel::Math::VectorS& Position, const Kernel::Math::VectorS& Target, const Kernel::Math::VectorS& Color ) = 0;

	/**
		@brief ポイントライトパラメーター設定
		@author 葉迩倭
		@param Distance	[in] ポイントライトを反映させる視点からの最大距離
		@note
		設定した値より視点から遠くにあるライトを適用させないようにポイントライトのLOD処理を行います。<BR>
		初期値は150.0です。
	*/
	virtual void SetParameter_PointLightLimitDistance( float Distance ) = 0;

	/**
		@brief 水中用パラメーター設定
		@author 葉迩倭
		@param Wrap				[in] 揺らぎの繰り返し回数
		@param Time				[in] 揺らぎの進行時間
		@param Scale			[in] 揺らぎのスケール値
		@param FogModulateColor	[in] 全体へ乗算する色
		@note
		水中揺らし用のパラメーターを設定します。
	*/
	virtual void SetParameter_WaterInsideWave( float Wrap, float Time, float Scale, const ColorF& FogModulateColor ) = 0;

	/**
		@brief 水面下深度フォグパラメーター設定
		@author 葉迩倭
		@param Color		[in] 色
		@param DepthLimit	[in] 完全にColor値になる深度
		@note
		水面下用深度フォグのパラメーターを設定します。
	*/
	virtual void SetParameter_WaterDepthFog( const ColorF& Color, float DepthLimit ) = 0;

	/**
		@brief 水面歪みパラメーター設定
		@author 葉迩倭
		@param Value	[in] 歪み率
		@note
		水面歪みパラメーターを設定します。
	*/
	virtual void SetParameter_WaterDistortion( float Value ) = 0;

	/**
		@brief フレネル反射テクスチャ設定
		@author 葉迩倭
		@param pTexture	[in] テクスチャ
		@note
		水面のフレネル反射率を定義したテクスチャを設定します。
	*/
	virtual void SetWaterReflectFresnelTexture( Engine::Graphics::Resource::ITexture* pTexture ) = 0;

	/**
		@brief ポイントライト削除
		@author 葉迩倭
		@param PointLight	[in] ライト情報
		@return ライトのID
		@note
		シーンにポイントライトを登録します。
	*/
	virtual POINTLIGHT_HANDLE RegistPointLight( const SPointLight& PointLight ) = 0;

	/**
		@brief ポイントライト削除
		@author 葉迩倭
		@param PointLightID	[in] ライトのID
		@note
		シーンに登録されているポイントライトを削除します。
	*/
	virtual void UnregistPointLight( POINTLIGHT_HANDLE PointLightID ) = 0;

	/**
		@brief ポイントライト更新
		@author 葉迩倭
		@param PointLightID	[in] ライトのID
		@param PointLight	[in] ライト情報
		@note
		シーンに登録されているポイントライトを更新します。
	*/
	virtual void UpdatePointLight( POINTLIGHT_HANDLE PointLightID, const SPointLight& PointLight ) = 0;

	/**
		@brief シーン用カラー変換
		@author 葉迩倭
		@param Color	[in] 元の色
		@return 変換後の色
		@note
		シーンへの描画を行う場合に適した色への変換を行います。
	*/
	virtual ColorF ConvertSceneColor( const ColorF& Color ) = 0;

	/**
		@brief エフェクト用バッファのデバッグ表示
		@author 葉迩倭
		@param ViewIndex	[in] ビューのインデックス
		@param IsEnable		[in] 表示ON/OFF
		@note
		エフェクト用のバッファを画面上に描画するかどうかを設定します
	*/
	virtual void EffectBufferDrawEnable( eViewType ViewIndex, bool IsEnable ) = 0;

	/**
		@brief デバッグ用ビューバウンディング表示
		@author 葉迩倭
		@param pRenderer	[in] レンダラー
		@note
		デバッグ用に描画オブジェクトのビューボリュームを表示します。
	*/
	virtual void DebugDraw_DrawObjectViewBounding( Engine::Graphics::Simple::ILineRenderer* pRenderer ) = 0;
};

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
}
}
}
}

/**
	@file
	@brief レンダラーマネージャー
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Renderer
{
	enum eShaderModel
	{
		SHADER_MODEL_0_0,
		SHADER_MODEL_3_0,
		SHADER_MODEL_4_0,
		SHADER_MODEL_5_0,
	};

	/**
		@brief レンダラー管理クラス
		@author 葉迩倭
		@note
		レンダラー関係のマネージャー
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		/**
			@brief 標準実装レンダラー生成
			@author 葉迩倭
			@param IsShaderEnable	[in] シェーダー利用の有無
			@return レンダラーインターフェイス
			@note
			標準実装レンダラーのインターフェイスを生成します。
		*/
		virtual Standard::IRenderer* CreateStandardRenderer( bool IsShaderEnable ) = 0;

		/**
			@brief 標準実装レンダラー用マテリアル生成
			@author 葉迩倭
			@return レンダラー用マテリアルインターフェイス
			@note
			標準実装レンダラー用マテリアルのインターフェイスを生成します。
		*/
		virtual Standard::Material::Standard::IMaterial* CreateStandardRendererMaterial() = 0;
	};
}
}
}

/**
	@file
	@brief コアインターフェイス
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
	/**
		@brief コアインターフェイス
		@author 葉迩倭
		@note
		エンジンに対するすべてのアクセスを権を持つコアになるインターフェイス
	*/
	class ICore
		: public Interface
	{
	protected:
		virtual ~ICore(){}

	public:
		/**
			@brief 初期化
			@author 葉迩倭
			@param pApplicationName		[in] アプリケーション名
			@param WindowSize			[in] ウィンドウのサイズ
			@param IsLogFileEnable		[in] ログ出力有無
			@param IsEnableBootCheck	[in] 多重起動ブロック有無
			@retval true	成功
			@retval false	失敗
			@note
			Coreの初期化を行います。<BR>
			内部でウィンドウの生成などのセットアップが行われます。
		*/
		virtual bool Initialize( const wchar_t* pApplicationName, const Point2DI& WindowSize, bool IsLogFileEnable, bool IsEnableBootCheck ) = 0;

		/**
			@brief 初期化
			@author 葉迩倭
			@param pApplicationName		[in] アプリケーション名
			@param WindowHandle		[in] ウィンドウのハンドル
			@param IsLogFileEnable		[in] ログ出力有無
			@param IsEnableBootCheck	[in] 多重起動ブロック有無
			@retval true	成功
			@retval false	失敗
			@note
			Coreの初期化を行います。<BR>
			内部でウィンドウを利用したセットアップが行われます。
		*/
		virtual bool InitializeByExternalWindow( const wchar_t* pApplicationName, HWND WindowHandle, bool IsLogFileEnable, bool IsEnableBootCheck ) = 0;

		/**
			@brief 終了
			@author 葉迩倭
			@note
			Coreの解放処理を行います。
		*/
		virtual void Finalize() = 0;

		/**
			@brief エラー用メッセージボックス
			@author 葉迩倭
			@param pTitle	[in] タイトル
			@param pMessage	[in] メッセージ(printf形式)
			@note
			エラー用のメッセージボックス表示を行います。
		*/
		virtual void ErrorMessageBox( const wchar_t* pTitle, const wchar_t* pMessage, ... ) = 0;

		/**
			@brief Graphics::Manager生成
			@author 葉迩倭
			@param pTable		[in] Api初期化優先度テーブル（NULLでデフォルト値を利用）
			@param IsWaitVSync	[in] Vsync待ちの有無
			@retval true	成功
			@retval false	失敗
			@note
			Graphics用のマネージャーを生成します。
		*/
		virtual bool CreateGraphicsManager( const Engine::Graphics::eGraphicsAPI* pTable = NULL, bool IsWaitVSync = false ) = 0;

		/**
			@brief File::Manager生成
			@author 葉迩倭
			@retval true	成功
			@retval false	失敗
			@note
			File用のマネージャーを生成します。
		*/
		virtual bool CreateFileManager() = 0;

		/**
			@brief Sound::Manager生成
			@author 葉迩倭
			@retval true	成功
			@retval false	失敗
			@note
			Sound用のマネージャーを生成します。
		*/
		virtual bool CreateSoundManager() = 0;

		/**
			@brief Network::Manager生成
			@author 葉迩倭
			@retval true	成功
			@retval false	失敗
			@note
			Network用のマネージャーを生成します。
		*/
		virtual bool CreateNetworkManager() = 0;

		/**
			@brief GUI::Manager生成
			@author 葉迩倭
			@retval true	成功
			@retval false	失敗
			@note
			GUI用のマネージャーを生成します。
		*/
		virtual bool CreateGUIManager( bool IsMouseEnable ) = 0;

		/**
			@brief Input::Manager生成
			@author 葉迩倭
			@retval true	成功
			@retval false	失敗
			@note
			Input用のマネージャーを生成します。
		*/
		virtual bool CreateInputManager() = 0;

		/**
			@brief Dynamics::Manager生成
			@author 葉迩倭
			@retval true	成功
			@retval false	失敗
			@note
			Dynamics用のマネージャーを生成します。
		*/
		virtual bool CreateDynamicsManager() = 0;

		/**
			@brief Renderer::Manager生成
			@author 葉迩倭
			@retval true	成功
			@retval false	失敗
			@note
			Renderer用のマネージャーを生成します。
		*/
		virtual bool CreateRendererManager() = 0;

		/**
			@brief Window::IWindowを取得
			@author 葉迩倭
			@return Window::IWindowインターフェイス
			@note
			Window::IWindowを取得します。
		*/
		virtual Window::IWindow* GetWindow() = 0;

		/**
			@brief Graphics::IManagerを取得
			@author 葉迩倭
			@return Graphics::IManagerインターフェイス
			@note
			Graphics::IManagerを取得します。
		*/
		virtual Graphics::IManager* GetGraphicsManager() = 0;

		/**
			@brief File::IManagerを取得
			@author 葉迩倭
			@return File::IManagerインターフェイス
			@note
			File::IManagerを取得します。
		*/
		virtual File::IManager* GetFileManager() = 0;

		/**
			@brief Sound::IManagerを取得
			@author 葉迩倭
			@return Sound::IManagerインターフェイス
			@note
			Sound::IManagerを取得します。
		*/
		virtual Sound::IManager* GetSoundManager() = 0;

		/**
			@brief Network::IManagerを取得
			@author 葉迩倭
			@return Network::IManagerインターフェイス
			@note
			Network::IManagerを取得します。
		*/
		virtual Network::IManager* GetNetworkManager() = 0;

		/**
			@brief GUI::IManagerを取得
			@author 葉迩倭
			@return GUI::IManagerインターフェイス
			@note
			GUI::IManagerを取得します。
		*/
		virtual GUI::IManager* GetGUIManager() = 0;

		/**
			@brief Input::IManagerを取得
			@author 葉迩倭
			@return Input::IManagerインターフェイス
			@note
			Input::IManagerを取得します。
		*/
		virtual Input::IManager* GetInputManager() = 0;

		/**
			@brief Dynamics::IManagerを取得
			@author 葉迩倭
			@return Dynamics::IManagerインターフェイス
			@note
			Dynamics::IManagerを取得します。
		*/
		virtual Dynamics::IManager* GetDynamicsManager() = 0;

		/**
			@brief Renderer::IManagerを取得
			@author 葉迩倭
			@return Renderer::IManagerインターフェイス
			@note
			Renderer::IManagerを取得します。
		*/
		virtual Renderer::IManager* GetRendererManager() = 0;
		virtual GUI::IHelper* GetGUIHelper() = 0;

		virtual float GetDeltaTime() = 0;

		/**
			@brief アプリケーションのイベント処理
			@author 葉迩倭
			@param FramePerSec	[in] 1秒間のフレーム数
			@note
			アプリケーションのイベント処理をします。<BR>
			この中でアプリケーションに必要な処理を行っています。
		*/
		virtual bool DoEvent( Uint32 FramePerSec ) = 0;

		/**
			@brief フレームの開始
			@author 葉迩倭
			@note
			フレームの処理を開始します。
		*/
		virtual void FrameBegin() = 0;

		/**
			@brief フレームの終了
			@author 葉迩倭
			@note
			フレームの処理を終了します。
		*/
		virtual void FrameEnd() = 0;

		/**
			@brief アプリケーションの終了
			@author 葉迩倭
			@note
			アプリケーションの終了をします。
		*/
		virtual void Exit() = 0;

		/**
			@brief 実行ファイルのパスを取得
			@author 葉迩倭
			@return 実行ファイルのパス
			@note
			実行ファイルのパスを取得します。
		*/
		virtual const wchar_t* GetModulePath() = 0;

		/**
			@brief フレームレート取得
			@author 葉迩倭
			@return 秒間のフレーム数の平均
			@note
			アプリケーションでリクエストしているFPSを取得します。
		*/
		virtual Uint32 GetFrameRate() = 0;

		/**
			@brief FPS取得
			@author 葉迩倭
			@return 秒間のフレーム数の平均
			@note
			現在のFPSを取得します。
		*/
		virtual float GetFPS() = 0;

		/**
			@brief 画面モードの許可/不許可設定
			@author 葉迩倭
			@param IsAllow	[in] 許可する場合はtrue
			@note
			画面モードの変更の許可/不許可を設定します。
		*/
		virtual void SetAllowChangeScreenMode( bool IsAllow ) = 0;

		/**
			@brief 画面モード変更
			@author 葉迩倭
			@note
			画面モードの変更を行います。
		*/
		virtual void ChangeScreenMode() = 0;

		virtual Uint32 GetPhysicalCoreCount() const = 0;
		virtual Uint32 GetPhysicalCoreAffinity( Uint32 CoreIndex ) const = 0;

		/**
			@brief タスクマネージャー生成
			@author 葉迩倭
			@return タスクマネージャー
			@note
			タスクマネージャーを生成します。
		*/
		virtual Task::ITaskManager* CreateTaskManager() = 0;
	};
}
}

namespace Selene
{
	typedef Kernel::Math::Vec2			sVec2;
	typedef Kernel::Math::Vector2		sVector2;
	typedef Kernel::Math::Vec3			sVec3;
	typedef Kernel::Math::Vector3		sVector3;
	typedef Kernel::Math::Vec4			sVec4;
	typedef Kernel::Math::Vector4		sVector4;
	typedef Kernel::Math::VecS			sVecS;
	typedef Kernel::Math::VectorS		sVectorS;
	typedef Kernel::Math::MatX			sMatX;
	typedef Kernel::Math::Matrix		sMatrix;
	typedef Kernel::Math::Quat			sQuat;
	typedef Kernel::Math::Quaternion	sQuaternion;
}
#ifdef __cplusplus_cli
#pragma managed(pop)
#endif
/**
	@file
	@brief Seleneアクセス用Library
	@author 葉迩倭
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
/**
	@brief エンジンの初期化
	@author 葉迩倭
	@param pModulePath	[in] SeleneのDLLのパス
	@retval true	初期化成功
	@retval false	初期化失敗
	@note
	Seleneのエンジン全体の初期化を行います。<BR>
	この関数が失敗するのはpModulePathで指定したDLLが<BR>
	読み込めない場合と、すでに初期化済みの場合だけです。
*/
bool SLN_STDCALL InitializeEngine( const wchar_t* pModulePath );

/**
	@brief エンジンの解放
	@author 葉迩倭
	@note
	Seleneのエンジン全体の解放を行います。<BR>
	アプリケーションの終了前の必ず呼び出して下さい。
*/
void SLN_STDCALL FinalizeEngine();

/**
	@brief コアの生成
	@author 葉迩倭
	@return コアのポインター
	@note
	Seleneへアクセスする為のICoreを作成します。<BR>
	１つのアプリケーションに付き１個しか生成されません。<BR>
	ようするにシングルトンになっています。
*/
Engine::ICore* SLN_STDCALL CreateCore();

/**
	@brief コアの取得
	@author 葉迩倭
	@return コアのポインター
	@note
	Seleneへアクセスする為のICoreを取得します。
*/
Engine::ICore* SLN_STDCALL GetCore();

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
}
#ifdef __cplusplus_cli
#pragma managed(pop)
#endif
