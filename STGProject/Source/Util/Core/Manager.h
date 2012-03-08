#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Core
{
	class Manager
	{
	public:
		// エンジンの初期化
		// 必ず最初に呼び出すこと
		static bool InitEngine();

		// コアの取得
		static PCore GetCore();
		// スプライト用インターフェイスの取得
		static PSpriteRenderer GetSpriteRenderer();
		// グラフィクスマネージャーの取得
		static PGraphicsManager GetGraphicsManager();
		// ファイルマネージャーの取得
		static PFileManager GetFileManager();
		// サウンドマネージャーの取得
		static PSoundManager GetSoundManager();
		// インプットマネージャーの取得
		static PInputManager GetInputManager();

		// コアの開放
		// 後始末用
		static void Release();
	};
}
}
}