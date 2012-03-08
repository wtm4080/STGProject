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
	// ストリームサウンド再生パラメーター
	typedef Selene::Engine::Sound::Resource::SPlayBlock PlayBlock;

	class IStream
	{
	public:
		// 再生
		virtual void Play() = 0;
		virtual void Play( Selene::Uint32 loopCount ) = 0;
		virtual void Play( const PlayBlock playBlocks[], Selene::Uint32 blockCount ) = 0;
		// 停止
		virtual void Stop() = 0;
		// 一時停止/解除
		virtual void Pause() = 0;
		// 再生状態かチェック
		virtual bool IsPlay() = 0;
		// ボリューム変更
		virtual void SetVolume( float volume = 1.0f ) = 0;
		// フェードイン処理
		virtual void FadeIn( float second ) = 0;
		// フェードアウト処理
		virtual void FadeOut( float second ) = 0;

		// SoundUtilのボリューム変更の反映
		virtual void UpdateVolume() = 0;

		// デストラクタ
		virtual ~IStream() {}
	};
}
}
}