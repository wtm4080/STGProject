#include "PCH.h"
#include "SyncFile.h"

using namespace Game;
using namespace Util::File::Detail;
using namespace Selene;


SyncFile::SyncFile( const wchar_t *pFileName, const void *pData, Sint32 size )
: mName( pFileName )
, mpData( pData )
, mSize( size )
{
}

SyncFile::~SyncFile()
{
	Kernel::Memory::Free( mpData );
}


bool SyncFile::IsLoaded() const
{
	return true;
}

const wchar_t *SyncFile::GetFileName() const
{
	return mName.c_str();
}

Sint32 SyncFile::GetSize() const
{
	return mSize;
}

const void *SyncFile::GetData() const
{
	return mpData;
}