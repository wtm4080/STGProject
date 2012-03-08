#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Parameter.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Option
{
	class Manager
	{
	public:
		// Setting.txtから読み込む
		static void Read();
		// Setting.txtへ書き込む
		static void Write();

		// 現在の設定を取得
		static const Parameter &GetParameter();

		// スクリーンモードの設定
		static void SetScreenMode( const Parameter &param );
		// BGMボリュームの設定
		static void SetBGMVolume( const Parameter &param );
		// SEボリュームの設定
		static void SetSEVolume( const Parameter &param );
		// コントローラーのアナログスティックの設定
		static void SetAxis();
		// コントローラーのボタンの設定
		static void SetButton();
		// 最大ファイルキャッシュサイズの設定
		static void SetMaxFileCacheSize( const Parameter &param );
		// デフォルトの設定の適用
		static void SetDefault();
	};
}
}
}
}