#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <bulletmlparser.h>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace BulletML
{
	class BulletML
	{
	public:
		static void Configurate();

		typedef Game::Util::Ptr<BulletMLParser>::Shared PBMLParser;
		static PBMLParser createParser( const std::wstring &path );
	};
}
}
}