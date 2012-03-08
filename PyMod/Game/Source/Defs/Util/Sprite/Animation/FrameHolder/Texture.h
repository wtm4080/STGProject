#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IFrameHolder.h"
#include <Selene.h>


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
	class Texture
		: public IFrameHolder
	{
	public:
		Texture( const Selene::Point2DI &frameSize, unsigned frameNum, 
			const DrawParameter &drawParam );

		virtual unsigned GetFrameNum() const;

		virtual unsigned GetFramePos() const;
		virtual void SetFramePos( unsigned framePos );

		virtual DrawParameter GetDrawParameter() const;
		virtual void SetDrawParameter( const DrawParameter &drawParam );

	private:
		Selene::Point2DI mFrameSize;
		const unsigned mFrameNum;
		unsigned mFramePos;
		DrawParameter mDrawParam;

		Selene::RectF GetCurrentTextureSrc() const;
	};
}
}
}
}
}