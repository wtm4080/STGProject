#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <Selene.h>
#include <memory>
#include <cmath>
#include <boost/throw_exception.hpp>
#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/tokenizer.hpp>


//----------------------------------------------------------------------------------
//	Define
//----------------------------------------------------------------------------------

// BOOST_FOREACHの別名定義
// 型に「,」が含まれている場合(std::pair<int, int>など)、typedefすること
#define foreach( variable, collection ) BOOST_FOREACH( variable, collection )
// BOOST_REVERSE_FOREACHの別名定義
#define foreach_rev( variable, collection ) BOOST_REVERSE_FOREACH( variable, collection )

// BOOST_AUTOの別名定義
//#define auto( var, expr ) BOOST_AUTO( var, expr )

// BOOST_THROW_EXCEPTIONの別名定義
#define THROW( e ) BOOST_THROW_EXCEPTION( e )


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	// shared_ptrの生成
	template <class T>
	static typename Ptr<T>::Shared MakeSharedPtr( T *p )
	{
		return Ptr<T>::Shared( p );
	}
	// weak_ptrの生成
	template <class T>
	static typename Ptr<T>::Weak MakeWeakPtr( typename Ptr<T>::Shared p )
	{
		return Ptr<T>::Weak( p );
	}
	// intrusive_ptrの生成
	template <class T>
	static typename Ptr<T>::Intrusive MakeIntrusivePtr( T *p, bool addRef = false )
	{
		return Ptr<T>::Intrusive( p, addRef );
	}

	// wchar_t から char へ変換
	static std::string ToMultiByte( const std::wstring wText )
	{
		return Selene::Kernel::String::Utility::ToMultiByte( wText.c_str() );
	}
	template<class ContainerIn, class ContainerOut>
	static void ToMultiByte( const ContainerIn &in, ContainerOut &out )
	{
		out.clear();

		foreach( const std::wstring &wStr, in )
		{
			std::inserter( out, out.end() ) = ToMultiByte( wStr );
		}
	}
	// char から wchar_t へ変換
	static std::wstring ToWide( const std::string text )
	{
		return Selene::Kernel::String::Utility::ToWide( text.c_str() );
	}
	template<class ContainerIn, class ContainerOut>
	static void ToWide( const ContainerIn &in, ContainerOut &out )
	{
		out.clear();

		foreach( const std::string &str, in )
		{
			std::inserter( out, out.end() ) = ToWide( str );
		}
	}

	// Rectを生成
	template <class T>
	static Selene::Rect<T> MakeRect( const Selene::Point2D<T> &upperLeftPos, 
		const Selene::Point2D<T> &widthHeight )
	{
		return Selene::Rect<T>( upperLeftPos.x, upperLeftPos.y, 
			widthHeight.x, widthHeight.y );
	}
	// 中心座標でRectを生成
	template <class T>
	static Selene::Rect<T> MakeRectByCenter( const Selene::Point2D<T> &centerPos, 
		const Selene::Point2D<T> &widthHeight )
	{
		return Selene::Rect<T>( centerPos.x - widthHeight.x/2, centerPos.y - widthHeight.y/2, 
			widthHeight.x, widthHeight.y );
	}

	// 三角関数
	static float Sin( float degree )
	{
		return Selene::Kernel::Math::FastSin( 
			Selene::Kernel::Math::DegToAngle( degree ) );
	}
	static float Cos( float degree )
	{
		return Selene::Kernel::Math::FastCos( 
			Selene::Kernel::Math::DegToAngle( degree ) );
	}
	static float Atan2( float y, float x )
	{
		return static_cast<float>( 180/Selene::PI * atan2( y, x ) );
	}

	// トークン分割
	static void Tokenize( const std::string &src, const std::string &delims, 
		std::vector<std::string> &resultList )
	{
		boost::char_separator<char> 
			separator( delims.c_str(), NULL, boost::keep_empty_tokens );
		boost::tokenizer<boost::char_separator<char>> 
			tokens( src, separator );
		resultList.assign( tokens.begin(), tokens.end() );
	}
	static void Tokenize( const std::wstring &src, const std::wstring &delims, 
		std::vector<std::wstring> &resultList )
	{
		boost::char_separator<wchar_t> 
			separator( delims.c_str(), NULL, boost::keep_empty_tokens );
		boost::tokenizer<boost::char_separator<wchar_t>, 
			std::wstring::const_iterator, std::wstring> 
			tokens( src, separator );
		resultList.assign( tokens.begin(), tokens.end() );
	}

	// 2乗
	template <class T>
	static T Pow( T x )
	{
		return x * x;
	}
	// n乗
	template <class T>
	static T Pow( T x, int n )
	{
		T result = static_cast<T>( 1 );

		if( n >= 0 )
		{
			for( int i = 0; i < n; i++ )
			{
				result *= x;
			}
		}
		else if( n < 0 )
		{
			for( int i = 0; i < -n; i++ )
			{
				result /= x;
			}
		}

		return result;
	}
}
}