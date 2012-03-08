#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
#include <boost/scoped_array.hpp>
#include "Util/Sound/IStream.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Sound
{
	class Stream
	{
	public:
		typedef Game::Util::Sound::PStream PStream;
		Stream( PStream p )
			: mpStream( p )
		{}

		// 再生
		void Play()
		{
			mpStream->Play();
		}
		void Play( Selene::Uint32 loopCount )
		{
			mpStream->Play( loopCount );
		}
		typedef Selene::Engine::Sound::Resource::SPlayBlock PlayBlock;
		void Play( const PlayBlock playBlocks[], Selene::Uint32 blockCount )
		{
			mpStream->Play( playBlocks, blockCount );
		}
		void Play( const boost::python::object &playBlocks )
		{
			auto blockNum = boost::python::len( playBlocks );
			boost::scoped_array<PlayBlock> pPlayBlocks( new PlayBlock[ blockNum ] );
			for( boost::python::ssize_t i = 0; i < blockNum; i++ )
			{
				{
					Selene::Sint32 loopCount = -1;
					boost::python::object pyLoopCount = 
						playBlocks[ i ].attr( "loopCount" );
					if( !pyLoopCount.is_none() )
					{
						loopCount = 
							boost::python::extract<Selene::Sint32>( pyLoopCount );
					}
					pPlayBlocks[ i ].LoopCount = loopCount;
				}

				{
					float startTime = Selene::Engine::Sound::Resource::PLAY_TIME_AUTO;
					boost::python::object pyStartTime = 
						playBlocks[ i ].attr( "startTime" );
					if( !pyStartTime.is_none() )
					{
						startTime = 
							boost::python::extract<float>( pyStartTime );
					}
					pPlayBlocks[ i ].StartTime = startTime;
				}

				{
					float endTime = Selene::Engine::Sound::Resource::PLAY_TIME_AUTO;
					boost::python::object pyEndTime = 
						playBlocks[ i ].attr( "endTime" );
					if( !pyEndTime.is_none() )
					{
						endTime = 
							boost::python::extract<float>( pyEndTime );
					}
					pPlayBlocks[ i ].EndTime = endTime;
				}
			}

			mpStream->Play( pPlayBlocks.get(), 
				static_cast<Selene::Uint32>( blockNum ) );
		}
		// 停止
		void Stop()
		{
			mpStream->Stop();
		}
		// 一時停止/解除
		void Pause()
		{
			mpStream->Pause();
		}
		// 再生状態かチェック
		bool IsPlay()
		{
			return mpStream->IsPlay();
		}
		// ボリューム変更
		void SetVolume( float volume )
		{
			mpStream->SetVolume( volume );
		}
		// フェードイン処理
		void FadeIn( float second )
		{
			mpStream->FadeIn( second );
		}
		// フェードアウト処理
		void FadeOut( float second )
		{
			mpStream->FadeOut( second );
		}

	private:
		PStream mpStream;
	};
}
}
}