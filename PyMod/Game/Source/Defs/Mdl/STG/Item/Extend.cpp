#include "PCH.h"
#include "Extend.h"

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
Extend::Extend( const Vector2DF &pos, float angle )
: Base( pos, angle )
{
	mDrawParam.SetTexture( 
		py::extract<Game::Util::Sprite::PTexture>( 
		mAuxs.GetCommonResource().attr( "get" )( "itemExtend" ) ) );
	mDrawParam.SetSrc( RectF( 0, 0, 32.0f, 32.0f ) );
	mDrawParam.SetDst( pos.MakeRect( 32.0f, 32.0f ) );
	mDrawParam.SetPriority( Game::View::STG::PRI_ITEM );
}


void Extend::OnUpdate()
{
	mDrawParam.SetDst( 
		Base::GetPosition().MakeRect( 
		mDrawParam.GetDst().w, mDrawParam.GetDst().h ) );
}

void Extend::OnDraw() const
{
	Defs::Util::Sprite::Sprite::draw( mDrawParam );
}

void Extend::OnErase()
{
	mAuxs.CreateFadeOut( mDrawParam );
}

void Extend::Effect() const
{
	Defs::Ctrl::STG::STG::getActors()->GetMyShip()->AddRemainder( 1 );
}