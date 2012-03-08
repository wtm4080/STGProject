#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "../Base.h"
#include "Resource.h"
#include "Util/Sprite/DrawParameter.h"
#include "Option.h"
#include <vector>
#include "Util/RepeatCounter.h"
#include "Mdl/STG/Auxs.h"


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
	class Core
		: public Base
	{
	public:
		Core( const Parameter &param );

		// 情報領域の描画
		virtual void DrawInfArea( const Util::STG::Vector2DF &basePos ) const;

		// 武器パワーの取得
		virtual int GetPower() const;
		// 武器パワーの上昇
		virtual bool SupplyPower();
		// 特殊攻撃カウントの取得
		virtual int GetSpAttack() const;
		// 特殊攻撃の補給
		virtual bool SupplySpAttack();

	private:
		Resource mResource;
		Util::Sprite::DrawParameter mShipDParam;
		Util::Sprite::DrawParameter mHitMarkDParam;
		Util::Sprite::DrawParameter mBarrierDParam;

		unsigned mWeaponPowerCount;
		unsigned mSpAttackCount;

		std::vector<Option> mOptions;

		Util::RepeatCounter mLaserInterval;
		Util::RepeatCounter mMissileInterval;

		bool mSlow;

		Auxs mAuxs;

		// 更新時の処理
		virtual void OnUpdate();
		// 描画時の処理
		virtual void OnDraw() const;
		// 自機破壊時の処理
		virtual void OnDestruction();
		// 自機復活時の処理
		virtual void OnRevival();
		// コンティニュー時の処理
		virtual void OnContinue();

		// 自機サイズの取得
		virtual Util::STG::Vector2DI GetShipSize() const;

		// バリア半径の取得
		virtual int GetBarrierRadius() const;
		// アイテム吸い寄せ半径の取得
		virtual int GetItemRetrieveRadius() const;

		// 移動速度の取得
		virtual float GetMoveSpeed() const;

		// ショット発射処理
		virtual void Shot();
		// 特殊攻撃発動処理
		virtual void SpecialAttack();

		void AddOption( unsigned num, float rotAngle = 0 );
	};
}
}
}
}
}