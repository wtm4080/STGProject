#include "PCH.h"
#include "Core.h"
#include "Laser.h"

#include "Ctrl/STG/Actors.h"
#include "Mdl/STG/Item/PowerUp.h"
#include "Mdl/STG/MyShip/Parameter.h"
#include "Mdl/STG/Resource/Common.h"
#include "Util/Input/STG/IController.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace MyShip::TypeA;
using namespace Util::STG;
using namespace boost;
using namespace Selene;
using namespace std;

namespace
{
	static const Vector2DF SHIP_SIZE( 64.0f, 64.0f );
	static const Vector2DF BARRIER_SIZE( 86.0f, 86.0f );
	static const numeric::interval<unsigned> WEAPON_POWER_DOMAIN( 0, 4 );
	static const unsigned INIT_SPATTACK_COUNT = 2;
	static const Vector2DF HIT_MARK_SIZE( 12.0f, 12.0f );
	static const Vector2DF EXPLOSION_SIZE( 96*3, 96*3 );
}


Core::Core( const Mdl::STG::MyShip::Parameter &param )
: Base( param )
, mWeaponPowerCount( 0 )
, mSpAttackCount( INIT_SPATTACK_COUNT )
, mLaserInterval( 5.5f )
, mMissileInterval( 12.0f )
, mSlow( false )
, mAuxs( param.GetMode() )
{
	mShipDParam.SetTexture( mResource.GetMyShip() );
	mShipDParam.SetSrc( Resource::MY_SHIP.GetRect() );
	mShipDParam.SetDst( Base::GetPosition().MakeRect( SHIP_SIZE ) );
	mShipDParam.SetPriority( View::STG::PRI_MYSHIP );

	mHitMarkDParam.SetTexture( mResource.GetHitMark() );
	mHitMarkDParam.SetSrc( Resource::HIT_MARK.GetRect() );
	mHitMarkDParam.SetDst( Base::GetPosition().MakeRect( HIT_MARK_SIZE ) );
	mHitMarkDParam.SetPriority( View::STG::PRI_MYSHIP_HITMARK );
	mHitMarkDParam.SetAlphaBlend( Util::Sprite::AB_ADD );

	mBarrierDParam.SetTexture( mResource.GetBlueCircle() );
	mBarrierDParam.SetSrc( Resource::BLUE_CIRCLE.GetRect() );
	mBarrierDParam.SetDst( Base::GetPosition().MakeRect( BARRIER_SIZE ) );
	mBarrierDParam.SetPriority( View::STG::PRI_MYBARRIER );
	mBarrierDParam.SetColor( ColorF( 1.0f, 1.0f, 1.0f, 160.0f/255 ) );
	mBarrierDParam.SetAlphaBlend( Util::Sprite::AB_ADD );

	AddOption( 2 );
}


// 情報領域の描画
void Core::DrawInfArea( const Vector2DF &basePos ) const
{
	Util::Font::PFont pFont = 
		Base::GetCommonResource()->GetFont32( View::STG::PRI_INFAREA_STR, false, 24 );
	RectF rect( basePos.x, basePos.y, 
		static_cast<float>( Util::Consts::STG_INFAREA_SIZE.x ), 32.0f );
	Point2DF offset;
	ColorF color;

	pFont->DrawLeft( rect, offset, color, L"Player:" );

	rect.y += 32.0f;
	if( Base::GetRemainder() > 0 )
	{
		wstring str;

		for( unsigned i = 0; i < Base::GetRemainder() - 1; i++ )
		{
			str += L"*";
		}

		pFont->DrawLeft( rect, offset, color, str );
	}

	rect.y += 32.0f;
	pFont->DrawLeft( rect, offset, color, L"Power:" );

	rect.y += 32.0f;
	{
		wstring str;

		for( unsigned i = 0; i < mWeaponPowerCount; i++ )
		{
			str += L"*";
		}

		pFont->DrawLeft( rect, offset, color, str );
	}

	rect.y += 32.0f;
	pFont->DrawLeft( rect, offset, color, L"SpAttack:" );

	rect.y += 32.0f;
	{
		wstring str;

		for( unsigned i = 0; i < mSpAttackCount; i++ )
		{
			str += L"*";
		}

		pFont->DrawLeft( rect, offset, color, str );
	}
}


