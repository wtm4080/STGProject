#include "PCH.h"
#include "Manager.h"
#include "Detail/SettingFile.h"
#include "Parameter.h"
#include "Util/Input/STG/Detail/Controller.h"

using namespace Game;
using namespace Game::Ctrl::STG::Option;
using namespace std;
using namespace boost;
using namespace Selene;

namespace
{
	static Parameter mParam;
	static const string DIR_PATH = ".";
	static const string FILE_NAME = "Setting.xml";

	static void InitAxis()
	{
		namespace Input = Util::Input::STG;

		Util::Ptr<Input::Detail::Controller>::Shared 
			pCtrler = Util::Input::Manager::GetSTGController();

		pCtrler->SetAxis( Input::Detail::AXIS_X_MINUS, mParam.GetVKeyXMinus() );
		pCtrler->SetAxis( Input::Detail::AXIS_X_PLUS, mParam.GetVKeyXPlus() );
		pCtrler->SetAxis( Input::Detail::AXIS_Y_MINUS, mParam.GetVKeyYMinus() );
		pCtrler->SetAxis( Input::Detail::AXIS_Y_PLUS, mParam.GetVKeyYPlus() );
	}

	static void InitButton()
	{
		namespace Input = Util::Input::STG;

		Util::Ptr<Input::Detail::Controller>::Shared pCtrler = 
			Util::Input::Manager::GetSTGController();

		pCtrler->SetButton( Input::KEY_Z, mParam.GetVKeyZ() );
		pCtrler->SetButton( Input::KEY_X, mParam.GetVKeyX() );
		pCtrler->SetButton( Input::KEY_C, mParam.GetVKeyC() );
		pCtrler->SetButton( Input::KEY_LSHIFT, mParam.GetVKeyLShift() );
		pCtrler->SetButton( Input::KEY_SPACE, mParam.GetVKeySpace() );
	}
}


// Setting.xmlから読み込む
void Manager::Read()
{
	Detail::SettingFile::Read( DIR_PATH + "/" + FILE_NAME, mParam );

	SetScreenMode( mParam );
	SetBGMVolume( mParam );
	SetSEVolume( mParam );
	InitAxis();
	InitButton();
	SetMaxFileCacheSize( mParam );
}

// Setting.xmlへ書き込む
void Manager::Write()
{
	Detail::SettingFile::Write( DIR_PATH + "/" + FILE_NAME, mParam );
}


// 現在の設定を取得
const Parameter &Manager::GetParameter()
{
	return mParam;
}


// スクリーンモードの設定
void Manager::SetScreenMode( const Parameter &param )
{
	mParam.SetFullScreen( param.IsFullScreen() );

	Util::Core::Manager::GetGraphicsManager()->ChangeScreenMode( mParam.IsFullScreen() );
}

// BGMボリュームの設定
void Manager::SetBGMVolume( const Parameter &param )
{
	mParam.SetBGMVolume( param.GetBGMVolume() );
	if( mParam.GetBGMVolume() > 100 )
	{
		mParam.SetBGMVolume( 100 );
	}

	Util::Sound::Manager::SetStreamVolumes( mParam.GetBGMVolume() / 100.0f );
}

// SEボリュームの設定
void Manager::SetSEVolume( const Parameter &param )
{
	mParam.SetSEVolume( param.GetSEVolume() );
	if( mParam.GetSEVolume() > 100 )
	{
		mParam.SetSEVolume( 100 );
	}

	Util::Sound::Manager::SetStaticVolumes( mParam.GetSEVolume() / 100.0f );
}

// コントローラーのアナログスティックの設定
void Manager::SetAxis()
{
	using namespace Util::Input::STG::Detail;
	auto pController = Util::Input::Manager::GetSTGController();

	mParam.SetVKeyXMinus( pController->GetAxisVirtualKey( AXIS_X_MINUS ) );
	mParam.SetVKeyXPlus( pController->GetAxisVirtualKey( AXIS_X_PLUS ) );
	mParam.SetVKeyYMinus( pController->GetAxisVirtualKey( AXIS_Y_MINUS ) );
	mParam.SetVKeyYPlus( pController->GetAxisVirtualKey( AXIS_Y_PLUS ) );
}

// コントローラーのボタンの設定
void Manager::SetButton()
{
	using namespace Util::Input::STG;
	auto pController = Util::Input::Manager::GetSTGController();

	mParam.SetVKeyZ( pController->GetButtonVirtualKey( KEY_Z ) );
	mParam.SetVKeyX( pController->GetButtonVirtualKey( KEY_X ) );
	mParam.SetVKeyC( pController->GetButtonVirtualKey( KEY_C ) );
	mParam.SetVKeyLShift( pController->GetButtonVirtualKey( KEY_LSHIFT ) );
	mParam.SetVKeySpace( pController->GetButtonVirtualKey( KEY_SPACE ) );
}

// 最大ファイルキャッシュサイズの設定
void Manager::SetMaxFileCacheSize( const Parameter &param )
{
	mParam.SetMaxFileCacheSize( param.GetMaxFileCacheSize() );

	Util::File::Manager::SetMaxCacheSize( mParam.GetMaxFileCacheSize() );
}

// デフォルトの設定の適用
void Manager::SetDefault()
{
	mParam = Parameter();

	SetScreenMode( mParam );
	SetBGMVolume( mParam );
	SetSEVolume( mParam );
	InitAxis();
	InitButton();
	SetMaxFileCacheSize( mParam );
}