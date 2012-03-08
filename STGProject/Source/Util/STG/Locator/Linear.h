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
	class Linear
		: public ILocator<T>
	{
	public:
		// コンストラクタ
		Linear()
			: mPos()
			, mSp()
			, mAc()
			, mExForce()
		{}
		Linear( const Vector2D<T> &position )
			: mPos( position )
			, mSp()
			, mAc()
			, mExForce()
		{}
		Linear( const Vector2D<T> &position, const Vector2D<T> &speed, 
			const Vector2D<T> &accel )
			: mPos( position )
			, mSp( speed )
			, mAc( accel )
			, mExForce()
		{}


		// 状態の更新
		virtual void Update()
		{
			mSp += mAc + mExForce;
			mPos += mSp;

			mExForce.SetXY( 0, 0 );
		}


		// 位置の取得
		virtual Vector2D<T> GetPosition() const
		{
			return mPos;
		}
		void SetPosition( const Vector2D<T> &pos )
		{
			mPos = pos;
		}
		Vector2D<T> &GetPosition()
		{
			return mPos;
		}

		// 速度ベクトルの取得
		Vector2D<T> GetSpeed() const
		{
			return mSp;
		}
		void SetSpeed( const Vector2D<T> &sp )
		{
			mSp = sp;
		}
		Vector2D<T> &GetSpeed()
		{
			return mSp;
		}

		// 加速度ベクトルの取得
		Vector2D<T> GetAccel() const
		{
			return mAc;
		}
		void SetAccel( const Vector2D<T> &ac )
		{
			mAc = ac;
		}
		Vector2D<T> &GetAccel()
		{
			return mAc;
		}

		// 外力の適用
		virtual Vector2D<T> ApplyExternalForce( const Vector2D<T> &vec )
		{
			Vector2D<T> ret = mAc + mExForce;

			mExForce += vec;

			return ret;
		}

	private:
		Vector2D<T> mPos, mSp, mAc, mExForce;

		friend class ::Defs::Util::LocatorObject;
	};

	typedef Linear<float> LinearF;
	typedef Linear<Selene::Sint32> LinearI;
}
}
}
}