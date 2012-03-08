#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Ctrl/Scene/IScene.h"
#include <boost/noncopyable.hpp>
#include "Ctrl/STG/Mode/Conf/Regular.h"
#include "Ctrl/STG/Mode/Conf/Replay.h"
#include "Ctrl/STG/Mode/Conf/StageSelect.h"
#include "Ctrl/STG/Python/ISTG.h"
#include "Util/Delegate/Delegate.h"
#include <boost/variant.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace Scene
{
namespace STG
{
	class STG
		: public IScene
		, public boost::noncopyable
	{
	public:
		// 1フレーム毎の状態更新
		virtual void UpdateState();

		// コンストラクタ
		STG( const Ctrl::STG::Mode::Conf::Regular &conf );
		STG( const Ctrl::STG::Mode::Conf::Replay &conf );
		STG( const Ctrl::STG::Mode::Conf::StageSelect &conf );
		// デストラクタ
		~STG();

		// 共通リソースの取得
		typedef Util::Ptr<Mdl::STG::Resource::Common>::Shared PResource;
		PResource GetResource() const;

		// 構成情報の取得
		typedef boost::variant<int, 
			Ctrl::STG::Mode::Conf::Regular, 
			Ctrl::STG::Mode::Conf::Replay, 
			Ctrl::STG::Mode::Conf::StageSelect> STGConf;
		enum CONF_TYPE
		{
			CONF_EMPTY, 

			CONF_REGULAR, 
			CONF_REPLAY, 
			CONF_STAGESELECT, 
		};
		const STGConf GetConf() const;

		// コンティニュー用ポーズ画面の起動
		void PauseForContinue();

		Util::Delegate::Delegate0<> GetDrawDelegate();

	private:
		// STG画面の共通リソース
		PResource mpResource;

		typedef Util::Ptr<Ctrl::STG::Python::ISTG>::Shared PPyInterface;
		PPyInterface mpPyInterface;

		typedef Util::Ptr<Ctrl::STG::Mode::IMode>::Shared PMode;
		PMode mpMode;

		bool mFadeFlag;

		// 構成情報
		STGConf mConf;
		// ポーズ画面起動用StageSetID
		int mStageSetId;

		void Init();
		// 描画
		void Draw();

		void Pause( bool continuing = false );
	};
}
}
}
}