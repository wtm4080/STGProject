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
namespace Sprite
{
	// スプライト関連の操作
	class Manager
	{
	public:
		// フレーム毎の更新
		static void Update();

		// 四角形の描画
		static void Draw( const Sprite::DrawParameter &param );

		// テクスチャをファイルから読み込む
		static PTexture LoadTexture( 
			const std::wstring &fileName, 
			bool mipmap = true, 
			const Selene::ColorF &transColor = Selene::ColorF( 0, 0, 0, 0 ) 
			);
		static PTexture LoadTexture( 
			File::PFile pFile, 
			bool mipmap = true, 
			const Selene::ColorF &transColor = Selene::ColorF( 0, 0, 0, 0 ) 
			);
		static void LoadTexture( const TextureSrcMap &srcFilePathMap, 
			TextureMap &textures );

		// 画面の振動の設定
		static void SetShake( float amount, float decAmount = 1.0f );
		static void SetShake( const Selene::Point2DF &amount, float decAmount = 1.0f );
		// 振動の一時停止
		static void StopShake();
		// 振動の再開
		static void StartShake();
		// 振動のリセット
		static void ResetShake();
		// 振動量の取得
		static Selene::Point2DF GetCurrentShakeAmount();
	};
}
}
}