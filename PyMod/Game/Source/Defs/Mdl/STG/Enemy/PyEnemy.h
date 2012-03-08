#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Defs/Mdl/STG/Actor/PyActor.h"
#include "Mdl/STG/Enemy/IEnemy.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------
namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Enemy
{
#pragma warning( disable:4250 )
	class PyEnemy
		: public Actor::PyActor
		, public Game::Mdl::STG::Enemy::IEnemy
	{
	public:
		PyEnemy( const boost::python::object &object )
			: PyActor( object )
		{}

		// 当たり判定
		virtual bool IsHit( const Game::Util::STG::Hit::RectI &hit ) const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "isHit" )( hit ) );
		}
		// 破壊(エフェクトあり)
		virtual void Destruct()
		{
			mPyObject.attr( "destruct" )();
		}
		virtual void Destruct( float hp )
		{
			mPyObject.attr( "applyDamage" )( hp );
		}

		// HPの取得
		virtual float GetHP() const
		{
			return boost::python::extract<float>( 
				mPyObject.attr( "hp" ) );
		}
		// 当たり判定の取得
		virtual Game::Util::STG::Hit::RectI GetHitRect() const
		{
			return boost::python::extract<Game::Util::STG::Hit::RectI>( 
				mPyObject.attr( "hitRect" ) );
		}

		// 当たり判定用の半径を取得
		virtual float GetHitRadius() const
		{
			return boost::python::extract<float>( 
				mPyObject.attr( "hitRadius" ) );
		}

		// PrimalArmorが生成されているかを取得
		virtual bool IsPAGenerated() const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "paGenerated" ) );
		}
		// PrimalArmorの総量を取得
		virtual float GetMaxPAAmount() const
		{
			return boost::python::extract<float>( 
				mPyObject.attr( "maxPAAmount" ) );
		}
		// PrimalArmorの残量を取得
		virtual float GetPAAmount() const
		{
			return boost::python::extract<float>( 
				mPyObject.attr( "paAmount" ) );
		}
	};
}
}
}
}