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
	// ファイルに関する処理
	class Manager
	{
	public:
		// 1つのファイルを読み込む
		static PFile Open( const std::wstring &filePath, 
			bool cache = true, bool throwException = true );
		// 1つのファイルを非同期で読み込む
		static PFile OpenASync( const std::wstring &filePath, 
			bool cache = true, bool throwException = true );
		// filePathListにあるファイルを一度にすべて読み込む
		static void Open( const std::vector<std::wstring> &filePathList, 
			FileMap &files, bool cache = true, bool throwException = true );

		// パックファイルのインターフェイスを生成
		static PPackFile CreatePackFile( PFile pFile );

		// DynamicFileの作成
		static Ptr<IDynamicFile>::Shared CreateDynamicFile();
		static Ptr<IDynamicFile>::Shared CreateDynamicFile( PFile pFile );

		// ファイルの書き込み
		// dirPathが存在しなければ作成する
		// dirPathがディレクトリでなかったら、削除してディレクトリを作成する
		static bool Write( const std::wstring &dirPath, const std::wstring &fileName, 
			PFile pFile );
		static bool Write( const std::wstring &dirPath, const std::wstring &fileName, 
			Ptr<IDynamicFile>::Shared pDynamicFile );

		// 指定したパスが見つからなければ、パスの先頭に"../"を追加する
		static std::wstring ConvertPath( const std::wstring &pathStr );

		// キャッシュサイズの取得
		static unsigned GetCacheSize();
		// 最大キャッシュサイズの取得
		static unsigned GetMaxCacheSize();
		// 最大キャッシュサイズの設定
		static void SetMaxCacheSize( unsigned size );

		// キャッシュの消去
		static void EraseCache( const std::wstring &path );
		// キャッシュの全クリア
		static void ClearCache();

		// 初期化処理
		static void Initialize();
		// 後始末処理
		static void Release();
	};
}
}
}