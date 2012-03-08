#include "PCH.h"
#include "TestCommon.h"

using namespace Game;
using namespace std;


TestSuite( TokenizeTest )


TestCase( StdStringTokenizeTest )
{
	string src( "token1,token2..token3" );
	string delims( ",." );

	vector<string> resultList;
	Util::Tokenize( src, delims, resultList );

	CheckEqual( 4, resultList.size() );
	CheckEqual( "token1", resultList.at( 0 ) );
	CheckEqual( "token2", resultList.at( 1 ) );
	CheckEqual( "", resultList.at( 2 ) );
	CheckEqual( "token3", resultList.at( 3 ) );
}


TestCase( StdWStringTokenizeTest )
{
	wstring src( L"token1,token2..token3" );
	wstring delims( L",." );

	vector<wstring> resultList;
	Util::Tokenize( src, delims, resultList );

	CheckEqual( 4, resultList.size() );
	// wchar_tはテストでは使えないっぽい
	CheckEqual( "token1", Util::ToMultiByte( resultList.at( 0 ) ) );
	CheckEqual( "token2", Util::ToMultiByte( resultList.at( 1 ) ) );
	CheckEqual( "", Util::ToMultiByte( resultList.at( 2 ) ) );
	CheckEqual( "token3", Util::ToMultiByte( resultList.at( 3 ) ) );
}


TestSuiteEnd()