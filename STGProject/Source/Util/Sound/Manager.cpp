#include "PCH.h"
#include "Manager.h"
#include "Detail/Static.h"
#include "Detail/Stream.h"

using namespace Game;
using namespace Util::Sound;
using namespace Selene;
using namespace std;
using namespace Util::Consts::Sound;


namespace
{
	// 効果音のボリューム
	static float mStaticVolume = VOLUME_ITV.upper();
	// BGMのボリューム
	static float mStreamVolume = VOLUME_ITV.upper();

	typedef Util::Ptr<Util::Sound::IStatic>::Weak WPStatic;
	typedef Util::Ptr<Util::Sound::IStream>::Weak WPStream;

	// StaticSoundのインスタンスへのアクセス用
	static set<WPStatic> mwpStatics;
	// StreamSoundのインスタンスへのアクセス用
	static set<WPStream> mwpStreams;
}


// 効果音用のサウンドファイルの読み込み
PStatic Manager::LoadStatic( const wstring &fileName, Uint32 layerCount )
{
	File::PFile pFile = File::Manager::Open( LOAD_TOP_PATH_SE + fileName );

	return LoadStatic( pFile, layerCount );
}

PStatic Manager::LoadStatic( Util::File::PFile pFile, Uint32 layerCount )
{
	PStatic pStatic( 
		new Detail::Static( MakeIntrusivePtr( 
		Core::Manager::GetSoundManager()->CreateStaticSound( 
			pFile->GetFileName(), 
			pFile->GetData(), 
			pFile->GetSize(), 
			layerCount, 
			false ) ), 
		pFile->GetFileName(), layerCount ) );

	mwpStatics.insert( WPStatic( pStatic ) );
	pStatic->UpdateVolume();

	return pStatic;
}

void Manager::LoadStatic( const StaticSrcMap &srcMap, StaticMap &statics )
{
	statics.clear();

	vector<wstring> filePathList;
	typedef pair<wstring, Uint32> SrcFilePathElem;
	foreach( const SrcFilePathElem &elem, srcMap )
	{
		filePathList.push_back( LOAD_TOP_PATH_SE + elem.first );
	}

	File::FileMap files;
	File::Manager::Open( filePathList, files );

	foreach( const SrcFilePathElem &elem, srcMap )
	{
		wstring path = elem.first;
		File::PFile pFile = files[ path ];
		Uint32 layerCount = elem.second;

		PStatic pStatic( 
			new Detail::Static( MakeIntrusivePtr( 
			Core::Manager::GetSoundManager()->CreateStaticSound( 
				pFile->GetFileName(), 
				pFile->GetData(), 
				pFile->GetSize(), 
				layerCount, 
				false ) ), 
			path, layerCount ) );

		mwpStatics.insert( WPStatic( pStatic ) );
		pStatic->UpdateVolume();

		statics[ path ] = pStatic;
	}
}

// BGM用のサウンドファイルの読み込み
PStream Manager::LoadStream( const wstring &fileName, bool isMemoryCopy )
{
	File::PFile pFile = File::Manager::Open( LOAD_TOP_PATH_BGM + fileName );

	return LoadStream( pFile, isMemoryCopy );
}

PStream Manager::LoadStream( Util::File::PFile pFile, bool isMemoryCopy )
{
	PStream pStream( 
		new Detail::Stream( MakeIntrusivePtr( 
		Core::Manager::GetSoundManager()->CreateStreamSound( 
			pFile->GetFileName(), 
			pFile->GetData(), 
			pFile->GetSize(), 
			L"OggVorbis", 
			isMemoryCopy ) ), 
		pFile->GetFileName() ) );

	mwpStreams.insert( WPStream( pStream ) );
	pStream->UpdateVolume();

	return pStream;
}

void Manager::LoadStream( const StreamSrcMap &srcMap, StreamMap &streams )
{
	streams.clear();

	vector<wstring> filePathList;
	typedef pair<wstring, bool> SrcFilePathElem;
	foreach( const SrcFilePathElem &elem, srcMap )
	{
		filePathList.push_back( LOAD_TOP_PATH_BGM + elem.first );
	}

	File::FileMap files;
	File::Manager::Open( filePathList, files );

	foreach( const SrcFilePathElem &elem, srcMap )
	{
		wstring path = elem.first;
		File::PFile pFile = files[ path ];
		bool isMemoryCopy = elem.second;

		PStream pStream( 
			new Detail::Stream( MakeIntrusivePtr( 
			Core::Manager::GetSoundManager()->CreateStreamSound( 
				pFile->GetFileName(), 
				pFile->GetData(), 
				pFile->GetSize(), 
				L"OggVorbis", 
				isMemoryCopy ) ), 
			path ) );

		mwpStreams.insert( WPStream( pStream ) );
		pStream->UpdateVolume();

		streams[ path ] = pStream;
	}
}


