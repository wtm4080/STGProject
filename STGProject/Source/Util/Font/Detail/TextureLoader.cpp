#include "PCH.h"
#include "TextureLoader.h"

using namespace Game;
using namespace Selene;
using namespace std;


// リソース読み込み時のコールバック
bool Util::Font::Detail::TextureLoader::OnLoad( const wchar_t *pFileName, 
				const void *&pFileBuffer, Sint32 &fileSize, void *&pUserData, void *pUserSetData )
{
	pair<wstring, File::PFile *> resourcePair = 
		*static_cast<pair<wstring, File::PFile *> *>(pUserSetData);

	wstring resourcePath = resourcePair.first + pFileName;

	// リクエストされたファイル読み込む
	*resourcePair.second = 
		File::Manager::Open( Util::Consts::Font::LOAD_TOP_PATH + resourcePath );

	pFileBuffer	= ( *resourcePair.second )->GetData();
	fileSize	= ( *resourcePair.second )->GetSize();

	return true;
}


void Util::Font::Detail::TextureLoader::OnRelease( const void *pFileBuffer, Sint32 fileSize, 
												  void *pUserData, void *pUserSetData )
{
}