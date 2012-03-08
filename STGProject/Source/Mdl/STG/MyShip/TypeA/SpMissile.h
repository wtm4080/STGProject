#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Mdl/STG/MyShot/Base.h"
#include "Util/STG/Locator/Linear.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace MyShip
{
namespace TypeA
{
	typedef Util::Ptr<class SpMissile>::Shared PSpMissile;

	class SpMissile
		: public MyShot::Base
	{
	public:
		// コンストラクタ
		SpMissile( Actor::Base::PMode pMode, 
			const Util::STG::Vector2DF &pos, 
			float angle, 
			Util::Sprite::PTexture pMissileTexture, 
			Util::Sprite::PTexture pExplosionTexture );

		// 位置の取得
		virtual Util::STG::Vector2DF GetPosition() const;
		// 外力の適用
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

	private:
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		Util::Sprite::Animation mExplodeAnimation;

		bool mExplodeFlag;
		unsigned mExplodeFrameCount;

		bool mInValidArea;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnDestruct();
		virtual void OnDestruct( float hp );
		virtual void OnErase();
	};
}
}
}
}
}