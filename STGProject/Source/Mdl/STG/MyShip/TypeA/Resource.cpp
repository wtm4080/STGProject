#include "PCH.h"
#include "Resource.h"

using namespace Game;
using namespace Mdl::STG::MyShip::TypeA;
using namespace Util::STG;
using namespace Util::Sprite;
using namespace Selene;

const SrcDef Resource::MY_SHIP( L"MyShip/Triangle.dds", 0, 0, 64, 64 );
const SrcDef Resource::HIT_MARK( L"RedCircle.dds", 0, 0, 64, 64 );
const SrcDef Resource::OPTION( L"MyShip/VistaLogo.dds", 0, 0, 256, 256 );
const SrcDef Resource::LASER( L"BlueCircle.dds", 0, 0, 64, 64 );
const SrcDef Resource::BLUE_CIRCLE( L"BlueCircle.dds", 0, 0, 64, 64 );
const SrcDef Resource::MISSILE( L"MyShip/Mine.dds", 0, 0, 256, 256 );
const SrcDef Resource::EXPLOSION( L"Explode.dds", 0, 0, 96*8, 96*2 );


// コンストラクタ
Resource::Resource()
{
	mpMyShip = Manager::LoadTexture( MY_SHIP.GetName() );
	mpHitMark = Manager::LoadTexture( HIT_MARK.GetName() );
	mpOption = Manager::LoadTexture( OPTION.GetName() );
	mpLaser = Manager::LoadTexture( LASER.GetName() );
	mpBlueCircle = Manager::LoadTexture( BLUE_CIRCLE.GetName() );
	mpMissile = Manager::LoadTexture( MISSILE.GetName() );
	mpExplosion = Manager::LoadTexture( EXPLOSION.GetName() );
}


// 自機の画像
PTexture Resource::GetMyShip() const
{
	return mpMyShip;
}

// 自機の当たり判定の画像
PTexture Resource::GetHitMark() const
{
	return mpHitMark;
}

// 自機オプション画像
PTexture Resource::GetOption() const
{
	return mpOption;
}

// 自機レーザーの画像
PTexture Resource::GetLaser() const
{
	return mpLaser;
}

// 青丸の画像
PTexture Resource::GetBlueCircle() const
{
	return mpBlueCircle;
}

// 自機ミサイルの画像
PTexture Resource::GetMissile() const
{
	return mpMissile;
}

// 爆発の画像の追加
PTexture Resource::GetExplosion() const
{
	return mpExplosion;
}