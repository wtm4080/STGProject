#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Delegate/Delegate.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace DelegateTest_Dynamic
{
namespace TestClass
{
	class Class0
	{
	public:
		void RetVoid()
		{}
		bool RetBool()
		{
			return true;
		}
	};

	class Class1
	{
	public:
		bool RetBool( int arg1 )
		{
			return arg1 == 1;
		}
	};

	class Class2
	{
	public:
		bool RetBool( int arg1, int arg2 )
		{
			return arg1 == 1 && arg2 == 2;
		}
	};

	class Class3
	{
	public:
		bool RetBool( int arg1, int arg2, int arg3 )
		{
			return arg1 == 1 && arg2 == 2 && arg3 == 3;
		}
	};
}
}