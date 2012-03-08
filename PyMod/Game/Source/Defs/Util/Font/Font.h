#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Wrapper.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Font
{
	class Font
	{
	public:
		static void Configurate();

		static void _setInstance( uintptr_t p );
		static Wrapper load( const std::wstring &path );
	};
}
}
}