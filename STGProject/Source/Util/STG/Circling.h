#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Common.h"

//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace STG
{
	template <class T>
	class Circling
	{
	public:
		Circling()
			: mCirclingFlag()
			, mAngle()
			, mCirclingAngle()
			, mTargetAngle()
		{}
		Circling( T circlingAngle )
			: mCirclingFlag()
			, mAngle()
			, mCirclingAngle( circlingAngle )
			, mTargetAngle()
		{}

		void Update()
		{
			if( IsCircling() )
			{
				if( IsRightCircling() )
				{
					IsMaxCircling() ? 
						( mAngle += mCirclingAngle ) : ( mAngle = mTargetAngle );
				}
				else
				{
					IsMaxCircling() ? 
						( mAngle -= mCirclingAngle ) : ( mAngle = mTargetAngle );
				}
			}
		}

		bool IsCircling() const
		{
			return mCirclingFlag;
		}
		void SetCircling( bool circling )
		{
			mCirclingFlag = circling;
		}

		T GetAngle() const
		{
			return mAngle;
		}
		void SetAngle( T angle )
		{
			mAngle = angle;
		}

		T GetCirclingAngle() const
		{
			return mCirclingAngle;
		}
		void SetCirclingAngle( T angle )
		{
			mCirclingAngle = angle;
		}

		T GetTargetAngle() const
		{
			return mTargetAngle;
		}
		void SetTargetAngle( T angle )
		{
			mTargetAngle = angle;
		}

	private:
		bool mCirclingFlag;
		T mAngle, mCirclingAngle, mTargetAngle;

		// ‰E‰ñ‚è‚©‚Ç‚¤‚©
		bool IsRightCircling() const
		{
			return 
				Util::Cos( mTargetAngle ) * Util::Cos( mAngle + mCirclingAngle ) + 
				Util::Sin( mTargetAngle ) * Util::Sin( mAngle + mCirclingAngle ) 
				>= 
				Util::Cos( mTargetAngle ) * Util::Cos( mAngle - mCirclingAngle ) + 
				Util::Sin( mTargetAngle ) * Util::Sin( mAngle - mCirclingAngle );
		}
		// ù‰ñãŒÀŠp“x‚Åù‰ñ‚·‚é‚©‚Ç‚¤‚©
		bool IsMaxCircling() const
		{
			return 
				Util::Cos( mAngle ) * Util::Cos( mAngle + mCirclingAngle ) + 
				Util::Sin( mAngle ) * Util::Sin( mAngle + mCirclingAngle ) 
				>= 
				Util::Cos( mAngle ) * Util::Cos( mTargetAngle ) + 
				Util::Sin( mAngle ) * Util::Sin( mTargetAngle );
		}
	};

	typedef Circling<float> CirclingF;
	typedef Circling<Selene::Sint32> CirclingI;
}
}
}