// 更新時の処理
void Core::OnUpdate()
{
	mSlow = Base::GetController()->IsHold( Util::Input::STG::KEY_LSHIFT );

	mShipDParam.SetDst( Base::GetPosition().MakeRect( SHIP_SIZE ) );
	mHitMarkDParam.SetDst( Base::GetPosition().MakeRect( HIT_MARK_SIZE ) );
	{
		mBarrierDParam.SetDst( Base::GetPosition().MakeRect( BARRIER_SIZE ) );

		if( Base::GetBarrierCount() > 16 )
		{
			mBarrierDParam.SetColor( ColorF( 1.0f, 1.0f, 1.0f, 160.0f/255 ) );
		}
		else
		{
			mBarrierDParam.SetColor( ColorF( 1.0f, 1.0f, 1.0f, 
				Base::GetBarrierCount()*10.0f / 255 ) );
		}
	}

	mLaserInterval.UpdateState();
	mMissileInterval.UpdateState();

	for( unsigned i = 0; i < mOptions.size(); i++ )
	{
		float xOffset;
		if( mSlow )
		{
			if( i % 2 == 0 )
			{
				xOffset = SHIP_SIZE.x/2 + Option::GetDrawSize().x/2 + 
					Option::GetDrawSize().x * ( i/2 );
			}
			else
			{
				xOffset = SHIP_SIZE.x/2 + Option::GetDrawSize().x/2 + 
					Option::GetDrawSize().x * ( ( i - 1 )/2 );
				xOffset *= -1.0f;
			}
		}
		else
		{
			xOffset = Option::GetDrawSize().x * 2;

			if( i % 2 == 0 )
			{
				xOffset += Option::GetDrawSize().x*2 * ( i/2 );
			}
			else
			{
				xOffset += Option::GetDrawSize().x*2 * ( ( i - 1 )/2 );
				xOffset *= -1.0f;
			}
		}

		mOptions.at( i ).SetTargetPosition( 
			Vector2DF( 
			Base::GetPosition().x + xOffset, 
			Base::GetPosition().y ) );

		mOptions.at( i ).Update();
	}
}

// 描画時の処理
void Core::OnDraw() const
{
	Util::Sprite::Manager::Draw( mShipDParam );
	
	{
		using namespace Util::Input::STG;

		if( mSlow )
		{
			Util::Sprite::Manager::Draw( mHitMarkDParam );
		}
	}

	foreach( const Option &option, mOptions )
	{
		option.Draw();
	}

	if( Base::IsBarriered() )
	{
		for( int i = 0; i < 2; i++ )
		{
			Util::Sprite::Manager::Draw( mBarrierDParam );
		}
	}
}


// 武器パワーの取得
int Core::GetPower() const
{
	return mWeaponPowerCount;
}

// 武器パワーの上昇
bool Core::SupplyPower()
{
	if( !IsDisappeared() )
	{
		if( mWeaponPowerCount < WEAPON_POWER_DOMAIN.upper() )
		{
			mWeaponPowerCount++;

			assert( numeric::in( mWeaponPowerCount, WEAPON_POWER_DOMAIN ) );

			switch( mWeaponPowerCount )
			{
			case 0:
				mOptions.clear();
				AddOption( 2 );
				mLaserInterval.SetInterval( 5.5f );
				mMissileInterval.SetInterval( 12.0f );
				break;
			case 1:
				assert( mOptions.size() == 2 );
				AddOption( 2, mOptions.front().GetRotateAngle() );
				mLaserInterval.SetInterval( 5.5f );
				mMissileInterval.SetInterval( 12.0f );
				break;
			case 2:
				mLaserInterval.SetInterval( 5.0f );
				mMissileInterval.SetInterval( 11.0f );
				break;
			case 3:
				mLaserInterval.SetInterval( 4.5f );
				mMissileInterval.SetInterval( 10.0f );
				break;
			case 4:
				mLaserInterval.SetInterval( 4.0f );
				mMissileInterval.SetInterval( 9.0f );
				break;
			default:
				assert( false );
				break;
			}

			return true;
		}
	}

	return false;
}

