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
namespace Python
{
namespace Wrapper
{
	class ISound
	{
	public:
		// 効果音用のサウンドファイルの読み込み
		virtual Sound::PStatic LoadStatic( const std::wstring &fileName ) = 0;
		virtual Sound::PStatic LoadStatic( const std::wstring &fileName, Selene::Sint32 layerCount ) = 0;
		virtual Sound::PStatic LoadStatic( File::PFile pFile ) = 0;
		virtual Sound::PStatic LoadStatic( File::PFile pFile, Selene::Sint32 layerCount ) = 0;
		// BGM用のサウンドファイルの読み込み
		virtual Sound::PStream LoadStream( const std::wstring &fileName ) = 0;
		virtual Sound::PStream LoadStream( File::PFile pFile ) = 0;

		// 効果音のボリュームの変更
		virtual void SetStaticVolumes( float volume ) = 0;
		// 効果音のボリュームの取得
		virtual float GetStaticVolumes() = 0;
		// BGMのボリュームの変更
		virtual void SetStreamVolumes( float volume ) = 0;
		// BGMのボリュームの取得
		virtual float GetStreamVolumes() = 0;

		// 効果音の停止
		virtual void StopStatics() = 0;
		// BGMの停止
		virtual void StopStreams() = 0;

		// 効果音の一時停止/解除
		virtual void PauseStatics() = 0;
		// BGMの一時停止/解除
		virtual void PauseStreams() = 0;

		// 効果音の再生状態チェック
		virtual bool IsPlayStatics() = 0;
		// BGMの再生状態チェック
		virtual bool IsPlayStreams() = 0;

		// BGMのフェードイン
		virtual void FadeInStreams( float second ) = 0;
		// BGMのフェードアウト
		virtual void FadeOutStreams( float second ) = 0;

		virtual ~ISound() {}
	};
}
}
}
}