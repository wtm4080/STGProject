#include "PCH.h"
#include "FadeOut.h"

using namespace Game;
using namespace Selene;


void View::FadeOut::Begin( unsigned frameNum, int drawPriority, 
						 const Delegate &drawFunction, const Delegate &afterEvent )
{
	Util::Ptr<FadeOut>::Shared pFadeOut( 
		new FadeOut( frameNum, drawPriority, drawFunction, afterEvent ) );

	Ctrl::Scene::Manager::Interrupt( 
		Ctrl::Scene::Manager::Delegate( pFadeOut, &FadeOut::Update ) );
}


View::FadeOut::FadeOut( unsigned frameNum, int drawPriority, 
					 const Delegate &drawFunction, const Delegate &afterEvent )
: mFrameNum( frameNum )
, mFrameCount( 0 )
, mDrawPriority( drawPriority )
, mDrawFunc( drawFunction )
, mAfterEvent( afterEvent )
{
}


bool View::FadeOut::Update()
{
	if( mFrameCount < mFrameNum )
	{
		mFrameCount++;
	}

	Draw();

	if( mFrameCount == mFrameNum )
	{
		mAfterEvent();

		return false;
	}

	return true;
}

void View::FadeOut::Draw()
{
	mDrawFunc();

	Util::Sprite::DrawParameter dParam;
	dParam.SetDst( RectF( 0, 0, static_cast<float>( Util::Consts::SCREEN_SIZE.x ), 
		static_cast<float>( Util::Consts::SCREEN_SIZE.y ) ) );
	dParam.SetPriority( mDrawPriority );
	dParam.SetColor( ColorF( 0.0f, 0.0f, 0.0f, 1.0f/mFrameNum * mFrameCount ) );

	Util::Sprite::Manager::Draw( dParam );
}