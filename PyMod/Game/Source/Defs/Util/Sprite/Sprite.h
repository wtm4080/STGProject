#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Sprite/DrawParameter.h"
#include "Defs/Util/File/FileObject.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Sprite
{
	class Sprite
	{
	public:
		static void Configurate();

		static void _setInstance( uintptr_t p );

		// 四角形の描画
		static void draw( const Game::Util::Sprite::DrawParameter &param );

		// テクスチャをファイルから読み込む
		static Game::Util::Sprite::PTexture loadTexture( const std::wstring &path );
		static Game::Util::Sprite::PTexture loadTexture( 
			const std::wstring &path, 
			bool mipmap 
			);
		static Game::Util::Sprite::PTexture loadTexture( 
			const std::wstring &path, 
			bool mipmap, 
			const Selene::ColorF &transColor 
			);
		static Game::Util::Sprite::PTexture loadTexture( 
			const File::FileObject &fileObject );
		static Game::Util::Sprite::PTexture loadTexture( 
			const File::FileObject &fileObject, 
			bool mipmap 
			);
		static Game::Util::Sprite::PTexture loadTexture( 
			const File::FileObject &fileObject, 
			bool mipmap, 
			const Selene::ColorF &transColor 
			);

		// 画面の振動の設定
		static void setShake( float amount );
		static void setShake( float amount, float decAmount );
		static void setShake( const Selene::Point2DF &amount );
		static void setShake( const Selene::Point2DF &amount, float decAmount );
		// 振動の一時停止
		static void stopShake();
		// 振動の再開
		static void startShake();
		// 振動のリセット
		static void resetShake();
		// 振動量の取得
		static Selene::Point2DF getCurrentShakeAmount();
	};
}
}
}