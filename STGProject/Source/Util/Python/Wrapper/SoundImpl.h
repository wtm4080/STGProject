#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "ISound.h"
#include "Util/Sound/Manager.h"


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
	class SoundImpl
		: public ISound
	{
	public:
		// 効果音用のサウンドファイルの読み込み
		virtual Sound::PStatic LoadStatic( const std::wstring &fileName )
		{
			return Sound::Manager::LoadStatic( fileName );
		}
		virtual Sound::PStatic LoadStatic( const std::wstring &fileName, Selene::Sint32 layerCount )
		{
			return Sound::Manager::LoadStatic( fileName, layerCount );
		}
		virtual Sound::PStatic LoadStatic( File::PFile pFile )
		{
			return Sound::Manager::LoadStatic( pFile );
		}
		virtual Sound::PStatic LoadStatic( File::PFile pFile, Selene::Sint32 layerCount )
		{
			return Sound::Manager::LoadStatic( pFile, layerCount );
		}
		// BGM用のサウンドファイルの読み込み
		virtual Sound::PStream LoadStream( const std::wstring &fileName )
		{
			return Sound::Manager::LoadStream( fileName );
		}
		virtual Sound::PStream LoadStream( File::PFile pFile )
		{
			return Sound::Manager::LoadStream( pFile );
		}

		// 効果音のボリュームの変更
		virtual void SetStaticVolumes( float volume )
		{
			Sound::Manager::SetStaticVolumes( volume );
		}
		// 効果音のボリュームの取得
		virtual float GetStaticVolumes()
		{
			return Sound::Manager::GetStaticVolumes();
		}
		// BGMのボリュームの変更
		virtual void SetStreamVolumes( float volume )
		{
			Sound::Manager::SetStreamVolumes( volume );
		}
		// BGMのボリュームの取得
		virtual float GetStreamVolumes()
		{
			return Sound::Manager::GetStreamVolumes();
		}

		// 効果音の停止
		virtual void StopStatics()
		{
			Sound::Manager::StopStatics();
		}
		// BGMの停止
		virtual void StopStreams()
		{
			Sound::Manager::StopStreams();
		}

		// 効果音の一時停止/解除
		virtual void PauseStatics()
		{
			Sound::Manager::PauseStatics();
		}
		// BGMの一時停止/解除
		virtual void PauseStreams()
		{
			Sound::Manager::PauseStreams();
		}

		// 効果音の再生状態チェック
		virtual bool IsPlayStatics()
		{
			return Sound::Manager::IsPlayStatics();
		}
		// BGMの再生状態チェック
		virtual bool IsPlayStreams()
		{
			return Sound::Manager::IsPlayStreams();
		}

		// BGMのフェードイン
		virtual void FadeInStreams( float second )
		{
			Sound::Manager::FadeInStreams( second );
		}
		// BGMのフェードアウト
		virtual void FadeOutStreams( float second )
		{
			Sound::Manager::FadeOutStreams( second );
		}
	};
}
}
}
}