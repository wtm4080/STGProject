#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IFrameHolder.h"
#include <vector>
#include <boost/python.hpp>


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
	class Sequence
		: public IFrameHolder
	{
	public:
		typedef Game::Util::Sprite::PTexture PTexture;
		typedef std::vector<PTexture> TextureList;
		Sequence( const TextureList &textureList, 
			const DrawParameter &drawParam );
		Sequence( boost::python::object pyTextureList, 
			const DrawParameter &drawParam );

		virtual unsigned GetFrameNum() const;

		virtual unsigned GetFramePos() const;
		virtual void SetFramePos( unsigned framePos );

		virtual DrawParameter GetDrawParameter() const;
		virtual void SetDrawParameter( const DrawParameter &drawParam );

	private:
		TextureList mTextureList;
		unsigned mFramePos;
		DrawParameter mDrawParam;
	};
}
}
}
}
}