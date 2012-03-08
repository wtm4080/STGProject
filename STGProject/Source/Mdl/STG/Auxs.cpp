#include "PCH.h"
#include "Auxs.h"

#include "Ctrl/Scene/STG/STG.h"
#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/Actor/Animation.h"
#include "Mdl/STG/Actor/FadeOut.h"
#include "Mdl/STG/Actor/Particle/Creator.h"
#include "Mdl/STG/Resource/Common.h"
#include "Util/STG/Consts.h"
#include "Util/STG/Hit/Rect.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Util::STG;
using namespace Selene;


Auxs::Auxs( PMode pMode )
	: mpMode( pMode )
{
}


void Auxs::SetMode( PMode pMode )
{
	mpMode = pMode;
}


void Auxs::CreateFadeOut( const Util::Sprite::DrawParameter &drawParam ) const
{
	Actor::PFadeOut pFadeOut( 
		new Actor::FadeOut( mpMode, 
		Hit::RectI( drawParam.GetDst().x, drawParam.GetDst().y, 
		drawParam.GetDst().w, drawParam.GetDst().h, false ) ) );
	pFadeOut->SetFrameNum( Consts::ONERASE_FADEOUT_FRAMENUM );
	pFadeOut->SetDrawParameter( drawParam );

	mpMode->GetActors().GetActors().push_back( Actor::PActor( pFadeOut ) );
}

void Auxs::CreateParticle( const Util::Sprite::DrawParameter &drawParam, 
	unsigned num ) const
{
	using namespace Actor::Particle;

	Parameter param;
	{
		Util::Sprite::DrawParameter dParam = drawParam;
		dParam.SetAlphaBlend( Util::Sprite::AB_ADD );
		param.SetDrawParameter( dParam );
	}
	param.SetPosition( 
		Vector2DF( 
		drawParam.GetDst().x + drawParam.GetDst().w/2, 
		drawParam.GetDst().y + drawParam.GetDst().h/2 ) );
	param.SetSpeedDomain( 8.0f, 14.0f );
	param.SetZoomRateDomain( 0.6f, 1.0f );
	param.SetZoomDecRateDomain( 0.04f, 0.06f );

	Creator creator( mpMode, param );
	creator.Create( num );
}

void Auxs::CreateExplosion( const Vector2DF &pos, const Vector2DF &size, 
	float frameItv ) const
{
	Util::Sprite::DrawParameter drawParam;
	drawParam.SetTexture( mpMode->GetScene()->GetResource()->GetExplosion() );
	drawParam.SetDst( pos.MakeRect( size ) );
	drawParam.SetPriority( View::STG::PRI_EXPLOSION );
	drawParam.SetAlphaBlend( Util::Sprite::AB_ADD );
	drawParam.SetFiltering( false );
	drawParam.SetRotDegree( mpMode->GetRandom()->GetFloat( -180.0f, 180.0f ) );

	Util::Sprite::Animation animation( Point2DI( 96, 96 ), 16, frameItv, drawParam );

	Actor::PAnimation pAnimeObject( 
		new Actor::Animation( 
		mpMode, Hit::RectI( drawParam.GetDst() ), animation ) );

	mpMode->GetActors().GetActors().push_back( Actor::PActor( pAnimeObject ) );
}


Util::Sprite::DrawParameter Auxs::GetBulletRedDrawParam( 
	const Util::STG::Vector2DF &pos, const Util::STG::Vector2DF &size ) const
{
	Util::Sprite::DrawParameter dParam;
	dParam.SetTexture( mpMode->GetScene()->GetResource()->GetBulletRed() );
	dParam.SetSrc( Resource::Common::BULLET_GREEN.GetRect() );
	dParam.SetDst( pos.MakeRect( size ) );
	dParam.SetPriority( View::STG::PRI_ENEMYBULLET );

	return dParam;
}

Util::Sprite::DrawParameter Auxs::GetBulletGreenDrawParam( 
	const Util::STG::Vector2DF &pos, const Util::STG::Vector2DF &size ) const
{
	Util::Sprite::DrawParameter dParam;
	dParam.SetTexture( mpMode->GetScene()->GetResource()->GetBulletGreen() );
	dParam.SetSrc( Resource::Common::BULLET_GREEN.GetRect() );
	dParam.SetDst( pos.MakeRect( size ) );
	dParam.SetPriority( View::STG::PRI_ENEMYBULLET );

	return dParam;
}

Util::Sprite::DrawParameter Auxs::GetBulletBlueDrawParam( 
	const Util::STG::Vector2DF &pos, const Util::STG::Vector2DF &size ) const
{
	Util::Sprite::DrawParameter dParam;
	dParam.SetTexture( mpMode->GetScene()->GetResource()->GetBulletBlue() );
	dParam.SetSrc( Resource::Common::BULLET_GREEN.GetRect() );
	dParam.SetDst( pos.MakeRect( size ) );
	dParam.SetPriority( View::STG::PRI_ENEMYBULLET );

	return dParam;
}

Util::Sprite::DrawParameter Auxs::GetBulletWhiteDrawParam( 
	const Util::STG::Vector2DF &pos, const Util::STG::Vector2DF &size ) const
{
	Util::Sprite::DrawParameter dParam;
	dParam.SetTexture( mpMode->GetScene()->GetResource()->GetBulletWhite() );
	dParam.SetSrc( Resource::Common::BULLET_GREEN.GetRect() );
	dParam.SetDst( pos.MakeRect( size ) );
	dParam.SetPriority( View::STG::PRI_ENEMYBULLET );

	return dParam;
}