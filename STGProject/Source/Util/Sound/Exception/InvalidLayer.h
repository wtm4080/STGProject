#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <string>
#include <boost/lexical_cast.hpp>
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
	// 無効なStaticSoundのレイヤー番号を指定した
	class InvalidLayer
		: public Exception
	{
	public:
		// コンストラクタ
		InvalidLayer( const std::wstring &name, Selene::Uint32 layer )
		{
			Exception::AddErrorInfo( L"\nStaticSound \"" + 
				name + 
				L"\" のレイヤー \"" + 
				boost::lexical_cast<std::wstring>( layer ) + 
				L"\" は無効です\n" );
		}

		// エラーメッセージボックスで表示する文字列の取得
		virtual std::wstring GetErrorMessageBoxInfo()
		{
			return L"InvalidSoundLayerException";
		}
	};
}
}
}
}