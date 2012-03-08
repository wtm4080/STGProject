#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "IItem.h"
#include "Mdl/STG/Actor/Base.h"
#include "Util/STG/Hit/Circle.h"
#include "Util/STG/Locator/Trace.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
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
		, public IItem
	{
	public:
		// 位置の取得
		virtual Util::STG::Vector2DF GetPosition() const;
		// 外力の適用
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );
		// 自機ヘの当たり判定の半径の取得
		virtual float GetHitRadius() const;
		// 当たり判定
		virtual bool IsHit( const Util::STG::Hit::CircleI &hit ) const;

	protected:
		// コンストラクタ
		Base( Actor::Base::PMode pMode, 
			const Util::STG::Vector2DF &pos, float angle = 270.0f );

		// 共通リソースの取得
		typedef Util::Ptr<Mdl::STG::Resource::Common>::Shared PCommonResource;
		PCommonResource GetCommonResource() const;

		// 位置の設定
		void SetPosition( const Util::STG::Vector2DF &pos );
		// 自機ヘの当たり判定の半径の設定
		void SetHitRadius( int radius );
		// 速度ベクトルの方向の設定
		void SetAngle( float angle );

	private:
		Util::STG::Hit::CircleI mHitCircle;
		Util::STG::Locator::TraceF mLocator;

		// 更新
		virtual void UpdateMiddle();

		virtual void Effect() const = 0;
	};
}
}
}
}