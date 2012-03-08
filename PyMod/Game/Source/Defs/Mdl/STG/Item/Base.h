#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Item/IItem.h"
#include "Defs/Mdl/STG/Actor/Base.h"
#include "Util/STG/Hit/Circle.h"
#include "Util/STG/Locator/Trace.h"
#include "Defs/Mdl/STG/Auxs.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Item
{
#pragma warning( disable:4250 )
	class Base
		: public Actor::Base
		, public Game::Mdl::STG::Item::IItem
	{
	public:
		// 位置の取得
		virtual Game::Util::STG::Vector2DF GetPosition() const;
		// 外力の適用
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( 
			const Game::Util::STG::Vector2DF &vec );
		// 自機ヘの当たり判定の半径の取得
		virtual float GetHitRadius() const;
		// 当たり判定
		virtual bool IsHit( const Game::Util::STG::Hit::CircleI &hit ) const;

	protected:
		Auxs mAuxs;

		// コンストラクタ
		Base( const Game::Util::STG::Vector2DF &pos, float angle = -90.0f );

		// 位置の設定
		void SetPosition( const Game::Util::STG::Vector2DF &pos );
		// 自機ヘの当たり判定の半径の設定
		void SetHitRadius( int radius );
		// 速度ベクトルの方向の設定
		void SetAngle( float angle );

	private:
		Game::Util::STG::Hit::CircleI mHitCircle;
		Game::Util::STG::Locator::TraceF mLocator;

		// 更新
		virtual void UpdateMiddle();

		virtual void Effect() const = 0;
	};
}
}
}
}