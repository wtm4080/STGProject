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
		// 四角形の描画
		virtual void Draw( const Sprite::DrawParameter &param )
		{
			Sprite::Manager::Draw( param );
		}

		// テクスチャをファイルから読み込む
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

		// 画面の振動の設定
		virtual void SetShake( float amount, float decAmount = 1.0f )
		{
			Sprite::Manager::SetShake( amount, decAmount );
		}
		virtual void SetShake( const Selene::Point2DF &amount, float decAmount = 1.0f )
		{
			Sprite::Manager::SetShake( amount, decAmount );
		}
		// 振動の一時停止
		virtual void StopShake()
		{
			Sprite::Manager::StopShake();
		}
		// 振動の再開
		virtual void StartShake()
		{
			Sprite::Manager::StartShake();
		}
		// 振動のリセット
		virtual void ResetShake()
		{
			Sprite::Manager::ResetShake();
		}
		// 振動量の取得
		virtual Selene::Point2DF GetCurrentShakeAmount()
		{
			return Sprite::Manager::GetCurrentShakeAmount();
		}
	};
}
}
}
}