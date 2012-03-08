#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Defs/Mdl/STG/Actor/PyActor.h"
#include "Mdl/STG/MyShot/IMyShot.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace MyShot
{
#pragma warning( disable:4250 )
	class PyMyShot
		: public Actor::PyActor
		, public Game::Mdl::STG::MyShot::IMyShot
	{
	public:
		PyMyShot( const boost::python::object &object )
			: PyActor( object )
		{}

		// 当たり判定
		virtual bool IsHit( const Game::Util::STG::Hit::CircleI &hit ) const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "isHitCircle" )( hit ) );
		}
		virtual bool IsHit( const Game::Util::STG::Hit::RectI &hit ) const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "isHitRect" )( hit ) );
		}
		// 破壊
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
		// 当たり判定の半径の取得
		virtual float GetHitRadius() const
		{
			return boost::python::extract<float>( 
				mPyObject.attr( "hitRadius" ) );
		}

		// PrimalArmorへのダメージを取得
		virtual float GetPADamage() const
		{
			return boost::python::extract<float>( 
				mPyObject.attr( "paDamage" ) );
		}
		// PrimalArmorが展開されていない時でも強制的にダメージを与えるかどうかを取得
		virtual bool IsForcibleForPA() const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "forcibleForPA" ) );
		}
	};
}
}
}
}