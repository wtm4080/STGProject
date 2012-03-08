#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <boost/python.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace Scene
{
	class Manager
	{
	public:
		// 1フレーム毎の状態更新
		static void UpdateState();

		// シーンの切り替え
		static void ChangeScene( Util::Ptr<Scene::IScene>::Shared pNextScene );
		static void ChangeScene( const boost::python::object &obj );

		// ゲームの終了
		static void End();
		// 終了フラグの取得
		static bool IsEnd();

		typedef Util::Delegate::Delegate0<bool> Delegate;
		// 1フレーム毎に呼び出す関数を追加
		// 引数が0個、戻り値がboolである関数を追加できる
		// 戻り値がfalseになると、その関数は削除される
		static void AddUpdateFunction( const Delegate &func );
		// 追加した更新関数をクリアする
		// 割り込みがある場合は復帰する
		static void ClearUpdateFunction();
		// 状態更新処理に割り込む
		static void Interrupt( const Delegate &func );
		// 割り込まれているかどうか調べる
		static bool IsInterrupted();
		// 割り込みから復帰する
		static void Return();
		// すべての割り込みから復帰する
		static void ReturnAll();

		// シーンの開放
		// 終了時の後始末用
		static void Release();
	};
}
}
}