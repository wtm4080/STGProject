#include "PCH.h"
#include "DeviceOfDynamicFile.h"

using namespace Game;
using namespace Util::File;
using namespace Detail;
using namespace std;


streamsize DeviceOfDynamicFile::read( char *s, streamsize n )
{
	streamsize amount = static_cast<streamsize>( mpFile->GetSize() - mPos );
	streamsize result = min( n, amount );

	if( result != 0 )
	{
		copy( mpFile->GetBegin() + mPos, mpFile->GetBegin() + static_cast<int>( mPos + result ), s );

		mPos += static_cast<IDynamicFile::Size>( result );

		return result;
	}
	else
	{
		return -1;
	}
}

streamsize DeviceOfDynamicFile::write( const char *s, streamsize n )
{
	mpFile->Write( reinterpret_cast<const unsigned char *>( s ), 
		static_cast<IDynamicFile::Size>( n ), 
		mPos );

	return n;
}

DeviceOfDynamicFile::stream_offset 
DeviceOfDynamicFile::seek( stream_offset off, ios_base::seekdir way )
{
	stream_offset nextPos;
	switch( way )
	{
	case ios_base::beg:
		nextPos = off;
		break;
	case ios_base::cur:
		nextPos = mPos + off;
		break;
	case ios_base::end:
		nextPos = mpFile->GetSize() + off - 1;
		break;
	default:
		throw ios_base::failure( "bad seek direction" );
		break;
	}

	if( nextPos < 0 || nextPos >= static_cast<stream_offset>( mpFile->GetSize() ) )
	{
		throw ios_base::failure( "bad seek offset" );
	}

	mPos = static_cast<IDynamicFile::Size>( nextPos );

	return mPos;
}

DeviceOfDynamicFile::DeviceOfDynamicFile( Util::Ptr<IDynamicFile>::Shared p )
: mpFile( p )
, mPos( 0 )
{
}