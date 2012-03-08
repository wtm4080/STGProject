#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"
#include "Util/STG/Locator/Linear.h"
#include "Util/STG/Locator/Rotate.h"
#include "Util/Sprite/DrawParameter.h"
#include "Defs/Util/Sprite/Sprite.h"
#include "BulletDefs.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Bullet
{
	template <class Locator>
	class Simple
		: public Base
	{
	public:
		// コンストラクタ
		typedef Game::Util::Sprite::DrawParameter DrawParameter;
		Simple( const Locator &locator, int hitRadius, 
			const DrawParameter &drawParam )
			: Base( locator.GetPosition(), hitRadius )
			, mLocator( locator )
			, mDrawParam( drawParam )
			, mPrevPos( locator.GetPosition() )
		{
		}

		// 位置の取得
		virtual Game::Util::STG::Vector2DF GetPosition() const
		{
			return mLocator.GetPosition();
		}
		// 外力の適用
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( 
			const Game::Util::STG::Vector2DF &vec )
		{
			return mLocator.ApplyExternalForce( vec );
		}

		// ロケータの取得
		Locator &GetLocator()
		{
			return mLocator;
		}
		// 描画パラメータの取得
		const DrawParameter &GetDrawParameter() const
		{
			return mDrawParam;
		}
		// 描画パラメータの設定
		void SetDrawParameter( const DrawParameter &drawParam )
		{
			mDrawParam = drawParam;
		}

	private:
		Locator mLocator;
		DrawParameter mDrawParam;
		Game::Util::STG::Vector2DF mPrevPos;

		friend BulletDefs;

	protected:
		virtual void OnUpdate()
		{
			mLocator.Update();

			auto dst = mDrawParam.GetDst();
			mDrawParam.SetDst( 
				mLocator.GetPosition().MakeRect( dst.w, dst.h ) );

			auto pos = mLocator.GetPosition();
			if( ( pos - mPrevPos ).GetAbs() != 0 )
			{
				mDrawParam.SetRotDegree( 
					mPrevPos.GetAngle( mLocator.GetPosition() ) );
			}
			mPrevPos = mLocator.GetPosition();
		}
		virtual void OnDraw() const
		{
			Defs::Util::Sprite::Sprite::draw( mDrawParam );
		}
		virtual void OnDestruct()
		{
			mAuxs.CreateParticle( mDrawParam );
		}
		virtual void OnDestruct( float hp )
		{
			mAuxs.CreateFadeOut( mDrawParam );
		}
		virtual void OnErase()
		{
			mAuxs.CreateFadeOut( mDrawParam );
		}
	};
}
}
}
}