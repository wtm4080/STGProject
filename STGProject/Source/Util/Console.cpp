#include "PCH.h"
#include "Console.h"
#include <iostream>

using namespace Game;
using namespace std;

namespace
{
	// すでに作成されているかどうか
	static bool mIsCreated = false;
}


// コンソールウィンドウを作成する
bool Util::Console::Create()
{
	if( !mIsCreated )
	{
		if( AllocConsole() != 0 )
		{
			mIsCreated = true;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

// コンソールウィンドウに書き込む
bool Util::Console::Write( const wstring &str )
{
	Create();

	wcout << str;
	flushall();

	DWORD writtenSize;
	if( WriteConsole( 
		GetStdHandle( STD_OUTPUT_HANDLE ), 
		str.c_str(), static_cast<DWORD>( str.size() ), &writtenSize, NULL ) != 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Util::Console::WriteLine( const wstring &str )
{
	return Write( str + L"\n" );
}

// コンソールを破棄する
bool Util::Console::Delete()
{
	if( mIsCreated )
	{
		if( FreeConsole() != 0 )
		{
			mIsCreated = false;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}