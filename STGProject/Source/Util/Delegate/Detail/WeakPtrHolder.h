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
	class WeakPtrHolder0
		: public IHolder0<RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( ClassType * )> ClassFunction;
		typedef typename Ptr<ClassType>::Weak PClass;

		WeakPtrHolder0( PClass p, ClassFunction f )
			: mpClass( p )
			, mFunc( f )
		{}

		virtual RetType Call() const
		{
			if( !mpClass.expired() )
			{
				typename Ptr<ClassType>::Shared p = mpClass.lock();

				return p ? mFunc( p.get() ) : RetType();
			}

			return RetType();
		}

	private:
		PClass mpClass;
		ClassFunction mFunc;
	};

	template <class ClassType, class Arg1, class RetType>
	class WeakPtrHolder1
		: public IHolder1<Arg1, RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( ClassType *, Arg1 )> ClassFunction;
		typedef typename Ptr<ClassType>::Weak PClass;

		WeakPtrHolder1( PClass p, ClassFunction f )
			: mpClass( p )
			, mFunc( f )
		{}

		virtual RetType Call( Arg1 arg1 ) const
		{
			if( !mpClass.expired() )
			{
				typename Ptr<ClassType>::Shared p = mpClass.lock();

				return p ? mFunc( p.get(), arg1 ) : RetType();
			}

			return RetType();
		}

	private:
		PClass mpClass;
		ClassFunction mFunc;
	};

	template <class ClassType, class Arg1, class Arg2, class RetType>
	class WeakPtrHolder2
		: public IHolder2<Arg1, Arg2, RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( ClassType *, Arg1, Arg2 )> ClassFunction;
		typedef typename Ptr<ClassType>::Weak PClass;

		WeakPtrHolder2( PClass p, ClassFunction f )
			: mpClass( p )
			, mFunc( f )
		{}

		virtual RetType Call( Arg1 arg1, Arg2 arg2 ) const
		{
			if( !mpClass.expired() )
			{
				typename Ptr<ClassType>::Shared p = mpClass.lock();

				return p ? mFunc( p.get(), arg1, arg2 ) : RetType();
			}

			return RetType();
		}

	private:
		PClass mpClass;
		ClassFunction mFunc;
	};

	template <class ClassType, class Arg1, class Arg2, class Arg3, class RetType>
	class WeakPtrHolder3
		: public IHolder3<Arg1, Arg2, Arg3, RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( ClassType *, Arg1, Arg2, Arg3 )> ClassFunction;
		typedef typename Ptr<ClassType>::Weak PClass;

		WeakPtrHolder3( PClass p, ClassFunction f )
			: mpClass( p )
			, mFunc( f )
		{}

		virtual RetType Call( Arg1 arg1, Arg2 arg2, Arg3 arg3 ) const
		{
			if( !mpClass.expired() )
			{
				typename Ptr<ClassType>::Shared p = mpClass.lock();

				return p ? mFunc( p.get(), arg1, arg2, arg3 ) : RetType();
			}

			return RetType();
		}

	private:
		PClass mpClass;
		ClassFunction mFunc;
	};
}
}
}
}