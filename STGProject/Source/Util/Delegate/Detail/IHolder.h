#pragma once


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
	class IHolder0
	{
	public:
		virtual RetType Call() const = 0;
		virtual ~IHolder0() {}
	};

	template <class Arg1, class RetType>
	class IHolder1
	{
	public:
		virtual RetType Call( Arg1 ) const = 0;
		virtual ~IHolder1() {}
	};

	template <class Arg1, class Arg2, class RetType>
	class IHolder2
	{
	public:
		virtual RetType Call( Arg1, Arg2 ) const = 0;
		virtual ~IHolder2() {}
	};

	template <class Arg1, class Arg2, class Arg3, class RetType>
	class IHolder3
	{
	public:
		virtual RetType Call( Arg1, Arg2, Arg3 ) const = 0;
		virtual ~IHolder3() {}
	};
}
}
}
}