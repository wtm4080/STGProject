#include "PCH.h"
#include "TestCommon.h"
#include "DelegateTest_Dynamic.h"

using namespace Game;
using namespace DelegateTest_Dynamic;
using namespace boost;


TestSuite( DelegateTest_RawPtr )


TestCase( CallTest )
{
	scoped_ptr<TestClass::Class0> pClass0( new TestClass::Class0() );

	Util::Delegate::Delegate0<> class0_RetVoid( pClass0.get(), &TestClass::Class0::RetVoid );
	Util::Delegate::Delegate0<bool> class0_RetBool( pClass0.get(), &TestClass::Class0::RetBool );

	class0_RetVoid();
	Check( class0_RetBool() );

	scoped_ptr<TestClass::Class1> pClass1( new TestClass::Class1() );
	scoped_ptr<TestClass::Class2> pClass2( new TestClass::Class2() );
	scoped_ptr<TestClass::Class3> pClass3( new TestClass::Class3() );

	Util::Delegate::Delegate1<int, bool> func1( pClass1.get(), &TestClass::Class1::RetBool );
	Util::Delegate::Delegate2<int, int, bool> func2( pClass2.get(), &TestClass::Class2::RetBool );
	Util::Delegate::Delegate3<int, int, int, bool> func3( pClass3.get(), &TestClass::Class3::RetBool );

	Check( func1( 1 ) );
	Check( func2( 1, 2 ) );
	Check( func3( 1, 2, 3 ) );
}

TestCase( ResetTest )
{
	Util::Delegate::Delegate0<bool> func0;
	Util::Delegate::Delegate1<int, bool> func1;
	Util::Delegate::Delegate2<int, int, bool> func2;
	Util::Delegate::Delegate3<int, int, int, bool> func3;

	scoped_ptr<TestClass::Class0> pClass0( new TestClass::Class0() );
	scoped_ptr<TestClass::Class1> pClass1( new TestClass::Class1() );
	scoped_ptr<TestClass::Class2> pClass2( new TestClass::Class2() );
	scoped_ptr<TestClass::Class3> pClass3( new TestClass::Class3() );

	func0.Reset( pClass0.get(), &TestClass::Class0::RetBool );
	func1.Reset( pClass1.get(), &TestClass::Class1::RetBool );
	func2.Reset( pClass2.get(), &TestClass::Class2::RetBool );
	func3.Reset( pClass3.get(), &TestClass::Class3::RetBool );

	Check( func0() );
	Check( func1( 1 ) );
	Check( func2( 1, 2 ) );
	Check( func3( 1, 2, 3 ) );
}


TestSuiteEnd()