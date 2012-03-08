#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/Sound/IStream.h"
#include <boost/noncopyable.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Sound
{
namespace Detail
{
	typedef Ptr<Selene::Engine::Sound::Resource::IStreamSound>::Intrusive 
		PStreamSound;

	class Stream
		: public IStream
		, public boost::noncopyable
	{
	public:
		// 再生
		virtual void Play();
		virtual void Play( Selene::Uint32 loopCount );
		virtual void Play( const PlayBlock playBlocks[], Selene::Uint32 blockCount );
		// 停止
		virtual void Stop();
		// 一時停止/解除
		virtual void Pause();
		// 再生状態かチェック
		virtual bool IsPlay();
		// ボリューム変更
		virtual void SetVolume( float volume = 1.0f );
		// フェードイン処理
		virtual void FadeIn( float second );
		// フェードアウト処理
		virtual void FadeOut( float second );

		// SoundUtilのボリューム変更の反映
		virtual void UpdateVolume();

		// コンストラクタ
		Stream( PStreamSound pStreamSound, const std::wstring &name );

	private:
		// SeleneのIStaticSound
		PStreamSound mpStreamSound;
		// ボリューム
		float mVolume;
		// フェードイン/アウト処理中フラグ
		bool mFading;
	};
}
}
}
}