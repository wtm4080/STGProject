#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <Selene.h>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Python
{
namespace Wrapper
{
	class ISprite
	{
	public:
		// 四角形の描画
		virtual void Draw( const Sprite::DrawParameter &param ) = 0;

		// テクスチャをファイルから読み込む
		virtual Sprite::PTexture LoadTexture( 
			const std::wstring &fileName, 
			bool mipmap = true, 
			const Selene::ColorF &transColor = Selene::ColorF( 0, 0, 0, 0 ) 
			) = 0;
		virtual Sprite::PTexture LoadTexture( 
			File::PFile pFile, 
			bool mipmap = true, 
			const Selene::ColorF &transColor = Selene::ColorF( 0, 0, 0, 0 ) 
			) = 0;

		// 画面の振動の設定
		virtual void SetShake( float amount, float decAmount = 1.0f ) = 0;
		virtual void SetShake( const Selene::Point2DF &amount, float decAmount = 1.0f ) = 0;
		// 振動の一時停止
		virtual void StopShake() = 0;
		// 振動の再開
		virtual void StartShake() = 0;
		// 振動のリセット
		virtual void ResetShake() = 0;
		// 振動量の取得
		virtual Selene::Point2DF GetCurrentShakeAmount() = 0;

		virtual ~ISprite() {}
	};
}
}
}
}