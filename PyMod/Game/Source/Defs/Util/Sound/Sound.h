#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Static.h"
#include "Stream.h"
#include "Defs/Util/File/FileObject.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Sound
{
	class Sound
	{
	public:
		static void Configurate();

		static void _setInstance( uintptr_t p );

		// 効果音用のサウンドファイルの読み込み
		static Static loadStatic( const std::wstring &path );
		static Static loadStatic( const std::wstring &path, Selene::Sint32 layerCount );
		static Static loadStatic( const File::FileObject &fileObject );
		static Static loadStatic( const File::FileObject &fileObject, Selene::Sint32 layerCount );
		// BGM用のサウンドファイルの読み込み
		static Stream loadStream( const std::wstring &path );
		static Stream loadStream( const File::FileObject &fileObject );

		// 効果音のボリュームの変更
		static void setStaticVolumes( float volume );
		// 効果音のボリュームの取得
		static float getStaticVolumes();
		// BGMのボリュームの変更
		static void setStreamVolumes( float volume );
		// BGMのボリュームの取得
		static float getStreamVolumes();

		// 効果音の停止
		static void stopStatics();
		// BGMの停止
		static void stopStreams();

		// 効果音の一時停止/解除
		static void pauseStatics();
		// BGMの一時停止/解除
		static void pauseStreams();

		// 効果音の再生状態チェック
		static bool isPlayStatics();
		// BGMの再生状態チェック
		static bool isPlayStreams();

		// BGMのフェードイン
		static void fadeInStreams( float second );
		// BGMのフェードアウト
		static void fadeOutStreams( float second );
	};
}
}
}