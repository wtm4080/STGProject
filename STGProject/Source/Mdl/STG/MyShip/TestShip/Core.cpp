#include "PCH.h"
#include "Core.h"

#include "Ctrl/STG/Actors.h"
#include "Mdl/STG/MyShip/TypeA/Laser.h"
#include "View/STG/DrawPriority.h"

using namespace Game;
using namespace Mdl::STG;
using namespace MyShip::TestShip;
using namespace Util::STG;
using namespace Selene;

namespace
{
	static const Vector2DF SHIP_SIZE( 64.0f, 64.0f );
}


Core::Core( const MyShip::Parameter &param )
	: Base( param )
{
	mShipDrawParam.SetTexture( 
		Util::Sprite::Manager::LoadTexture( L"MyShip/Triangle.dds" ) );
	mShipDrawParam.SetSrc( RectF( 0, 0, 64, 64 ) );
	mShipDrawParam.SetDst( Base::GetPosition().MakeRect( SHIP_SIZE ) );
	mShipDrawParam.SetPriority( View::STG::PRI_MYSHIP );

	mpLaserTexture = 
		Util::Sprite::Manager::LoadTexture( L"BlueCircle.dds" );
}


void Core::DrawInfArea( const Vector2DF &basePos ) const
{
}


void Core::OnUpdate()
{
	mShipDrawParam.SetDst( Base::GetPosition().MakeRect( SHIP_SIZE ) );
}

void Core::OnDraw() const
{
	Util::Sprite::Manager::Draw( mShipDrawParam );
}


int Core::GetPower() const
{
	return 0;
}

bool Core::SupplyPower()
{
	return false;
}

int Core::GetSpAttack() const
{
	return 0;
}

bool Core::SupplySpAttack()
{
	return false;
}


float Core::GetMoveSpeed() const
{
	return 5.0f;
}


int Core::GetBarrierRadius() const
{
	return 32;
}

int Core::GetItemRetrieveRadius() const
{
	return 96;
}


void Core::Shot()
{
	Base::GetActors().GetMyShots().push_back( 
		MyShot::PMyShot( 
		new MyShip::TypeA::Laser( 
		Base::GetMode(), Base::GetPosition(), 
		mpLaserTexture, mpLaserTexture ) ) );
}

void Core::SpecialAttack()
{
}


void Core::OnDestruction()
{
}

void Core::OnRevival()
{
}

void Core::OnContinue()
{
}


Vector2DI Core::GetShipSize() const
{
	return SHIP_SIZE;
}