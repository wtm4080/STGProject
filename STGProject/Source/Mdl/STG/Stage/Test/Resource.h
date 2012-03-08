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
namespace Stage
{
namespace Test
{
	class Resource
	{
	public:
		Resource();

		static const Util::Sprite::SrcDef BACKGROUND1;
		Util::Sprite::PTexture GetBackground1() const;
		static const Util::Sprite::SrcDef BACKGROUND2;
		Util::Sprite::PTexture GetBackground2() const;

		static const Util::Sprite::SrcDef ICON1;
		Util::Sprite::PTexture GetIcon1() const;
		static const Util::Sprite::SrcDef ICON2;
		Util::Sprite::PTexture GetIcon2() const;
		static const Util::Sprite::SrcDef ICON3;
		Util::Sprite::PTexture GetIcon3() const;
		static const Util::Sprite::SrcDef ICON4;
		Util::Sprite::PTexture GetIcon4() const;

	private:
		Util::Sprite::PTexture mpBackground1;
		Util::Sprite::PTexture mpBackground2;

		Util::Sprite::PTexture mpIcon1;
		Util::Sprite::PTexture mpIcon2;
		Util::Sprite::PTexture mpIcon3;
		Util::Sprite::PTexture mpIcon4;
	};
}
}
}
}
}