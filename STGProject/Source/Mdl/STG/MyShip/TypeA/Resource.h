#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/Sprite/SrcDef.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace MyShip
{
namespace TypeA
{
	class Resource
	{
	public:
		// コンストラクタ
		Resource();

		// 自機の画像
		Util::Sprite::PTexture GetMyShip() const;
		static const Util::Sprite::SrcDef MY_SHIP;
		// 自機の当たり判定の画像
		Util::Sprite::PTexture GetHitMark() const;
		static const Util::Sprite::SrcDef HIT_MARK;
		// 自機オプション画像
		Util::Sprite::PTexture GetOption() const;
		static const Util::Sprite::SrcDef OPTION;
		// 自機レーザーの画像
		Util::Sprite::PTexture GetLaser() const;
		static const Util::Sprite::SrcDef LASER;
		// 青丸の画像
		Util::Sprite::PTexture GetBlueCircle() const;
		static const Util::Sprite::SrcDef BLUE_CIRCLE;
		// 自機ミサイルの画像
		Util::Sprite::PTexture GetMissile() const;
		static const Util::Sprite::SrcDef MISSILE;
		// 爆発の画像の追加
		Util::Sprite::PTexture GetExplosion() const;
		static const Util::Sprite::SrcDef EXPLOSION;

	private:
		Util::Sprite::PTexture mpMyShip;
		Util::Sprite::PTexture mpHitMark;
		Util::Sprite::PTexture mpOption;
		Util::Sprite::PTexture mpLaser;
		Util::Sprite::PTexture mpBlueCircle;
		Util::Sprite::PTexture mpMissile;
		Util::Sprite::PTexture mpExplosion;
	};
}
}
}
}
}