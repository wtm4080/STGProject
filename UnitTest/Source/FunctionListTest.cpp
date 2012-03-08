#include "PCH.h"
#include "TestCommon.h"
#include "FunctionListTest.h"

using namespace Game;


TestSuite( FunctionListTest )


TestCase( CallTest )
{
	TestClass testClass;
	testClass.SetRetFlag1( true );
	testClass.SetRetFlag2( true );
	testClass.ClearFlags();

	Util::FunctionList funcList;
	typedef Util::FunctionList::Delegate Delegate;
	funcList.Add( Delegate( &testClass, &TestClass::SetFlag1 ) );
	funcList.Add( Delegate( &testClass, &TestClass::SetFlag2 ) );

	CheckEqual( 2, funcList.GetSize() );

	funcList();

	Check( testClass.GetFlag1() );
	Check( testClass.GetFlag2() );

	testClass.ClearFlags();
	testClass.SetRetFlag1( false );

	funcList();

	Check( testClass.GetFlag1() );
	Check( testClass.GetFlag2() );
	CheckEqual( 1, funcList.GetSize() );

	testClass.ClearFlags();
	testClass.SetRetFlag2( false );

	funcList();

	Check( !testClass.GetFlag1() );
	Check( testClass.GetFlag2() );
	Check( funcList.IsEmpty() );

	testClass.ClearFlags();

	funcList();

	Check( !testClass.GetFlag1() );
	Check( !testClass.GetFlag2() );
}

TestCase( SetDefaultFunctionTest )
{
	TestClass testClass;
	testClass.SetDefaultFuncRetFlag( true );
	testClass.ClearDefaultFuncFlag();

	Util::FunctionList funcList;
	typedef Util::FunctionList::Delegate Delegate;
	funcList.SetDefaultFunction( Delegate( &testClass, &TestClass::DefaultFunc ) );

	Check( funcList.IsEmpty() );
	funcList();

	Check( testClass.GetDefaultFuncFlag() );

	testClass.SetDefaultFuncRetFlag( false );

	funcList();
	testClass.ClearDefaultFuncFlag();
	funcList();

	Check( !testClass.GetDefaultFuncFlag() );

	testClass.ClearDefaultFuncFlag();
	testClass.SetDefaultFuncRetFlag( true );
	testClass.SetRetFlag1( true );
	funcList.Add( Delegate( &testClass, &TestClass::SetFlag1 ) );
	funcList.SetDefaultFunction( Delegate( &testClass, &TestClass::DefaultFunc ) );

	funcList();

	Check( !testClass.GetDefaultFuncFlag() );

	funcList.SetDefaultFunction( Delegate( &testClass, &TestClass::DefaultFunc ), false );

	funcList();

	Check( testClass.GetDefaultFuncFlag() );

	testClass.SetDefaultFuncRetFlag( false );

	funcList();
	testClass.ClearDefaultFuncFlag();
	funcList();

	Check( !testClass.GetDefaultFuncFlag() );
}


TestSuiteEnd()