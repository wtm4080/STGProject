#include "PCH.h"
#include "Common.h"

using namespace Game;
using namespace Game::Mdl::STG::Resource;
using namespace Selene;

// 情報表示領域の背景画像
const Util::Sprite::SrcDef Common::INFAREA_BACK( L"InfAreaBack.dds", 0, 0, 200.0f, 480.0f );

// 1UPアイテムの画像
const Util::Sprite::SrcDef Common::ITEM_EXTEND( L"Item/1Up.dds", 0, 0, 32.0f, 32.0f );
// 武器パワーアップの画像
const Util::Sprite::SrcDef Common::ITEM_POWERUP( L"Item/PowerUp.dds", 0, 0, 32.0f, 32.0f );
// 特殊攻撃補給アイテムの画像
const Util::Sprite::SrcDef Common::ITEM_SPATTACK( L"Item/SpAttack.dds", 0, 0, 32.0f, 32.0f );

// 爆発のアニメーション画像
const Util::Sprite::SrcDef Common::EXPLOSION( L"Explode.dds", 0, 0, 96*8, 96*2 );

// 敵弾の画像
const Util::Sprite::SrcDef Common::BULLET_RED( L"RedCircle.dds", 0, 0, 64, 64 );
const Util::Sprite::SrcDef Common::BULLET_GREEN( L"GreenCircle.dds", 0, 0, 64, 64 );
const Util::Sprite::SrcDef Common::BULLET_BLUE( L"BlueCircle.dds", 0, 0, 64, 64 );
const Util::Sprite::SrcDef Common::BULLET_WHITE( L"WhiteCircle.dds", 0, 0, 64, 64 );
const Util::Sprite::SrcDef Common::BULLET_PURPLE( L"PurpleCircle.dds", 0, 0, 64, 64 );

// 敵弾ダメージエフェクトの画像
const Util::Sprite::SrcDef Common::BULLET_DAMAGED_EFFECT( L"BulletDamagedEffect.dds", 0, 0, 64, 64 );

// HPゲージの画像
const Util::Sprite::SrcDef Common::HP_GAUGE( L"HPGauge.dds", 0, 0, 100, 16 );


// コンストラクタ
Common::Common()
{
	mpFont16 = Util::Font::Manager::LoadFont( L"Font16.sff" );
	mpFont32 = Util::Font::Manager::LoadFont( L"Font32.sff" );

	mpInfAreaBack = Util::Sprite::Manager::LoadTexture( INFAREA_BACK.GetName() );

	mpItemExtend = Util::Sprite::Manager::LoadTexture( ITEM_EXTEND.GetName() );
	mpItemPowerUp = Util::Sprite::Manager::LoadTexture( ITEM_POWERUP.GetName() );
	mpItemSpAttack = Util::Sprite::Manager::LoadTexture( ITEM_SPATTACK.GetName() );

	mpExplosion = Util::Sprite::Manager::LoadTexture( EXPLOSION.GetName() );

	mpBulletRed = Util::Sprite::Manager::LoadTexture( BULLET_RED.GetName() );
	mpBulletGreen = Util::Sprite::Manager::LoadTexture( BULLET_GREEN.GetName() );
	mpBulletBlue = Util::Sprite::Manager::LoadTexture( BULLET_BLUE.GetName() );
	mpBulletWhite = Util::Sprite::Manager::LoadTexture( BULLET_WHITE.GetName() );
	mpBulletPurple = Util::Sprite::Manager::LoadTexture( BULLET_PURPLE.GetName() );

	mpBulletDamagedEffect = Util::Sprite::Manager::LoadTexture( BULLET_DAMAGED_EFFECT.GetName() );

	mpHPGauge = Util::Sprite::Manager::LoadTexture( HP_GAUGE.GetName() );
}


// 文字描画用フォントの取得
Util::Font::PFont Common::GetFont16( Sint32 priority, bool shakable, Sint32 size ) const
{
	mpFont16->SetPriority( priority );
	mpFont16->SetShakable( shakable );
	mpFont16->SetSize( size );

	return mpFont16;
}

Util::Font::PFont Common::GetFont32( Sint32 priority, bool shakable, Sint32 size ) const
{
	mpFont32->SetPriority( priority );
	mpFont32->SetShakable( shakable );
	mpFont32->SetSize( size );

	return mpFont32;
}


// 情報表示領域の背景画像
Util::Sprite::PTexture Common::GetInfAreaBack() const
{
	return mpInfAreaBack;
}


// 1UPアイテムの画像
Util::Sprite::PTexture Common::GetItemExtend() const
{
	return mpItemExtend;
}

// 武器パワーアップの画像
Util::Sprite::PTexture Common::GetItemPowerUp() const
{
	return mpItemPowerUp;
}

// 特殊攻撃補給アイテムの画像
Util::Sprite::PTexture Common::GetItemSpAttack() const
{
	return mpItemSpAttack;
}


// 爆発のアニメーション画像
Util::Sprite::PTexture Common::GetExplosion() const
{
	return mpExplosion;
}


// 敵弾の画像
Util::Sprite::PTexture Common::GetBulletRed() const
{
	return mpBulletRed;
}

Util::Sprite::PTexture Common::GetBulletGreen() const
{
	return mpBulletGreen;
}

Util::Sprite::PTexture Common::GetBulletBlue() const
{
	return mpBulletBlue;
}

Util::Sprite::PTexture Common::GetBulletWhite() const
{
	return mpBulletWhite;
}

Util::Sprite::PTexture Common::GetBulletPurple() const
{
	return mpBulletPurple;
}


// 敵弾ダメージエフェクトの画像
Util::Sprite::PTexture Common::GetBulletDamagedEffect() const
{
	return mpBulletDamagedEffect;
}


// HPゲージの画像
Util::Sprite::PTexture Common::GetHPGauge() const
{
	return mpHPGauge;
}