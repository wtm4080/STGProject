#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Delegate/Delegate.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace DelegateTest_Static
{
namespace TestClass
{
	static void Func0_RetVoid()
	{}
	static bool Func0_RetBool()
	{
		return true;
	}
	static bool Func1_RetBool( int arg1 )
	{
		return arg1 == 1;
	}
	static bool Func2_RetBool( int arg1, int arg2 )
	{
		return arg1 == 1 && arg2 == 2;
	}
	static bool Func3_RetBool( int arg1, int arg2, int arg3 )
	{
		return arg1 == 1 && arg2 == 2 && arg3 == 3;
	}

	class Class0
	{
	public:
		static void RetVoid()
		{}
		static bool RetBool()
		{
			return true;
		}
	};
}
}