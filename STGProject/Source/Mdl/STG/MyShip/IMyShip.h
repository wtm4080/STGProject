#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/STG/Vector2D.h"


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
	class IMyShip
	{
	public:
		// フレーム毎の更新
		virtual void Update() = 0;
		// フレーム毎の描画
		virtual void Draw() const = 0;
		// 情報領域の描画
		virtual void DrawInfArea( const Util::STG::Vector2DF &basePos ) const = 0;

		// 敵弾当たり判定
		virtual bool IsHit( const Util::STG::Hit::CircleI &bulletHit ) const = 0;
		// アイテム吸い寄せ当たり判定
		virtual bool IsHit_ItemRetrieve( const Util::STG::Hit::CircleI &itemhit ) const = 0;
		// アイテム取得当たり判定
		virtual bool IsHit_GetItem( const Util::STG::Hit::CircleI &itemHit ) const = 0;
		// 自機の破壊
		virtual void Destruct() = 0;

		// 武器パワーの取得
		virtual int GetPower() const = 0;
		// 武器パワーの上昇
		virtual bool SupplyPower() = 0;
		// 特殊攻撃カウントの取得
		virtual int GetSpAttack() const = 0;
		// 特殊攻撃の補給
		virtual bool SupplySpAttack() = 0;

		// 無敵状態判定
		virtual bool IsBarriered() const = 0;
		// 無敵状態フレームカウントの取得
		virtual unsigned GetBarrierCount() const = 0;
		// 無敵状態の設定
		virtual void SetBarrier( unsigned frameNum ) = 0;
		// 破壊後の消失状態判定
		virtual bool IsDisappeared() const = 0;

		// 現在位置の取得
		virtual Util::STG::Vector2DF GetPosition() const = 0;
		// 現在位置の設定
		virtual void SetPosition( const Util::STG::Vector2DF &position ) = 0;
		// 外力の適用
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec ) = 0;

		// 残機の取得
		virtual unsigned GetRemainder() const = 0;
		// 残機の追加
		virtual void AddRemainder( unsigned num ) = 0;
		// 初期残機数の設定
		virtual void SetInitRemainder( unsigned num ) = 0;

		// コンティニュー時の処理
		virtual void Continue() = 0;

		// 移動禁止設定
		virtual void SetMoveForbidFlag( bool flag ) = 0;
		// ショット禁止設定
		virtual void SetShotForbidFlag( bool flag ) = 0;
		// 特殊攻撃禁止設定
		virtual void SetSpecialAttackForbidFlag( bool flag ) = 0;

		virtual ~IMyShip() {}
	};
}
}
}
}