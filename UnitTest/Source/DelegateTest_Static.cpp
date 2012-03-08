#include "PCH.h"
#include "TestCommon.h"
#include "DelegateTest_Static.h"

using namespace Game;


TestSuite( DelegateTest_Static )


TestCase( CallTest )
{
	Util::Delegate::Delegate0<bool> empty0;
	Util::Delegate::Delegate1<int, int> empty1;
	Util::Delegate::Delegate2<int, int, int> empty2;
	Util::Delegate::Delegate3<int, int, int, int> empty3;

	Check( !empty0() );
	CheckEqual( 0, empty1( 0 ) );
	CheckEqual( 0, empty2( 0, 0 ) );
	CheckEqual( 0, empty3( 0, 0, 0 ) );

	Util::Delegate::Delegate0<> func0_RetVoid( &TestClass::Func0_RetVoid );
	Util::Delegate::Delegate0<bool> func0_RetBool( &TestClass::Func0_RetBool );
	Util::Delegate::Delegate0<> class0_RetVoid( &TestClass::Class0::RetVoid );
	Util::Delegate::Delegate0<bool> class0_RetBool( &TestClass::Class0::RetBool );

	func0_RetVoid();
	Check( func0_RetBool() );
	class0_RetVoid();
	Check( class0_RetBool() );

	Util::Delegate::Delegate1<int, bool> func1( &TestClass::Func1_RetBool );
	Util::Delegate::Delegate2<int, int, bool> func2( &TestClass::Func2_RetBool );
	Util::Delegate::Delegate3<int, int, int, bool> func3( &TestClass::Func3_RetBool );

	Check( func1( 1 ) );
	Check( func2( 1, 2 ) );
	Check( func3( 1, 2, 3 ) );
}

TestCase( IsEmptyTest )
{
	Util::Delegate::Delegate0<bool> empty0;
	Util::Delegate::Delegate1<int, int> empty1;
	Util::Delegate::Delegate2<int, int, int> empty2;
	Util::Delegate::Delegate3<int, int, int, int> empty3;

	Check( empty0.IsEmpty() );
	Check( empty1.IsEmpty() );
	Check( empty2.IsEmpty() );
	Check( empty3.IsEmpty() );

	Util::Delegate::Delegate0<bool> func0( &TestClass::Func0_RetBool );
	Util::Delegate::Delegate1<int, bool> func1( &TestClass::Func1_RetBool );
	Util::Delegate::Delegate2<int, int, bool> func2( &TestClass::Func2_RetBool );
	Util::Delegate::Delegate3<int, int, int, bool> func3( &TestClass::Func3_RetBool );

	Check( !func0.IsEmpty() );
	Check( !func1.IsEmpty() );
	Check( !func2.IsEmpty() );
	Check( !func3.IsEmpty() );
}

TestCase( ResetTest )
{
	Util::Delegate::Delegate0<bool> func0( &TestClass::Func0_RetBool );
	Util::Delegate::Delegate1<int, bool> func1( &TestClass::Func1_RetBool );
	Util::Delegate::Delegate2<int, int, bool> func2( &TestClass::Func2_RetBool );
	Util::Delegate::Delegate3<int, int, int, bool> func3( &TestClass::Func3_RetBool );

	func0.Reset();
	func1.Reset();
	func2.Reset();
	func3.Reset();

	Check( func0.IsEmpty() );
	Check( func1.IsEmpty() );
	Check( func2.IsEmpty() );
	Check( func3.IsEmpty() );

	func0.Reset( &TestClass::Func0_RetBool );
	func1.Reset( &TestClass::Func1_RetBool );
	func2.Reset( &TestClass::Func2_RetBool );
	func3.Reset( &TestClass::Func3_RetBool );

	Check( func0() );
	Check( func1( 1 ) );
	Check( func2( 1, 2 ) );
	Check( func3( 1, 2, 3 ) );
}


TestSuiteEnd()