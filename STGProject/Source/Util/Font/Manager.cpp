#include "PCH.h"
#include "Manager.h"
#include "Detail/SLNFont.h"
#include "Detail/TextureLoader.h"
#include "IFont.h"

using namespace Game;
using namespace Util::Font;
using namespace Selene;
using namespace std;
using namespace Util::Consts::Font;

namespace
{
	// テクスチャ用パラメーター
	static const Engine::Graphics::STextureLoadParameter LOAD_PARAM = { true };

	// フォントリソース読み込み用パスの取得
	static wstring GetResourcePath( const wstring &fontFilePath )
	{
		// fontFilePathを'/'と'\'で分割
		vector<wstring> fontPathTokenList;
		Util::Tokenize( fontFilePath, L"/\\", fontPathTokenList );

		wstring resourcePath;
		for( auto itr = fontPathTokenList.begin(); 
			itr != fontPathTokenList.end() - 1; 
			itr++ )
		{
			resourcePath += *itr + L"/";
		}

		return resourcePath;
	}
}


// フォントデータの読み込み
PFont Manager::LoadFont( const wstring &fontFilePath )
{
	wstring resourcePath = GetResourcePath( fontFilePath );
	File::PFile pResourceFile;
	pair<wstring, File::PFile *> resourcePair( resourcePath, &pResourceFile );

	File::PFile pFontFile = File::Manager::Open( LOAD_TOP_PATH + fontFilePath );

	Detail::TextureLoader loader;
	Detail::PSLNFont pSLNFont = MakeIntrusivePtr( 
		Core::Manager::GetGraphicsManager()->CreateText(
			pFontFile->GetData(),		// ファイルデータ
			pFontFile->GetSize(),		// ファイルサイズ
			pFontFile->GetFileName(),	// ファイル名
			LOAD_PARAM,					// テクスチャ生成用パラメーター
			&loader,					// リソース読み込み用リスナー
			&resourcePair ) );			// ユーザーデータ（Resource::IFileLoadListenerのpUserSetData引数）

	if( !pSLNFont )
	{
		THROW( Exception::Invalid( fontFilePath ) );
	}
	else
	{
		pSLNFont->SetDrawSprite( Core::Manager::GetSpriteRenderer().get() );
		pSLNFont->SetScissorRect( RectI( 0, 0, Consts::SCREEN_SIZE.x, Consts::SCREEN_SIZE.y ) );
	}

	return PFont( new Detail::SLNFont( pSLNFont ) );
}

void Manager::LoadFont( const vector<wstring> &fontFilePathList, FontMap &fonts )
{
	fonts.clear();

	list<wstring> invalidFontList;
	Detail::TextureLoader loader;

	File::FileMap fontFiles;
	vector<wstring> pathList;
	foreach( const wstring &path, fontFilePathList )
	{
		pathList.push_back( LOAD_TOP_PATH + path );
	}
	File::Manager::Open( pathList, fontFiles );

	foreach( const File::FileMapElemType &fontPair, fontFiles )
	{
		wstring resourcePath = GetResourcePath( fontPair.first );
		File::PFile pResourceFile;
		pair<wstring, File::PFile *> resourcePair( resourcePath, &pResourceFile );

		Detail::PSLNFont pSLNFont = MakeIntrusivePtr( 
			Core::Manager::GetGraphicsManager()->CreateText(
				fontPair.second->GetData(),		// ファイルデータ
				fontPair.second->GetSize(),		// ファイルサイズ
				fontPair.second->GetFileName(),	// ファイル名
				LOAD_PARAM,						// テクスチャ生成用パラメーター
				&loader,						// リソース読み込み用リスナー
				&resourcePair ) );				// ユーザーデータ（Resource::IFileLoadListenerのpUserSetData引数）

		if( !pSLNFont )
		{
			invalidFontList.push_back( fontPair.first );
		}
		else
		{
			pSLNFont->SetDrawSprite( Core::Manager::GetSpriteRenderer().get() );
			pSLNFont->SetScissorRect( 
				RectI( 0, 0, Consts::SCREEN_SIZE.x, Consts::SCREEN_SIZE.y ) );

			fonts[ fontPair.first ] = PFont( new Detail::SLNFont( pSLNFont ) );
		}
	}

	if( !invalidFontList.empty() )
	{
		THROW( Exception::Invalid( invalidFontList ) );
	}
}