// 効果音のボリュームの変更
void Manager::SetStaticVolumes( float volume )
{
	mStaticVolume = volume;

	if( mStaticVolume > Consts::Sound::VOLUME_ITV.upper() )
	{
		mStaticVolume = Consts::Sound::VOLUME_ITV.upper();
	}
	else if( mStaticVolume < Consts::Sound::VOLUME_ITV.lower() )
	{
		mStaticVolume = Consts::Sound::VOLUME_ITV.lower();
	}

	for( auto itr = mwpStatics.begin(); 
		itr != mwpStatics.end(); )
	{
		if( !itr->expired() )
		{
			auto pStatic = itr->lock();
			pStatic->UpdateVolume();

			itr++;
		}
		else
		{
			mwpStatics.erase( itr++ );
		}
	}
}

// 効果音のボリュームの取得
float Manager::GetStaticVolumes()
{
	return mStaticVolume;
}

// BGMのボリュームの変更
void Manager::SetStreamVolumes( float volume )
{
	mStreamVolume = volume;

	if( mStreamVolume > Consts::Sound::VOLUME_ITV.upper() )
	{
		mStreamVolume = Consts::Sound::VOLUME_ITV.upper();
	}
	else if( mStreamVolume < Consts::Sound::VOLUME_ITV.lower() )
	{
		mStreamVolume = Consts::Sound::VOLUME_ITV.lower();
	}

	for( auto itr = mwpStreams.begin(); 
		itr != mwpStreams.end(); )
	{
		if( !itr->expired() )
		{
			auto pStream = itr->lock();
			pStream->UpdateVolume();

			itr++;
		}
		else
		{
			mwpStreams.erase( itr++ );
		}
	}
}

// BGMのボリュームの取得
float Manager::GetStreamVolumes()
{
	return mStreamVolume;
}


// 効果音の停止
void Manager::StopStatics()
{
	for( auto itr = mwpStatics.begin(); 
		itr != mwpStatics.end(); )
	{
		if( !itr->expired() )
		{
			auto pStatic = itr->lock();
			pStatic->Stop();

			itr++;
		}
		else
		{
			mwpStatics.erase( itr++ );
		}
	}
}

// BGMの停止
void Manager::StopStreams()
{
	for( auto itr = mwpStreams.begin(); 
		itr != mwpStreams.end(); )
	{
		if( !itr->expired() )
		{
			auto pStream = itr->lock();
			pStream->Stop();

			itr++;
		}
		else
		{
			mwpStreams.erase( itr++ );
		}
	}
}


// 効果音の一時停止/解除
void Manager::PauseStatics()
{
	for( auto itr = mwpStatics.begin(); 
		itr != mwpStatics.end(); )
	{
		if( !itr->expired() )
		{
			auto pStatic = itr->lock();
			pStatic->Pause();

			itr++;
		}
		else
		{
			mwpStatics.erase( itr++ );
		}
	}
}

// BGMの一時停止/解除
void Manager::PauseStreams()
{
	for( auto itr = mwpStreams.begin(); 
		itr != mwpStreams.end(); )
	{
		if( !itr->expired() )
		{
			auto pStream = itr->lock();
			pStream->Pause();

			itr++;
		}
		else
		{
			mwpStreams.erase( itr++ );
		}
	}
}


// 効果音の再生状態チェック
bool Manager::IsPlayStatics()
{
	for( auto itr = mwpStatics.begin(); 
		itr != mwpStatics.end(); )
	{
		if( !itr->expired() )
		{
			auto pStatic = itr->lock();
			if( pStatic->IsPlay() )
			{
				return true;
			}

			itr++;
		}
		else
		{
			mwpStatics.erase( itr++ );
		}
	}

	return false;
}

// BGMの再生状態チェック
bool Manager::IsPlayStreams()
{
	for( auto itr = mwpStreams.begin(); 
		itr != mwpStreams.end(); )
	{
		if( !itr->expired() )
		{
			auto pStream = itr->lock();
			if( pStream->IsPlay() )
			{
				return true;
			}

			itr++;
		}
		else
		{
			mwpStreams.erase( itr++ );
		}
	}

	return false;
}


// BGMのフェードイン
void Manager::FadeInStreams( float second )
{
	for( auto itr = mwpStreams.begin(); 
		itr != mwpStreams.end(); )
	{
		if( !itr->expired() )
		{
			auto pStream = itr->lock();
			pStream->FadeIn( second );

			itr++;
		}
		else
		{
			mwpStreams.erase( itr++ );
		}
	}
}

// BGMのフェードアウト
void Manager::FadeOutStreams( float second )
{
	for( auto itr = mwpStreams.begin(); 
		itr != mwpStreams.end(); )
	{
		if( !itr->expired() )
		{
			auto pStream = itr->lock();
			pStream->FadeOut( second );

			itr++;
		}
		else
		{
			mwpStreams.erase( itr++ );
		}
	}
}