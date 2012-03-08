#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <bulletmlparser.h>
#include <map>
#include "BMLParserType.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Stage
{
namespace Test
{
namespace TestStage1
{
	typedef Util::Ptr<BulletMLParser>::Shared PBMLParser;

	class BMLParserHolder
	{
	public:
		BMLParserHolder();

		PBMLParser GetParser( BMLParserType type ) const;

	private:
		typedef std::map<BMLParserType, PBMLParser> BMLParserMap;
		BMLParserMap mParserMap;

		void Register( BMLParserType type, const std::wstring &path );
	};
}
}
}
}
}
}