#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Font/IFont.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Font
{
	class Wrapper
	{
	public:
		Wrapper( Game::Util::Font::PFont p )
			: mpFont( p )
		{}

		// テキストデータの文字サイズ設定
		void SetSize( Selene::Sint32 size )
		{
			mpFont->SetSize( size );
		}
		// テキストデータのオリジナルの文字サイズ取得
		Selene::Sint32 GetOriginalSize() const
		{
			return mpFont->GetOriginalSize();
		}
		// テキストデータの文字サイズ取得
		Selene::Sint32 GetSize() const
		{
			return mpFont->GetSize();
		}

		// テキストデータの描画優先度を設定
		void SetPriority( Selene::Sint32 priority )
		{
			mpFont->SetPriority( priority );
		}

		// 振動フラグの取得
		bool IsShakable() const
		{
			return mpFont->IsShakable();
		}
		// 振動フラグの設定
		void SetShakable( bool shakable )
		{
			return mpFont->SetShakable( shakable );
		}

		// テキストデータの文字描画
		Selene::Point2DF Draw( const Selene::Point2DF &position, 
			const Selene::ColorF &color, const std::wstring &string )
		{
			return mpFont->Draw( position, color, string, -1 );
		}
		Selene::Point2DF Draw( const Selene::Point2DF &position, 
			const Selene::ColorF &color, const std::wstring &string, 
			Selene::Sint32 length )
		{
			return mpFont->Draw( position, color, string, length );
		}
		// 左揃えテキストデータの文字描画
		Selene::Point2DF DrawLeft( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string )
		{
			return mpFont->DrawLeft( rect, offset, color, string, -1 );
		}
		Selene::Point2DF DrawLeft( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length )
		{
			return mpFont->DrawLeft( rect, offset, color, string, length );
		}
		// 中央揃えテキストデータの文字描画
		Selene::Point2DF DrawCenter( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string )
		{
			return mpFont->DrawCenter( rect, offset, color, string, -1 );
		}
		Selene::Point2DF DrawCenter( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length )
		{
			return mpFont->DrawCenter( rect, offset, color, string, length );
		}
		// 右揃えテキストデータの文字描画
		Selene::Point2DF DrawRight( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string )
		{
			return mpFont->DrawRight( rect, offset, color, string, -1 );
		}
		Selene::Point2DF DrawRight( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length )
		{
			return mpFont->DrawRight( rect, offset, color, string, length );
		}

	private:
		Game::Util::Font::PFont mpFont;
	};
}
}
}