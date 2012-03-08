#include "PCH.h"
#include "TestCommon.h"
#include "Util/Resource/Manager.h"

using namespace Game;
using namespace Util::Resource;
using namespace std::tr1;
using namespace std;


TestSuite( ResourceManagerTest )


template <class T>
class Deleter
{
public:
	void operator () ( T *p )
	{
//		cout << "The type of <" << typeid(*p).name() << "> has deleted." << endl;
		delete p;
	}
};


TestCase( AddTest )
{
	Manager::Add( L"Resource", 
		shared_ptr<int>( new int(), Deleter<int>() ) );

	CheckThrow( Manager::Add( L"Resource", 
		shared_ptr<double>( new double(), Deleter<double>() ) ), 
		Exception::Duplicate );

	Manager::Clear();
}


TestCase( IsExistTest )
{
	Check( !Manager::IsExist( L"Resource" ) );

	Manager::Add( L"Resource", 
		shared_ptr<int>( new int( 0 ), Deleter<int>() ) );

	Check( Manager::IsExist( L"Resource" ) );

	Manager::Clear();
}


TestCase( GetTest )
{
	CheckThrow( Manager::Get<int>( L"Resource" ), 
		Exception::NotFound );

	shared_ptr<int> resource = shared_ptr<int>( new int( 10 ), Deleter<int>() );
	Manager::Add( L"Resource", resource );

	shared_ptr<int> getResource = Manager::Get<int>( L"Resource" );

	Check( *resource == *getResource );

	Manager::Clear();
}


TestCase( IsEmptyTest )
{
	Check( Manager::IsEmpty() );

	Manager::Add( L"Resource", 
		shared_ptr<int>( new int( 1 ), Deleter<int>() ) );

	Check( !Manager::IsEmpty() );

	Manager::Clear();
}


TestCase( EraseTest )
{
	Manager::Add( L"Resource", 
		shared_ptr<int>( new int( 1 ), Deleter<int>() ) );

	Manager::Erase( L"Resource" );

	Check( !Manager::IsExist( L"Resource" ) );

	Manager::Clear();
}


TestCase( ClearTest )
{
	Manager::Add( L"Resource1", 
		shared_ptr<int>( new int( 1 ), Deleter<int>() ) );
	Manager::Add( L"Resource2", 
		shared_ptr<int>( new int( 2 ), Deleter<int>() ) );
	Manager::Add( L"Resource3", 
		shared_ptr<int>( new int( 3 ), Deleter<int>() ) );

	Manager::Clear();

	Check( Manager::IsEmpty() );
}


TestCase( GetListTest )
{
	Manager::Add( L"Resource1", 
		shared_ptr<int>( new int( 1 ), Deleter<int>() ) );
	Manager::Add( L"Resource2", 
		shared_ptr<int>( new int( 2 ), Deleter<int>() ) );
	Manager::Add( L"Resource3", 
		shared_ptr<int>( new int( 3 ), Deleter<int>() ) );

	vector<wstring> resourceList;
	Manager::GetList( resourceList );
	sort( resourceList.begin(), resourceList.end() );

	CheckEqual( 3, resourceList.size() );
	string at0 = Game::Util::ToMultiByte( resourceList.at( 0 ) );
	CheckEqual( "Resource1", at0 );
	string at1 = Game::Util::ToMultiByte( resourceList.at( 1 ) );
	CheckEqual( "Resource2", at1 );
	string at2 = Game::Util::ToMultiByte( resourceList.at( 2 ) );
	CheckEqual( "Resource3", at2 );

	Manager::Clear();
}


TestSuiteEnd()