#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IHolder.h"
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>


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
	class RawPtrHolder0
		: public IHolder0<RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( ClassType * )> ClassFunction;

		RawPtrHolder0( ClassType *p, ClassFunction f )
			: mpClass( p )
			, mFunc( f )
		{}

		virtual RetType Call() const
		{
			return mpClass ? mFunc( mpClass ) : RetType();
		}

	private:
		ClassType *mpClass;
		ClassFunction mFunc;
	};

	template <class ClassType, class Arg1, class RetType>
	class RawPtrHolder1
		: public IHolder1<Arg1, RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( ClassType *, Arg1 )> ClassFunction;

		RawPtrHolder1( ClassType *p, ClassFunction f )
			: mpClass( p )
			, mFunc( f )
		{}

		virtual RetType Call( Arg1 arg1 ) const
		{
			return mpClass ? mFunc( mpClass, arg1 ) : RetType();
		}

	private:
		ClassType *mpClass;
		ClassFunction mFunc;
	};

	template <class ClassType, class Arg1, class Arg2, class RetType>
	class RawPtrHolder2
		: public IHolder2<Arg1, Arg2, RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( ClassType *, Arg1, Arg2 )> ClassFunction;

		RawPtrHolder2( ClassType *p, ClassFunction f )
			: mpClass( p )
			, mFunc( f )
		{}

		virtual RetType Call( Arg1 arg1, Arg2 arg2 ) const
		{
			return mpClass ? mFunc( mpClass, arg1, arg2 ) : RetType();
		}

	private:
		ClassType *mpClass;
		ClassFunction mFunc;
	};

	template <class ClassType, class Arg1, class Arg2, class Arg3, class RetType>
	class RawPtrHolder3
		: public IHolder3<Arg1, Arg2, Arg3, RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( ClassType *, Arg1, Arg2, Arg3 )> ClassFunction;

		RawPtrHolder3( ClassType *p, ClassFunction f )
			: mpClass( p )
			, mFunc( f )
		{}

		virtual RetType Call( Arg1 arg1, Arg2 arg2, Arg3 arg3 ) const
		{
			return mpClass ? mFunc( mpClass, arg1, arg2, arg3 ) : RetType();
		}

	private:
		ClassType *mpClass;
		ClassFunction mFunc;
	};
}
}
}
}