#include "PCH.h"
#include "SourceOfFile.h"

using namespace Game;
using namespace Util::File;
using namespace Detail;
using namespace std;


streamsize SourceOfFile::read( char *s, streamsize n )
{
	streamsize amount = static_cast<streamsize>( mpFile->GetSize() - mPos );
	streamsize result = min( n, amount );

	if( result != 0 )
	{
		copy( static_cast<const char *>( mpFile->GetData() ) + mPos, 
			static_cast<const char *>( mpFile->GetData() ) + mPos + result, 
			s );

		mPos += static_cast<Selene::Sint32>( result );

		return result;
	}
	else
	{
		return -1;
	}
}


SourceOfFile::SourceOfFile( PFile p )
: mpFile( p )
, mPos( 0 )
{
}