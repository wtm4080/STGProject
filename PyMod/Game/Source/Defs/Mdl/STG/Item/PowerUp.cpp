#include "PCH.h"
#include "PowerUp.h"

#include "Mdl/STG/MyShip/IMyShip.h"
#include "View/STG/DrawPriority.h"

#include "Defs/Ctrl/STG/STG.h"
#include "Defs/Util/Sprite/Sprite.h"

using namespace Defs::Mdl::STG;
using namespace Item;
using namespace Game::Util::STG;
namespace py = boost::python;
using namespace Selene;


// コンストラクタ
PowerUp::PowerUp( const Vector2DF &pos, float angle )
: Base( pos, angle )
, mDrawParam()
, mEffectCallback()
{
	mDrawParam.SetTexture( 
		py::extract<Game::Util::Sprite::PTexture>( 
		mAuxs.GetCommonResource().attr( "get" )( "itemPowerUp" ) ) );
	mDrawParam.SetSrc( RectF( 0, 0, 32.0f, 32.0f ) );
	mDrawParam.SetDst( pos.MakeRect( 32.0f, 32.0f ) );
	mDrawParam.SetPriority( Game::View::STG::PRI_ITEM );
}


void PowerUp::SetEffectCallback( const py::object &callback )
{
	mEffectCallback = callback;
}


void PowerUp::OnUpdate()
{
	mDrawParam.SetDst( 
		Base::GetPosition().MakeRect( 
		mDrawParam.GetDst().w, mDrawParam.GetDst().h ) );
}

void PowerUp::OnDraw() const
{
	Defs::Util::Sprite::Sprite::draw( mDrawParam );
}

void PowerUp::OnErase()
{
	mAuxs.CreateFadeOut( mDrawParam );
}

void PowerUp::Effect() const
{
	bool result = Defs::Ctrl::STG::STG::getActors()->GetMyShip()->SupplyPower();
	if( mEffectCallback )
	{
		mEffectCallback( result );
	}
}