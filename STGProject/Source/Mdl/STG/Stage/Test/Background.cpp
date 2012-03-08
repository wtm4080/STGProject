#include "PCH.h"
#include "Background.h"
#include "StageSetCore.h"
#include "Resource.h"

#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/MyShip/IMyShip.h"
#include "View/STG/DrawPriority.h"
#include "Util/Input/STG/IController.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Stage::Test;
using namespace Util::STG;
using namespace Selene;

const float Background::INIT_SCROLL_AMOUNT = 1.0f;


Background::Background( PStageSet pStageSet )
: mpStageSet( pStageSet )
{
	mDrawParam1.SetTexture( mpStageSet->GetResource()->GetBackground1() );
	mDrawParam1.SetSrc( Resource::BACKGROUND1.GetRect() );
	mDrawParam1.SetDst( RectF( 0, -480, 640, 480 ) );
	mDrawParam1.SetPriority( View::STG::PRI_BACKGROUND );

	mDrawParam2.SetTexture( mpStageSet->GetResource()->GetBackground2() );
	mDrawParam2.SetSrc( Resource::BACKGROUND2.GetRect() );
	mDrawParam2.SetDst( RectF( 0, 0, 640, 480 ) );
	mDrawParam2.SetPriority( View::STG::PRI_BACKGROUND );

	mScrollAmount = INIT_SCROLL_AMOUNT;
	assert( mScrollAmount >= 0 );

	ScrollH( mDrawParam1 );
	ScrollH( mDrawParam2 );
}


void Background::Update()
{
	ScrollV( mDrawParam1, mDrawParam2 );
	ScrollV( mDrawParam2, mDrawParam1, true );

	ScrollH( mDrawParam1 );
	ScrollH( mDrawParam2 );
}

void Background::Draw() const
{
	Util::Sprite::Manager::Draw( mDrawParam1 );
	Util::Sprite::Manager::Draw( mDrawParam2 );
}


float Background::GetScrollAmount() const
{
	return mScrollAmount;
}

void Background::SetScrollAmount( float amount )
{
	assert( amount >= 0 );

	mScrollAmount = amount;
}


void Background::ScrollV( Util::Sprite::DrawParameter &param1, 
						const Util::Sprite::DrawParameter &param2, bool after )
{
	RectF dst = param1.GetDst();

	float amount;
	if( mpStageSet->GetMode()->GetController()->IsHold( Util::Input::STG::KEY_LSHIFT ) )
	{
		amount = mScrollAmount * 
			( -mpStageSet->GetMode()->GetController()->GetDirection().y * 0.1f + 1.0f );
	}
	else
	{
		amount = mScrollAmount * 
			( -mpStageSet->GetMode()->GetController()->GetDirection().y * 0.2f + 1.0f );
	}

	dst.y += amount;

	if( dst.y >= 480 )
	{
		dst.y = param2.GetDst().y - 480.0f;

		// å„ÇÃÇ‚Ç¬ÇìÆÇ©Ç∑Ç∆ÉYÉåÇƒÇµÇ‹Ç§ÇÃÇ≈ï‚ê≥
		if( !after )
		{
			dst.y += amount;
		}
	}

	param1.SetDst( dst );
}

void Background::ScrollH( Util::Sprite::DrawParameter &param )
{
	static const float stgAreaX = static_cast<float>( 
		Util::Consts::SCREEN_SIZE.x - Util::Consts::STG_INFAREA_SIZE.x );

	RectF dst = param.GetDst();
	dst.x = stgAreaX/2 - 640/2;

	float xMoveRate = 
		mpStageSet->GetActors().GetMyShip()->GetPosition().x / stgAreaX * 2 - 1.0f;
	//Util::Console::WriteLine( "xMoveRate = " + boost::lexical_cast<std::string>( xMoveRate ) );

	float xOffset = ( 640 - stgAreaX )/2 * -xMoveRate;
	//Util::Console::WriteLine( "xOffset = " + boost::lexical_cast<std::string>( xOffset ) );

	dst.x += xOffset;

	param.SetDst( dst );
	//Util::Console::WriteLine( "dst.x = " + boost::lexical_cast<std::string>( dst.x ) );
}