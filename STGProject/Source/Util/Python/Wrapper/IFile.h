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
namespace Python
{
namespace Wrapper
{
	class IFile
	{
	public:
		// 1つのファイルを読み込む
		virtual File::PFile Open( const std::wstring &filePath, 
			bool cache = true, bool throwException = true ) const = 0;
		// 1つのファイルを非同期で読み込む
		virtual File::PFile OpenASync( const std::wstring &filePath, 
			bool cache = true, bool throwException = true ) const = 0;

		// キャッシュサイズの取得
		virtual unsigned GetCacheSize() const = 0;
		// 最大キャッシュサイズの取得
		virtual unsigned GetMaxCacheSize() const = 0;
		// 最大キャッシュサイズの設定
		virtual void SetMaxCacheSize( unsigned size ) const = 0;

		// キャッシュの消去
		virtual void EraseCache( const std::wstring &path ) const = 0;
		// キャッシュの全クリア
		virtual void ClearCache() const = 0;

		virtual ~IFile() {}
	};
}
}
}
}