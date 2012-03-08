#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <Selene.h>
#include <memory>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Sprite
{
	class Sprite;
}
}
}

namespace Game
{
namespace Util
{
namespace Sprite
{
	// 単色塗りつぶし用のテクスチャ
	static const PTexture NULL_TEXTURE = PTexture();

	// アルファブレンディング
	enum AlphaBlend
	{
		AB_OPACITY = Selene::Engine::Graphics::State::AB_OPACITY,	// 不透明
		AB_BLEND = Selene::Engine::Graphics::State::AB_BLEND,		// 透明
		AB_ADD = Selene::Engine::Graphics::State::AB_ADD,			// 加算
		AB_SUB = Selene::Engine::Graphics::State::AB_SUB,			// 減算
		AB_MUL = Selene::Engine::Graphics::State::AB_MUL,			// 乗算
		AB_SCREEN = Selene::Engine::Graphics::State::AB_SCREEN,		// スクリーン
	};

	// 四角形描画のパラメータ
	class DrawParameter
	{
	public:
		// コンストラクタ
		DrawParameter()
			: mpTexture( NULL_TEXTURE )
			, mSrc()
			, mDst()
			, mPriority()
			, mAlphaBlend( AB_BLEND )
			, mFiltering( true )
			, mRotDegree()
			, mRotOffset()
			, mColor()
			, mShakable( true )
			, mFlipedX( false )
			, mFlipedY( false )
		{}
		DrawParameter( PTexture pTexture, 
			const Selene::RectF &src, 
			const Selene::RectF &dst, 
			Selene::Sint32 priority, 
			AlphaBlend alphaBlend = AB_BLEND, 
			bool filtering = true, 
			float rotDegree = 0, 
			const Selene::Point2DF &rotOffset = Selene::Point2DF(), 
			const Selene::ColorF &color = Selene::ColorF(), 
			bool shakable = true )
			: mpTexture( pTexture )
			, mSrc( src )
			, mDst( dst )
			, mPriority( priority )
			, mAlphaBlend( alphaBlend )
			, mFiltering( filtering )
			, mRotDegree( rotDegree )
			, mRotOffset( rotOffset )
			, mColor( color )
			, mShakable( shakable )
			, mFlipedX( false )
			, mFlipedY( false )
		{}

		PTexture GetTexture() const { return mpTexture; }
		void SetTexture( PTexture pTexture = NULL_TEXTURE ) { mpTexture = pTexture; }
		Selene::RectF GetSrc() const { return mSrc; }
		void SetSrc( const Selene::RectF &src ) { mSrc = src; }
		Selene::RectF GetDst() const { return mDst; }
		void SetDst( const Selene::RectF &dst ) { mDst = dst; }
		Selene::Sint32 GetPriority() const { return mPriority; }
		void SetPriority( Selene::Sint32 priority ) { mPriority = priority; }
		AlphaBlend GetAlphaBlend() const { return mAlphaBlend; }
		void SetAlphaBlend( AlphaBlend alphaBlend = AB_BLEND ) { mAlphaBlend = alphaBlend; }
		bool IsFiltering() const { return mFiltering; }
		void SetFiltering( bool filtering = true ) { mFiltering = filtering; }
		float GetRotDegree() const { return mRotDegree; }
		void SetRotDegree( float rotDegree = 0 ) { mRotDegree = rotDegree; }
		Selene::Point2DF GetRotOffset() const { return mRotOffset; }
		void SetRotOffset( const Selene::Point2DF &rotOffset = Selene::Point2DF() ) { mRotOffset = rotOffset; }
		Selene::ColorF GetColor() const { return mColor; }
		void SetColor( const Selene::ColorF &color = Selene::ColorF() ) { mColor = color; }
		bool IsShakable() const { return mShakable; }
		void SetShakable( bool shakable = true ) { mShakable = shakable; }

		bool IsFlipedX() const { return mFlipedX; }
		void FlipX() { mFlipedX = !mFlipedX; }
		bool IsFlipedY() const { return mFlipedY; }
		void FlipY() { mFlipedY = !mFlipedY; }

	private:
		// 描画テクスチャ（NULLでColor単色塗りつぶし）
		PTexture mpTexture;
		// 描画元
		Selene::RectF mSrc;
		// 描画先
		Selene::RectF mDst;
		// 描画優先度（値が大きい程手前に描画される）
		Selene::Sint32 mPriority;
		// アルファブレンドの種類
		AlphaBlend mAlphaBlend;
		// フィルタの適用
		bool mFiltering;
		// 回転角度
		float mRotDegree;
		// 回転時の中心からのオフセット
		Selene::Point2DF mRotOffset;
		// 描画色（テクスチャの色に乗算）
		Selene::ColorF mColor;
		// 振動フラグ
		bool mShakable;
		// 反転フラグ
		bool mFlipedX, mFlipedY;

		friend class ::Defs::Util::Sprite::Sprite;
	};
}
}
}