// 特殊攻撃カウントの取得
int Core::GetSpAttack() const
{
	return mSpAttackCount;
}

// 特殊攻撃の補給
bool Core::SupplySpAttack()
{
	mSpAttackCount++;

	return true;
}


// 移動速度の取得
float Core::GetMoveSpeed() const
{
	if( mSlow )
	{
		return 2.5f;
	}
	else
	{
		return 6.0f;
	}
}


// バリア半径の取得
int Core::GetBarrierRadius() const
{
	return 32;
}

// アイテム吸い寄せ半径の取得
int Core::GetItemRetrieveRadius() const
{
	return 96;
}


// ショット発射処理
void Core::Shot()
{
	for( unsigned i = 0; i < mLaserInterval.GetRepeatCount(); i++ )
	{
		Vector2DF 
			leftPos = Base::GetPosition(), 
			rightPos = leftPos;
		leftPos.x -= 10;
		rightPos.x += 10;

		MyShot::PMyShot pLeftShot( 
			new Laser( Base::GetMode(), leftPos, 
			mResource.GetLaser(), mResource.GetBlueCircle() ) );
		MyShot::PMyShot pRightShot( 
			new Laser( Base::GetMode(), rightPos, 
			mResource.GetLaser(), mResource.GetBlueCircle() ) );

		Base::GetActors().GetMyShots().push_back( pLeftShot );
		Base::GetActors().GetMyShots().push_back( pRightShot );
	}

	{
		float circlingAngle = mSlow ? 2.0f : 0.6f;

		for( unsigned i = 0; i < mMissileInterval.GetRepeatCount(); i++ )
		{
			foreach( const Option &option, mOptions )
			{
				option.LaunchMissile( circlingAngle );
			}
		}
	}
}

// 特殊攻撃発動処理
void Core::SpecialAttack()
{
	bool launchOk = true;
	foreach( Option &option, mOptions )
	{
		if( option.IsExistSpMissile() )
		{
			launchOk = false;
			break;
		}
	}

	if( mSpAttackCount > 0 && launchOk )
	{
		bool aiming = mSlow;

		foreach( Option &option, mOptions )
		{
			option.LaunchSpMissile( aiming );
		}

		Base::SetBarrier( 150 );

		mSpAttackCount--;

		Util::Sprite::Manager::SetShake( 20 );
	}
}


// 自機破壊時の処理
void Core::OnDestruction()
{
	mOptions.clear();

	mAuxs.CreateExplosion( Base::GetPosition(), EXPLOSION_SIZE );

	{
		unsigned itemNum = 0;

		switch( mWeaponPowerCount )
		{
		case 0:
		case 1:
		case 2:
			itemNum = 2;
			break;
		case 3:
		case 4:
			itemNum = mWeaponPowerCount;
			break;
		default:
			assert( false );
			break;
		}

		for( unsigned i = 0; i < itemNum; i++ )
		{
			const float angle = -180.0f/( itemNum + 1 ) * ( i + 1 );

			Item::PItem pItem( 
				new Item::PowerUp( Base::GetMode(), 
				Base::GetPosition(), angle ) );

			Base::GetActors().GetItems().push_back( pItem );
		}

		mWeaponPowerCount = 0;
	}
}

// 自機復活時の処理
void Core::OnRevival()
{
	mSpAttackCount += INIT_SPATTACK_COUNT;

	AddOption( 2 );

	mLaserInterval.SetInterval( 5.5f );
}

// コンティニュー時の処理
void Core::OnContinue()
{
	mSpAttackCount = 0;
}


// 自機サイズの取得
Vector2DI Core::GetShipSize() const
{
	return SHIP_SIZE;
}


void Core::AddOption( unsigned num, float rotAngle )
{
	assert( num % 2 == 0 );

	for( unsigned i = 0; i < num; i++ )
	{
		mOptions.push_back( 
			Option( Base::GetMode(), Base::GetPosition(), mResource.GetOption(), 
			mResource.GetMissile(), mResource.GetExplosion(), rotAngle ) );
	}
}