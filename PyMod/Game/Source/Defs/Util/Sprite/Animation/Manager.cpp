#include "PCH.h"
#include "Manager.h"

#include "Defs/Util/Sprite/Sprite.h"

using namespace Defs::Util::Sprite::Animation;


Manager::Manager( PFrameHolder pFrameHolder )
	: mpFrameHolder( pFrameHolder )
	, mRepCounter( 1.0f )
	, mPlaying( false )
{
}

Manager::Manager( PFrameHolder pFrameHolder, float frameInterval )
	: mpFrameHolder( pFrameHolder )
	, mRepCounter( frameInterval )
	, mPlaying( false )
	, mLastFrame( false )
{
}


PFrameHolder Manager::GetFrameHolder() const
{
	return mpFrameHolder;
}

float Manager::GetFrameInterval() const
{
	return mRepCounter.GetInterval();
}

void Manager::SetFrameInterval( float itv )
{
	mRepCounter.SetInterval( itv );
}

bool Manager::IsPlaying() const
{
	return mPlaying;
}


void Manager::Update()
{
	if( mPlaying )
	{
		if( mLastFrame )
		{
			mPlaying = false;
		}
		else if( mpFrameHolder->GetFramePos() == mpFrameHolder->GetFrameNum() - 1 )
		{
			mLastFrame = true;
		}
		else
		{
			mpFrameHolder->SetFramePos( 
				mpFrameHolder->GetFramePos() + mRepCounter.GetRepeatCount() );
			mRepCounter.UpdateState();
		}
	}
}

void Manager::Draw() const
{
	Sprite::draw( mpFrameHolder->GetDrawParameter() );
}


void Manager::Play( unsigned framePos )
{
	mpFrameHolder->SetFramePos( framePos );
	mPlaying = true;
	mLastFrame = false;
}

void Manager::Stop()
{
	mPlaying = false;
}