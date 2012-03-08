#include "PCH.h"
#include "Base.h"

#include "Defs/Ctrl/STG/STG.h"

using namespace Defs::Mdl::STG::MyShip;
using namespace Game::Util::STG;
using namespace Game::Util::Consts;

namespace
{
	// 初期残機数
	static const unsigned INIT_REMAINDER_NUM = 3;
	// 初期位置
	static const Vector2DF INIT_POS( 
		( SCREEN_SIZE.x - STG_INFAREA_SIZE.x ) / 2.0f, 
		SCREEN_SIZE.y * 0.8f );

	// 自機破壊時の自機消失フレーム数
	static const unsigned DISAPPEAR_FRAME_NUM = 60;
	// 自機復帰時の無敵フレーム数
	static const unsigned BARRIER_FRAME_NUM = 90;

	// 敵弾当たり判定半径
	static const int HIT_RADIUS = 1;
	// アイテム吸い寄せ当たり判定半径
	static const int HIT_RADIUS_ITEM_RETRIEVE = 64;
	// アイテム当たり判定半径
	static const int HIT_RADIUS_ITEM = 16;

	typedef Defs::Ctrl::STG::STG STGControl;
}


Base::Base()
: mLocator()
, mHitCircle( INIT_POS, HIT_RADIUS )
, mItemRetrieveHitCircle( INIT_POS, HIT_RADIUS_ITEM_RETRIEVE )
, mItemHitCircle( INIT_POS, HIT_RADIUS_ITEM )
, mInitRemainder( INIT_REMAINDER_NUM )
, mRemainder( INIT_REMAINDER_NUM )
, mBarrierCount( 0 )
, mDisappearCount( 0 )
, mMoveForbidFlag( false )
, mShotForbidFlag( false )
, mSpecialAttackForbidFlag( false )
{
	mLocator.GetPosition() = INIT_POS;
}


// フレーム毎の更新
void Base::Update()
{
	if( !IsDisappeared() )
	{
		auto pBullets = STGControl::getActors()->DetectBulletHitAll( mHitCircle );
		if( !pBullets->empty() )
		{
			foreach( Game::Mdl::STG::Bullet::PBullet pBullet, *pBullets )
			{
				pBullet->Destruct();
			}

			Destruct();
		}
	}

	if( IsDisappeared() )
	{
		mDisappearCount--;

		if( !IsDisappeared() )
		{
			if( GetRemainder() > 0 )
			{
				mLocator.GetPosition() = INIT_POS;

				OnRevival();
			}
			else
			{
				mDisappearCount++;
			}
		}
	}
	else if( IsBarriered() )
	{
		mBarrierCount--;
	}

	Input();

	mHitCircle.SetCenter( mLocator.GetPosition() );
	mItemRetrieveHitCircle.SetCenter( mLocator.GetPosition() );
	mItemHitCircle.SetCenter( mLocator.GetPosition() );
	if( IsBarriered() )
	{
		mHitCircle.SetRadius( GetBarrierRadius() );
	}
	else
	{
		mHitCircle.SetRadius( HIT_RADIUS );
	}
	mItemRetrieveHitCircle.SetRadius( GetItemRetrieveRadius() );

	OnUpdate();
}

void Base::Input()
{
	if( !IsDisappeared() )
	{
		auto controller = STGControl::getController();

		if( !mMoveForbidFlag )
		{
			mLocator.GetSpeed() = 
				controller.GetDirection() * GetMoveSpeed();

			mLocator.Update();

			Vector2DF 
				&pos = mLocator.GetPosition(), 
				size = GetShipSize();
			int rightBorder = 
				SCREEN_SIZE.x - STG_INFAREA_SIZE.x;
			int bottomBorder = SCREEN_SIZE.y;
			if( pos.x - size.x/2 < 0 )
			{
				pos.x = size.x/2;
			}
			else if( pos.x + size.x/2 > rightBorder )
			{
				pos.x = rightBorder - size.x/2;
			}
			if( pos.y - size.y/2 < 0 )
			{
				pos.y = size.y/2;
			}
			else if( pos.y + size.y/2 > bottomBorder )
			{
				pos.y = bottomBorder - size.y/2;
			}
		}

		if( !mShotForbidFlag && 
			controller.IsHold( Game::Util::Input::STG::KEY_Z ) )
		{
			Shot();
		}

		if( !mSpecialAttackForbidFlag && 
			controller.IsPush( Game::Util::Input::STG::KEY_X ) )
		{
			SpecialAttack();
		}
	}
}

// フレーム毎の描画
void Base::Draw() const
{
	if( !IsDisappeared() )
	{
		OnDraw();
	}
}


// 敵弾当たり判定
bool Base::IsHit( const Hit::CircleI &bulletHit ) const
{
	if( !IsDisappeared() )
	{
		return mHitCircle.IsHit( bulletHit );
	}

	return false;
}

// アイテム吸い寄せ当たり判定
bool Base::IsHit_ItemRetrieve( const Hit::CircleI &itemHit ) const
{
	if( !IsDisappeared() )
	{
		return mItemRetrieveHitCircle.IsHit( itemHit );
	}

	return false;
}

// アイテム取得当たり判定
bool Base::IsHit_GetItem( const Hit::CircleI &itemHit ) const
{
	if( !IsDisappeared() )
	{
		return mItemHitCircle.IsHit( itemHit );
	}

	return false;
}

// 自機の破壊
void Base::Destruct()
{
	if( !IsDisappeared() && !IsBarriered() )
	{
		mRemainder--;

		mDisappearCount = DISAPPEAR_FRAME_NUM;
		mBarrierCount = BARRIER_FRAME_NUM;

		OnDestruction();
	}
}


// 無敵状態判定
bool Base::IsBarriered() const
{
	return mBarrierCount > 0;
}

// 無敵状態フレームカウントの取得
unsigned Base::GetBarrierCount() const
{
	return mBarrierCount;
}

// 破壊後の消失状態判定
bool Base::IsDisappeared() const
{
	return mDisappearCount > 0;
}


// 現在位置の取得
Vector2DF Base::GetPosition() const
{
	return mLocator.GetPosition();
}

// 現在位置の設定
void Base::SetPosition( const Vector2DF &position )
{
	mLocator.SetPosition( position );
}

// 外力の適用
Vector2DF Base::ApplyExternalForce( const Vector2DF &vec )
{
	if( !IsDisappeared() )
	{
		return mLocator.ApplyExternalForce( vec );
	}

	return Vector2DF();
}


// 残機の取得
unsigned Base::GetRemainder() const
{
	return mRemainder;
}

// 残機の追加
void Base::AddRemainder( unsigned num )
{
	mRemainder += num;
}


// コンティニュー時の処理
void Base::Continue()
{
	mRemainder = mInitRemainder;

	OnContinue();
}


// 移動禁止設定
void Base::SetMoveForbidFlag( bool flag )
{
	mMoveForbidFlag = flag;
}

// ショット禁止設定
void Base::SetShotForbidFlag( bool flag )
{
	mShotForbidFlag = flag;
}

// 特殊攻撃禁止設定
void Base::SetSpecialAttackForbidFlag( bool flag )
{
	mSpecialAttackForbidFlag = flag;
}


// 初期残機数の設定
void Base::SetInitRemainder( unsigned num )
{
	assert( num > 0 );

	mInitRemainder = num;
	mRemainder = num;
}

// 無敵状態の設定
void Base::SetBarrier( unsigned frameNum )
{
	mBarrierCount = frameNum;
}