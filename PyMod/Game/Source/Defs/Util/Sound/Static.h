#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Sound/IStatic.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Sound
{
	class Static
	{
	public:
		typedef Game::Util::Sound::PStatic PStatic;
		Static( PStatic p )
			: mpStatic( p )
		{}

		// 再生
		void Play()
		{
			mpStatic->Play();
		}
		void Play( bool isLoop )
		{
			mpStatic->Play( isLoop );
		}
		// 停止
		void Stop()
		{
			mpStatic->Stop();
		}
		// 一時停止/解除
		void Pause()
		{
			mpStatic->Pause();
		}
		// 一時停止チェック
		bool IsPause()
		{
			return mpStatic->IsPause();
		}
		// 再生状態かチェック
		bool IsPlay()
		{
			return mpStatic->IsPlay();
		}
		// ボリューム変更
		void SetVolume( float volume )
		{
			mpStatic->SetVolume( volume );
		}
		// レイヤーがすべで再生状態の時に待つかどうか
		bool IsWaitingForPlay()
		{
			return mpStatic->IsWaitingForPlay();
		}
		void SetWaitingForPlay( bool waiting )
		{
			mpStatic->SetWaitingForPlay( waiting );
		}

	private:
		Game::Util::Sound::PStatic mpStatic;
	};
}
}
}