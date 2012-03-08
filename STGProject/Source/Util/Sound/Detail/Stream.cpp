#include "PCH.h"
#include "Stream.h"

using namespace Game;
using namespace Util::Sound::Detail;
using namespace Selene;
using namespace std;
using namespace boost;


// コンストラクタ
Stream::Stream( PStreamSound pStreamSound, const wstring &name )
: mpStreamSound( pStreamSound )
, mVolume( Consts::Sound::VOLUME_ITV.upper() )
, mFading( false )
{
	if( !mpStreamSound )
	{
		THROW( 
			Exception::Invalid( name ) );
	}
}


// 再生
void Stream::Play()
{
	mpStreamSound->Play( -1 );

	mFading = false;
}

void Stream::Play( Uint32 loopCount )
{
	mpStreamSound->Play( loopCount );

	mFading = false;
}

void Stream::Play( const Util::Sound::PlayBlock playBlocks[], Uint32 blockCount )
{
	mpStreamSound->Play( playBlocks, blockCount );

	mFading = false;
}


// 停止
void Stream::Stop()
{
	mpStreamSound->Stop();

	mFading = false;
}


// 一時停止/解除
void Stream::Pause()
{
	mpStreamSound->Pause();
}


// 再生状態かチェック
bool Stream::IsPlay()
{
	return mpStreamSound->IsPlay();
}


// ボリューム変更
void Stream::SetVolume( float volume )
{
	if( numeric::in( volume, Consts::Sound::VOLUME_ITV ) )
	{
		mVolume = volume;
	}
	else if( volume > Consts::Sound::VOLUME_ITV.upper() )
	{
		mVolume = Consts::Sound::VOLUME_ITV.upper();
	}
	else if( volume < Consts::Sound::VOLUME_ITV.lower() )
	{
		mVolume = Consts::Sound::VOLUME_ITV.lower();
	}

	UpdateVolume();
}


// フェードイン処理
void Stream::FadeIn( float second )
{
	mpStreamSound->FadeIn( second, mVolume * Manager::GetStreamVolumes() * 100.0f );

	//mFading = true;
}

// フェードアウト処理
void Stream::FadeOut( float second )
{
	mpStreamSound->FadeOut( second );

	mFading = true;
}


// SoundUtilのボリューム変更の反映
void Stream::UpdateVolume()
{
	if( !mFading )
	{
		mpStreamSound->SetVolume( mVolume * Manager::GetStreamVolumes() * 100.0f );
	}
}