#include "PCH.h"
#include "PowerUp.h"

#include "Ctrl/STG/Actors.h"
#include "Mdl/STG/MyShip/IMyShip.h"
#include "Mdl/STG/Resource/Common.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Item;
using namespace Util::STG;


// コンストラクタ
PowerUp::PowerUp( PMode pMode, const Vector2DF &pos, float angle )
: Base( pMode, pos, angle )
, mAuxs( pMode )
{
	mDrawParam.SetTexture( Base::GetCommonResource()->GetItemPowerUp() );
	mDrawParam.SetSrc( Resource::Common::ITEM_POWERUP.GetRect() );
	mDrawParam.SetDst( pos.MakeRect( 
		Resource::Common::ITEM_POWERUP.GetRect().w, 
		Resource::Common::ITEM_POWERUP.GetRect().h ) );
	mDrawParam.SetPriority( View::STG::PRI_ITEM );
}


void PowerUp::OnUpdate()
{
	mDrawParam.SetDst( 
		Base::GetPosition().MakeRect( 
		mDrawParam.GetDst().w, mDrawParam.GetDst().h ) );
}

void PowerUp::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}

void PowerUp::OnErase()
{
	mAuxs.CreateFadeOut( mDrawParam );
}

void PowerUp::Effect() const
{
	Base::GetActors().GetMyShip()->SupplyPower();
}