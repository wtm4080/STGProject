#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <vector>


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
	class IFont
	{
	public:
		// フォントデータの読み込み
		// fontFilePathには、SFFファイルのパスを指定すること
		virtual Font::PFont LoadFont( const std::wstring &fontFilePath ) const = 0;

		virtual ~IFont() {}
	};
}
}
}
}