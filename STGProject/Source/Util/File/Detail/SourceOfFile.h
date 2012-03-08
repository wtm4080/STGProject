#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <boost/iostreams/concepts.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace File
{
namespace Detail
{
	class SourceOfFile
		: public boost::iostreams::source
	{
	public:
		std::streamsize read( char *s, std::streamsize n );

		SourceOfFile( PFile p );

	private:
		PFile mpFile;
		Selene::Sint32 mPos;
	};
}
}
}
}