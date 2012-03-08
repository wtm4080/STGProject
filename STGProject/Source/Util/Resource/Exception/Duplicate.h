#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Exception.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Resource
{
namespace Exception
{
	// リソースを追加しようとしたときに、すでに同じ名前のリソースが存在している
	class Duplicate
		: public Exception
	{
	public:
		// コンストラクタ
		Duplicate( const std::wstring &resourceName )
		{
			Exception::AddErrorInfo( std::wstring( L"リソース \"" ) + 
				resourceName + 
				std::wstring( L"\" は既に存在します" ) );
		}

		// エラーメッセージボックスで表示する文字列の取得
		virtual std::wstring GetErrorMessageBoxInfo()
		{
			return L"ResourceDuplicateException";
		}
	};
}
}
}
}