#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"
#include "Util/STG/Locator/Linear.h"
#include "Util/Sprite/DrawParameter.h"
#include "ActorDefs.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Actor
{
	class FadeOut
		: public Base
	{
	public:
		// コンストラクタ
		FadeOut( const Game::Util::STG::Hit::RectI &validRect );

		// 位置の取得
		virtual Game::Util::STG::Vector2DF GetPosition() const;
		// 外力の適用
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( 
			const Game::Util::STG::Vector2DF &vec );

		// 描画パラメータの取得
		typedef Game::Util::Sprite::DrawParameter DrawParameter;
		DrawParameter GetDrawParameter() const;
		// 描画パラメータの設定
		void SetDrawParameter( const DrawParameter &param );
		// 消失するまでの総フレーム数の取得
		unsigned GetFrameNum() const;
		// 消失するまでの総フレーム数の設定
		void SetFrameNum( unsigned num );
		// フレームカウントの取得
		unsigned GetFrameCount() const;
		// フレームカウントの設定
		void SetFrameCount( unsigned count );
		// ロケータの取得
		Game::Util::STG::Locator::LinearF &GetLocator();

	private:
		Game::Util::STG::Locator::LinearF mLocator;
		Game::Util::Sprite::DrawParameter mDrawParam;
		float mMaxAlpha;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();

		friend ActorDefs;
	};
}
}
}
}