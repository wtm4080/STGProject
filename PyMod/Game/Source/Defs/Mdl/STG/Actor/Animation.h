#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"
#include "Defs/Mdl/STG/Auxs.h"
#include "Util/STG/Locator/Linear.h"
#include "Defs/Util/Sprite/Animation/Manager.h"
#include "ActorDefs.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
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
		Animation( const Game::Util::STG::Hit::RectI &validRect, 
			const Util::Sprite::Animation::Manager &animationManager );

		// 位置の取得
		virtual Game::Util::STG::Vector2DF GetPosition() const;
		// 外力の適用
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( 
			const Game::Util::STG::Vector2DF &vec );

		// アニメーション設定の取得
		Util::Sprite::Animation::Manager &GetAnimationManager();
		// ロケータの取得
		Game::Util::STG::Locator::LinearF &GetLocator();

	private:
		Game::Util::STG::Locator::LinearF mLocator;
		Util::Sprite::Animation::Manager mAnimationManager;
		Auxs mAuxs;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();

		friend ActorDefs;
	};
}
}
}
}