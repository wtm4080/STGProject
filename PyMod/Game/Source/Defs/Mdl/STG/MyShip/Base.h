#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/MyShip/IMyShip.h"
#include "Util/STG/Locator/Linear.h"
#include "Util/STG/Hit/Circle.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace MyShip
{
	class Base
		: public Game::Mdl::STG::MyShip::IMyShip
	{
	public:
		// フレーム毎の更新
		virtual void Update();
		// フレーム毎の描画
		virtual void Draw() const;

		// 敵弾当たり判定
		virtual bool IsHit( const Game::Util::STG::Hit::CircleI &bulletHit ) const;
		// アイテム吸い寄せ当たり判定
		virtual bool IsHit_ItemRetrieve( 
			const Game::Util::STG::Hit::CircleI &itemHit ) const;
		// アイテム取得当たり判定
		virtual bool IsHit_GetItem( 
			const Game::Util::STG::Hit::CircleI &itemHit ) const;
		// 自機の破壊
		virtual void Destruct();

		// 無敵状態判定
		virtual bool IsBarriered() const;
		// 無敵状態フレームカウントの取得
		virtual unsigned GetBarrierCount() const;
		// 無敵状態の設定
		virtual void SetBarrier( unsigned frameNum );
		// 破壊後の消失状態判定
		virtual bool IsDisappeared() const;

		// 現在位置の取得
		virtual Game::Util::STG::Vector2DF GetPosition() const;
		// 現在位置の設定
		virtual void SetPosition( const Game::Util::STG::Vector2DF &position );
		// 外力の適用
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( 
			const Game::Util::STG::Vector2DF &vec );

		// 残機の取得
		virtual unsigned GetRemainder() const;
		// 残機の追加
		virtual void AddRemainder( unsigned num );
		// 初期残機数の設定
		virtual void SetInitRemainder( unsigned num );

		// コンティニュー時の処理
		virtual void Continue();

		// 移動禁止設定
		virtual void SetMoveForbidFlag( bool flag );
		// ショット禁止設定
		virtual void SetShotForbidFlag( bool flag );
		// 特殊攻撃禁止設定
		virtual void SetSpecialAttackForbidFlag( bool flag );

	protected:
		Base();

	private:
		Game::Util::STG::Locator::LinearF mLocator;

		Game::Util::STG::Hit::CircleI 
			mHitCircle, mItemRetrieveHitCircle, mItemHitCircle;

		unsigned mInitRemainder;
		unsigned mRemainder;

		unsigned mBarrierCount;
		unsigned mDisappearCount;

		bool mMoveForbidFlag;
		bool mShotForbidFlag;
		bool mSpecialAttackForbidFlag;

		// 更新時の処理
		virtual void OnUpdate() = 0;
		// 描画時の処理
		virtual void OnDraw() const = 0;
		// 自機破壊時の処理
		virtual void OnDestruction() = 0;
		// 自機復活時の処理
		virtual void OnRevival() = 0;
		// コンティニュー時の処理
		virtual void OnContinue() = 0;

		// 自機サイズの取得
		virtual Game::Util::STG::Vector2DI GetShipSize() const = 0;

		// 移動速度の取得
		virtual float GetMoveSpeed() const = 0;

		// バリア半径の取得
		virtual int GetBarrierRadius() const = 0;
		// アイテム吸い寄せ半径の取得
		virtual int GetItemRetrieveRadius() const = 0;

		// ショット発射処理
		virtual void Shot() = 0;
		// 特殊攻撃発動処理
		virtual void SpecialAttack() = 0;

		void Input();
	};
}
}
}
}