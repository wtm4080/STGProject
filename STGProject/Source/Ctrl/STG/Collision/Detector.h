#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/STG/Hit/Circle.h"
#include "Util/STG/Hit/Rect.h"

//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Collision
{
	template <class PTarget>
	class Detector_Circle
	{
	public:
		Detector_Circle( const Util::STG::Hit::CircleI &circle )
			: mCircle( circle )
		{}

		Util::STG::Vector2DF GetPosition() const { return mCircle.GetCenter(); }
		float GetRadius() const { return static_cast<float>( mCircle.GetRadius() ); }
		bool Detect( PTarget pTarget ) const { return pTarget->IsHit( mCircle ); }

	private:
		Util::STG::Hit::CircleI mCircle;
	};

	template <class PTarget>
	class Detector_Rect
	{
	public:
		Detector_Rect( const Util::STG::Hit::RectI &rect )
			: mRect( rect )
			, mRadius()
		{
			Util::STG::Vector2DF widthHeight( mRect.GetWidthHeight() );
			mRadius = sqrt( 
				Util::Pow( widthHeight.x ) + Util::Pow( widthHeight.y ) ) / 2;
		}

		Util::STG::Vector2DF GetPosition() const { return mRect.GetPosition(); }
		float GetRadius() const { return mRadius; }
		bool Detect( PTarget pTarget ) const { return pTarget->IsHit( mRect ); }

	private:
		Util::STG::Hit::RectI mRect;
		float mRadius;
	};
}
}
}
}