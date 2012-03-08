#include "PCH.h"

using namespace Selene;
using namespace Game;


//----------------------------------------------------------------------------------
//
//	メイン関数
//
//----------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
	Util::Console::Create();
#endif

	// Pythonインタプリタの初期化
	bool pyInitStatus = Util::Python::Manager::Initialize();

	//------------------------------------------------------------
	// エンジンアクセス用のコアを生成
	//		複数作成は出来ない
	//------------------------------------------------------------
	if( !Util::Core::Manager::InitEngine() )
	{
		return 0;
	}

	const std::wstring appName = 
		boost::python::extract<std::wstring>( 
		boost::python::import( "Config" ).attr( "appName" ) );

	try
	{
		if( !pyInitStatus )
		{
			throw std::exception( "Pythonインタプリタの初期化に失敗しました" );
		}

		Util::Core::PCore				pCore		= Util::Core::Manager::GetCore();
		Util::Core::PInputManager		pIManager	= pCore->GetInputManager();
		Util::Core::PSoundManager		pSManager	= pCore->GetSoundManager();
		Util::Core::PGraphicsManager	pGManager	= pCore->GetGraphicsManager();
		Util::Core::PSpriteRenderer		pSprite		= Util::Core::Manager::GetSpriteRenderer();

		// タイトルバーに表示するFPSの更新タイミング管理
		Util::RepeatCounter titleBarUpdateCounter( 60 );

		//------------------------------------------------------------
		// メインループ
		//		Seleneを利用する上でのメインループの書き方です
		//		ICore::DoEvent()でOSのイベント処理を行います。
		//------------------------------------------------------------
		while ( pCore->DoEvent( 60 ) )
		{
			// 利用するマネージャーの更新
			pIManager->Update();
			pSManager->Update();
			Util::Sprite::Manager::Update();

			// 画面のクリア
			pGManager->Clear( true, false, ColorF(0, 0, 0) );

			//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// フレームの開始
			//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			pCore->FrameBegin();

			// スプライト内のキャッシュをリセット
			pSprite->CacheReset();

			// シーンの状態更新
			Ctrl::Scene::Manager::UpdateState();

			// スプライトの描画
			// キャッシュにたまったデータを一気に描画します
			pSprite->CacheDraw();

			//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// フレームの終了
			//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			pCore->FrameEnd();

			// 画面の更新
			pGManager->Present();

			// タイトルバーの更新
			titleBarUpdateCounter.UpdateState();
			if( titleBarUpdateCounter.GetRepeatCount() >= 1 )
			{
				boost::wformat fm( L"%s FPS[ %d ]" );
				fm % appName;
				fm % static_cast<int>( pCore->GetFPS() );

				pCore->GetWindow()->SetTitleText( fm.str().c_str() );
			}

			// シーンの終了フラグが立っていたらループを抜ける
			if( Ctrl::Scene::Manager::IsEnd() )
			{
				break;
			}
		}
		// 解放されていないリソースが存在する場合、コンソールにそのリソースを表示する
		std::vector<std::wstring> resourceList;
		Util::Resource::Manager::GetList( resourceList );

		if( resourceList.size() != 0 )
		{
			Util::Console::WriteLine( L"以下のリソースが解放されていません\n" );

			foreach( const std::wstring &rName, resourceList )
			{
				Util::Console::WriteLine( rName );
			}

			pCore->ErrorMessageBox( appName.c_str(), 
				L"解放されていないリソースがあります" );
		}
	}
	catch( boost::python::error_already_set const & )
	{
		PyErr_Print();

		Util::Core::Manager::GetCore()->ErrorMessageBox( appName.c_str(), 
			L"Pythonインタプリタで例外が発生しました" );
	}
	catch( Util::Exception &e )
	{
		Util::Console::WriteLine( 
			Util::ToWide( boost::diagnostic_information( e ) ) );

		Util::Core::Manager::GetCore()->ErrorMessageBox( appName.c_str(), 
			L"例外が発生しました：%s", e.GetErrorMessageBoxInfo().c_str() );
	}
	catch( boost::exception &e )
	{
		Util::Console::WriteLine( 
			Util::ToWide( boost::diagnostic_information( e ) ) );

		Util::Core::Manager::GetCore()->ErrorMessageBox( appName.c_str(), 
			L"例外が発生しました：%s", Util::ToWide( typeid(e).name() ).c_str() );
	}
	catch( std::exception &e )
	{
		Util::Console::WriteLine( Util::ToWide( e.what() ) );

		Util::Core::Manager::GetCore()->ErrorMessageBox( appName.c_str(), 
			L"例外が発生しました：%s", Util::ToWide( typeid(e).name() ).c_str() );
	}
	catch( ... )
	{
		Util::Core::Manager::GetCore()->ErrorMessageBox( appName.c_str(), 
			L"予期しない例外が発生しました" );
	}

	// 後始末
	Ctrl::Scene::Manager::Release();
	Util::Core::Manager::Release();
	Util::File::Manager::Release();
	Util::Input::Manager::Release();
	Util::Resource::Manager::Clear();
	FinalizeEngine();

	return 0;
}