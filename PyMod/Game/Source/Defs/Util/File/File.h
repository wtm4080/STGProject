#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <stdint.h>
#include "Fwd.h"
#include "FileObject.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace File
{
	class File
	{
	public:
		static void Configurate();

		static void _setInstance( uintptr_t p );

		// 1つのファイルを読み込む
		static boost::python::object open( const std::wstring &filePath );
		static boost::python::object open( const std::wstring &filePath, 
			bool cache );
		static boost::python::object open( const std::wstring &filePath, 
			bool cache, bool throwException );
		// 1つのファイルを非同期で読み込む
		static boost::python::object openASync( const std::wstring &filePath );
		static boost::python::object openASync( const std::wstring &filePath, 
			bool cache );
		static boost::python::object openASync( const std::wstring &filePath, 
			bool cache, bool throwException );

		// キャッシュサイズの取得
		static unsigned getCacheSize();
		// 最大キャッシュサイズの取得
		static unsigned getMaxCacheSize();
		// 最大キャッシュサイズの設定
		static void setMaxCacheSize( unsigned size );

		// キャッシュの消去
		static void eraseCache( const std::wstring &path );
		// キャッシュの全クリア
		static void clearCache();
	};
}
}
}