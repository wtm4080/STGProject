#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"
#include "Mdl/STG/Auxs.h"
#include "Util/STG/Locator/Linear.h"
#include "Util/Sprite/Animation.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Actor
{
	class Animation
		: public Base
	{
	public:
		// コンストラクタ
		Animation( PMode pMode, const Util::STG::Hit::RectI &validRect, 
			const Util::Sprite::Animation &animation );

		// 位置の取得
		virtual Util::STG::Vector2DF GetPosition() const;
		// 外力の適用
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

		// アニメーション設定の取得
		Util::Sprite::Animation &GetAnimation();

	private:
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::Animation mAnimation;
		Auxs mAuxs;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();
	};
}
}
}
}