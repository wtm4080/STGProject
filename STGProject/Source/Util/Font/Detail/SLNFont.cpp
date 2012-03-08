#include "PCH.h"
#include "SLNFont.h"

using namespace Game;
using namespace Util::Font::Detail;
using namespace Selene;
using namespace std;


// コンストラクタ
SLNFont::SLNFont( PSLNFont pFont )
: mpFont( pFont )
, mShakable( true )
{
}


// テキストデータの文字サイズ設定
void SLNFont::SetSize( Sint32 size )
{
	mpFont->SetDrawFontSize( size );
}

// テキストデータのオリジナルの文字サイズ取得
Sint32 SLNFont::GetOriginalSize() const
{
	return mpFont->GetOriginalFontSize();
}

// テキストデータの文字サイズ取得
Sint32 SLNFont::GetSize() const
{
	return mpFont->GetDrawFontSize();
}


// テキストデータの描画優先度を設定
void SLNFont::SetPriority( Sint32 priority )
{
	mpFont->SetPriority( priority );
}


// 振動フラグの取得
bool SLNFont::IsShakable() const
{
	return mShakable;
}

// 振動フラグの設定
void SLNFont::SetShakable( bool shakable )
{
	mShakable = shakable;
}


// テキストデータの文字描画
Point2DF SLNFont::Draw( const Point2DF &position, const ColorF &color, 
					   const wstring &string, Sint32 length )
{
	Point2DF pos = position;
	if( mShakable )
	{
		pos += Sprite::Manager::GetCurrentShakeAmount();
	}

	return mpFont->DrawRequest( pos, color, string.c_str(), length );
}

// 左揃えテキストデータの文字描画
Point2DF SLNFont::DrawLeft( const RectF &rect, const Point2DF &offset, 
						   const ColorF &color, const wstring &string, 
						   Sint32 length )
{
	RectF baseRect = rect;
	if( mShakable )
	{
		Point2DF shakeAmount = 
			Sprite::Manager::GetCurrentShakeAmount();
		baseRect.x += shakeAmount.x;
		baseRect.y += shakeAmount.y;
	}

	return mpFont->DrawRequestLeft( 
		baseRect, offset, color, string.c_str(), length );
}

// 中央揃えテキストデータの文字描画
Point2DF SLNFont::DrawCenter( const RectF &rect, const Point2DF &offset, 
							 const ColorF &color, const wstring &string, 
							 Sint32 length )
{
	RectF baseRect = rect;
	if( mShakable )
	{
		Point2DF shakeAmount = 
			Sprite::Manager::GetCurrentShakeAmount();
		baseRect.x += shakeAmount.x;
		baseRect.y += shakeAmount.y;
	}

	return mpFont->DrawRequestCenter( 
		baseRect, offset, color, string.c_str(), length );
}

// 右揃えテキストデータの文字描画
Point2DF SLNFont::DrawRight( const RectF &rect, const Point2DF &offset, 
							const ColorF &color, const wstring &string, 
							Sint32 length )
{
	RectF baseRect = rect;
	if( mShakable )
	{
		Point2DF shakeAmount = 
			Sprite::Manager::GetCurrentShakeAmount();
		baseRect.x += shakeAmount.x;
		baseRect.y += shakeAmount.y;
	}

	return mpFont->DrawRequestRight( 
		baseRect, offset, color, string.c_str(), length );
}