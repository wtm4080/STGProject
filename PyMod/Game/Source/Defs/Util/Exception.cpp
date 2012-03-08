#include "PCH.h"
#include "Exception.h"

#include "Console.h"
#include "Util/Exception.h"

using namespace boost::python;
using namespace Defs::Util;

namespace
{
	void TranslateException( Game::Util::Exception const &e )
	{
		PyErr_SetString( PyExc_RuntimeError, 
			( "...\n\n" + boost::diagnostic_information( e ) ).c_str() );
	}
}


void Exception::Configurate()
{
	register_exception_translator<Game::Util::Exception>( &TranslateException );
}