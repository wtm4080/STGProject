#include "PCH.h"
#include "BulletML.h"

#include "RunnerHandler.h"

using namespace boost::python;
using namespace Game;
using namespace std;
using namespace Defs::Util::BulletML;


void BulletML::Configurate()
{
	class_<BulletMLParser, boost::noncopyable, PBMLParser>( "BulletMLParser", no_init )
		.def( "build", &BulletMLParser::build )
		;

	class_<BulletMLState, BulletMLState *>( "BulletMLState", no_init )
		;

	{
		typedef RunnerHandler Handler;
		class_<Handler, boost::noncopyable>( "BulletMLHandler", 
			init<const object &, PBMLParser>() )
			.def( init<const object &, PBMLParser, BulletMLState *>() )
			.def( "run", &Handler::run )
			.def( "isEnd", &Handler::isEnd )
			.def( "getParser", &Handler::getParser )
			;
	}

	class_<BulletML>( "BulletML", no_init )
		.def( "createParser", &BulletML::createParser )
		;
}


namespace
{
	wstring ConvertPath( const wstring &pathStr )
	{
		namespace fs = boost::filesystem;

		if( fs::exists( fs::path( pathStr ) ) )
		{
			return pathStr;
		}
		else if( fs::exists( fs::path( L"../" + pathStr ) ) )
		{
			return L"../" + pathStr;
		}
		else
		{
			std::list<wstring> pathList;
			pathList.push_back( pathStr );
			pathList.push_back( L"../" + pathStr );

			THROW( Util::File::Exception::NotFound( pathList ) );
		}

		return wstring();
	}
}

BulletML::PBMLParser BulletML::createParser( const wstring &path )
{
	return PBMLParser( 
		new BulletMLParserTinyXML( 
		Game::Util::ToMultiByte( ::ConvertPath( path ) ) ) );
}