#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
#include "Mdl/STG/MyShip/IMyShip.h"


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
	class PyMyShip
		: public Game::Mdl::STG::MyShip::IMyShip
	{
	public:
		PyMyShip( const boost::python::object &object )
			: mPyObject( object )
		{}

		typedef Game::Util::STG::Vector2DF Vector2DF;
		typedef Game::Util::STG::Hit::CircleI CircleI;

		// フレーム毎の更新
		virtual void Update()
		{
			mPyObject.attr( "update" )();
		}
		// フレーム毎の描画
		virtual void Draw() const
		{
			mPyObject.attr( "draw" )();
		}
		// 情報領域の描画
		virtual void DrawInfArea( const Vector2DF &basePos ) const
		{
			mPyObject.attr( "drawInfArea" )( basePos );
		}

		// 敵弾当たり判定
		virtual bool IsHit( const CircleI &bulletHit ) const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "isHit" )( bulletHit ) );
		}
		// アイテム吸い寄せ当たり判定
		virtual bool IsHit_ItemRetrieve( const CircleI &itemHit ) const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "isHit_ItemRetrieve" )( itemHit ) );
		}
		// アイテム取得当たり判定
		virtual bool IsHit_GetItem( const CircleI &itemHit ) const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "isHit_GetItem" )( itemHit ) );
		}
		// 自機の破壊
		virtual void Destruct()
		{
			mPyObject.attr( "destruct" )();
		}

		// 武器パワーの取得
		virtual int GetPower() const
		{
			return boost::python::extract<int>( 
				mPyObject.attr( "power" ) );
		}
		// 武器パワーの上昇
		virtual bool SupplyPower()
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "supplyPower" )() );
		}
		// 特殊攻撃カウントの取得
		virtual int GetSpAttack() const
		{
			return boost::python::extract<int>( 
				mPyObject.attr( "spAttack" ) );
		}
		// 特殊攻撃の補給
		virtual bool SupplySpAttack()
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "supplySpAttack" )() );
		}

		// 無敵状態判定
		virtual bool IsBarriered() const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "barriered" ) );
		}
		// 無敵状態フレームカウントの取得
		virtual unsigned GetBarrierCount() const
		{
			return boost::python::extract<unsigned>( 
				mPyObject.attr( "barrierCount" ) );
		}
		// 無敵状態の設定
		virtual void SetBarrier( unsigned frameNum )
		{
			mPyObject.attr( "setBarrier" )( frameNum );
		}
		// 破壊後の消失状態判定
		virtual bool IsDisappeared() const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "disappeared" ) );
		}

		// 現在位置の取得
		virtual Vector2DF GetPosition() const
		{
			return boost::python::extract<Vector2DF>( 
				mPyObject.attr( "position" ) );
		}
		// 現在位置の設定
		virtual void SetPosition( const Vector2DF &position )
		{
			mPyObject.attr( "position" ) = position;
		}
		// 外力の適用
		virtual Vector2DF ApplyExternalForce( const Vector2DF &vec )
		{
			return boost::python::extract<Vector2DF>( 
				mPyObject.attr( "applyExternalForce" )( vec ) );
		}

		// 残機の取得
		virtual unsigned GetRemainder() const
		{
			return boost::python::extract<unsigned>( 
				mPyObject.attr( "remainder" ) );
		}
		// 残機の追加
		virtual void AddRemainder( unsigned num )
		{
			mPyObject.attr( "addRemainder" )( num );
		}
		// 初期残機数の設定
		virtual void SetInitRemainder( unsigned num )
		{
			mPyObject.attr( "setInitRemainder" )( num );
		}

		// コンティニュー時の処理
		virtual void Continue()
		{
			mPyObject.attr( "doContinue" )();
		}

		// 移動禁止設定
		virtual void SetMoveForbidFlag( bool flag )
		{
			mPyObject.attr( "setMoveForbidFlag" )( flag );
		}
		// ショット禁止設定
		virtual void SetShotForbidFlag( bool flag )
		{
			mPyObject.attr( "setShotForbidFlag" )( flag );
		}
		// 特殊攻撃禁止設定
		virtual void SetSpecialAttackForbidFlag( bool flag )
		{
			mPyObject.attr( "setSpecialAttackForbidFlag" )( flag );
		}

	private:
		boost::python::object mPyObject;
	};
}
}
}
}