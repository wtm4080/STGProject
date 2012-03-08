#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Common.h"
#include "Util/Exception.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Font
{
namespace Exception
{
	// フォントのインスタンスの生成に失敗した
	class Invalid
		: public Exception
	{
	public:
		// コンストラクタ
		Invalid( const std::wstring &name )
		{
			Exception::AddErrorInfo( L"\nフォント \"" + 
				name + 
				L"\" の生成に失敗しました\n" );
		}
		Invalid( const std::list<std::wstring> &names )
		{
			std::wstring info = L"\nフォント\n";

			foreach( const std::wstring &name, names )
			{
				info += L"\t\"" + name + L"\"\n";
			}

			info += L"の生成に失敗しました\n";

			Exception::AddErrorInfo( info );
		}

		// エラーメッセージボックスで表示する文字列の取得
		virtual std::wstring GetErrorMessageBoxInfo()
		{
			return L"InvalidFontException";
		}
	};
}
}
}
}