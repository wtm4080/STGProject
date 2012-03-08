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
namespace File
{
	class IDynamicFile
	{
	public:
		typedef std::vector<unsigned char> Container;
		typedef Container::const_iterator Iterator;
		typedef Container::size_type Size;

		// 読み取り用のイテレータの取得
		virtual Iterator GetBegin() const = 0;
		virtual Iterator GetEnd() const = 0;
		// サイズの取得
		virtual Size GetSize() const = 0;
		// 任意の場所に書き込み
		virtual void Write( unsigned char value, Size offset = 0 ) = 0;
		virtual void Write( const unsigned char *pData, Size size, Size offset = 0 ) = 0;

		// 内容に対してxor演算をする
		virtual void Xor( unsigned value ) = 0;
		// 文字列のハッシュ値でxor演算をする
		virtual void Xor( const std::string &str ) = 0;
		// Selene付属のCryptPluginで暗号化する
		virtual void Encrypt( const std::string &pass ) = 0;
		// Selene付属のCryptPluginで復号化する
		virtual void Decrypt( const std::string &pass ) = 0;

		// コピーを作成する
		typedef Ptr<IDynamicFile>::Shared PDynamicFile;
		virtual PDynamicFile CreateClone() const = 0;
		// Seleneのファイルインターフェイスを作成する
		virtual PFile CreateSLNFile( const std::wstring &name ) const = 0;

		// デストラクタ
		virtual ~IDynamicFile() {}
	};
}
}
}