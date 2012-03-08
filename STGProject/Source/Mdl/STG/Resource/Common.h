#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <boost/noncopyable.hpp>
#include "Util/Font/Manager.h"
#include "Util/Sprite/Manager.h"
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
namespace Resource
{
	class Common
		: public boost::noncopyable
	{
	public:
		// コンストラクタ
		Common();

		// 文字描画用フォントの取得
		Util::Font::PFont GetFont16( Selene::Sint32 priority, 
			bool shakable = true, 
			Selene::Sint32 size = 16 ) const;
		Util::Font::PFont GetFont32( Selene::Sint32 priority, 
			bool shakable = true, 
			Selene::Sint32 size = 32 ) const;

		// 情報表示領域の背景画像
		static const Util::Sprite::SrcDef INFAREA_BACK;
		Util::Sprite::PTexture GetInfAreaBack() const;

		// 1UPアイテムの画像
		static const Util::Sprite::SrcDef ITEM_EXTEND;
		Util::Sprite::PTexture GetItemExtend() const;
		// 武器パワーアップの画像
		static const Util::Sprite::SrcDef ITEM_POWERUP;
		Util::Sprite::PTexture GetItemPowerUp() const;
		// 特殊攻撃補給アイテムの画像
		static const Util::Sprite::SrcDef ITEM_SPATTACK;
		Util::Sprite::PTexture GetItemSpAttack() const;

		// 爆発のアニメーション画像
		static const Util::Sprite::SrcDef EXPLOSION;
		Util::Sprite::PTexture GetExplosion() const;

		// 敵弾の画像
		static const Util::Sprite::SrcDef BULLET_RED;
		Util::Sprite::PTexture GetBulletRed() const;
		static const Util::Sprite::SrcDef BULLET_GREEN;
		Util::Sprite::PTexture GetBulletGreen() const;
		static const Util::Sprite::SrcDef BULLET_BLUE;
		Util::Sprite::PTexture GetBulletBlue() const;
		static const Util::Sprite::SrcDef BULLET_WHITE;
		Util::Sprite::PTexture GetBulletWhite() const;
		static const Util::Sprite::SrcDef BULLET_PURPLE;
		Util::Sprite::PTexture GetBulletPurple() const;

		// 敵弾ダメージエフェクトの画像
		static const Util::Sprite::SrcDef BULLET_DAMAGED_EFFECT;
		Util::Sprite::PTexture GetBulletDamagedEffect() const;

		// HPゲージの画像
		static const Util::Sprite::SrcDef HP_GAUGE;
		Util::Sprite::PTexture GetHPGauge() const;

	private:
		// 文字描画用フォント
		Util::Font::PFont mpFont16;
		Util::Font::PFont mpFont32;

		// 情報表示領域の背景画像
		Util::Sprite::PTexture mpInfAreaBack;

		// 1UPアイテムの画像
		Util::Sprite::PTexture mpItemExtend;
		// 武器パワーアップの画像
		Util::Sprite::PTexture mpItemPowerUp;
		// 特殊攻撃補給アイテムの画像
		Util::Sprite::PTexture mpItemSpAttack;

		// 爆発のアニメーション画像
		Util::Sprite::PTexture mpExplosion;

		// 敵弾の画像
		Util::Sprite::PTexture mpBulletRed;
		Util::Sprite::PTexture mpBulletGreen;
		Util::Sprite::PTexture mpBulletBlue;
		Util::Sprite::PTexture mpBulletWhite;
		Util::Sprite::PTexture mpBulletPurple;

		// 敵弾ダメージエフェクトの画像
		Util::Sprite::PTexture mpBulletDamagedEffect;

		// HPゲージの画像
		Util::Sprite::PTexture mpHPGauge;
	};
}
}
}
}