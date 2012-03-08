#include "PCH.h"
#include "Ev02.h"

#include "Ctrl/STG/Actors.h"
#include "Mdl/STG/Stage/Test/TestStage1/Enemy/En01.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Stage::Test;
using namespace TestStage1::Event;
using namespace TestStage1::Enemy;
using namespace Util::STG;


Ev02::Ev02( TestStage1::StageCore *pStage )
	: Base( pStage )
	, mEnemyCreated( false )
	, mwpEnemy()
	, mAfterDestroyedCount( 0 )
{
}


void Ev02::OnUpdate()
{
	if( !mEnemyCreated )
	{
		Mdl::STG::Enemy::PEnemy pEnemy( new En01( Base::GetStageSet() ) );

		mwpEnemy = pEnemy;

		Base::GetActors().GetEnemies().push_back( pEnemy );

		mEnemyCreated = true;
	}

	if( mAfterDestroyedCount == 240 )
	{
		Base::SetEnd();
	}
	else if( mEnemyCreated && mwpEnemy.expired() )
	{
		mAfterDestroyedCount++;
	}
}

void Ev02::OnDraw() const
{
}