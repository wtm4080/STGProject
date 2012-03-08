#include "PCH.h"
#include "MLActor.h"

#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/Bullet/Linear.h"
#include "Mdl/STG/MyShip/IMyShip.h"


using namespace Game;
using namespace Mdl::STG;
using namespace Bullet::BulletML;
using namespace Util::STG;

const double MLActor::DEFAULT_RANK = 0.1;

namespace
{
	static const double DEFAULT_SPEED = 4.0;
}


MLActor::MLActor( PMode pMode, PBMLParser bp, 
	const Vector2DF &pos )
	: Base( pMode, pos, 0 )
	, BulletMLRunner( bp.get() )
	, mLocator( pos )
	, mDrawParam()
	, mAuxs( pMode )
	, mRank( DEFAULT_RANK )
	, mFrameCount( 0 )
	, mCreateParamList()
	, mAngle( -90.0f )
	, mpBMLParser( bp )
{
	Actor::Base::SetFrameCounting( false );
}

MLActor::MLActor( PMode pMode, PBMLParser bp, 
	const Locator::LinearF &locator, int hitRadius, 
	const Util::Sprite::DrawParameter &drawParam )
	: Base( pMode, locator.GetPosition(), hitRadius )
	, BulletMLRunner( bp.get() )
	, mLocator( locator )
	, mDrawParam( drawParam )
	, mAuxs( pMode )
	, mRank( DEFAULT_RANK )
	, mFrameCount( 0 )
	, mCreateParamList()
	, mAngle( -90.0f )
	, mpBMLParser( bp )
{
}

MLActor::MLActor( PMode pMode, PBMLParser bp, BulletMLState *bs, 
	const Locator::LinearF &locator, int hitRadius, 
	const Util::Sprite::DrawParameter &drawParam, 
	const CreateParamList &createParamList, 
	float angle )
	: Base( pMode, locator.GetPosition(), hitRadius )
	, BulletMLRunner( bs )
	, mLocator( locator )
	, mDrawParam( drawParam )
	, mAuxs( pMode )
	, mRank( DEFAULT_RANK )
	, mFrameCount( 0 )
	, mCreateParamList( createParamList )
	, mAngle( angle )
	, mpBMLParser( bp )
{
}


Vector2DF MLActor::GetPosition() const
{
	return mLocator.GetPosition();
}

Vector2DF MLActor::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


Locator::LinearF &MLActor::GetLocator()
{
	return mLocator;
}

const Util::Sprite::DrawParameter &MLActor::GetDrawParameter() const
{
	return mDrawParam;
}

void MLActor::SetDrawParameter( const Util::Sprite::DrawParameter &drawParam )
{
	mDrawParam = drawParam;
}


double MLActor::GetRank() const
{
	return mRank;
}

void MLActor::SetRank( double rank )
{
	assert( rank >= 0 && rank <= 1 );

	mRank = rank;
}

MLActor::CreateParamList &MLActor::GetCreateParamList()
{
	return mCreateParamList;
}


void MLActor::OnUpdate()
{
	BulletMLRunner::run();

	mLocator.Update();
	if( mLocator.GetSpeed().GetAbs() > 0 )
	{
		mAngle = mLocator.GetSpeed().GetAngle();
	}

	mDrawParam.SetDst( 
		mLocator.GetPosition().MakeRect( 
		mDrawParam.GetDst().w, mDrawParam.GetDst().h ) );

	mFrameCount++;

	//if( BulletMLRunner::isEnd() )
	//{
	//	Actor::Base::Erase();
	//}
}

void MLActor::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}

void MLActor::OnDestruct()
{
	mAuxs.CreateParticle( mDrawParam );
}

void MLActor::OnDestruct( float hp )
{
	mAuxs.CreateFadeOut( mDrawParam );
}

void MLActor::OnErase()
{
	mAuxs.CreateFadeOut( mDrawParam );
}


/// この弾の角度を求める
// 角度を度単位で、上方向 0 で時計周りで返す
double MLActor::getBulletDirection()
{
	return mAngle + 90;
}

/// この弾から自機を狙う角度を求める
// 角度を度単位で、上方向 0 で時計周りで返す
double MLActor::getAimDirection()
{
	return mLocator.GetPosition().GetAngle( 
		Actor::Base::GetActors().GetMyShip()->GetPosition() ) + 90;
}

