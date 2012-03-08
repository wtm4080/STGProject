#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
#include "Mdl/STG/Actor/IActor.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Actor
{
	class PyActor
		: virtual public Game::Mdl::STG::Actor::IActor
	{
	public:
		PyActor( const boost::python::object &object )
			: mPyObject( object )
		{}

		// 一意な整数値を取得
		virtual Selene::Uint64 GetId() const
		{
			return boost::python::extract<Selene::Uint64>( 
				mPyObject.attr( "objectId" ) );
		}

		// 更新
		virtual void Update()
		{
			mPyObject.attr( "update" )();
		}
		// 描画
		virtual void Draw() const
		{
			mPyObject.attr( "draw" )();
		}

		// 有効フラグの取得
		virtual bool IsValid() const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "valid" ) );
		}
		// 有効フラグの設定
		virtual void SetValid( bool flag )
		{
			mPyObject.attr( "valid" ) = flag;
		}

		// 消去
		virtual void Erase()
		{
			mPyObject.attr( "erase" )();
		}

		// 位置の取得
		virtual Game::Util::STG::Vector2DF GetPosition() const
		{
			return boost::python::extract<Game::Util::STG::Vector2DF>( 
				mPyObject.attr( "position" ) );
		}
		// 外力の適用
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( const Game::Util::STG::Vector2DF &vec )
		{
			return boost::python::extract<Game::Util::STG::Vector2DF>( 
				mPyObject.attr( "applyExternalForce" )( vec ) );
		}
		// 有効領域判定の取得
		virtual Game::Util::STG::Hit::RectI GetValidRect() const
		{
			return boost::python::extract<Game::Util::STG::Hit::RectI>( 
				mPyObject.attr( "validRect" ) );
		}
		// 有効領域判定の設定
		virtual void SetValidRect( const Game::Util::STG::Hit::RectI &rect )
		{
			mPyObject.attr( "validRect" ) = rect;
		}
		// 有効領域の余白の設定
		virtual void SetValidAreaMargin( int margin )
		{
			mPyObject.attr( "setValidAreaMargin" )( margin );
		}
		// 現在のフレームカウントを取得
		virtual unsigned GetFrameCount() const
		{
			return boost::python::extract<unsigned>( 
				mPyObject.attr( "frameCount" ) );
		}
		// 現在のフレームカウントを設定
		virtual void SetFrameCount( unsigned count )
		{
			mPyObject.attr( "frameCount" ) = count;
		}
		// 有効上限フレームカウントの取得
		virtual unsigned GetValidFrameNum() const
		{
			return boost::python::extract<unsigned>( 
				mPyObject.attr( "validFrameNum" ) );
		}
		// 有効上限フレームカウントの設定
		virtual void SetValidFrameNum( unsigned frameNum )
		{
			mPyObject.attr( "validFrameNum" )( frameNum );
		}

	protected:
		boost::python::object mPyObject;
	};
}
}
}
}