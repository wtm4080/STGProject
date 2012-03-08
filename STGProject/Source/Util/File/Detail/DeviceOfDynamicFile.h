#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <boost/iostreams/concepts.hpp>
#include "../IDynamicFile.h"


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
	class DeviceOfDynamicFile
		: public boost::iostreams::device<boost::iostreams::seekable>
	{
	public:
		std::streamsize read( char *s, std::streamsize n );
		std::streamsize write( const char *s, std::streamsize n );
		typedef boost::iostreams::stream_offset stream_offset;
		stream_offset seek( stream_offset off, std::ios_base::seekdir way );

		DeviceOfDynamicFile( Ptr<IDynamicFile>::Shared p );

	private:
		Ptr<IDynamicFile>::Shared mpFile;
		IDynamicFile::Size mPos;
	};
}
}
}
}