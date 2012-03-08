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
namespace Ctrl
{
namespace STG
{
namespace Option
{
namespace Detail
{
	class SettingFile
	{
	public:
		// 設定ファイルを読み込む
		static void Read( const std::string &path, Parameter &param );
		// 設定ファイルを書き込む
		static void Write( const std::string &path, const Parameter &param );
	};
}
}
}
}
}