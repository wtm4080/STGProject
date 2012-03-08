#include "PCH.h"
#include "SupplySpAttack.h"

#include "Ctrl/STG/Actors.h"
#include "Mdl/STG/MyShip/IMyShip.h"
#include "Mdl/STG/Resource/Common.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Item;
using namespace Util::STG;


// コンストラクタ
SupplySpAttack::SupplySpAttack( PMode pMode, const Vector2DF &pos, float angle )
: Base( pMode, pos, angle )
, mAuxs( pMode )
{
	mDrawParam.SetTexture( Base::GetCommonResource()->GetItemSpAttack() );
	mDrawParam.SetSrc( Resource::Common::ITEM_SPATTACK.GetRect() );
	mDrawParam.SetDst( pos.MakeRect( 
		Resource::Common::ITEM_SPATTACK.GetRect().w, 
		Resource::Common::ITEM_SPATTACK.GetRect().h ) );
	mDrawParam.SetPriority( View::STG::PRI_ITEM );
}


void SupplySpAttack::OnUpdate()
{
	mDrawParam.SetDst( 
		Base::GetPosition().MakeRect( 
		mDrawParam.GetDst().w, mDrawParam.GetDst().h ) );
}

void SupplySpAttack::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}

void SupplySpAttack::OnErase()
{
	mAuxs.CreateFadeOut( mDrawParam );
}

void SupplySpAttack::Effect() const
{
	Base::GetActors().GetMyShip()->SupplySpAttack();
}