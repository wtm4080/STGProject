#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
#include <bulletmlrunner.h>
#include "Fwd.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace BulletML
{
	class RunnerHandler
		: public BulletMLRunner
	{
	public:
		typedef Game::Util::Ptr<BulletMLParser>::Shared PParser;
		explicit RunnerHandler( const boost::python::object &object, 
			PParser pParser )
			: BulletMLRunner( pParser.get() )
			, mPyObject( object )
			, mpParser( pParser )
		{}
		explicit RunnerHandler( const boost::python::object &object, 
			PParser pParser, BulletMLState *state )
			: BulletMLRunner( state )
			, mPyObject( object )
			, mpParser( pParser )
		{}

		PParser getParser() const
		{
			return mpParser;
		}

		// ----- 絶対実装しなければならない関数群の始まり -----
		//@{
		/// この弾の角度を求める
		/**
		 * @return 角度を度単位で、上方向 0 で時計周りで返す
		 */
		virtual double getBulletDirection()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getBulletDirection" )() );
		}
		/// この弾から自機を狙う角度を求める
		/**
		 * @return 角度を度単位で、上方向 0 で時計周りで返す
		 */
		virtual double getAimDirection()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getAimDirection" )() );
		}
		/// この弾の速度を求める
		virtual double getBulletSpeed()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getBulletSpeed" )() );
		}
		/// デフォルトの速度を求める
		virtual double getDefaultSpeed()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getDefaultSpeed" )() );
		}
		/// ランクを求める
		/**
		 * @return 0 から 1 までの実数
		 */
		virtual double getRank()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getRank" )() );
		}
		/// action を持たない弾を作る
		virtual void createSimpleBullet(double direction, double speed)
		{
			mPyObject.attr( "createSimpleBullet" )( direction, speed );
		}
		/// action を持つ弾を作る
		/**
		 * @param state
		 * 新しい弾の BulletMLRunner のコンストラクタに渡すこと。
		 * もし渡さないのであれば、delete で解放しなければならない。
		 */
		virtual void createBullet(BulletMLState* state,
										   double direction, double speed)
		{
			mPyObject.attr( "createBullet" )( state, direction, speed );
		}
		/// 弾の基準となるターンの値を返す、通常はフレーム数
		/**
		 * @return
		 * ゲームごとの基準でオーダーは変更して構いませんが、
		 * 負数は許されません。
		 * xml データ上で、wait と term のオーダーが揃っていれば問題ありません。
		 */
		virtual int getTurn()
		{
			return boost::python::extract<int>( 
				mPyObject.attr( "getTurn" )() );
		}
		/// 死ぬ
		virtual void doVanish()
		{
			mPyObject.attr( "doVanish" )();
		}
		//@}
		// ----- 絶対実装しなければならない関数群の終わり -----

		// ----- 必要があれば実装する関数群の始まり -----
		//@{
		/// 弾の方向を指定した方向に変更する
		virtual void doChangeDirection( double direction )
		{
			mPyObject.attr( "doChangeDirection" )( direction );
		}
		/// 弾の速度を指定した値に変更する
		virtual void doChangeSpeed( double speed )
		{
			mPyObject.attr( "doChangeSpeed" )( speed );
		}
		/// accel に対するインターフェイス
		/**
		 * @todo
		 * horizontal, vertical の type は未実装です。
		 * どれも absolute になってしまいます。
		 */
		virtual void doAccelX( double accelX )
		{
			mPyObject.attr( "doAccelX" )( accelX );
		}
		/// accel に対するインターフェイス
		/**
		 * @todo
		 * horizontal, vertical の type は未実装です。
		 * どれも absolute になってしまいます。
		 */
		virtual void doAccelY( double accelY )
		{
			mPyObject.attr( "doAccelY" )( accelY );
		}
		/// 弾の速さの X 方向成分を返します
		/**
		 * accel を使う場合はオーバーライドして下さい
		 */
		virtual double getBulletSpeedX()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getBulletSpeedX" )() );
		}
		/// 弾の速さの Y 方向成分を返します
		/**
		 * accel を使う場合はオーバーライドして下さい
		 */
		virtual double getBulletSpeedY()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getBulletSpeedY" )() );
		}
		//@}
		// ----- 必要があれば実装する関数群の終わり -----

		/// 乱数を返す
		/**
		 * 見てのとおり、デフォルトでは std::rand が用いられます。
		 */
		virtual double getRand()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getRand" )() );
		}

	private:
		boost::python::object mPyObject;
		PParser mpParser;
	};
}
}
}