/// この弾の速度を求める
double MLActor::getBulletSpeed()
{
	return mLocator.GetSpeed().GetAbs();
}

/// デフォルトの速度を求める
double MLActor::getDefaultSpeed()
{
	return DEFAULT_SPEED;
}

/// ランクを求める
// 0 から 1 までの実数
double MLActor::getRank()
{
	return mRank;
}

/// action を持たない弾を作る
void MLActor::createSimpleBullet( double direction, double speed )
{
	Locator::LinearF locator( mLocator.GetPosition() );
	locator.GetSpeed().SetUnitVector( 
		static_cast<float>( direction - 90 ) ) *= static_cast<float>( speed );

	if( mCreateParamList.empty() )
	{
		Actor::Base::GetActors().GetBullets().push_back( 
			PBullet( new Linear( Actor::Base::GetMode(), 
			locator, static_cast<int>( Base::GetHitRadius() ), mDrawParam ) ) );
	}
	else
	{
		int hitRadius = mCreateParamList.front().GetHitRadius();
		Util::Sprite::DrawParameter dParam = 
			mCreateParamList.front().GetDrawParameter();
		dParam.SetDst( mLocator.GetPosition().MakeRect( 
			dParam.GetDst().w, dParam.GetDst().h ) );

		if( mCreateParamList.front().IsPopped() )
		{
			mCreateParamList.pop_front();
		}

		Actor::Base::GetActors().GetBullets().push_back( 
			PBullet( new Linear( Actor::Base::GetMode(), 
			locator, hitRadius, dParam ) ) );
	}
}

/// action を持つ弾を作る
void MLActor::createBullet( BulletMLState *state, 
	double direction, double speed )
{
	float angle = static_cast<float>( direction - 90 );

	Locator::LinearF locator( mLocator.GetPosition() );
	locator.GetSpeed().SetUnitVector( angle ) *= static_cast<float>( speed );

	if( mCreateParamList.empty() )
	{
		Actor::Base::GetActors().GetBullets().push_back( 
			PBullet( new MLActor( Actor::Base::GetMode(), 
			mpBMLParser, state, 
			locator, static_cast<int>( Base::GetHitRadius() ), mDrawParam, 
			mCreateParamList, angle ) ) );
	}
	else
	{
		int hitRadius = mCreateParamList.front().GetHitRadius();
		Util::Sprite::DrawParameter dParam = 
			mCreateParamList.front().GetDrawParameter();
		dParam.SetDst( mLocator.GetPosition().MakeRect( 
			dParam.GetDst().w, dParam.GetDst().h ) );

		if( mCreateParamList.front().IsPopped() )
		{
			mCreateParamList.pop_front();
		}

		Actor::Base::GetActors().GetBullets().push_back( 
			PBullet( new MLActor( Actor::Base::GetMode(), 
			mpBMLParser, state, 
			locator, hitRadius, dParam, 
			mCreateParamList, angle ) ) );
	}
}

/// 弾の基準となるターンの値を返す、通常はフレーム数
int MLActor::getTurn()
{
	return mFrameCount;
}

/// 死ぬ
void MLActor::doVanish()
{
	//Base::Destruct();

	Actor::Base::SetValid( false );
}

/// 弾の方向を指定した方向に変更する
void MLActor::doChangeDirection( double dir )
{
	mAngle = static_cast<float>( dir - 90 );
	float speed = mLocator.GetSpeed().GetAbs();

	mLocator.GetSpeed().SetUnitVector( mAngle ) *= speed;
}

/// 弾の速度を指定した値に変更する
void MLActor::doChangeSpeed( double speed )
{
	mLocator.GetSpeed().SetUnitVector( mAngle ) *= 
		static_cast<float>( speed );
}

/// accel に対するインターフェイス
void MLActor::doAccelX( double accelX )
{
	mLocator.GetAccel().x = static_cast<float>( accelX );
}

void MLActor::doAccelY( double accelY )
{
	mLocator.GetAccel().y = static_cast<float>( accelY );
}

/// 弾の速さの X 方向成分を返します
double MLActor::getBulletSpeedX()
{
	return mLocator.GetSpeed().x;
}

/// 弾の速さの Y 方向成分を返します
double MLActor::getBulletSpeedY()
{
	return mLocator.GetSpeed().y;
}

/// 乱数を返す
double MLActor::getRand()
{
	return Actor::Base::GetMode()->GetRandom()->GetFloat( 0, 1 );
}