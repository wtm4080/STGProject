#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Font
{
	class IFont
	{
	public:
		// テキストデータの文字サイズ設定
		virtual void SetSize( Selene::Sint32 size ) = 0;
		// テキストデータのオリジナルの文字サイズ取得
		virtual Selene::Sint32 GetOriginalSize() const = 0;
		// テキストデータの文字サイズ取得
		virtual Selene::Sint32 GetSize() const = 0;

		// テキストデータの描画優先度を設定
		virtual void SetPriority( Selene::Sint32 priority ) = 0;

		// 振動フラグの取得
		virtual bool IsShakable() const = 0;
		// 振動フラグの設定
		virtual void SetShakable( bool shakable = true ) = 0;

		// テキストデータの文字描画
		virtual Selene::Point2DF Draw( const Selene::Point2DF &position, 
			const Selene::ColorF &color, const std::wstring &string, 
			Selene::Sint32 length = -1 ) = 0;
		// 左揃えテキストデータの文字描画
		virtual Selene::Point2DF DrawLeft( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length = -1 ) = 0;
		// 中央揃えテキストデータの文字描画
		virtual Selene::Point2DF DrawCenter( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length = -1 ) = 0;
		// 右揃えテキストデータの文字描画
		virtual Selene::Point2DF DrawRight( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length = -1 ) = 0;

		virtual ~IFont() {}
	};
}
}
}