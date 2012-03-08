#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "ISprite.h"
#include "Util/Sprite/Manager.h"


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
	class SpriteImpl
		: public ISprite
	{
	public:
		// lŠpŒ`‚Ì•`‰æ
		virtual void Draw( const Sprite::DrawParameter &param )
		{
			Sprite::Manager::Draw( param );
		}

		// ƒeƒNƒXƒ`ƒƒ‚ğƒtƒ@ƒCƒ‹‚©‚ç“Ç‚İ‚Ş
		virtual Sprite::PTexture LoadTexture( 
			const std::wstring &fileName, 
			bool mipmap = true, 
			const Selene::ColorF &transColor = Selene::ColorF( 0, 0, 0, 0 ) 
			)
		{
			return Sprite::Manager::LoadTexture( fileName, mipmap, transColor );
		}
		virtual Sprite::PTexture LoadTexture( 
			File::PFile pFile, 
			bool mipmap = true, 
			const Selene::ColorF &transColor = Selene::ColorF( 0, 0, 0, 0 ) 
			)
		{
			return Sprite::Manager::LoadTexture( pFile, mipmap, transColor );
		}

		// ‰æ–Ê‚ÌU“®‚Ìİ’è
		virtual void SetShake( float amount, float decAmount = 1.0f )
		{
			Sprite::Manager::SetShake( amount, decAmount );
		}
		virtual void SetShake( const Selene::Point2DF &amount, float decAmount = 1.0f )
		{
			Sprite::Manager::SetShake( amount, decAmount );
		}
		// U“®‚Ìˆê’â~
		virtual void StopShake()
		{
			Sprite::Manager::StopShake();
		}
		// U“®‚ÌÄŠJ
		virtual void StartShake()
		{
			Sprite::Manager::StartShake();
		}
		// U“®‚ÌƒŠƒZƒbƒg
		virtual void ResetShake()
		{
			Sprite::Manager::ResetShake();
		}
		// U“®—Ê‚Ìæ“¾
		virtual Selene::Point2DF GetCurrentShakeAmount()
		{
			return Sprite::Manager::GetCurrentShakeAmount();
		}
	};
}
}
}
}