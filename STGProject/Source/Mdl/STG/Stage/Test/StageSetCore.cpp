#include "PCH.h"
#include "StageSetCore.h"
#include "Resource.h"

using namespace Game;
using namespace Mdl::STG::Stage::Test;
using namespace Mdl::STG::Stage::StageSet;


StageSetCore::StageSetCore( const Parameter &param )
: Base( param )
{
	mpResource = PResource( new Resource() );
	mpBack = PBackground( new Background( this ) );
}


PBackground StageSetCore::GetBackground() const
{
	return mpBack;
}

PResource StageSetCore::GetResource() const
{
	assert( mpResource );

	return mpResource;
}


void StageSetCore::OnUpdate()
{
	mpBack->Update();
}

void StageSetCore::OnDraw() const
{
	mpBack->Draw();
}