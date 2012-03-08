#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Sprite/DrawParameter.h"
#include "Defs/Mdl/STG/Bullet/BulletDefs.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
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
		CreateParam()
			: mPopped( false )
			, mHitRadius( 1 )
			, mDrawParam()
			, mHP( 100.0f )
		{}

		bool IsPopped() const { return mPopped; }
		void SetPopped( bool popped ) { mPopped = popped; }

		int GetHitRadius() const { return mHitRadius; }
		void SetHitRadius( int radius ) { mHitRadius = radius; }

		typedef Game::Util::Sprite::DrawParameter DrawParameter;
		const DrawParameter &GetDrawParameter() const { return mDrawParam; }
		void SetDrawParam( const DrawParameter &param ) { mDrawParam = param; }

		float GetHP() const { return mHP; }
		void SetHP( float hp ) { mHP = hp; }

	private:
		bool mPopped;
		int mHitRadius;
		DrawParameter mDrawParam;
		float mHP;

		friend BulletDefs;
	};
}
}
}
}
}