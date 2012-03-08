#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/numeric/interval.hpp>


//----------------------------------------------------------------------------------
//	Const Values
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Consts
{
	// 画面のサイズ
	static const Selene::Point2DI SCREEN_SIZE( 640, 480 );
	// STG画面の情報表示領域のサイズ
	static const Selene::Point2DI STG_INFAREA_SIZE( 200, 480 );

	namespace Sound
	{
		// サウンドのボリュームの定義域
		static const boost::numeric::interval<float> VOLUME_ITV( 0.0f, 1.0f );

		// 再生時間自動設定
		static const float PLAY_TIME_AUTO = -1.0f;

		// 読み込み元パス
		static const std::wstring LOAD_TOP_PATH_SE = L"SE/";
		static const std::wstring LOAD_TOP_PATH_BGM = L"BGM/";
	}

	namespace Sprite
	{
		// 読み込み元パス
		static const std::wstring LOAD_TOP_PATH = L"Graphics/";
	}

	namespace File
	{
		// 復号化用Pass
		static const char CRYPT_PASS[] = "qawsedrftgyhujikolp";
	}

	namespace Font
	{
		// 読み込み元パス
		static const std::wstring LOAD_TOP_PATH = L"Font/";
	}
}
}
}