#include "PCH.h"
#include "Font.h"

#include "Util/Python/Wrapper/IFont.h"
#include "Wrapper.h"

using namespace Game;
using namespace Util::Python::Wrapper;
using namespace boost::python;
using namespace Selene;
using namespace Defs::Util::Font;

namespace
{
	IFont *pFont;
}


void Font::Configurate()
{
	class_<Font>( "Font", no_init )
		.def( "_setInstance", &Font::_setInstance )
		.def( "load", &Font::load )
		;

	class_<Wrapper>( "FontObject", no_init )
		.add_property( "size", &Wrapper::GetSize, &Wrapper::SetSize )
		.add_property( "originalSize", &Wrapper::GetOriginalSize )
		.def( "setPriority", &Wrapper::SetPriority )
		.add_property( "shakable", &Wrapper::IsShakable, &Wrapper::SetShakable )
		.def( "draw", 
			static_cast<Point2DF (Wrapper::*)( const Point2DF &, const ColorF &, const std::wstring & )>( &Wrapper::Draw ) )
		.def( "draw", 
			static_cast<Point2DF (Wrapper::*)( const Point2DF &, const ColorF &, const std::wstring &, Sint32 )>( &Wrapper::Draw ) )
		.def( "drawLeft", 
			static_cast<Point2DF (Wrapper::*)( const RectF &, const Point2DF &, const ColorF &, const std::wstring & )>( &Wrapper::DrawLeft ) )
		.def( "drawLeft", 
			static_cast<Point2DF (Wrapper::*)( const RectF &, const Point2DF &, const ColorF &, const std::wstring &, Sint32 )>( &Wrapper::DrawLeft ) )
		.def( "drawCenter", 
			static_cast<Point2DF (Wrapper::*)( const RectF &, const Point2DF &, const ColorF &, const std::wstring & )>( &Wrapper::DrawCenter ) )
		.def( "drawCenter", 
			static_cast<Point2DF (Wrapper::*)( const RectF &, const Point2DF &, const ColorF &, const std::wstring &, Sint32 )>( &Wrapper::DrawCenter ) )
		.def( "drawRight", 
			static_cast<Point2DF (Wrapper::*)( const RectF &, const Point2DF &, const ColorF &, const std::wstring & )>( &Wrapper::DrawRight ) )
		.def( "drawRight", 
			static_cast<Point2DF (Wrapper::*)( const RectF &, const Point2DF &, const ColorF &, const std::wstring &, Sint32 )>( &Wrapper::DrawRight ) )
		;
}


void Font::_setInstance( uintptr_t p )
{
	pFont = reinterpret_cast<IFont *>( p );
}

Wrapper Font::load( const std::wstring &path )
{
	return Wrapper( pFont->LoadFont( path ) );
}