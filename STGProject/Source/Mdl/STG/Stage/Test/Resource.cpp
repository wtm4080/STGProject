#include "PCH.h"
#include "Resource.h"

using namespace Game;
using namespace Mdl::STG::Stage::Test;

const Util::Sprite::SrcDef Resource::BACKGROUND1( L"Background1.dds", 0, 0, 640, 480 );
const Util::Sprite::SrcDef Resource::BACKGROUND2( L"Background2.dds", 0, 0, 640, 480 );

const Util::Sprite::SrcDef Resource::ICON1( L"Icon1.dds", 0, 0, 256, 256 );
const Util::Sprite::SrcDef Resource::ICON2( L"Icon2.dds", 0, 0, 256, 256 );
const Util::Sprite::SrcDef Resource::ICON3( L"Icon3.dds", 0, 0, 256, 256 );
const Util::Sprite::SrcDef Resource::ICON4( L"Icon4.dds", 0, 0, 256, 256 );


Resource::Resource()
{
	mpBackground1 = Util::Sprite::Manager::LoadTexture( BACKGROUND1.GetName() );
	mpBackground2 = Util::Sprite::Manager::LoadTexture( BACKGROUND2.GetName() );

	mpIcon1 = Util::Sprite::Manager::LoadTexture( ICON1.GetName() );
	mpIcon2 = Util::Sprite::Manager::LoadTexture( ICON2.GetName() );
	mpIcon3 = Util::Sprite::Manager::LoadTexture( ICON3.GetName() );
	mpIcon4 = Util::Sprite::Manager::LoadTexture( ICON4.GetName() );
}


Util::Sprite::PTexture Resource::GetBackground1() const
{
	return mpBackground1;
}

Util::Sprite::PTexture Resource::GetBackground2() const
{
	return mpBackground2;
}


Util::Sprite::PTexture Resource::GetIcon1() const
{
	return mpIcon1;
}

Util::Sprite::PTexture Resource::GetIcon2() const
{
	return mpIcon2;
}

Util::Sprite::PTexture Resource::GetIcon3() const
{
	return mpIcon3;
}

Util::Sprite::PTexture Resource::GetIcon4() const
{
	return mpIcon4;
}