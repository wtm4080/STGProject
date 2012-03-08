#include "PCH.h"
#include "TestCommon.h"

using namespace Game;
using namespace std;


TestSuite( PagerTest )


TestCase( ConstructorTest )
{
	Util::Pager<int> pager1( 5 );
	Check( pager1.GetElemCollection().empty() );
	CheckEqual( 5, pager1.GetPageSize() );

	vector<int> v;
	v.push_back( 0 );
	v.push_back( 1 );
	v.push_back( 2 );
	Util::Pager<int> pager2( 10, v.begin(), v.end() );
	CheckEqualCollection( v.begin(), v.end(), 
		pager2.GetElemCollection().begin(), pager2.GetElemCollection().end() );
	CheckEqual( 10, pager2.GetPageSize() );

	Util::Pager<int> pager3( 0 );
	Check( pager3.GetPageSize() != 0 );

	Util::Pager<int> pager4( 0, v.begin(), v.end() );
	Check( pager4.GetPageSize() != 0 );
}


TestCase( SetPageSizeTest )
{
	Util::Pager<int> pager1( 1 );
	pager1.SetPageSize( 5 );
	CheckEqual( 5, pager1.GetPageSize() );

	Util::Pager<int> pager2( 1 );
	pager2.SetPageSize( 0 );
	Check( pager2.GetPageSize() != 0 );
}


TestCase( GetPageNumTest )
{
	Util::Pager<int> pager( 3 );
	for( int i = 0; i < 20; i++ )
	{
		pager.GetElemCollection().push_back( i );
	}

	CheckEqual( 7, pager.GetPageNum() );

	pager.SetPageSize( 1 );
	CheckEqual( 20, pager.GetPageNum() );

	pager.SetPageSize( 50 );
	CheckEqual( 1, pager.GetPageNum() );

	pager.GetElemCollection().clear();
	CheckEqual( 0, pager.GetPageNum() );
}


TestCase( GetPageTest )
{
	Util::Pager<int> pager( 3 );
	for( int i = 0; i < 20; i++ )
	{
		pager.GetElemCollection().push_back( i );
	}

	Util::Pager<int>::PageLocator pageLocator = 
		pager.GetPage( 4 );
	CheckEqual( 12, *pageLocator.first );
	CheckEqual( 15, *pageLocator.second );

	pageLocator = pager.GetPage( 0 );
	CheckEqual( 0, *pageLocator.first );
	CheckEqual( 3, *pageLocator.second );

	pageLocator = pager.GetPage( 6 );
	CheckEqual( 18, *pageLocator.first );
	Check( pager.GetElemCollection().end() == pageLocator.second );

	pageLocator = pager.GetPage( 7 );
	Check( pager.GetElemCollection().end() == pageLocator.first );
	Check( pager.GetElemCollection().end() == pageLocator.second );


	const Util::Pager<int> constPager( pager );

	Util::Pager<int>::ConstPageLocator constPageLocator = 
		constPager.GetPage( 4 );
	CheckEqual( 12, *constPageLocator.first );
	CheckEqual( 15, *constPageLocator.second );

	constPageLocator = constPager.GetPage( 0 );
	CheckEqual( 0, *constPageLocator.first );
	CheckEqual( 3, *constPageLocator.second );

	constPageLocator = constPager.GetPage( 6 );
	CheckEqual( 18, *constPageLocator.first );
	Check( constPager.GetElemCollection().end() == constPageLocator.second );

	constPageLocator = constPager.GetPage( 7 );
	Check( constPager.GetElemCollection().end() == constPageLocator.first );
	Check( constPager.GetElemCollection().end() == constPageLocator.second );
}


TestSuiteEnd()