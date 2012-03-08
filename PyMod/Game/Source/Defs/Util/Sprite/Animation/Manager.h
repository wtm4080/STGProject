#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "FrameHolder/IFrameHolder.h"
#include "Util/RepeatCounter.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Sprite
{
namespace Animation
{
	class Manager
	{
	public:
		Manager( PFrameHolder pFrameHolder );
		Manager( PFrameHolder pFrameHolder, float frameInterval );

		PFrameHolder GetFrameHolder() const;
		float GetFrameInterval() const;
		void SetFrameInterval( float itv );
		bool IsPlaying() const;

		void Update();
		void Draw() const;

		void Play() { Play( 0 ); }
		void Play( unsigned framePos );
		void Stop();

	private:
		PFrameHolder mpFrameHolder;
		Game::Util::RepeatCounter mRepCounter;
		bool mPlaying, mLastFrame;
	};
}
}
}
}