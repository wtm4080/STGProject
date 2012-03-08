#include "PCH.h"
#include "Manager.h"
#include "Initialize.h"
#include "PyScene.h"
#include "Finalizer.h"

using namespace Game;
using namespace Game::Ctrl::Scene;
using namespace Selene;
using namespace std;

namespace
{
	typedef Util::Ptr<IScene>::Shared PScene;

	static PScene mpCurrentScene( new Initialize() );
	static PScene mpOldScene;
	static bool mIsEnd = false;
	static Util::FunctionList mFuncList;
	static stack<Util::FunctionList> mFuncStack;
}


// 1フレーム毎の状態更新
void Manager::UpdateState()
{
	if( mpOldScene )
	{
		mpOldScene.reset();

		ReturnAll();
		ClearUpdateFunction();

		Util::Sound::Manager::StopStatics();
		Util::Sound::Manager::StopStreams();
		Util::Sprite::Manager::ResetShake();

		boost::python::import( "gc" ).attr( "collect" )();
	}

	if( mFuncStack.empty() )
	{
		mFuncList();

		mpCurrentScene->Update( mpCurrentScene );
	}
	else
	{
		mFuncStack.top()();

		if( mFuncStack.top().IsEmpty() )
		{
			Return();
		}
	}

	// Escを押すと終了
	if( Util::Core::Manager::GetInputManager()->GetKeyboard()->GetKeyData( 
		Engine::Input::KEY_ESCAPE ) )
	{
		End();
	}
}


// シーンの切り替え
void Manager::ChangeScene( ::PScene pNextScene )
{
	if( pNextScene )
	{
		mpOldScene = mpCurrentScene;
		mpCurrentScene = pNextScene;
	}
}

void Manager::ChangeScene( const boost::python::object &obj )
{
	ChangeScene( PScene( new PyScene( obj ) ) );
}


// ゲームの終了
void Manager::End()
{
	mIsEnd = true;
}

// 終了フラグの取得
bool Manager::IsEnd()
{
	return mIsEnd;
}


// 1フレーム毎に呼び出す関数を追加
void Manager::AddUpdateFunction( const Delegate &func )
{
	if( mFuncStack.empty() )
	{
		mFuncList.Add( func );
	}
	else
	{
		mFuncStack.top().Add( func );
	}
}

// 追加した更新関数をクリアする
// 割り込みがある場合は復帰する
void Manager::ClearUpdateFunction()
{
	if( IsInterrupted() )
	{
		mFuncStack.pop();
	}
	else
	{
		mFuncList.Clear();
	}
}

// 状態更新処理に割り込む
void Manager::Interrupt( const Delegate &func )
{
	mFuncStack.push( Util::FunctionList() );
	mFuncStack.top().Add( func );
}

// 割り込まれているかどうか調べる
bool Manager::IsInterrupted()
{
	return !mFuncStack.empty();
}

// 割り込みから復帰する
void Manager::Return()
{
	if( IsInterrupted() )
	{
		mFuncStack.pop();
	}
}

// すべての割り込みから復帰する
void Manager::ReturnAll()
{
	while( IsInterrupted() )
	{
		mFuncStack.pop();
	}
}


// シーンの開放
void Manager::Release()
{
	mpCurrentScene.reset();
	mpOldScene.reset();
	ReturnAll();
	ClearUpdateFunction();

	Finalizer::Finalize();
}