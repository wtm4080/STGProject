#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <boost/noncopyable.hpp>
#include "../IDynamicFile.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace File
{
namespace Detail
{
	class DynamicFile
		: public IDynamicFile
		, public boost::noncopyable
	{
	public:
		// コンストラクタ
		DynamicFile( ::HMODULE hCryptModule );
		DynamicFile( ::HMODULE hCryptModule, PFile pFile );

		// 読み取り用のイテレータの取得
		virtual Iterator GetBegin() const;
		virtual Iterator GetEnd() const;
		// サイズの取得
		virtual Size GetSize() const;
		// 任意の場所に書き込み
		virtual void Write( unsigned char value, Size offset = 0 );
		virtual void Write( const unsigned char *pData, Size size, Size offset = 0 );

		// 内容に対してxor演算をする
		virtual void Xor( unsigned value );
		// 文字列のハッシュ値でxor演算をする
		virtual void Xor( const std::string &str );
		// Selene付属のCryptPluginで暗号化する
		virtual void Encrypt( const std::string &pass );
		// Selene付属のCryptPluginで復号化する
		virtual void Decrypt( const std::string &pass );

		// コピーを作成する
		virtual PDynamicFile CreateClone() const;
		// Seleneのファイルインターフェイスを作成する
		virtual PFile CreateSLNFile( const std::wstring &name ) const;

	private:
		Container mContainer;
		::HMODULE mhCryptModule;
		Selene::Plugin::File::CreateCryptInterfaceProc mCreateCryptInterface;
		typedef Ptr<Selene::Plugin::File::ICrypt>::Intrusive PCrypt;
		typedef std::map<std::string, PCrypt> CryptMap;
		CryptMap mCryptMap;

		void Init();

		PCrypt GetCrypt( const std::string &pass );
	};
}
}
}
}