#include "PCH.h"
#include "TestCommon.h"

using namespace Game;


TestSuite( FunctionQueueTest )


class FuncClass
{
public:
	FuncClass()
		: state( 0 )
	{}

	int GetState() const
	{
		return state;
	}

	bool F1()
	{
		if( state != 1 )
		{
			state = 1;

			return true;
		}

		return false;
	}

	bool F2()
	{
		if( state != 2 )
		{
			state = 2;

			return true;
		}

		return false;
	}

	bool F3()
	{
		if( state != 3 )
		{
			state = 3;

			return true;
		}

		return false;
	}

	bool SetDefFlag()
	{
		defFlag = true;

		return defRetFlag;
	}
	bool GetDefFlag() const { return defFlag; }
	void ClearDefFlag() { defFlag = false; }
	void SetDefRetFlag( bool flag ) { defRetFlag = flag; }

private:
	int state;

	bool defFlag, defRetFlag;
};


TestCase( CallTest )
{
	FuncClass fClass;
	Util::FunctionQueue fQueue;
	typedef Util::FunctionQueue::Delegate Delegate;

	CheckEqual( 0, fClass.GetState() );
	Check( fQueue.IsEmpty() );

	fQueue.Push( Delegate( &fClass, &FuncClass::F1 ) );
	fQueue.Push( Delegate( &fClass, &FuncClass::F2 ) );
	fQueue.Push( Delegate( &fClass, &FuncClass::F3 ) );

	CheckEqual( 3, fQueue.GetSize() );

	fQueue();
	CheckEqual( 1, fClass.GetState() );
	CheckEqual( 3, fQueue.GetSize() );

	fQueue();
	CheckEqual( 1, fClass.GetState() );
	CheckEqual( 2, fQueue.GetSize() );

	fQueue();
	CheckEqual( 2, fClass.GetState() );
	CheckEqual( 2, fQueue.GetSize() );

	fQueue();
	CheckEqual( 2, fClass.GetState() );
	CheckEqual( 1, fQueue.GetSize() );

	fQueue();
	CheckEqual( 3, fClass.GetState() );
	CheckEqual( 1, fQueue.GetSize() );

	fQueue();
	CheckEqual( 3, fClass.GetState() );
	CheckEqual( 0, fQueue.GetSize() );

	fQueue();
	CheckEqual( 3, fClass.GetState() );
	CheckEqual( 0, fQueue.GetSize() );
}

TestCase( SetDefaultFunctionTest )
{
	FuncClass fClass;
	fClass.ClearDefFlag();
	fClass.SetDefRetFlag( true );
	Util::FunctionQueue fQueue;
	typedef Util::FunctionQueue::Delegate Delegate;
	fQueue.SetDefaultFunction( Delegate( &fClass, &FuncClass::SetDefFlag ) );

	fQueue();

	Check( fClass.GetDefFlag() );

	fClass.SetDefRetFlag( false );

	fQueue();
	fClass.ClearDefFlag();
	fQueue();

	Check( !fClass.GetDefFlag() );

	fClass.ClearDefFlag();
	fClass.SetDefRetFlag( true );
	fQueue.SetDefaultFunction( Delegate( &fClass, &FuncClass::SetDefFlag ) );
	fQueue.Push( Delegate( &fClass, &FuncClass::F1 ) );

	fQueue();

	Check( !fClass.GetDefFlag() );
}


TestSuiteEnd()