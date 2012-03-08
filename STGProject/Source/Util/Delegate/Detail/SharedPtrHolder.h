#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IHolder.h"
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <memory>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Delegate
{
namespace Detail
{
	template <class ClassType, class RetType>
	class SharedPtrHolder0
		: public IHolder0<RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( ClassType * )> ClassFunction;
		typedef typename Ptr<ClassType>::Shared PClass;

		SharedPtrHolder0( PClass p, ClassFunction f )
			: mpClass( p )
			, mFunc( f )
		{}

		virtual RetType Call() const
		{
			return mpClass ? mFunc( mpClass.get() ) : RetType();
		}

	private:
		PClass mpClass;
		ClassFunction mFunc;
	};

	template <class ClassType, class Arg1, class RetType>
	class SharedPtrHolder1
		: public IHolder1<Arg1, RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( ClassType *, Arg1 )> ClassFunction;
		typedef typename Ptr<ClassType>::Shared PClass;

		SharedPtrHolder1( PClass p, ClassFunction f )
			: mpClass( p )
			, mFunc( f )
		{}

		virtual RetType Call( Arg1 arg1 ) const
		{
			return mpClass ? mFunc( mpClass.get(), arg1 ) : RetType();
		}

	private:
		PClass mpClass;
		ClassFunction mFunc;
	};

	template <class ClassType, class Arg1, class Arg2, class RetType>
	class SharedPtrHolder2
		: public IHolder2<Arg1, Arg2, RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( ClassType *, Arg1, Arg2 )> ClassFunction;
		typedef typename Ptr<ClassType>::Shared PClass;

		SharedPtrHolder2( PClass p, ClassFunction f )
			: mpClass( p )
			, mFunc( f )
		{}

		virtual RetType Call( Arg1 arg1, Arg2 arg2 ) const
		{
			return mpClass ? mFunc( mpClass.get(), arg1, arg2 ) : RetType();
		}

	private:
		PClass mpClass;
		ClassFunction mFunc;
	};

	template <class ClassType, class Arg1, class Arg2, class Arg3, class RetType>
	class SharedPtrHolder3
		: public IHolder3<Arg1, Arg2, Arg3, RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( ClassType *, Arg1, Arg2, Arg3 )> ClassFunction;
		typedef typename Ptr<ClassType>::Shared PClass;

		SharedPtrHolder3( PClass p, ClassFunction f )
			: mpClass( p )
			, mFunc( f )
		{}

		virtual RetType Call( Arg1 arg1, Arg2 arg2, Arg3 arg3 ) const
		{
			return mpClass ? mFunc( mpClass.get(), arg1, arg2, arg3 ) : RetType();
		}

	private:
		PClass mpClass;
		ClassFunction mFunc;
	};
}
}
}
}