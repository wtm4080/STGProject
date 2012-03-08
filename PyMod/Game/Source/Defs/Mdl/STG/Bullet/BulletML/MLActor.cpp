#include "PCH.h"
#include "MLActor.h"

#include "Defs/Ctrl/STG/STG.h"
#include "Defs/Mdl/STG/Bullet/Simple.h"
#include "Defs/Util/Sprite/Sprite.h"
#include "Mdl/STG/MyShip/IMyShip.h"

using namespace Defs::Mdl::STG;
using namespace Bullet::BulletML;
using namespace Game::Util::STG;

const double MLActor::DEFAULT_RANK = 0.1;

namespace
{
	static const double DEFAULT_SPEED = 4.0;

	typedef Defs::Ctrl::STG::STG STGControl;
}


MLActor::MLActor( PBMLParser bp, 
	const Vector2DF &pos )
	: Base( pos, 0 )
	, BulletMLRunner( bp.get() )
	, mLocator( pos )
	, mDrawParam()
	, mRank( DEFAULT_RANK )
	, mFrameCount( 0 )
	, mCreateParamList()
	, mAngle( -90.0f )
	, mpBMLParser( bp )
{
	Actor::Base::SetFrameCounting( false );
}

MLActor::MLActor( PBMLParser bp, 
	const Locator::LinearF &locator, int hitRadius, 
	const DrawParameter &drawParam )
	: Base( locator.GetPosition(), hitRadius )
	, BulletMLRunner( bp.get() )
	, mLocator( locator )
	, mDrawParam( drawParam )
	, mRank( DEFAULT_RANK )
	, mFrameCount( 0 )
	, mCreateParamList()
	, mAngle( -90.0f )
	, mpBMLParser( bp )
{
}

MLActor::MLActor( PBMLParser bp, BulletMLState *bs, 
	const Locator::LinearF &locator, int hitRadius, 
	const DrawParameter &drawParam, 
	const CreateParamList &createParamList, 
	float angle )
	: Base( locator.GetPosition(), hitRadius )
	, BulletMLRunner( bs )
	, mLocator( locator )
	, mDrawParam( drawParam )
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

const MLActor::DrawParameter &MLActor::GetDrawParameter() const
{
	return mDrawParam;
}

void MLActor::SetDrawParameter( const DrawParameter &drawParam )
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
	Defs::Util::Sprite::Sprite::draw( mDrawParam );
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
	auto pMyShip = STGControl::getActors()->GetMyShip();

	return mLocator.GetPosition().GetAngle( pMyShip->GetPosition() ) + 90;
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
		STGControl::getActors()->GetBulletList().push_back( 
			Game::Mdl::STG::Bullet::PBullet( 
			new Linear( locator, 
			static_cast<int>( Base::GetHitRadius() ), mDrawParam ) ) );
	}
	else
	{
		int hitRadius = mCreateParamList.front().GetHitRadius();
		DrawParameter dParam = 
			mCreateParamList.front().GetDrawParameter();
		dParam.SetDst( mLocator.GetPosition().MakeRect( 
			dParam.GetDst().w, dParam.GetDst().h ) );

		PLinear pBullet( 
			new Linear( locator, hitRadius, dParam ) );
		pBullet->SetHP( mCreateParamList.front().GetHP() );

		if( mCreateParamList.front().IsPopped() )
		{
			mCreateParamList.pop_front();
		}

		STGControl::getActors()->GetBulletList().push_back( pBullet );
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
		STGControl::getActors()->GetBulletList().push_back( 
			Game::Mdl::STG::Bullet::PBullet( 
			new MLActor( mpBMLParser, state, 
			locator, static_cast<int>( Base::GetHitRadius() ), mDrawParam, 
			mCreateParamList, angle ) ) );
	}
	else
	{
		int hitRadius = mCreateParamList.front().GetHitRadius();
		DrawParameter dParam = 
			mCreateParamList.front().GetDrawParameter();
		dParam.SetDst( mLocator.GetPosition().MakeRect( 
			dParam.GetDst().w, dParam.GetDst().h ) );
		float hp = mCreateParamList.front().GetHP();

		if( mCreateParamList.front().IsPopped() )
		{
			mCreateParamList.pop_front();
		}

		PMLActor pBullet( 
			new MLActor( mpBMLParser, state, 
			locator, hitRadius, dParam, 
			mCreateParamList, angle ) );
		pBullet->SetHP( hp );

		STGControl::getActors()->GetBulletList().push_back( pBullet );
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
	return STGControl::getRandom()->GetFloat( 0, 1 );
}