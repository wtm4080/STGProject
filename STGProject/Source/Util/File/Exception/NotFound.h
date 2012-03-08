#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Exception.h"
#include "Util/Common.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace File
{
namespace Exception
{
	// 開こうとしたファイルが存在しない
	class NotFound
		: public Exception
	{
	public:
		// コンストラクタ
		NotFound( const std::wstring &filePath )
		{
			Exception::AddErrorInfo( L"\nファイル \"" + 
				filePath + 
				L"\" を開けませんでした\n" );
		}
		NotFound( const std::list<std::wstring> &filePathList )
		{
			std::wstring info = L"\nファイル\n";

			foreach( const std::wstring &path, filePathList )
			{
				info += L"\t\"" + path + L"\"\n";
			}

			info += L"を開けませんでした\n";

			Exception::AddErrorInfo( info );
		}

		// エラーメッセージボックスで表示する文字列の取得
		virtual std::wstring GetErrorMessageBoxInfo()
		{
			return L"FileNotFoundException";
		}
	};
}
}
}
}