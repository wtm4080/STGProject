#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Linear.h"
#include <bulletmlrunner.h>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
	class LocatorObject;
}
}

namespace Game
{
namespace Util
{
namespace STG
{
namespace Locator
{
	class MLLocator
		: public ILocator<float>
		, public BulletMLRunner
	{
	public:
		// コンストラクタ
		typedef Util::Ptr<BulletMLParser>::Shared PBMLParser;
		MLLocator( PBMLParser bp, const Vector2DF &pos, 
			Random::PRandom pRandom );

		// 状態の更新
		virtual void Update();

		// 位置の取得
		virtual Vector2DF GetPosition() const;
		Vector2DF &GetPosition();
		// 位置の設定
		void SetPosition( const Vector2DF &pos );
		// 速度ベクトルの取得
		Vector2DF GetSpeed() const;
		Vector2DF &GetSpeed();
		// 速度ベクトルの設定
		void SetSpeed( const Vector2DF &sp );
		// 加速度ベクトルの取得
		Vector2DF GetAccel() const;
		Vector2DF &GetAccel();
		// 加速度ベクトルの設定
		void SetAccel( const Vector2DF &ac );
		// 外力の適用
		virtual Vector2DF ApplyExternalForce( const Vector2DF &vec );

		// 実行が終了しているかどうか
		bool IsEnd() const;
		// 狙う角度の取得
		float GetAimAngle() const;
		// 狙う角度の設定
		void SetAimAngle( float angle );
		// ランクの取得
		double GetRank() const;
		// ランクの設定
		static const double DEFAULT_RANK;
		void SetRank( double rank );

	private:
		LinearF mLocator;
		PBMLParser mpBMLParser;
		double mRank;
		int mFrameCount;
		float mAngle;
		float mAimAngle;
		Random::PRandom mpRandom;
		bool mVanished;

		friend class ::Defs::Util::LocatorObject;

		/// この弾の角度を求める
		// 角度を度単位で、上方向 0 で時計周りで返す
		virtual double getBulletDirection();
		/// この弾から自機を狙う角度を求める
		// 角度を度単位で、上方向 0 で時計周りで返す
		virtual double getAimDirection();
		/// この弾の速度を求める
		virtual double getBulletSpeed();
		/// デフォルトの速度を求める
		virtual double getDefaultSpeed();
		/// ランクを求める
		// 0 から 1 までの実数
		virtual double getRank();
		/// action を持たない弾を作る
		virtual void createSimpleBullet( double direction, double speed ) {}
		/// action を持つ弾を作る
		virtual void createBullet( BulletMLState *state, 
			double direction, double speed ) { delete state; }
		/// 弾の基準となるターンの値を返す、通常はフレーム数
		virtual int getTurn();
		/// 死ぬ
		virtual void doVanish();
		/// 弾の方向を指定した方向に変更する
		virtual void doChangeDirection( double dir );
		/// 弾の速度を指定した値に変更する
		virtual void doChangeSpeed( double speed );
		/// accel に対するインターフェイス
		virtual void doAccelX( double accelX );
		virtual void doAccelY( double accelY );
		/// 弾の速さの X 方向成分を返します
		virtual double getBulletSpeedX();
		/// 弾の速さの Y 方向成分を返します
		virtual double getBulletSpeedY();
		/// 乱数を返す
		virtual double getRand();
	};
}
}
}
}