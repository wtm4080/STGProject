#include "PCH.h"
#include "BMLParserHolder.h"

using namespace Game;
using namespace Mdl::STG::Stage::Test::TestStage1;
using namespace std;


BMLParserHolder::BMLParserHolder()
{
	Register( BML_TEST, L"Script/BulletML/Test/TestStage1/Test.xml" );

	typedef pair<BMLParserType, PBMLParser> ElemType;
	foreach( const ElemType &elem, mParserMap )
	{
		elem.second->build();
	}
}

void BMLParserHolder::Register( BMLParserType type, const wstring &path )
{
	mParserMap[ type ] = PBMLParser( new BulletMLParserTinyXML( 
		Util::ToMultiByte( 
		Util::File::Manager::ConvertPath( path ) 
		) ) );
}


PBMLParser BMLParserHolder::GetParser( BMLParserType type ) const
{
	auto itr = mParserMap.find( type );

	if( itr != mParserMap.end() )
	{
		return itr->second;
	}
	else
	{
		return PBMLParser();
	}
}