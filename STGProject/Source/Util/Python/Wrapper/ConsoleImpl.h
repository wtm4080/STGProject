#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IConsole.h"
#include "Util/Console.h"


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
	class ConsoleImpl
		: public IConsole
	{
	public:
		// コンソールウィンドウを作成する
		virtual bool Create() const
		{
			return Util::Console::Create();
		}
		// コンソールウィンドウに書き込む
		virtual bool Write( const std::wstring &str ) const
		{
			return Util::Console::Write( str );
		}
		virtual bool WriteLine( const std::wstring &str ) const
		{
			return Util::Console::WriteLine( str );
		}
		// コンソールを破棄する
		virtual bool Delete() const
		{
			return Util::Console::Delete();
		}
	};
}
}
}
}