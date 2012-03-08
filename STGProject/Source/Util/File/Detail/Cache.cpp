#include "PCH.h"
#include "Cache.h"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

using namespace Game;
using namespace Util::File;
using namespace Detail;
using namespace std;
using namespace boost::multi_index;

namespace
{
	static const unsigned DEFAULT_MAX_SIZE = 1024 * 1024 * 100;
	static unsigned maxSize = DEFAULT_MAX_SIZE;

	struct Elem
	{
		wstring mPath;
		PFile mpFile;

		Elem( const wstring &path, PFile pFile )
			: mPath( path )
			, mpFile( pFile )
		{}

		bool operator < ( const Elem &elem ) const
		{
			return mpFile->GetSize() < elem.mpFile->GetSize();
		}
	};

	typedef multi_index_container<Elem, 
		indexed_by<
			hashed_unique<member<Elem, wstring, &Elem::mPath>>, 
			ordered_non_unique<boost::multi_index::identity<Elem>>
		>> Container;
	enum CONTAINER_INDEX
	{
		IDX_PATH, 
		IDX_SIZE, 
	};
	typedef Container::nth_index<IDX_PATH>::type PathContainer;
	typedef Container::nth_index<IDX_SIZE>::type SizeContainer;

	static Container container;

	static void Adjust()
	{
		SizeContainer &con = container.get<IDX_SIZE>();

		for( unsigned size = Cache::GetSize(); 
			size > maxSize; 
			size = Cache::GetSize() )
		{
			con.erase( --con.end() );
		}
	}
}


PFile Cache::Get( const wstring &path )
{
	PathContainer &con = container.get<IDX_PATH>();

	PathContainer::iterator itr = con.find( path );

	if( itr != con.end() )
	{
		return itr->mpFile;
	}
	else
	{
		return PFile();
	}
}

void Cache::Put( const wstring &path, PFile pFile )
{
	if( pFile )
	{
		container.get<IDX_PATH>().insert( Elem( path, pFile ) );

		Adjust();
	}
}


unsigned Cache::GetSize()
{
	unsigned size = 0;

	foreach( const Elem &elem, container.get<IDX_SIZE>() )
	{
		size += elem.mpFile->GetSize();
	}

	return size;
}

unsigned Cache::GetMaxSize()
{
	return maxSize;
}

void Cache::SetMaxSize( unsigned size )
{
	maxSize = size;

	Adjust();
}


void Cache::Erase( const wstring &path )
{
	PathContainer &con = container.get<IDX_PATH>();

	PathContainer::iterator itr = con.find( path );

	if( itr != con.end() )
	{
		con.erase( itr );
	}
}

void Cache::Clear()
{
	container.get<IDX_PATH>().clear();
}