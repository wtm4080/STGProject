#include "PCH.h"
#include "Manager.h"

using namespace Game;
using namespace Util::Core;
using namespace Selene;

namespace
{
	// コアの保持
	static PCore mpCore;
	// スプライト用インターフェイスの保持
	static PSpriteRenderer mpSpriteRenderer;
}


// エンジンの初期化
bool Manager::InitEngine()
{
#ifdef SLN_DEVELOP
	if ( !Selene::InitializeEngine( L"Selene.Develop.dll" ) )
#else // SLN_DEVELOP
#ifdef SLN_DEBUG
	if ( !Selene::InitializeEngine( L"Selene.Debug.dll" ) )
#else // SLN_DEBUG
	if ( !Selene::InitializeEngine( L"Selene.dll" ) )
#endif // SLN_DEBUG
#endif // SLN_DEVELOP
	{
		return false;
	}

	mpCore = MakeIntrusivePtr( CreateCore() );

	const std::wstring appName = 
		boost::python::extract<std::wstring>( 
		boost::python::import( "Config" ).attr( "appName" ) );
	if ( !mpCore->Initialize( appName.c_str(), Consts::SCREEN_SIZE, true, true ) )
	{
		return false;
	}

	// 各種マネージャーの生成
	if( !mpCore->CreateGraphicsManager() || 
		!mpCore->CreateFileManager() || 
		!mpCore->CreateSoundManager() || 
		!mpCore->CreateInputManager() )
	{
		return false;
	}
	if( !( mpSpriteRenderer = 
		Util::MakeIntrusivePtr( mpCore->GetGraphicsManager()->CreateSpriteRenderer() ) ) )
	{
		return false;
	}

	// サウンドのデコード用のプラグインの
	// 入っているディレクトリの場所。
	mpCore->GetSoundManager()->SetPluginDirectory( L"Plugin/Sound" );

	// タイトルバーのテキスト設定
	mpCore->GetWindow()->SetTitleText( appName.c_str() );

	// カーソル表示ON/OFF
	mpCore->GetWindow()->SetShowCursor( false );

	File::Manager::Initialize();

	return true;
}


// コアの取得
PCore Manager::GetCore()
{
	assert( mpCore );

	return mpCore;
}

// スプライト用インターフェイスの取得
PSpriteRenderer Manager::GetSpriteRenderer()
{
	assert( mpSpriteRenderer );

	return mpSpriteRenderer;
}

// グラフィクスマネージャーの取得
PGraphicsManager Manager::GetGraphicsManager()
{
	assert( mpCore );

	return mpCore->GetGraphicsManager();
}

// ファイルマネージャーの取得
PFileManager Manager::GetFileManager()
{
	assert( mpCore );

	return mpCore->GetFileManager();
}

// サウンドマネージャーの取得
PSoundManager Manager::GetSoundManager()
{
	assert( mpCore );

	return mpCore->GetSoundManager();
}

// インプットマネージャーの取得
PInputManager Manager::GetInputManager()
{
	assert( mpCore );

	return mpCore->GetInputManager();
}


// コアの開放
void Manager::Release()
{
	mpSpriteRenderer.reset();
	mpCore.reset();
}