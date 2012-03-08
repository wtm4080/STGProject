#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Sprite/DrawParameter.h"
#include <boost/numeric/interval.hpp>
#include "Util/STG/Vector2D.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Actor
{
namespace Particle
{
	class Parameter
	{
	public:
		typedef boost::numeric::interval<float> IntervalF;

		Parameter()
			: mDrawParam()
			, mPosXDomain()
			, mPosYDomain()
			, mAngleDomain( -180.0f, 180.0f )
			, mSpeedDomain( 1.0f )
			, mAccelDomain()
			, mZoomRateDomain( 1.0f )
			, mZoomDecRateDomain( 0.01f )
		{}

		const Util::Sprite::DrawParameter &GetDrawParameter() const { return mDrawParam; }
		void SetDrawParameter( const Util::Sprite::DrawParameter &param ) { mDrawParam = param; }

		const IntervalF &GetPositionXDomain() const { return mPosXDomain; }
		const IntervalF &GetPositionYDomain() const { return mPosYDomain; }
		void SetPosition( float x, float y ) { mPosXDomain = IntervalF( x ); mPosYDomain = IntervalF( y ); }
		void SetPosition( const Util::STG::Vector2DF &pos ) { mPosXDomain = IntervalF( pos.x ); mPosYDomain = IntervalF( pos.y ); }
		void SetPositionXDomain( float min, float max ) { mPosXDomain = IntervalF( min, max ); }
		void SetPositionXDomain( const IntervalF &domain ) { mPosXDomain = domain; }
		void SetPositionYDomain( float min, float max ) { mPosYDomain = IntervalF( min, max ); }
		void SetPositionYDomain( const IntervalF &domain ) { mPosYDomain = domain; }

		const IntervalF &GetAngleDomain() const { return mAngleDomain; }
		void SetAngle( float angle ) { mAngleDomain = IntervalF( angle ); }
		void SetAngleDomain( float min, float max ) { mAngleDomain = IntervalF( min, max ); }
		void SetAngleDomain( const IntervalF &domain ) { mAngleDomain = domain; }

		const IntervalF &GetSpeedDomain() const { return mSpeedDomain; }
		void SetSpeed( float speed ) { mSpeedDomain = IntervalF( speed ); }
		void SetSpeedDomain( float min, float max ) { mSpeedDomain = IntervalF( min, max ); }
		void SetSpeedDomain( const IntervalF &domain ) { mSpeedDomain = domain; }

		const IntervalF &GetAccelDomain() const { return mAccelDomain; }
		void SetAccel( float accel ) { mAccelDomain = IntervalF( accel ); }
		void SetAccelDomain( float min, float max ) { mAccelDomain = IntervalF( min, max ); }
		void SetAccelDomain( const IntervalF &domain ) { mAccelDomain = domain; }

		const IntervalF &GetZoomRateDomain() const { return mZoomRateDomain; }
		void SetZoomRate( float zoomRate ) { mZoomRateDomain = IntervalF( zoomRate ); }
		void SetZoomRateDomain( float min, float max ) { mZoomRateDomain = IntervalF( min, max ); }
		void SetZoomRateDomain( const IntervalF &domain ) { mZoomRateDomain = domain; }

		const IntervalF &GetZoomDecRateDomain() const { return mZoomDecRateDomain; }
		void SetZoomDecRate( float zoomDecRate ) { mZoomDecRateDomain = IntervalF( zoomDecRate ); }
		void SetZoomDecRateDomain( float min, float max ) { mZoomDecRateDomain = IntervalF( min, max ); }
		void SetZoomDecRateDomain( const IntervalF &domain ) { mZoomDecRateDomain = domain; }

	private:
		Util::Sprite::DrawParameter mDrawParam;
		IntervalF 
			mPosXDomain, 
			mPosYDomain, 
			mAngleDomain, 
			mSpeedDomain, 
			mAccelDomain, 
			mZoomRateDomain, 
			mZoomDecRateDomain;
	};
}
}
}
}
}