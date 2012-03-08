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
namespace Font
{
	// フォント関係の処理
	class Manager
	{
	public:
		// フォントデータの読み込み
		// fontFilePathには、SFFファイルのパスを指定すること
		static PFont LoadFont( const std::wstring &fontFilePath );
		static void LoadFont( const std::vector<std::wstring> &fontFilePathList, 
			FontMap &fonts );
	};
}
}
}