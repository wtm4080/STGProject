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
namespace Font
{
namespace Detail
{
	// フォントスプライトのローダークラス
	class TextureLoader
		: public Selene::Engine::Graphics::Resource::IFileLoadListener		// ファイル読み込み用のリスナー
	{
	private:
		//
		// IFileLoadListener用
		// リソース読み込み時のコールバック
		// 成功時はtrueを返す事。
		//
		// pFileName	[in]	ファイル名
		// pFileBuffer	[out]	ファイルのバッファ
		// FileSize		[out]	ファイルサイズ
		// pUserData	[out]	ユーザーが任意に格納できるデータ
		// pUserSetData	[in]	CreateText()時の指定した pUserSetData 引数
		//
		virtual bool OnLoad( const wchar_t* pFileName, const void*& pFileBuffer, 
			Selene::Sint32& fileSize, void*& pUserData, void* pUserSetData );

		//
		// IFileLoadListener用
		// リソース読み込み終了時のコールバック
		//
		// pFileBuffer	[in]	ファイルのバッファ
		// FileSize		[in]	ファイルサイズ
		// pUserData	[in]	OnLoad()時に渡したユーザーが任意に格納できるデータ
		// pUserSetData	[in]	CreateText()時の指定した pUserSetData 引数
		//
		virtual void OnRelease( const void* pFileBuffer, Selene::Sint32 fileSize, 
			void* pUserData, void* pUserSetData );
	};
}
}
}
}