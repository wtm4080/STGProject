#include "PCH.h"
#include "Creator.h"
#include "Particle.h"

#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"

using namespace Game;
using namespace Mdl::STG::Actor::Particle;
using namespace Util::STG;


// コンストラクタ
Creator::Creator( PMode pMode, const Parameter &param )
: mpMode( pMode )
, mParam( param )
{
}


// パラメータの取得
const Parameter &Creator::GetParameter() const
{
	return mParam;
}

// パラメータの設定
void Creator::SetParameter( const Parameter &param )
{
	mParam = param;
}


// パーティクル生成
void Creator::Create( unsigned num ) const
{
	Create( num, mParam );
}

void Creator::Create( unsigned num, const Parameter &param ) const
{
	for( unsigned i = 0; i < num; i++ )
	{
		Vector2DF pos( 
			mpMode->GetRandom()->GetFloat( param.GetPositionXDomain() ), 
			mpMode->GetRandom()->GetFloat( param.GetPositionYDomain() ) );
		float 
			angle = mpMode->GetRandom()->GetFloat( param.GetAngleDomain() ), 
			speed = mpMode->GetRandom()->GetFloat( param.GetSpeedDomain() ), 
			accel = mpMode->GetRandom()->GetFloat( param.GetAccelDomain() ), 
			zoomRate = mpMode->GetRandom()->GetFloat( param.GetZoomRateDomain() ), 
			zoomDecRate = mpMode->GetRandom()->GetFloat( param.GetZoomDecRateDomain() );

		Vector2DF speedVec, accelVec;
		speedVec.SetUnitVector( angle ) *= speed;
		accelVec.SetUnitVector( angle ) *= accel;

		PParticle pParticle( 
			new Particle( mpMode, pos, param.GetDrawParameter() ) );
		pParticle->GetLocator().GetSpeed() = speedVec;
		pParticle->GetLocator().GetAccel() = accelVec;
		pParticle->SetZoomRate( zoomRate );
		pParticle->SetZoomDecRate( zoomDecRate );

		mpMode->GetActors().GetActors().push_back( PActor( pParticle ) );
	}
}