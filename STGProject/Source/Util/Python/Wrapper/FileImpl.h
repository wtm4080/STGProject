#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/intrusive_ptr.hpp>
#include "IFile.h"
#include "Util/File/Manager.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Python
{
namespace Wrapper
{
	class FileImpl
		: public IFile
	{
	public:
		// 1つのファイルを読み込む
		virtual File::PFile Open( const std::wstring &filePath, 
			bool cache = true, bool throwException = true ) const
		{
			return File::Manager::Open( filePath, cache, throwException );
		}
		// 1つのファイルを非同期で読み込む
		virtual File::PFile OpenASync( const std::wstring &filePath, 
			bool cache = true, bool throwException = true ) const
		{
			return File::Manager::OpenASync( filePath, cache, throwException );
		}

		// キャッシュサイズの取得
		virtual unsigned GetCacheSize() const
		{
			return File::Manager::GetCacheSize();
		}
		// 最大キャッシュサイズの取得
		virtual unsigned GetMaxCacheSize() const
		{
			return File::Manager::GetMaxCacheSize();
		}
		// 最大キャッシュサイズの設定
		virtual void SetMaxCacheSize( unsigned size ) const
		{
			File::Manager::SetMaxCacheSize( size );
		}

		// キャッシュの消去
		virtual void EraseCache( const std::wstring &path ) const
		{
			File::Manager::EraseCache( path );
		}
		// キャッシュの全クリア
		virtual void ClearCache() const
		{
			File::Manager::ClearCache();
		}
	};
}
}
}
}