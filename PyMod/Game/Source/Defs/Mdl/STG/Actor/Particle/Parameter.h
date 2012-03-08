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

namespace Defs
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
		typedef Game::Util::Sprite::DrawParameter DrawParameter;

		Parameter()
			: mDrawParam()
			, mPosXRange()
			, mPosYRange()
			, mAngleRange( -180.0f, 180.0f )
			, mSpeedRange( 1.0f )
			, mAccelRange()
			, mZoomRateRange( 1.0f )
			, mZoomDecRateRange( 0.01f )
			, mRotSpeedRange()
		{}

		DrawParameter GetDrawParameter() const { return mDrawParam; }
		void SetDrawParameter( const DrawParameter &param ) { mDrawParam = param; }

		const IntervalF &GetPositionXRange() const { return mPosXRange; }
		const IntervalF &GetPositionYRange() const { return mPosYRange; }
		void SetPosition( float x, float y ) { mPosXRange = IntervalF( x ); mPosYRange = IntervalF( y ); }
		void SetPosition( const Game::Util::STG::Vector2DF &pos ) { mPosXRange = IntervalF( pos.x ); mPosYRange = IntervalF( pos.y ); }
		void SetPositionXRange( float min, float max ) { mPosXRange = IntervalF( min, max ); }
		void SetPositionXRange( const IntervalF &range ) { mPosXRange = range; }
		void SetPositionYRange( float min, float max ) { mPosYRange = IntervalF( min, max ); }
		void SetPositionYRange( const IntervalF &range ) { mPosYRange = range; }

		const IntervalF &GetAngleRange() const { return mAngleRange; }
		void SetAngle( float angle ) { mAngleRange = IntervalF( angle ); }
		void SetAngleRange( float min, float max ) { mAngleRange = IntervalF( min, max ); }
		void SetAngleRange( const IntervalF &range ) { mAngleRange = range; }

		const IntervalF &GetSpeedRange() const { return mSpeedRange; }
		void SetSpeed( float speed ) { mSpeedRange = IntervalF( speed ); }
		void SetSpeedRange( float min, float max ) { mSpeedRange = IntervalF( min, max ); }
		void SetSpeedRange( const IntervalF &range ) { mSpeedRange = range; }

		const IntervalF &GetAccelRange() const { return mAccelRange; }
		void SetAccel( float accel ) { mAccelRange = IntervalF( accel ); }
		void SetAccelRange( float min, float max ) { mAccelRange = IntervalF( min, max ); }
		void SetAccelRange( const IntervalF &range ) { mAccelRange = range; }

		const IntervalF &GetZoomRateRange() const { return mZoomRateRange; }
		void SetZoomRate( float zoomRate ) { mZoomRateRange = IntervalF( zoomRate ); }
		void SetZoomRateRange( float min, float max ) { mZoomRateRange = IntervalF( min, max ); }
		void SetZoomRateRange( const IntervalF &range ) { mZoomRateRange = range; }

		const IntervalF &GetZoomDecRateRange() const { return mZoomDecRateRange; }
		void SetZoomDecRate( float zoomDecRate ) { mZoomDecRateRange = IntervalF( zoomDecRate ); }
		void SetZoomDecRateRange( float min, float max ) { mZoomDecRateRange = IntervalF( min, max ); }
		void SetZoomDecRateRange( const IntervalF &range ) { mZoomDecRateRange = range; }

		const IntervalF &GetRotSpeedRange() const { return mRotSpeedRange; }
		void SetRotSpeed( float speed ) { mRotSpeedRange = IntervalF( speed ); }
		void SetRotSpeedRange( float min, float max ) { mRotSpeedRange = IntervalF( min, max ); }
		void SetRotSpeedRange( const IntervalF &range ) { mRotSpeedRange = range; }

	private:
		DrawParameter mDrawParam;
		IntervalF 
			mPosXRange, 
			mPosYRange, 
			mAngleRange, 
			mSpeedRange, 
			mAccelRange, 
			mZoomRateRange, 
			mZoomDecRateRange, 
			mRotSpeedRange;
	};
}
}
}
}
}