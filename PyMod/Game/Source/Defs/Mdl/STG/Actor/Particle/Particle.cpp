#include "PCH.h"
#include "Particle.h"

#include "Defs/Util/Sprite/Sprite.h"

using namespace Defs::Mdl::STG;
using namespace Actor::Particle;
using namespace Game::Util::STG;
using namespace Selene;

namespace
{
	static const float INIT_ZOOM_DEC_RATE = 0.01f;
	static const boost::numeric::interval<float> ZOOM_DEC_RATE_DOMAIN( 0.0f, 1.0f );
}


// コンストラクタ
Particle::Particle( const Vector2DF &pos, const DrawParameter &dParam )
: Base( Hit::RectI() )
, mLocator( pos, Vector2DF(), Vector2DF() )
, mDrawParam( dParam )
, mZoomDecRate( INIT_ZOOM_DEC_RATE )
, mZoomRateCount( ZOOM_DEC_RATE_DOMAIN.upper() )
, mRotSpeed()
{
	ModifyValidRect();
}


// 位置の取得
Vector2DF Particle::GetPosition() const
{
	return mLocator.GetPosition();
}

// 外力の適用
Vector2DF Particle::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


// ロケータの取得
Locator::LinearF &Particle::GetLocator()
{
	return mLocator;
}

// 描画パラメータの取得
Particle::DrawParameter Particle::GetDrawParameter() const
{
	return mDrawParam;
}

// 描画パラメータの設定
void Particle::SetDrawParameter( const DrawParameter &param )
{
	mDrawParam = param;

	ModifyValidRect();
}

// 拡大率の取得
float Particle::GetZoomRate() const
{
	return mZoomRateCount;
}

// 拡大率の設定
void Particle::SetZoomRate( float rate )
{
	mZoomRateCount = rate;

	ModifyValidRect();
}

// 拡大率の減少率の取得
float Particle::GetZoomDecRate() const
{
	return mZoomDecRate;
}

// 拡大率の減少率の設定
void Particle::SetZoomDecRate( float rate )
{
	assert( boost::numeric::in( rate, ZOOM_DEC_RATE_DOMAIN ) );

	mZoomDecRate = rate;
}

// 回転速度の取得
float Particle::GetRotSpeed() const
{
	return mRotSpeed;
}

// 回転速度の設定
void Particle::SetRotSpeed( float speed )
{
	mRotSpeed = speed;
}


void Particle::OnUpdate()
{
	mLocator.Update();

	mZoomRateCount -= mZoomDecRate;
	if( mZoomRateCount <= 0 )
	{
		Base::SetValid( false );
	}

	mDrawParam.SetRotDegree( mDrawParam.GetRotDegree() + mRotSpeed );
	if( mDrawParam.GetRotDegree() >= 180 )
	{
		mDrawParam.SetRotDegree( mDrawParam.GetRotDegree() - 180 );
	}
	else if( mDrawParam.GetRotDegree() <= -180 )
	{
		mDrawParam.SetRotDegree( mDrawParam.GetRotDegree() + 180 );
	}

	ModifyValidRect();
}

void Particle::OnDraw() const
{
	if( Base::IsValid() )
	{
		Defs::Util::Sprite::Sprite::draw( CreateDrawParam() );
	}
}

void Particle::OnErase()
{
	mAuxs.CreateFadeOut( CreateDrawParam () );
}


Particle::DrawParameter Particle::CreateDrawParam() const
{
	DrawParameter dParam = mDrawParam;
	RectF dst = dParam.GetDst();
	dst.w *= mZoomRateCount;
	dst.h *= mZoomRateCount;
	dst = mLocator.GetPosition().MakeRect( dst.w, dst.h );
	dParam.SetDst( dst );

	return dParam;
}

void Particle::ModifyValidRect()
{
	Hit::RectI validRect;
	validRect.SetPosition( mLocator.GetPosition() );
	validRect.SetWidthHeight( 
		mDrawParam.GetDst().w * mZoomRateCount, 
		mDrawParam.GetDst().h * mZoomRateCount );
	Base::SetValidRect( validRect );
}