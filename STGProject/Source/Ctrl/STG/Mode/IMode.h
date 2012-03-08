#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/Delegate/Delegate.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Mode
{
	class IMode
	{
	public:
		// フレーム毎の更新
		virtual void Update() = 0;
		// フレーム毎の描画
		virtual void Draw() const = 0;

		// シーンの取得
		typedef Ctrl::Scene::STG::STG *PScene;
		virtual PScene GetScene() const = 0;
		// 次のステージを取得する
		typedef Util::Ptr<Mdl::STG::Stage::Stage::IStage>::Shared PStage;
		virtual PStage GetNextStage() = 0;
		// 現在のステージデータの取得
		typedef Configuration::Data::Stage StageData;
		virtual const StageData &GetCurrentStageData() const = 0;
		// STG構成オブジェクトの取得
		virtual Actors &GetActors() = 0;
		virtual const Actors &GetActors() const = 0;
		// コントローラの取得
		typedef Util::Ptr<Util::Input::STG::IController>::Shared PController;
		virtual PController GetController() const = 0;
		// 乱数生成器の取得
		typedef Util::Random::PRandom PRandom;
		virtual PRandom GetRandom() const = 0;
		// デバッグ情報文字列表示フラグの取得
		virtual bool GetDebugStrFlag() const = 0;
		// デバッグ情報文字列表示フラグの設定
		virtual void SetDebugStrFlag( bool flag ) = 0;
		// シーンの再起動
		virtual void Restart() const = 0;
		// オブジェクト用の一意な整数値の生成
		virtual Selene::Uint64 GenObjectId() = 0;

		virtual ~IMode() {}
	};
}
}
}
}