#include "PCH.h"
#include "Creator.h"
#include "Particle.h"

#include "Defs/Ctrl/STG/STG.h"

using namespace Defs::Mdl::STG::Actor::Particle;
using namespace Game::Util::STG;


// コンストラクタ
Creator::Creator( const Parameter &param )
: mParam( param )
{
}


// パラメータの取得
Parameter Creator::GetParameter() const
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
	typedef Defs::Ctrl::STG::STG STGControl;
	auto random = STGControl::getRandom();

	for( unsigned i = 0; i < num; i++ )
	{
		Vector2DF pos( 
			random->GetFloat( mParam.GetPositionXRange() ), 
			random->GetFloat( mParam.GetPositionYRange() ) );
		float 
			angle = random->GetFloat( mParam.GetAngleRange() ), 
			speed = random->GetFloat( mParam.GetSpeedRange() ), 
			accel = random->GetFloat( mParam.GetAccelRange() ), 
			zoomRate = random->GetFloat( mParam.GetZoomRateRange() ), 
			zoomDecRate = random->GetFloat( mParam.GetZoomDecRateRange() ), 
			rotSpeed = random->GetFloat( mParam.GetRotSpeedRange() );

		Vector2DF speedVec, accelVec;
		speedVec.SetUnitVector( angle ) *= speed;
		accelVec.SetUnitVector( angle ) *= accel;

		PParticle pParticle( 
			new Particle( pos, mParam.GetDrawParameter() ) );
		pParticle->GetLocator().GetSpeed() = speedVec;
		pParticle->GetLocator().GetAccel() = accelVec;
		pParticle->SetZoomRate( zoomRate );
		pParticle->SetZoomDecRate( zoomDecRate );
		pParticle->SetRotSpeed( rotSpeed );

		STGControl::getActors()->GetActorList().push_back( 
			Game::Mdl::STG::Actor::PActor( pParticle ) );
	}
}