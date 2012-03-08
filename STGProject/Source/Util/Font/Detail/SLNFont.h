#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Font/IFont.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Font
{
namespace Detail
{
	class SLNFont
		: public IFont
	{
	public:
		// コンストラクタ
		SLNFont( PSLNFont pFont );

		// テキストデータの文字サイズ設定
		virtual void SetSize( Selene::Sint32 size );
		// テキストデータのオリジナルの文字サイズ取得
		virtual Selene::Sint32 GetOriginalSize() const;
		// テキストデータの文字サイズ取得
		virtual Selene::Sint32 GetSize() const;

		// テキストデータの描画優先度を設定
		virtual void SetPriority( Selene::Sint32 priority );

		// 振動フラグの取得
		virtual bool IsShakable() const;
		// 振動フラグの設定
		virtual void SetShakable( bool shakable = true );

		// テキストデータの文字描画
		virtual Selene::Point2DF Draw( const Selene::Point2DF &position, 
			const Selene::ColorF &color, const std::wstring &string, 
			Selene::Sint32 length = -1 );
		// 左揃えテキストデータの文字描画
		virtual Selene::Point2DF DrawLeft( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length = -1 );
		// 中央揃えテキストデータの文字描画
		virtual Selene::Point2DF DrawCenter( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length = -1 );
		// 右揃えテキストデータの文字描画
		virtual Selene::Point2DF DrawRight( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length = -1 );

	private:
		PSLNFont mpFont;
		bool mShakable;
	};
}
}
}
}