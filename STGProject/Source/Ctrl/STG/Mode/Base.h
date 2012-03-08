#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "IMode.h"
#include <boost/noncopyable.hpp>
#include "Conf/Holder.h"


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
	class Base
		: public IMode
		, public boost::noncopyable
	{
	public:
		// フレーム毎の更新
		virtual void Update();
		// フレーム毎の描画
		virtual void Draw() const;

		// シーンの取得
		virtual PScene GetScene() const;
		// 現在のステージデータの取得
		virtual const StageData &GetCurrentStageData() const;
		// STG構成オブジェクトの取得
		virtual Actors &GetActors();
		virtual const Actors &GetActors() const;
		// コントローラの取得
		virtual PController GetController() const;
		// デバッグ情報文字列表示フラグの取得
		virtual bool GetDebugStrFlag() const;
		// デバッグ情報文字列表示フラグの設定
		virtual void SetDebugStrFlag( bool flag );
		// オブジェクト用の一意な整数値の生成
		virtual Selene::Uint64 GenObjectId();

	protected:
		// コンストラクタ
		typedef Configuration::Data::StageSet::Id StageSetId;
		Base( PScene pScene, StageSetId stageSetId );

		// STG画面を終了し、タイトル画面へ遷移する
		void End() const;

		// 構成管理オブジェクトの取得
		Conf::Holder &GetConfHolder();
		// コントローラの設定
		void SetController( PController pController );

	private:
		Selene::Uint64 mObjectIdCount;
		PScene mpScene;
		Conf::Holder mConfHolder;
		PController mpController;
		unsigned mContinueWaitCount;
		bool mContinueFlag;
		bool mDebugStrFlag;
		bool mPrevMyShipDisappear;

		// 更新時の処理
		virtual void OnUpdate() = 0;
		// 描画時の処理
		virtual void OnDraw() const = 0;

		// タイトル画面へ遷移
		void ToTitle() const;
	};
}
}
}
}