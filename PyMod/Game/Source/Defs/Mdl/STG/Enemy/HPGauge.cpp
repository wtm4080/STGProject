#include "PCH.h"
#include "HPGauge.h"

#include "View/STG/DrawPriority.h"

#include "Defs/Util/Sprite/Sprite.h"

using namespace Defs::Mdl::STG;
using namespace Enemy;
using namespace Game::Util::STG;
using namespace Selene;
namespace py = boost::python;

namespace
{
	static const Vector2DF INIT_POS( 20.0f, 10.0f );
	static const float LENGTH = 400.0f;
	static const float APPEARING_SPEED = 1.0f;
}


HPGauge::HPGauge( float maxValue )
: mPos( INIT_POS )
, mMaxValue( maxValue )
, mValue( maxValue )
, mState( ST_DISAPPEAR )
, mVisibleValue( 0 )
{
	assert( maxValue > 0 );

	mDrawParam.SetTexture( 
		py::extract<Game::Util::Sprite::PTexture>( 
		mAuxs.GetCommonResource().attr( "get" )( "hpGauge" ) ) );
	mDrawParam.SetPriority( Game::View::STG::PRI_ENEMY_HPGAUGE );
}


void HPGauge::Update()
{
	switch( mState )
	{
	case ST_DISAPPEAR:
		break;
	case ST_APPEARING:
		{
			mVisibleValue += mMaxValue/100 * APPEARING_SPEED;

			if( mVisibleValue >= mValue )
			{
				mVisibleValue = mValue;
				mState = ST_APPEARED;
			}

			UpdateDrawParam();

			break;
		}
	case ST_APPEARED:
		{
			mVisibleValue = mValue;

			if( mValue <= 0 )
			{
				mValue = 0;
				mVisibleValue = 0;
				mState = ST_DISAPPEAR;
			}

			UpdateDrawParam();

			break;
		}
	default:
		assert( false );
		break;
	}
}

void HPGauge::UpdateDrawParam()
{
	float rate = mVisibleValue / mMaxValue;
	assert( rate >= 0 );

	RectF src( 0, 0, 100.0f, 16.0f );
	src.x = rate <= 1.0f ? ( rate * 100.0f ) : 100.0f;
	src.w = 1.0f;

	mDrawParam.SetSrc( src );
	mDrawParam.SetDst( mPos.MakeRect( 
		LENGTH * rate, 16.0f, false ) );
}

void HPGauge::Draw() const
{
	if( mState != ST_DISAPPEAR )
	{
		Defs::Util::Sprite::Sprite::draw( mDrawParam );
	}
}


void HPGauge::Appear()
{
	mState = ST_APPEARING;
	mVisibleValue = 0;
}

void HPGauge::Disappear()
{
	mState = ST_DISAPPEAR;
	mVisibleValue = 0;
}


float HPGauge::GetMaxValue() const
{
	return mMaxValue;
}

void HPGauge::SetMaxValue( float value )
{
	assert( value > 0 );

	mMaxValue = value;
}

float HPGauge::GetValue() const
{
	return mValue;
}

void HPGauge::SetValue( float value )
{
	mValue = value > 0 ? value : 0;
}


float HPGauge::GetVisibleValue() const
{
	return mVisibleValue;
}