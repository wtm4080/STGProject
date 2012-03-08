#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"


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
	class Cache
	{
	public:
		static PFile Get( const std::wstring &path );
		static void Put( const std::wstring &path, PFile pFile );

		static unsigned GetSize();
		static unsigned GetMaxSize();
		static void SetMaxSize( unsigned size );

		static void Erase( const std::wstring &path );
		static void Clear();
	};
}
}
}
}