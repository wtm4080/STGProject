#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <Selene.h>
#include "DrawParameter.h"
#include "Util/RepeatCounter.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Sprite
{
	class Animation
	{
	public:
		// コンストラクタ
		Animation();
		Animation( const Selene::Point2DI &frameSize, unsigned frameNum, float frameInterval, 
			const DrawParameter &param );

		// フレームの更新
		void Update();
		// フレームの描画
		void Draw() const;

		// フレームサイズの取得
		Selene::Point2DI GetFrameSize() const;
		// フレームサイズの設定
		void SetFrameSize( const Selene::Point2DI &size );
		// 総フレーム数の取得
		unsigned GetFrameNum() const;
		// 総フレーム数の設定
		void SetFrameNum( unsigned num );
		// フレーム位置の取得
		unsigned GetFramePos() const;
		// フレーム位置の設定
		void SetFramePos( unsigned framePos );

		// アニメーション開始
		void Play( unsigned framePos = 0 );
		// アニメーション停止
		void Stop();
		// アニメーション開始フラグの取得
		bool IsPlay() const;

		// フレーム間隔の取得
		float GetFrameInterval() const;
		// フレーム間隔の設定
		void SetFrameInterval( float interval );

		// 描画パラメータの取得
		const DrawParameter &GetDrawParameter() const;
		// 描画パラメータの設定
		void SetDrawParameter( const DrawParameter &param );
		// 描画先の設定
		void SetDst( const Selene::RectF &dst );
		// 描画優先度の設定
		void SetPriority( Selene::Sint32 priority );
		// アルファブレンドの種類の設定
		void SetAlphaBlend( AlphaBlend alphaBlend = AB_BLEND );
		// 回転角度の設定
		void SetRotDegree( float degree );
		// 回転時の中心からのオフセットの設定
		void SetRotOffset( const Selene::Point2DF &rotOffset = Selene::Point2DF() );
		// 描画色の設定
		void SetColor( const Selene::ColorF &color = Selene::ColorF() );

		// 描画するテクスチャ位置の取得
		Selene::RectF GetCurrentTextureSrc() const;

	private:
		Selene::Point2DI mFrameSize;
		unsigned mFrameNum;
		DrawParameter mDrawParam;

		Util::RepeatCounter mCounter;
		unsigned mFrameCount;
		bool mPlayFlag;
	};
}
}
}