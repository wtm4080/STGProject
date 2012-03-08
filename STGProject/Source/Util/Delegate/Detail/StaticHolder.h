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
	template <class RetType>
	class StaticHolder0
		: public IHolder0<RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ()> StaticFunction;

		StaticHolder0( StaticFunction f )
			: mFunc( f )
		{}

		virtual RetType Call() const
		{
			return mFunc();
		}

	private:
		StaticFunction mFunc;
	};

	template <class Arg1, class RetType>
	class StaticHolder1
		: public IHolder1<Arg1, RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( Arg1 )> StaticFunction;

		StaticHolder1( StaticFunction f )
			: mFunc( f )
		{}

		virtual RetType Call( Arg1 arg1 ) const
		{
			return mFunc( arg1 );
		}

	private:
		StaticFunction mFunc;
	};

	template <class Arg1, class Arg2, class RetType>
	class StaticHolder2
		: public IHolder2<Arg1, Arg2, RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( Arg1, Arg2 )> StaticFunction;

		StaticHolder2( StaticFunction f )
			: mFunc( f )
		{}

		virtual RetType Call( Arg1 arg1, Arg2 arg2 ) const
		{
			return mFunc( arg1, arg2 );
		}

	private:
		StaticFunction mFunc;
	};

	template <class Arg1, class Arg2, class Arg3, class RetType>
	class StaticHolder3
		: public IHolder3<Arg1, Arg2, Arg3, RetType>
		, public boost::noncopyable
	{
	public:
		typedef boost::function<RetType ( Arg1, Arg2, Arg3 )> StaticFunction;

		StaticHolder3( StaticFunction f )
			: mFunc( f )
		{}

		virtual RetType Call( Arg1 arg1, Arg2 arg2, Arg3 arg3 ) const
		{
			return mFunc( arg1, arg2, arg3 );
		}

	private:
		StaticFunction mFunc;
	};
}
}
}
}