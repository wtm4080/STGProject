#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
	class Console
	{
	public:
		static void Configurate();

		static void _setInstance( uintptr_t p );
		static bool create();
		static bool write( const std::wstring &str );
		static bool writeLine( const std::wstring &str );
		static bool _delete();
	};
}
}