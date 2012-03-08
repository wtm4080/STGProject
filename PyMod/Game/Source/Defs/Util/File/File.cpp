#include "PCH.h"
#include "File.h"

#include "Util/Python/Wrapper/IFile.h"

using namespace boost::python;
using namespace Defs::Util::File;
using namespace std;

namespace
{
	typedef Game::Util::Python::Wrapper::IFile IFile;
	IFile *pFile;
}


void File::Configurate()
{
	class_<File>( "File", no_init )
		.def( "_setInstance", &File::_setInstance )
		.def( "open", static_cast<object (*)( const wstring & )>( &File::open ) )
		.def( "open", static_cast<object (*)( const wstring &, bool )>( &File::open ) )
		.def( "open", static_cast<object (*)( const wstring &, bool, bool )>( &File::open ) )
		.def( "openASync", static_cast<object (*)( const wstring & )>( &File::openASync ) )
		.def( "openASync", static_cast<object (*)( const wstring &, bool )>( &File::openASync ) )
		.def( "openASync", static_cast<object (*)( const wstring &, bool, bool )>( &File::openASync ) )
		.def( "getCacheSize", &File::getCacheSize )
		.def( "getMaxCacheSize", &File::getMaxCacheSize )
		.def( "setMaxCacheSize", &File::setMaxCacheSize )
		.def( "eraseCache", &File::eraseCache )
		.def( "clearCache", &File::clearCache )
		;

	class_<FileObject>( "FileObject", no_init )
		.add_property( "loaded", &FileObject::IsLoaded )
		.add_property( "fileName", &FileObject::GetFileName )
		.add_property( "size", &FileObject::GetSize )
		;
}


void File::_setInstance( uintptr_t p )
{
	pFile = reinterpret_cast<IFile *>( p );
}


object File::open( const wstring &filePath )
{
	return open( filePath, true, true );
}

object File::open( const wstring &filePath, bool cache )
{
	return open( filePath, cache, true );
}

object File::open( const wstring &filePath, bool cache, bool throwException )
{
	auto file = pFile->Open( filePath, cache, throwException );

	if( file )
	{
		return object( FileObject( file ) );
	}
	else
	{
		return object();
	}
}

object File::openASync( const wstring &filePath )
{
	return openASync( filePath, true, true );
}

object File::openASync( const wstring &filePath, bool cache )
{
	return openASync( filePath, cache, true );
}

object File::openASync( const wstring &filePath, bool cache, bool throwException )
{
	auto file = pFile->OpenASync( filePath, cache, throwException );

	if( file )
	{
		return object( FileObject( file ) );
	}
	else
	{
		return object();
	}
}


unsigned File::getCacheSize()
{
	return pFile->GetCacheSize();
}

unsigned File::getMaxCacheSize()
{
	return pFile->GetMaxCacheSize();
}

void File::setMaxCacheSize( unsigned size )
{
	pFile->SetMaxCacheSize( size );
}


void File::eraseCache( const wstring &path )
{
	pFile->EraseCache( path );
}

void File::clearCache()
{
	pFile->ClearCache();
}