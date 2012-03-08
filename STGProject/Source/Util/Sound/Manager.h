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
namespace Sound
{
	/*
		サウンド関連の操作

		ここでの操作は、LoadStatic/Stream()で作成した全てのインスタンスに適用される

		同じサウンドファイルでインスタンスを作ると、
		終了時にSELENE側で例外"out_of_range"が出るっぽい
	*/
	class Manager
	{
	public:
		// 効果音用のサウンドファイルの読み込み
		static PStatic LoadStatic( const std::wstring &fileName, 
			Selene::Uint32 layerCount = 1 );
		static PStatic LoadStatic( File::PFile pFile, 
			Selene::Uint32 layerCount = 1 );
		static void LoadStatic( const StaticSrcMap &srcMap, 
			StaticMap &statics );

		// BGM用のサウンドファイルの読み込み
		static PStream LoadStream( const std::wstring &fileName, 
			bool isMemoryCopy = true );
		static PStream LoadStream( File::PFile pFile, 
			bool isMemoryCopy = true );
		static void LoadStream( const StreamSrcMap &srcMap, 
			StreamMap &streams );

		// 効果音のボリュームの変更
		static void SetStaticVolumes( float volume = 1.0f );
		// 効果音のボリュームの取得
		static float GetStaticVolumes();
		// BGMのボリュームの変更
		static void SetStreamVolumes( float volume = 1.0f );
		// BGMのボリュームの取得
		static float GetStreamVolumes();

		// 効果音の停止
		static void StopStatics();
		// BGMの停止
		static void StopStreams();

		// 効果音の一時停止/解除
		static void PauseStatics();
		// BGMの一時停止/解除
		static void PauseStreams();

		// 効果音の再生状態チェック
		static bool IsPlayStatics();
		// BGMの再生状態チェック
		static bool IsPlayStreams();

		// BGMのフェードイン
		static void FadeInStreams( float second );
		// BGMのフェードアウト
		static void FadeOutStreams( float second );
	};
}
}
}