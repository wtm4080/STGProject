#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IFont.h"
#include "Util/Font/Manager.h"


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
	class FontImpl
		: public IFont
	{
	public:
		// フォントデータの読み込み
		// fontFilePathには、SFFファイルのパスを指定すること
		virtual Font::PFont LoadFont( const std::wstring &fontFilePath ) const
		{
			return Font::Manager::LoadFont( fontFilePath );
		}
	};
}
}
}
}