#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Delegate/Delegate.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace View
{
	class FadeIn
	{
	public:
		typedef Util::Delegate::Delegate0<> Delegate;

		static void Begin( unsigned frameNum, int drawPriority, 
			const Delegate &drawFunction, 
			const Delegate &afterEvent = Delegate() );

	private:
		FadeIn( unsigned frameNum, int drawPriority, 
			const Delegate &drawFunction, 
			const Delegate &afterEvent );

		bool Update();
		void Draw();

		const unsigned mFrameNum;
		unsigned mFrameCount;
		int mDrawPriority;
		Delegate mDrawFunc;
		Delegate mAfterEvent;
	};
}
}