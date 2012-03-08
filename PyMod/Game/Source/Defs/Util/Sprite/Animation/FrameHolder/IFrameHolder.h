#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/Sprite/DrawParameter.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Sprite
{
namespace Animation
{
	namespace FrameHolder
	{
		class IFrameHolder
		{
		public:
			virtual unsigned GetFrameNum() const = 0;

			virtual unsigned GetFramePos() const = 0;
			virtual void SetFramePos( unsigned framePos ) = 0;

			typedef Game::Util::Sprite::DrawParameter DrawParameter;
			virtual DrawParameter GetDrawParameter() const = 0;
			virtual void SetDrawParameter( const DrawParameter &drawParam ) = 0;

			virtual ~IFrameHolder() {}
		};
	}

	typedef Game::Util::Ptr<FrameHolder::IFrameHolder>::Shared PFrameHolder;
}
}
}
}