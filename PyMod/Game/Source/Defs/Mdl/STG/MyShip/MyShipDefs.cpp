#include "PCH.h"
#include "MyShipDefs.h"

#include "Base.h"

using namespace boost::python;
using namespace Defs::Mdl::STG;
using namespace MyShip;
using namespace Game::Util::STG;


void MyShipDefs::Configurate()
{
	class_<Base, boost::noncopyable, bases<Game::Mdl::STG::MyShip::IMyShip>>( "STGMyShipBase", no_init )
		.def( "update", &Base::Update )
		.def( "draw", &Base::Draw )
		.def( "isHit", &Base::IsHit )
		.def( "isHit_ItemRetrieve", &Base::IsHit_ItemRetrieve )
		.def( "isHit_GetItem", &Base::IsHit_GetItem )
		.def( "destruct", &Base::Destruct )
		.add_property( "barriered", &Base::IsBarriered )
		.add_property( "barrierCount", &Base::GetBarrierCount )
		.def( "setBarrier", &Base::SetBarrier )
		.add_property( "disappeared", &Base::IsDisappeared )
		.add_property( "position", &Base::GetPosition, &Base::SetPosition )
		.def( "applyExternalForce", &Base::ApplyExternalForce )
		.add_property( "remainder", &Base::GetRemainder )
		.def( "addRemainder", &Base::AddRemainder )
		.def( "setInitRemainder", &Base::SetInitRemainder )
		.def( "continue", &Base::Continue )
		.def( "setMoveForbidFlag", &Base::SetMoveForbidFlag )
		.def( "setShotForbidFlag", &Base::SetShotForbidFlag )
		.def( "setSpecialAttackForbidFlag", &Base::SetSpecialAttackForbidFlag )
		;
}