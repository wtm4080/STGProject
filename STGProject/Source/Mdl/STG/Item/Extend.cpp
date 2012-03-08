#include "PCH.h"
#include "Extend.h"

#include "Ctrl/STG/Actors.h"
#include "Mdl/STG/MyShip/IMyShip.h"
#include "Mdl/STG/Resource/Common.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Item;
using namespace Util::STG;


// コンストラクタ
Extend::Extend( PMode pMode, const Vector2DF &pos, float angle )
: Base( pMode, pos, angle )
, mAuxs( pMode )
{
	mDrawParam.SetTexture( Base::GetCommonResource()->GetItemExtend() );
	mDrawParam.SetSrc( Resource::Common::ITEM_EXTEND.GetRect() );
	mDrawParam.SetDst( pos.MakeRect( 
		Resource::Common::ITEM_EXTEND.GetRect().w, 
		Resource::Common::ITEM_EXTEND.GetRect().h ) );
	mDrawParam.SetPriority( View::STG::PRI_ITEM );
}


void Extend::OnUpdate()
{
	mDrawParam.SetDst( 
		Base::GetPosition().MakeRect( 
		mDrawParam.GetDst().w, mDrawParam.GetDst().h ) );
}

void Extend::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}

void Extend::OnErase()
{
	mAuxs.CreateFadeOut( mDrawParam );
}

void Extend::Effect() const
{
	Base::GetActors().GetMyShip()->AddRemainder( 1 );
}