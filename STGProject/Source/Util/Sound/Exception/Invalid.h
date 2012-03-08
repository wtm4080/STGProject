#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <string>
#include "Util/Exception.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Sound
{
namespace Exception
{
	// サウンドのインスタンスの生成に失敗した
	class Invalid
		: public Exception
	{
	public:
		// コンストラクタ
		Invalid( const std::wstring &name )
		{
			Exception::AddErrorInfo( L"\nサウンド \"" + 
				name + 
				L"\" の生成に失敗しました\n" );
		}

		// エラーメッセージボックスで表示する文字列の取得
		virtual std::wstring GetErrorMessageBoxInfo()
		{
			return L"InvalidSoundException";
		}
	};
}
}
}
}