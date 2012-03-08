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
	class IStatic
	{
	public:
		// 再生
		virtual void Play( bool isLoop = false ) = 0;
		virtual void Play( Selene::Uint32 layer, bool isLoop = false ) = 0;
		// 停止
		virtual void Stop() = 0;
		virtual void Stop( Selene::Uint32 layer ) = 0;
		// 一時停止/解除
		virtual void Pause() = 0;
		virtual void Pause( Selene::Uint32 layer ) = 0;
		// 一時停止チェック
		virtual bool IsPause() = 0;
		virtual bool IsPause( Selene::Uint32 layer ) = 0;
		// 再生状態かチェック
		virtual bool IsPlay() = 0;
		virtual bool IsPlay( Selene::Uint32 layer ) = 0;
		// ボリューム変更
		virtual void SetVolume( float volume = 1.0f ) = 0;
		virtual void SetVolume( Selene::Uint32 layer, float volume = 1.0f ) = 0;
		// レイヤーがすべで再生状態の時に待つかどうか
		virtual bool IsWaitingForPlay() const = 0;
		virtual void SetWaitingForPlay( bool waiting ) = 0;

		// SoundUtilのボリューム変更の反映
		virtual void UpdateVolume() = 0;

		// デストラクタ
		virtual ~IStatic() {}
	};
}
}
}