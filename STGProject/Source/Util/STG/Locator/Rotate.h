#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "ILocator.h"


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
	template <class T>
	class Rotate
		: public ILocator<T>
	{
	public:
		Rotate()
			: mCenter()
			, mCenterSp()
			, mCenterAc()
			, mExForce()
			, mRadius()
			, mRadiusSp()
			, mRadiusAc()
			, mAngle()
			, mAngleSp()
			, mAngleAc()
		{}

		// 状態の更新
		virtual void Update()
		{
			mCenterSp += mCenterAc + mExForce;
			mCenter += mCenterSp;

			mRadiusSp += mRadiusAc;
			mRadius += mRadiusSp;

			mAngleSp += mAngleAc;
			mAngle += mAngleSp;

			mExForce.SetXY( 0, 0 );
		}


		// 位置の取得
		virtual Vector2D<T> GetPosition() const
		{
			Vector2D<T> pos;
			pos.SetUnitVector( static_cast<float>( mAngle ) );
			pos *= mRadius;
			pos += mCenter;

			return pos;
		}

		// 外力の適用
		virtual Vector2D<T> ApplyExternalForce( const Vector2D<T> &vec )
		{
			Vector2D<T> ret = mCenterAc + mExForce;

			mExForce += vec;

			return ret;
		}


		// 中心位置の取得
		Vector2D<T> GetCenter() const
		{
			return mCenter;
		}
		void SetCenter( const Vector2D<T> &center )
		{
			mCenter = center;
		}
		Vector2D<T> &GetCenter()
		{
			return mCenter;
		}

		// 中心位置の移動速度の取得
		Vector2D<T> GetCenterSpeed() const
		{
			return mCenterSp;
		}
		void SetCenterSpeed( const Vector2D<T> &centerSp )
		{
			mCenterSp = centerSp;
		}
		Vector2D<T> &GetCenterSpeed()
		{
			return mCenterSp;
		}

		// 中心位置の移動加速度の取得
		Vector2D<T> GetCenterAccel() const
		{
			return mCenterAc;
		}
		void SetCenterAccel( const Vector2D<T> &centerAc )
		{
			mCenterAc = centerAc;
		}
		Vector2D<T> &GetCenterAccel()
		{
			return mCenterAc;
		}

		// 半径の取得
		T GetRadius() const
		{
			return mRadius;
		}
		// 半径の設定
		void SetRadius( T radius )
		{
			mRadius = radius;
		}

		// 半径の増加速度の取得
		T GetRadiusSpeed() const
		{
			return mRadiusSp;
		}
		// 半径の増加速度の設定
		void SetRadiusSpeed( T speed )
		{
			mRadiusSp = speed;
		}

		// 半径の増加加速度の取得
		T GetRadiusAccel() const
		{
			return mRadiusAc;
		}
		// 半径の増加速度の設定
		void SetRadiusAccel( T accel )
		{
			mRadiusAc = accel;
		}

		// 角度の取得
		T GetAngle() const
		{
			return mAngle;
		}
		// 角度の設定
		void SetAngle( T angle )
		{
			mAngle = angle;
		}

		// 角速度の取得
		T GetAngleSpeed() const
		{
			return mAngleSp;
		}
		// 角速度の設定
		void SetAngleSpeed( T speed )
		{
			mAngleSp = speed;
		}

		// 角加速度の取得
		T GetAngleAccel() const
		{
			return mAngleAc;
		}
		// 角加速度の設定
		void SetAngleAccel( T accel )
		{
			mAngleAc = accel;
		}

	private:
		Vector2D<T> mCenter, mCenterSp, mCenterAc, mExForce;
		T mRadius, mRadiusSp, mRadiusAc;
		T mAngle, mAngleSp, mAngleAc;

		friend class ::Defs::Util::LocatorObject;
	};

	typedef Rotate<float> RotateF;
	typedef Rotate<Selene::Sint32> RotateI;
}
}
}
}