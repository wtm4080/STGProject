#include "PCH.h"
#include "TestCommon.h"
#include "DelegateTest_Dynamic.h"

using namespace Game;
using namespace DelegateTest_Dynamic;


TestSuite( DelegateTest_SharedPtr )


TestCase( CallTest )
{
	Util::Ptr<TestClass::Class0>::Shared pClass0( new TestClass::Class0() );

	Util::Delegate::Delegate0<> class0_RetVoid( pClass0, &TestClass::Class0::RetVoid );
	Util::Delegate::Delegate0<bool> class0_RetBool( pClass0, &TestClass::Class0::RetBool );

	class0_RetVoid();
	Check( class0_RetBool() );

	Util::Ptr<TestClass::Class1>::Shared pClass1( new TestClass::Class1() );
	Util::Ptr<TestClass::Class2>::Shared pClass2( new TestClass::Class2() );
	Util::Ptr<TestClass::Class3>::Shared pClass3( new TestClass::Class3() );

	Util::Delegate::Delegate1<int, bool> func1( pClass1, &TestClass::Class1::RetBool );
	Util::Delegate::Delegate2<int, int, bool> func2( pClass2, &TestClass::Class2::RetBool );
	Util::Delegate::Delegate3<int, int, int, bool> func3( pClass3, &TestClass::Class3::RetBool );

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

	Util::Ptr<TestClass::Class0>::Shared pClass0( new TestClass::Class0() );
	Util::Ptr<TestClass::Class1>::Shared pClass1( new TestClass::Class1() );
	Util::Ptr<TestClass::Class2>::Shared pClass2( new TestClass::Class2() );
	Util::Ptr<TestClass::Class3>::Shared pClass3( new TestClass::Class3() );

	func0.Reset( pClass0, &TestClass::Class0::RetBool );
	func1.Reset( pClass1, &TestClass::Class1::RetBool );
	func2.Reset( pClass2, &TestClass::Class2::RetBool );
	func3.Reset( pClass3, &TestClass::Class3::RetBool );

	Check( func0() );
	Check( func1( 1 ) );
	Check( func2( 1, 2 ) );
	Check( func3( 1, 2, 3 ) );
}

TestCase( RefCountTest )
{
	Util::Ptr<TestClass::Class0>::Shared pClass0( new TestClass::Class0() );

	Util::Delegate::Delegate0<> class0_RetVoid( pClass0, &TestClass::Class0::RetVoid );
	Util::Delegate::Delegate0<bool> class0_RetBool( pClass0, &TestClass::Class0::RetBool );

	CheckEqual( 3, pClass0.use_count() );

	Util::Ptr<TestClass::Class1>::Shared pClass1( new TestClass::Class1() );
	Util::Ptr<TestClass::Class2>::Shared pClass2( new TestClass::Class2() );
	Util::Ptr<TestClass::Class3>::Shared pClass3( new TestClass::Class3() );

	Util::Delegate::Delegate1<int, bool> func1( pClass1, &TestClass::Class1::RetBool );
	Util::Delegate::Delegate2<int, int, bool> func2( pClass2, &TestClass::Class2::RetBool );
	Util::Delegate::Delegate3<int, int, int, bool> func3( pClass3, &TestClass::Class3::RetBool );

	Check( !pClass1.unique() );
	Check( !pClass2.unique() );
	Check( !pClass3.unique() );

	class0_RetVoid.Reset();
	class0_RetBool.Reset();
	func1.Reset();
	func2.Reset();
	func3.Reset();

	Check( pClass0.unique() );
	Check( pClass1.unique() );
	Check( pClass2.unique() );
	Check( pClass3.unique() );
}

TestCase( InvalidSharedPtrTest )
{
	Util::Ptr<TestClass::Class0>::Shared pClass0;
	Util::Ptr<TestClass::Class1>::Shared pClass1;
	Util::Ptr<TestClass::Class2>::Shared pClass2;
	Util::Ptr<TestClass::Class3>::Shared pClass3;

	Util::Delegate::Delegate0<bool> func0( pClass0, &TestClass::Class0::RetBool );
	Util::Delegate::Delegate1<int, bool> func1( pClass1, &TestClass::Class1::RetBool );
	Util::Delegate::Delegate2<int, int, bool> func2( pClass2, &TestClass::Class2::RetBool );
	Util::Delegate::Delegate3<int, int, int, bool> func3( pClass3, &TestClass::Class3::RetBool );

	Check( !func0() );
	Check( !func1( 1 ) );
	Check( !func2( 1, 2 ) );
	Check( !func3( 1, 2, 3) );

	func0.Reset( pClass0, &TestClass::Class0::RetBool );
	func1.Reset( pClass1, &TestClass::Class1::RetBool );
	func2.Reset( pClass2, &TestClass::Class2::RetBool );
	func3.Reset( pClass3, &TestClass::Class3::RetBool );

	Check( !func0() );
	Check( !func1( 1 ) );
	Check( !func2( 1, 2 ) );
	Check( !func3( 1, 2, 3) );
}


TestSuiteEnd()