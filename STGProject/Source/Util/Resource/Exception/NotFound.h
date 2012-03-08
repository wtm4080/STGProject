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
	// 取得しようとしたリソースが見つからなかった
	class NotFound
		: public Exception
	{
	public:
		// コンストラクタ
		NotFound( const std::wstring &resourceName )
		{
			Exception::AddErrorInfo( std::wstring( L"リソース \"" ) + 
				resourceName + 
				std::wstring( L"\" は見つかりませんでした" ) );
		}

		// エラーメッセージボックスで表示する文字列の取得
		virtual std::wstring GetErrorMessageBoxInfo()
		{
			return L"ResourceNotFoundException";
		}
	};
}
}
}
}