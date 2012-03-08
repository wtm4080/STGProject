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
	class Trace
		: public ILocator<T>
	{
	public:
		// コンストラクタ
		Trace()
			: mTracingFlag()
			, mPos()
			, mTargetPos()
			, mSp()
			, mAc()
			, mExForce()
			, mMaxCAngle()
		{}
		Trace( T maxCirclingAngle )
			: mTracingFlag()
			, mPos()
			, mTargetPos()
			, mSp()
			, mAc()
			, mExForce()
			, mMaxCAngle( maxCirclingAngle )
		{}


		// 追尾フラグの取得
		bool IsTracing() const
		{
			return mTracingFlag;
		}
		// 追尾の有効/無効化
		void SetTracing( bool flag )
		{
			mTracingFlag = flag;
		}


		// 状態の更新
		virtual void Update()
		{
			mSp += mAc + mExForce;

			if( IsTracing() )
			{
				T angle = mSp.GetAngle();

				if( IsRightCircling() )
				{
					IsMaxCircling() ? 
						( angle += mMaxCAngle ) : ( angle = mPos.GetAngle( mTargetPos ) );
				}
				else
				{
					IsMaxCircling() ? 
						( angle -= mMaxCAngle ) : ( angle = mPos.GetAngle( mTargetPos ) );
				}

				T abs = mSp.GetAbs();
				mSp.SetUnitVector( angle ) *= abs;
			}

			if( IsTracing() && 
				mTargetPos.GetDistance( mPos ) <= mSp.GetAbs() )
			{
				mPos = mTargetPos;
			}
			else
			{
				mPos += mSp;
			}

			mExForce = 0;
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

		// 目標位置の取得
		Vector2D<T> GetTargetPosition() const
		{
			return mTargetPos;
		}
		void SetTargetPosition( const Vector2D<T> &targetPos )
		{
			mTargetPos = targetPos;
		}
		Vector2D<T> &GetTargetPosition()
		{
			return mTargetPos;
		}

		// 速度の取得
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

		// 加速度の取得
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

		// 最大旋回角度の取得
		T GetMaxCirclingAngle() const
		{
			return mMaxCAngle;
		}
		// 最大旋回角度の設定
		void SetMaxCirclingAngle( T angle )
		{
			mMaxCAngle = angle;
		}

		// 外力の適用
		virtual Vector2D<T> ApplyExternalForce( const Vector2D<T> &vec )
		{
			Vector2D<T> ret = mAc + mExForce;

			mExForce += vec;

			return ret;
		}

	private:
		bool mTracingFlag;
		Vector2D<T> mPos, mTargetPos, mSp, mAc, mExForce;
		T mMaxCAngle;

		// 右回りかどうか
		bool IsRightCircling() const
		{
			float 
				angle = static_cast<float>( mSp.GetAngle() ), 
				targetAngle = static_cast<float>( mPos.GetAngle( mTargetPos ) ), 
				maxCAngle = static_cast<float>( mMaxCAngle );

			return 
				Util::Cos( targetAngle ) * Util::Cos( angle + maxCAngle ) + 
				Util::Sin( targetAngle ) * Util::Sin( angle + maxCAngle ) 
				>= 
				Util::Cos( targetAngle ) * Util::Cos( angle - maxCAngle ) + 
				Util::Sin( targetAngle ) * Util::Sin( angle - maxCAngle );
		}
		// 旋回上限角度で曲がるかどうか
		bool IsMaxCircling() const
		{
			float 
				angle = static_cast<float>( mSp.GetAngle() ), 
				targetAngle = static_cast<float>( mPos.GetAngle( mTargetPos ) ), 
				maxCAngle = static_cast<float>( mMaxCAngle );

			return 
				Util::Cos( angle ) * Util::Cos( angle + maxCAngle ) + 
				Util::Sin( angle ) * Util::Sin( angle + maxCAngle ) 
				>= 
				Util::Cos( angle ) * Util::Cos( targetAngle ) + 
				Util::Sin( angle ) * Util::Sin( targetAngle );
		}

		friend class ::Defs::Util::LocatorObject;
	};

	typedef Trace<float> TraceF;
	typedef Trace<Selene::Sint32> TraceI;
}
}
}
}