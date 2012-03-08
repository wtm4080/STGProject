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

		// lŠpŒ`‚Ì•`‰æ
		static void draw( const Game::Util::Sprite::DrawParameter &param );

		// ƒeƒNƒXƒ`ƒƒ‚ğƒtƒ@ƒCƒ‹‚©‚ç“Ç‚İ‚Ş
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

		// ‰æ–Ê‚ÌU“®‚Ìİ’è
		static void setShake( float amount );
		static void setShake( float amount, float decAmount );
		static void setShake( const Selene::Point2DF &amount );
		static void setShake( const Selene::Point2DF &amount, float decAmount );
		// U“®‚Ìˆê’â~
		static void stopShake();
		// U“®‚ÌÄŠJ
		static void startShake();
		// U“®‚ÌƒŠƒZƒbƒg
		static void resetShake();
		// U“®—Ê‚Ìæ“¾
		static Selene::Point2DF getCurrentShakeAmount();
	};
}
}
}