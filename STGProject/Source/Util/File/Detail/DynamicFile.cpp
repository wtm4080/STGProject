#include "PCH.h"
#include "DynamicFile.h"
#include "SyncFile.h"
#include "ICrypt.h"

#pragma warning( disable:4996 )

using namespace Game;
using namespace Util::File;
using namespace Detail;
using namespace Selene;
using namespace std;


// コンストラクタ
DynamicFile::DynamicFile( HMODULE hCryptModule )
: mContainer()
, mhCryptModule( hCryptModule )
, mCreateCryptInterface( NULL )
, mCryptMap()
{
	Init();
}

DynamicFile::DynamicFile( HMODULE hCryptModule, PFile pFile )
: mContainer()
, mhCryptModule( hCryptModule )
, mCreateCryptInterface( NULL )
, mCryptMap()
{
	Init();

	if( pFile )
	{
		const unsigned char *pData = 
			static_cast<const unsigned char *>( pFile->GetData() );
		copy( pData, pData + pFile->GetSize(), back_inserter( mContainer ) );
	}
}

void DynamicFile::Init()
{
	void *pFunction = ::GetProcAddress( mhCryptModule, "CreateCryptInterface" );
	mCreateCryptInterface = 
		static_cast<Plugin::File::CreateCryptInterfaceProc>( pFunction );
}


// 読み取り用のイテレータの取得
DynamicFile::Iterator DynamicFile::GetBegin() const
{
	return mContainer.begin();
}

DynamicFile::Iterator DynamicFile::GetEnd() const
{
	return mContainer.end();
}

// サイズの取得
DynamicFile::Size DynamicFile::GetSize() const
{
	return mContainer.size();
}

// 任意の場所に書き込み
void DynamicFile::Write( unsigned char value, Size offset )
{
	if( offset < mContainer.size() )
	{
		mContainer.at( offset ) = value;
	}
	else
	{
		for( Size i = 0; i < offset - mContainer.size(); i++ )
		{
			mContainer.push_back( 0 );
		}

		mContainer.push_back( value );
	}
}

void DynamicFile::Write( const unsigned char *pData, Size size, Size offset )
{
	for( Size i = 0; i < size; i++ )
	{
		Write( *( pData + i ), i + offset );
	}
}


// 内容に対してxor演算をする
void DynamicFile::Xor( unsigned value )
{
	static const unsigned ANDMASK_1 = 0x000000ff;
	static const unsigned ANDMASK_2 = 0x0000ff00;
	static const unsigned ANDMASK_3 = 0x00ff0000;
	static const unsigned ANDMASK_4 = 0xff000000;

	using boost::numeric_cast;
	const unsigned char v1 = 
		numeric_cast<unsigned char>( value & ANDMASK_1 );
	const unsigned char v2 = 
		numeric_cast<unsigned char>( ( value & ANDMASK_2 ) >> 8 );
	const unsigned char v3 = 
		numeric_cast<unsigned char>( ( value & ANDMASK_3 ) >> 8 * 2 );
	const unsigned char v4 = 
		numeric_cast<unsigned char>( ( value & ANDMASK_4 ) >> 8 * 3 );

	unsigned rotation = 0;
	for( Size i = 0; i < mContainer.size(); i++ )
	{
		switch( rotation )
		{
		case 0:
			mContainer.at( i ) ^= v1;
			rotation++;
			break;
		case 1:
			mContainer.at( i ) ^= v2;
			rotation++;
			break;
		case 2:
			mContainer.at( i ) ^= v3;
			rotation++;
			break;
		case 3:
			mContainer.at( i ) ^= v4;
			rotation = 0;
			break;
		default:
			assert( false );
			break;
		}
	}
}

// 文字列のハッシュ値でxor演算をする
void DynamicFile::Xor( const string &str )
{
	boost::hash<string> sHash;

	Xor( static_cast<unsigned>( sHash( str ) ) );
}

// intrusive_ptrの参照カウンタ操作用関数
void intrusive_ptr_add_ref( Plugin::File::ICrypt *p )
{
}
void intrusive_ptr_release( Plugin::File::ICrypt *p )
{
	SAFE_RELEASE( p );
}

