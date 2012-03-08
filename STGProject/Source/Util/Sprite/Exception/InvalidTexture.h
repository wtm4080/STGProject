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
namespace Sprite
{
namespace Exception
{
	// テクスチャのインスタンスの生成に失敗した
	class InvalidTexture
		: public Exception
	{
	public:
		// コンストラクタ
		InvalidTexture( const std::wstring &name )
		{
			Exception::AddErrorInfo( L"\nテクスチャ \"" + 
				name + 
				L"\" の生成に失敗しました\n" );
		}
		InvalidTexture( const std::list<std::wstring> &names )
		{
			std::wstring info = L"\nテクスチャ\n";

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
			return L"InvalidTextureException";
		}
	};
}
}
}
}