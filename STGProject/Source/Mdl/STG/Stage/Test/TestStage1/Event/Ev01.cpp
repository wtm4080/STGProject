#include "PCH.h"
#include "Ev01.h"

#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/MyShip/IMyShip.h"
#include "Mdl/STG/Stage/Test/TestStage1/Enemy/Idiot01a.h"
#include "Mdl/STG/Stage/Test/TestStage1/Enemy/Idiot01b.h"
#include "Mdl/STG/Stage/Test/TestStage1/Enemy/Idiot02.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Stage::Test;
using namespace TestStage1::Event;
using namespace TestStage1::Enemy;
using namespace Util::STG;


Ev01::Ev01( TestStage1::StageCore *pStage )
: Base( pStage )
, mFrameCount( 0 )
, mIdiot01aItv( 10.0f )
, mIdiot01aLeftAppear( true )
, mIdiot01bItv( 8.0f )
{
}


void Ev01::OnUpdate()
{
	mFrameCount++;

	typedef Mdl::STG::Enemy::PEnemy PEnemy;
	auto random = Base::GetMode()->GetRandom();

	if( mFrameCount >= 60 && mFrameCount < 640 )
	{
		mIdiot01aItv.UpdateState();

		for( unsigned i = 0; i < mIdiot01aItv.GetRepeatCount(); i++ )
		{
			Vector2DF 
				initPos( mIdiot01aLeftAppear ? 
					random->GetFloat( 0, 220.0f ) : 
					random->GetFloat( 220.0f, 440.0f ), 
					-24.0f ), 
				targetPos( mIdiot01aLeftAppear ? 
					random->GetFloat( 220.0f, 220.0f * 1.5f ) : 
					random->GetFloat( 220.0f * 0.5f, 220.0f ), 
					200.0f );

			mIdiot01aLeftAppear = !mIdiot01aLeftAppear;

			Base::GetActors().GetEnemies().push_back( PEnemy( 
				new Idiot01a( Base::GetStageSet(), initPos, targetPos, 3.0f, 15.0f ) ) );
		}
	}

	if( mFrameCount >= 640 && mFrameCount <= 120 + 500*3 )
	{
		mIdiot01bItv.UpdateState();

		for( unsigned i = 0; i < mIdiot01bItv.GetRepeatCount(); i++ )
		{
			Vector2DF 
				initPos( random->GetBool() ? -24.0f : 440.0f - 24.0f, 
					random->GetFloat( 100.0f, 200.0f ) ), 
				targetPos( random->GetFloat( 220.0f * 0.5f, 220.0f * 1.5f ), 
					random->GetFloat( 125.0f, 175.0f ) );

			Base::GetActors().GetEnemies().push_back( PEnemy( 
				new Idiot01b( Base::GetStageSet(), initPos, targetPos ) ) );
		}
	}

	if( mFrameCount == 120 )
	{
		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 64.0f, -32.0f ), true ) ) );
		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 440.0f - 64.0f, -32.0f ), true ) ) );
	}
	else if( mFrameCount == 120 + 500 )
	{
		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 96.0f, -32.0f ), false ) ) );
		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 96.0f, -96.0f ), true ) ) );

		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 440.0f - 96.0f, -32.0f ), false ) ) );
		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 440.0f - 96.0f, -96.0f ), true ) ) );
	}
	else if( mFrameCount == 120 + 500*2 )
	{
		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 64.0f, -32.0f ), false ) ) );
		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 64.0f, -96.0f ), false ) ) );
		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 128.0f, -32.0f ), false ) ) );
		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 128.0f, -96.0f ), false ) ) );

		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 440.0f - 64.0f, -32.0f ), false ) ) );
		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 440.0f - 64.0f, -96.0f ), false ) ) );
		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 440.0f - 128.0f, -32.0f ), false ) ) );
		Base::GetActors().GetEnemies().push_back( PEnemy( 
			new Idiot02( Base::GetStageSet(), Vector2DF( 440.0f - 128.0f, -96.0f ), false ) ) );
	}
	else if( mFrameCount == 120 + 500*3 )
	{
		for( int i = 0; i < 2; i++ )
		{
			for( int j = 0; j < 4; j++ )
			{
				Base::GetActors().GetEnemies().push_back( PEnemy( 
					new Idiot02( Base::GetStageSet(), 
						Vector2DF( 220.0f - 32.0f*3 + 64.0f*j, -32.0f - 64.0f*i ), true ) ) );
			}
		}
	}

	if( mFrameCount == 120 + 500*3.5f )
	{
		mIdiot01aItv.SetInterval( 4.0f );
	}
	if( mFrameCount >= 120 + 500*3.5f && mFrameCount < 120 + 500*4.8f )
	{
		mIdiot01aItv.UpdateState();

		for( unsigned i = 0; i < mIdiot01aItv.GetRepeatCount(); i++ )
		{
			Vector2DF initPos( random->GetFloat( 24.0f, 440.0f - 24.0f ), -48.0f ), 
				targetPos = Vector2DF().SetUnitVector( 
				initPos.GetAngle( 
				Base::GetActors().GetMyShip()->GetPosition() ) ) * ( 480.0f + 24.0f );

			Base::GetActors().GetEnemies().push_back( PEnemy( 
				new Idiot01a( Base::GetStageSet(), initPos, targetPos, 5.0f ) ) );
		}
	}

	if( mFrameCount == 120 + 500*5 )
	{
		Base::SetEnd();
	}
}

void Ev01::OnDraw() const
{
}