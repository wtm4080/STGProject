#include "PCH.h"
#include "Base.h"

#include "Ctrl/Scene/STG/STG.h"
#include "Ctrl/Scene/STG/Title.h"
#include "Mdl/STG/MyShip/IMyShip.h"
#include "Mdl/STG/Resource/Common.h"
#include "Mdl/STG/Stage/StageSet/IStageSet.h"
#include "View/STG/DrawPriority.h"


namespace
{
	static const unsigned CONTINUE_WAIT_FRAME_NUM = 90;
}

using namespace Game;
using namespace Ctrl::STG;
using namespace Mode;
using namespace std;


// コンストラクタ
Base::Base( PScene pScene, StageSetId stageSetId )
: mObjectIdCount( 0 )
, mpScene( pScene )
, mContinueWaitCount( CONTINUE_WAIT_FRAME_NUM )
, mContinueFlag( false )
#ifdef SLN_DEBUG
, mDebugStrFlag( true )
#else
, mDebugStrFlag( false )
#endif
, mPrevMyShipDisappear( false )
{
}


// フレーム毎の更新
void Base::Update()
{
	mConfHolder.GetStageSet()->Update();
	mConfHolder.GetActors().Update();

	OnUpdate();

	{
		auto pMyShip = mConfHolder.GetActors().GetMyShip();
		auto pStageSet = mConfHolder.GetStageSet();

		if( pMyShip->GetRemainder() == 0 && mContinueWaitCount == 0 )
		{
			if( !mContinueFlag )
			{
				mpScene->PauseForContinue();

				mContinueFlag = true;
			}
			else
			{
				pMyShip->Continue();

				mContinueWaitCount = CONTINUE_WAIT_FRAME_NUM;
				mContinueFlag = false;

				pStageSet->OnContinue();
			}
		}
		else if( pMyShip->GetRemainder() == 0 )
		{
			mContinueWaitCount--;
		}

		if( !mPrevMyShipDisappear && pMyShip->IsDisappeared() )
		{
			pStageSet->OnMyShipDestruction();
		}
		else if( mPrevMyShipDisappear && !pMyShip->IsDisappeared() )
		{
			pStageSet->OnMyShipRevival();
		}
		mPrevMyShipDisappear = pMyShip->IsDisappeared();
	}

	if( mConfHolder.GetStageSet()->IsEnd() )
	{
		End();
	}
}

// フレーム毎の描画
void Base::Draw() const
{
	GetActors().Draw();
	mConfHolder.GetStageSet()->Draw();

	OnDraw();

	if( mDebugStrFlag )
	{
		static Util::RepeatCounter debugStrUpdateInterval( 20.0f );

		static size_t 
			actorNum = GetActors().GetActors().size(), 
			bulletNum = GetActors().GetBullets().size(), 
			enemyNum = GetActors().GetEnemies().size(), 
			itemNum = GetActors().GetItems().size(), 
			myShotNum = GetActors().GetMyShots().size();

		debugStrUpdateInterval.UpdateState();
		if( debugStrUpdateInterval.GetRepeatCount() >= 1 )
		{
			actorNum = GetActors().GetActors().size();
			bulletNum = GetActors().GetBullets().size();
			enemyNum = GetActors().GetEnemies().size();
			itemNum = GetActors().GetItems().size();
			myShotNum = GetActors().GetMyShots().size();
		}

		Util::Font::PFont pFont = 
			GetScene()->GetResource()->GetFont16( View::STG::PRI_DEBUG_STR, false );

		boost::wformat 
			fm( L"ActorNum: %u\nBulletNum: %u\nEnemyNum: %u\nItemNum: %u\nMyShotNum: %u" );
		fm % actorNum;
		fm % bulletNum;
		fm % enemyNum;
		fm % itemNum;
		fm % myShotNum;

		using namespace Selene;
		Point2DF pos( 0, 0 );
		ColorF color;
		pFont->Draw( pos, color, fm.str() );
	}
}


// シーンの取得
Base::PScene Base::GetScene() const
{
	return mpScene;
}

// 現在のステージデータの取得
const IMode::StageData &Base::GetCurrentStageData() const
{
	return mConfHolder.GetCurrentStageData();
}

// STG構成オブジェクトの取得
Actors &Base::GetActors()
{
	return mConfHolder.GetActors();
}

const Actors &Base::GetActors() const
{
	return mConfHolder.GetActors();
}


// STG画面を終了し、タイトル画面へ遷移する
void Base::End() const
{
	View::FadeOut::Begin( 30, View::STG::PRI_FADE_EFFECT, 
		GetScene()->GetDrawDelegate(), View::FadeOut::Delegate( this, &Base::ToTitle ) );
}

// 構成管理オブジェクトの取得
Conf::Holder &Base::GetConfHolder()
{
	return mConfHolder;
}

// コントローラの取得
IMode::PController Base::GetController() const
{
	assert( mpController );

	return mpController;
}

// デバッグ情報文字列表示フラグの取得
bool Base::GetDebugStrFlag() const
{
	return mDebugStrFlag;
}

// オブジェクト用の一意な整数値の生成
Selene::Uint64 Base::GenObjectId()
{
	return mObjectIdCount++;
}

// デバッグ情報文字列表示フラグの設定
void Base::SetDebugStrFlag( bool flag )
{
	mDebugStrFlag = flag;
}

// コントローラの設定
void Base::SetController( PController pController )
{
	assert( pController );

	mpController = pController;
}

// タイトル画面へ遷移
void Base::ToTitle() const
{
	Scene::Manager::ChangeScene( 
		Util::Ptr<Scene::IScene>::Shared( new Scene::STG::Title() ) );
}