#include "PCH.h"
#include "MLLocator.h"

using namespace Game;
using namespace Util::STG;
using namespace Locator;

const double MLLocator::DEFAULT_RANK = 0.1;

namespace
{
	static const double DEFAULT_SPEED = 4.0;
}


// コンストラクタ
MLLocator::MLLocator( PBMLParser bp, const Vector2DF &pos, 
	Util::Random::PRandom pRandom )
	: BulletMLRunner( bp.get() )
	, mLocator( pos )
	, mpBMLParser( bp )
	, mRank( DEFAULT_RANK )
	, mFrameCount( 0 )
	, mAngle( -90.0f )
	, mAimAngle( -90.0f )
	, mpRandom( pRandom )
	, mVanished( false )
{
}


// 状態の更新
void MLLocator::Update()
{
	BulletMLRunner::run();

	mLocator.Update();
	if( mLocator.GetSpeed().GetAbs() > 0 )
	{
		mAngle = mLocator.GetSpeed().GetAngle();
	}

	mFrameCount++;
}


// 位置の取得
Vector2DF MLLocator::GetPosition() const
{
	return mLocator.GetPosition();
}

Vector2DF &MLLocator::GetPosition()
{
	return mLocator.GetPosition();
}

// 位置の設定
void MLLocator::SetPosition( const Vector2DF &pos )
{
	mLocator.SetPosition( pos );
}

// 速度ベクトルの取得
Vector2DF MLLocator::GetSpeed() const
{
	return mLocator.GetSpeed();
}

Vector2DF &MLLocator::GetSpeed()
{
	return mLocator.GetSpeed();
}

// 速度ベクトルの設定
void MLLocator::SetSpeed( const Vector2DF &sp )
{
	mLocator.SetSpeed( sp );
}

// 加速度ベクトルの取得
Vector2DF MLLocator::GetAccel() const
{
	return mLocator.GetAccel();
}

Vector2DF &MLLocator::GetAccel()
{
	return mLocator.GetAccel();
}

// 加速度ベクトルの設定
void MLLocator::SetAccel( const Vector2DF &ac )
{
	mLocator.SetAccel( ac );
}

// 外力の適用
Vector2DF MLLocator::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


// 実行が終了しているかどうか
bool MLLocator::IsEnd() const
{
	return BulletMLRunner::isEnd() || mVanished;
}

// 狙う角度の取得
float MLLocator::GetAimAngle() const
{
	return mAimAngle;
}

// 狙う角度の設定
void MLLocator::SetAimAngle( float angle )
{
	mAimAngle = angle;
}

// ランクの取得
double MLLocator::GetRank() const
{
	return mRank;
}

// ランクの設定
void MLLocator::SetRank( double rank )
{
	assert( rank >= 0 && rank <= 1 );

	mRank = rank;
}


/// この弾の角度を求める
// 角度を度単位で、上方向 0 で時計周りで返す
double MLLocator::getBulletDirection()
{
	return mAngle + 90;
}

/// この弾から自機を狙う角度を求める
// 角度を度単位で、上方向 0 で時計周りで返す
double MLLocator::getAimDirection()
{
	return mAimAngle + 90;
}

/// この弾の速度を求める
double MLLocator::getBulletSpeed()
{
	return mLocator.GetSpeed().GetAbs();
}

/// デフォルトの速度を求める
double MLLocator::getDefaultSpeed()
{
	return DEFAULT_SPEED;
}

/// ランクを求める
// 0 から 1 までの実数
double MLLocator::getRank()
{
	return mRank;
}

/// 弾の基準となるターンの値を返す、通常はフレーム数
int MLLocator::getTurn()
{
	return mFrameCount;
}

/// 死ぬ
void MLLocator::doVanish()
{
	mVanished = true;
}

/// 弾の方向を指定した方向に変更する
void MLLocator::doChangeDirection( double dir )
{
	mAngle = static_cast<float>( dir - 90 );
	float speed = mLocator.GetSpeed().GetAbs();

	mLocator.GetSpeed().SetUnitVector( mAngle ) *= speed;
}

/// 弾の速度を指定した値に変更する
void MLLocator::doChangeSpeed( double speed )
{
	mLocator.GetSpeed().SetUnitVector( mAngle ) *= 
		static_cast<float>( speed );
}

/// accel に対するインターフェイス
void MLLocator::doAccelX( double accelX )
{
	mLocator.GetAccel().x = static_cast<float>( accelX );
}

void MLLocator::doAccelY( double accelY )
{
	mLocator.GetAccel().y = static_cast<float>( accelY );
}

/// 弾の速さの X 方向成分を返します
double MLLocator::getBulletSpeedX()
{
	return mLocator.GetSpeed().x;
}

/// 弾の速さの Y 方向成分を返します
double MLLocator::getBulletSpeedY()
{
	return mLocator.GetSpeed().y;
}

/// 乱数を返す
double MLLocator::getRand()
{
	return mpRandom->GetFloat( 0, 1 );
}