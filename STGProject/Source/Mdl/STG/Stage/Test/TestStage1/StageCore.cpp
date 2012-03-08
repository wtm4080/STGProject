#include "PCH.h"
#include "StageCore.h"

#include "Event/Ev01.h"
#include "Event/Ev02.h"
#include "Event/Ev03.h"

#include "Ctrl/STG/Actors.h"
#include "Mdl/STG/MyShip/IMyShip.h"
#include "Util/Input/STG/IController.h"

using namespace Game;
using namespace Mdl::STG::Stage::Test::TestStage1;
using namespace Mdl::STG::Stage::Stage;


StageCore::StageCore( const Parameter &param )
: Base( param )
{
	Base::GetEventList().push_back( 
		PEvent( new Event::Ev01( this ) ) );
	Base::GetEventList().push_back( 
		PEvent( new Event::Ev02( this ) ) );
	Base::GetEventList().push_back( 
		PEvent( new Event::Ev03( this ) ) );
}


const BMLParserHolder &StageCore::GetBMLParsers() const
{
	return mBMLParserHolder;
}


void StageCore::OnUpdate()
{
	//if( Util::Input::Manager::GetSTGController()->IsPush( Util::Input::STG::KEY_C ) )
	//{
	//	Base::GetActors().GetMyShip()->SupplyPower();
	//	Base::GetActors().GetMyShip()->SetBarrier( 60 );
	//}
}

void StageCore::OnDraw() const
{
}