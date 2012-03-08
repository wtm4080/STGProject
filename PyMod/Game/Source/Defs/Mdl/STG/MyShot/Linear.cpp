#include "PCH.h"
#include "Linear.h"

#include "Defs/Ctrl/STG/STG.h"
#include "Defs/Mdl/STG/Actor/Animation.h"
#include "Defs/Util/Sprite/Sprite.h"


namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace MyShot
{
	Linear::Linear( const Locator &locator, int hitRadius, 
		const DrawParameter &drawParam, 
		float baseDamage, 
		const boost::optional<Animation> &vanishAnimation )
		: Base( locator.GetPosition(), hitRadius, baseDamage )
		, mAuxs()
		, mLocator( locator )
		, mSpeed( locator.GetSpeed().GetAbs() )
		, mDrawParam( drawParam )
		, mRotDegreeCorrection( 0 )
		, mVanishAnimation( vanishAnimation )
		, mDestructionCallback()
		, mDamageToBullet()
		, mDamageKickbackRateToBullet()
		, mDamageToBulletCallback()
	{
	}

	Linear::Vector2DF Linear::GetPosition() const
	{
		return mLocator.GetPosition();
	}
	Linear::Vector2DF Linear::ApplyExternalForce( const Vector2DF &v )
	{
		return mLocator.ApplyExternalForce( v );
	}

	Linear::Locator &Linear::GetLocator()
	{
		return mLocator;
	}

	const Linear::DrawParameter &Linear::GetDrawParameter() const
	{
		return mDrawParam;
	}
	void Linear::SetDrawParameter( const DrawParameter &drawParam )
	{
		mDrawParam = drawParam;
	}

	float Linear::GetRotDegreeCorrection() const
	{
		return mRotDegreeCorrection;
	}
	void Linear::SetRotDegreeCorrection( float degree )
	{
		mRotDegreeCorrection = degree;
	}

	void Linear::SetDestructionCallback( const boost::python::object &callback )
	{
		mDestructionCallback = callback;
	}

	float Linear::GetDamageToBullet() const
	{
		if( mDamageToBullet )
		{
			return mDamageToBullet.get();
		}
		else
		{
			return 0;
		}
	}
	void Linear::SetDamageToBullet( float damage )
	{
		mDamageToBullet = damage;
	}
	float Linear::GetDamageKickbackRateToBullet() const
	{
		if( mDamageKickbackRateToBullet )
		{
			return mDamageKickbackRateToBullet.get();
		}
		else
		{
			return 1.0f;
		}
	}
	void Linear::SetDamageKickbackRateToBullet( float rate )
	{
		mDamageKickbackRateToBullet = rate;
	}
	void Linear::SetDamageToBulletCallback( const boost::python::object &callback )
	{
		mDamageToBulletCallback = callback;
	}

	void Linear::OnUpdate()
	{
		mLocator.Update();
		if( mLocator.GetSpeed().GetAbs() < mSpeed )
		{
			mLocator.GetSpeed().Normalize();
			mLocator.GetSpeed() *= mSpeed;
		}

		auto dst = mDrawParam.GetDst();
		mDrawParam.SetDst( 
			mLocator.GetPosition().MakeRect( dst.w, dst.h ) );

		if( mLocator.GetSpeed().GetAbs() != 0 )
		{
			mDrawParam.SetRotDegree( 
				mLocator.GetSpeed().GetAngle() + mRotDegreeCorrection );
		}

		if( mDamageToBullet )
		{
			float kickbackRate = 1.0f;
			if( mDamageKickbackRateToBullet )
			{
				kickbackRate = mDamageKickbackRateToBullet.get();
			}

			float damageSum = mAuxs.ApplyDamageToBullets( 
				GetHitRect(), mDamageToBullet.get() );

			if( damageSum != 0 )
			{
				SetHP( GetHP() - damageSum * kickbackRate );

				if( mDamageToBulletCallback )
				{
					mDamageToBulletCallback( mLocator );
				}
			}
		}
	}
	void Linear::OnDraw() const
	{
		Util::Sprite::Sprite::draw( mDrawParam );
	}

	void Linear::OnErase()
	{
		if( mVanishAnimation )
		{
			CreateVanishAnimation();
		}
		else
		{
			mAuxs.CreateFadeOut( mDrawParam );
		}
	}
	void Linear::OnDestruct()
	{
		if( mVanishAnimation )
		{
			CreateVanishAnimation();
		}
		else
		{
			mAuxs.CreateParticle( mDrawParam );
		}

		if( mDestructionCallback )
		{
			mDestructionCallback();
		}
	}
	void Linear::OnDestruct( float damage )
	{
		mAuxs.CreateFadeOut( mDrawParam );
	}

	void Linear::CreateVanishAnimation() const
	{
		auto animation = mVanishAnimation.get();

		auto drawParam = animation.GetFrameHolder()->GetDrawParameter();
		auto dst = drawParam.GetDst();
		dst = mLocator.GetPosition().MakeRect( dst.w, dst.h );
		drawParam.SetDst( dst );
		drawParam.SetRotDegree( mDrawParam.GetRotDegree() );
		animation.GetFrameHolder()->SetDrawParameter( drawParam );

		Actor::PAnimation pAnimeObj( 
			new Actor::Animation( 
			Game::Util::STG::Hit::RectI( dst ), animation ) );
		Ctrl::STG::STG::getActors()->RegisterActor( pAnimeObj );
	}
}
}
}
}