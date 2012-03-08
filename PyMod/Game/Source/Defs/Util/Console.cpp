#include "PCH.h"
#include "Console.h"

#include "Util/Python/Wrapper/IConsole.h"

using namespace boost::python;
using namespace Game;
using namespace Util::Python::Wrapper;
using namespace Defs::Util;

namespace
{
	IConsole *pConsole;

	class StdOut
	{
	public:
		static void write( const std::wstring &str )
		{
			Console::write( str );
		}
	};
}


void Console::Configurate()
{
	class_<Console>( "Console", no_init )
		.def( "_setInstance", &Console::_setInstance )
		.def( "create", &Console::create )
		.def( "write", &Console::write )
		.def( "writeLine", &Console::writeLine )
		.def( "delete", &Console::_delete )
		;

	class_<StdOut>( "stdout" )
		.def( "write", &StdOut::write )
		;
}


void Console::_setInstance( uintptr_t p )
{
	pConsole = reinterpret_cast<IConsole *>( p );
}

bool Console::create()
{
	return pConsole->Create();
}

bool Console::write( const std::wstring &str )
{
	return pConsole->Write( str );
}

bool Console::writeLine( const std::wstring &str )
{
	return pConsole->WriteLine( str );
}

bool Console::_delete()
{
	return pConsole->Delete();
}