// Selene付属のCryptPluginで暗号化する
DynamicFile::PCrypt DynamicFile::GetCrypt( const string &pass )
{
	CryptMap::const_iterator itr = mCryptMap.find( pass );

	PCrypt pCrypt;
	if( itr != mCryptMap.end() )
	{
		pCrypt = itr->second;
	}
	else
	{
		pCrypt = PCrypt( mCreateCryptInterface( pass.c_str() ) );

		mCryptMap[ pass ] = pCrypt;
	}

	return pCrypt;
}
void DynamicFile::Encrypt( const std::string &pass )
{
	PCrypt pCrypt = GetCrypt( pass );

	if( pCrypt )
	{
		boost::scoped_array<unsigned char> 
			pBufIn( new unsigned char[ mContainer.size() ] ), 
			pBufOut( new unsigned char[ mContainer.size() ] );

		copy( mContainer.begin(), mContainer.end(), pBufIn.get() );

		pCrypt->Encrypt( pBufIn.get(), pBufOut.get(), 
			static_cast<unsigned long>( mContainer.size() ), 0 );

		copy( pBufOut.get(), pBufOut.get() + mContainer.size(), mContainer.begin() );
	}
}

// Selene付属のCryptPluginで復号化する
void DynamicFile::Decrypt( const std::string &pass )
{
	PCrypt pCrypt = GetCrypt( pass );

	if( pCrypt )
	{
		boost::scoped_array<unsigned char> 
			pBufIn( new unsigned char[ mContainer.size() ] ), 
			pBufOut( new unsigned char[ mContainer.size() ] );

		copy( mContainer.begin(), mContainer.end(), pBufIn.get() );

		pCrypt->Decrypt( pBufIn.get(), pBufOut.get(), 
			static_cast<unsigned long>( mContainer.size() ), 0 );

		copy( pBufOut.get(), pBufOut.get() + mContainer.size(), mContainer.begin() );
	}
}


// コピーを作成する
DynamicFile::PDynamicFile DynamicFile::CreateClone() const
{
	DynamicFile *pNewFile = new DynamicFile( mhCryptModule );
	pNewFile->mContainer = mContainer;
	pNewFile->mCryptMap = mCryptMap;

	return PDynamicFile( pNewFile );
}

// Seleneのファイルインターフェイスを作成する
namespace
{
	static void ConvertFilePath( wstring &out, const wstring &in )
	{
		wchar_t temp[ MAX_PATH ] = L"";
		const wchar_t *pIn = in.c_str();

		Sint32 pos = 0;
		while( pos < MAX_PATH && pIn[ pos ] != L'\0' )
		{
			switch( pIn[ pos ] )
			{
			case L'a':  temp[ pos ] = L'A';      break;
			case L'b':  temp[ pos ] = L'B';      break;
			case L'c':  temp[ pos ] = L'C';      break;
			case L'd':  temp[ pos ] = L'D';      break;
			case L'e':  temp[ pos ] = L'E';      break;
			case L'f':  temp[ pos ] = L'F';      break;
			case L'g':  temp[ pos ] = L'G';      break;
			case L'h':  temp[ pos ] = L'H';      break;
			case L'i':  temp[ pos ] = L'I';      break;
			case L'j':  temp[ pos ] = L'J';      break;
			case L'k':  temp[ pos ] = L'K';      break;
			case L'l':  temp[ pos ] = L'L';      break;
			case L'm':  temp[ pos ] = L'M';      break;
			case L'n':  temp[ pos ] = L'N';      break;
			case L'o':  temp[ pos ] = L'O';      break;
			case L'p':  temp[ pos ] = L'P';      break;
			case L'q':  temp[ pos ] = L'Q';      break;
			case L'r':  temp[ pos ] = L'R';      break;
			case L's':  temp[ pos ] = L'S';      break;
			case L't':  temp[ pos ] = L'T';      break;
			case L'u':  temp[ pos ] = L'U';      break;
			case L'v':  temp[ pos ] = L'V';      break;
			case L'w':  temp[ pos ] = L'W';      break;
			case L'x':  temp[ pos ] = L'X';      break;
			case L'y':  temp[ pos ] = L'Y';      break;
			case L'z':  temp[ pos ] = L'Z';      break;
			case L'\\': temp[ pos ] = L'/';      break;
			default:    temp[ pos ] = pIn[ pos ];  break;
			}

			pos++;
		}

		out = temp;
	}
}
PFile DynamicFile::CreateSLNFile( const wstring &name ) const
{
	boost::scoped_array<unsigned char> 
		pData( new unsigned char[ mContainer.size() ] );
	copy( mContainer.begin(), mContainer.end(), pData.get() );

	void *pSLNFileData = Kernel::Memory::Alloc( mContainer.size() );
	Kernel::Memory::Copy( pSLNFileData, pData.get(), mContainer.size() );

	wstring convertedName;
	ConvertFilePath( convertedName, name );

	return PFile( new SyncFile( convertedName.c_str(), pSLNFileData, 
		static_cast<Sint32>( mContainer.size() ) ) );
}