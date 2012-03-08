#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/Sound/IStatic.h"
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
	typedef Ptr<Selene::Engine::Sound::Resource::IStaticSound>::Intrusive 
		PStaticSound;

	class Static
		: public IStatic
		, public boost::noncopyable
	{
	public:
		// 再生
		virtual void Play( bool isLoop = false );
		virtual void Play( Selene::Uint32 layer, bool isLoop = false );
		// 停止
		virtual void Stop();
		virtual void Stop( Selene::Uint32 layer );
		// 一時停止/解除
		virtual void Pause();
		virtual void Pause( Selene::Uint32 layer );
		// 一時停止チェック
		virtual bool IsPause();
		virtual bool IsPause( Selene::Uint32 layer );
		// 再生状態かチェック
		virtual bool IsPlay();
		virtual bool IsPlay( Selene::Uint32 layer );
		// ボリューム変更
		virtual void SetVolume( float volume = 1.0f );
		virtual void SetVolume( Selene::Uint32 layer, float volume = 1.0f );
		// レイヤーがすべで再生状態の時に待つかどうか
		virtual bool IsWaitingForPlay() const;
		virtual void SetWaitingForPlay( bool waiting );

		// SoundUtilのボリューム変更の反映
		virtual void UpdateVolume();

		// コンストラクタ
		Static( PStaticSound pStaticSound, const std::wstring &name, 
			Selene::Uint32 layerCount = 32 );

	private:
		// SeleneのIStaticSound
		PStaticSound mpStaticSound;
		// 個々のレイヤーのボリューム
		std::vector<float> mIndividualVolumes;
		// レイヤーの番号の定義域
		const boost::numeric::interval<Selene::Uint32> mLayerItv;
		// 例外の構築に使用
		const std::wstring mName;
		// レイヤーがすべで再生状態の時に待つかどうか
		bool mWaitingForPlay;
	};
}
}
}
}