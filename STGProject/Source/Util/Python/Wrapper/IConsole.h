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
namespace Python
{
namespace Wrapper
{
	class IConsole
	{
	public:
		// コンソールウィンドウを作成する
		virtual bool Create() const = 0;
		// コンソールウィンドウに書き込む
		virtual bool Write( const std::wstring &str ) const = 0;
		virtual bool WriteLine( const std::wstring &str ) const = 0;
		// コンソールを破棄する
		virtual bool Delete() const = 0;

		virtual ~IConsole() {}
	};
}
}
}
}