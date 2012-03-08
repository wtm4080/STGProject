#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/Sprite/DrawParameter.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Bullet
{
namespace BulletML
{
	class CreateParam
	{
	public:
		bool IsPopped() const
		{
			return mPopped;
		}
		void SetPopped( bool popped )
		{
			mPopped = popped;
		}

		int GetHitRadius() const
		{
			return mHitRadius;
		}
		void SetHitRadius( int radius )
		{
			mHitRadius = radius;
		}

		const Util::Sprite::DrawParameter &GetDrawParameter() const
		{
			return mDrawParam;
		}
		void SetDrawParam( const Util::Sprite::DrawParameter &param )
		{
			mDrawParam = param;
		}

	private:
		bool mPopped;
		int mHitRadius;
		Util::Sprite::DrawParameter mDrawParam;
	};
}
}
}
}
}