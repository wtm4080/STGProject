#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "IBullet.h"
#include "Mdl/STG/Actor/Base.h"
#include "Util/Sprite/DrawParameter.h"
#include "Util/STG/Hit/Circle.h"
#include "Util/STG/Hit/Rect.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Bullet
{
#pragma warning( disable:4250 )
	class Base
		: public Actor::Base
		, public IBullet
	{
	public:
		// 当たり判定
		virtual bool IsHit( const Util::STG::Hit::CircleI &hit ) const;
		virtual bool IsHit( const Util::STG::Hit::RectI &hit ) const;
		// 破壊
		virtual void Destruct();
		virtual void Destruct( float hp );

		// HPの取得
		virtual float GetHP() const;
		// 当たり判定の半径の取得
		virtual float GetHitRadius() const;

	protected:
		// コンストラクタ
		Base( Actor::Base::PMode pMode, 
			const Util::STG::Vector2DF &pos, int radius );

		// HPの設定
		void SetHP( float hp );
		// 当たり判定の半径の設定
		void SetHitRadius( int radius );

		// 当たり判定の位置の更新
		void UpdateHitPos();

	private:
		Util::STG::Hit::CircleI mHitCircle;
		Util::STG::Hit::RectI mHitRect;
		float mHP;
		Util::Sprite::DrawParameter mDamagedDrawParam;

		// 更新
	public:
		virtual void Update();
	private:
		virtual void UpdateMiddle();
		virtual void UpdateDamagedDraw();
		virtual void DrawMiddle() const;

		virtual void OnDestruct() = 0;
		virtual void OnDamaged( float damage ) {}
		virtual void OnDestruct( float hp ) = 0;
	};
}
}
}
}