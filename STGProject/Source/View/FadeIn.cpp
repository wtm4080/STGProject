#include "PCH.h"
#include "FadeIn.h"

using namespace Game;
using namespace Selene;


void View::FadeIn::Begin( unsigned frameNum, int drawPriority, 
						 const Delegate &drawFunction, const Delegate &afterEvent )
{
	Util::Ptr<FadeIn>::Shared pFadeIn( 
		new FadeIn( frameNum, drawPriority, drawFunction, afterEvent ) );

	Ctrl::Scene::Manager::Interrupt( 
		Ctrl::Scene::Manager::Delegate( pFadeIn, &FadeIn::Update ) );
}


View::FadeIn::FadeIn( unsigned frameNum, int drawPriority, 
					 const Delegate &drawFunction, const Delegate &afterEvent )
: mFrameNum( frameNum )
, mFrameCount( frameNum )
, mDrawPriority( drawPriority )
, mDrawFunc( drawFunction )
, mAfterEvent( afterEvent )
{
}


bool View::FadeIn::Update()
{
	if( mFrameCount > 0 )
	{
		mFrameCount--;
	}

	Draw();

	if( mFrameCount == 0 )
	{
		mAfterEvent();

		return false;
	}

	return true;
}

void View::FadeIn::Draw()
{
	mDrawFunc();

	Util::Sprite::DrawParameter dParam;
	dParam.SetDst( RectF( 0, 0, static_cast<float>( Util::Consts::SCREEN_SIZE.x ), 
		static_cast<float>( Util::Consts::SCREEN_SIZE.y ) ) );
	dParam.SetPriority( mDrawPriority );
	dParam.SetColor( ColorF( 0.0f, 0.0f, 0.0f, 1.0f/mFrameNum * mFrameCount ) );

	Util::Sprite::Manager::Draw( dParam );
}