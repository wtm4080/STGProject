#include "PCH.h"
#include "Sound.h"

#include "Util/Python/Wrapper/ISound.h"

using namespace boost::python;
using namespace Game::Util::Python::Wrapper;
using namespace Selene;
using namespace Defs::Util::Sound;
using namespace std;

namespace
{
	ISound *pSound;

	typedef Defs::Util::File::FileObject FileObject;
}


void Sound::Configurate()
{
	class_<Sound>( "Sound", no_init )
		.def( "_setInstance", &Sound::_setInstance )
		.def( "loadStatic", static_cast<Static (*)( const wstring & )>( &Sound::loadStatic ) )
		.def( "loadStatic", static_cast<Static (*)( const wstring &, Sint32 )>( &Sound::loadStatic ) )
		.def( "loadStatic", static_cast<Static (*)( const FileObject & )>( &Sound::loadStatic ) )
		.def( "loadStatic", static_cast<Static (*)( const FileObject &, Sint32 )>( &Sound::loadStatic ) )
		.def( "loadStream", static_cast<Stream (*)( const wstring & )>( &Sound::loadStream ) )
		.def( "loadStream", static_cast<Stream (*)( const FileObject & )>( &Sound::loadStream ) )
		.def( "setStaticVolumes", &Sound::setStaticVolumes )
		.def( "getStaticVolumes", &Sound::getStaticVolumes )
		.def( "setStreamVolumes", &Sound::setStreamVolumes )
		.def( "getStreamVolumes", &Sound::getStreamVolumes )
		.def( "stopStatics", &Sound::stopStatics )
		.def( "stopStreams", &Sound::stopStreams )
		.def( "pauseStatics", &Sound::pauseStatics )
		.def( "pauseStreams", &Sound::pauseStreams )
		.def( "isPlayStatics", &Sound::isPlayStatics )
		.def( "isPlayStreams", &Sound::isPlayStreams )
		.def( "fadeInStreams", &Sound::fadeInStreams )
		.def( "fadeOutStreams", &Sound::fadeOutStreams )
		;

	class_<Static>( "Sound_Static", no_init )
		.def( "play", static_cast<void (Static::*)()>( &Static::Play ) )
		.def( "play", static_cast<void (Static::*)( bool )>( &Static::Play ) )
		.def( "stop", &Static::Stop )
		.def( "pause", &Static::Pause )
		.def( "isPause", &Static::IsPause )
		.def( "isPlay", &Static::IsPlay )
		.def( "setVolume", &Static::SetVolume )
		.add_property( "waitingForPlay", &Static::IsWaitingForPlay, &Static::SetWaitingForPlay )
		;
	class_<Stream>( "Sound_Stream", no_init )
		.def( "play", static_cast<void (Stream::*)( const object & )>( &Stream::Play ) )
		.def( "play", static_cast<void (Stream::*)()>( &Stream::Play ) )
		.def( "play", static_cast<void (Stream::*)( Uint32 )>( &Stream::Play ) )
		.def( "stop", &Stream::Stop )
		.def( "pause", &Stream::Pause )
		.def( "isPlay", &Stream::IsPlay )
		.def( "setVolume", &Stream::SetVolume )
		.def( "fadeIn", &Stream::FadeIn )
		.def( "fadeOut", &Stream::FadeOut )
		;
}


void Sound::_setInstance( uintptr_t p )
{
	pSound = reinterpret_cast<ISound *>( p );
}


Static Sound::loadStatic( const wstring &path )
{
	return Static( pSound->LoadStatic( path ) );
}

Static Sound::loadStatic( const wstring &path, Sint32 layerCount )
{
	return Static( pSound->LoadStatic( path, layerCount ) );
}

Static Sound::loadStatic( const FileObject &fileObject )
{
	return Static( pSound->LoadStatic( fileObject.GetFilePtr() ) );
}

Static Sound::loadStatic( const FileObject &fileObject, Sint32 layerCount )
{
	return Static( pSound->LoadStatic( fileObject.GetFilePtr(), layerCount ) );
}

Stream Sound::loadStream( const wstring &path )
{
	return Stream( pSound->LoadStream( path ) );
}

Stream Sound::loadStream( const FileObject &fileObject )
{
	return Stream( pSound->LoadStream( fileObject.GetFilePtr() ) );
}


void Sound::setStaticVolumes( float volume )
{
	pSound->SetStaticVolumes( volume );
}

float Sound::getStaticVolumes()
{
	return pSound->GetStaticVolumes();
}

void Sound::setStreamVolumes( float volume )
{
	pSound->SetStreamVolumes( volume );
}

float Sound::getStreamVolumes()
{
	return pSound->GetStreamVolumes();
}


void Sound::stopStatics()
{
	pSound->StopStatics();
}

void Sound::stopStreams()
{
	pSound->StopStreams();
}


void Sound::pauseStatics()
{
	pSound->PauseStatics();
}

void Sound::pauseStreams()
{
	pSound->PauseStreams();
}


bool Sound::isPlayStatics()
{
	return pSound->IsPlayStatics();
}

bool Sound::isPlayStreams()
{
	return pSound->IsPlayStreams();
}


void Sound::fadeInStreams( float second )
{
	pSound->FadeInStreams( second );
}

void Sound::fadeOutStreams( float second )
{
	pSound->FadeOutStreams( second );
}