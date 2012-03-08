#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"
#include "Util/STG/Locator/Linear.h"
#include "Util/Sprite/DrawParameter.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
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
		FadeOut( PMode pMode, const Util::STG::Hit::RectI &validRect );

		// 位置の取得
		virtual Util::STG::Vector2DF GetPosition() const;
		// 外力の適用
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

		// 描画パラメータの取得
		Util::Sprite::DrawParameter GetDrawParameter() const;
		// 描画パラメータの設定
		void SetDrawParameter( const Util::Sprite::DrawParameter &param );
		// 消失するまでの総フレーム数の取得
		unsigned GetFrameNum() const;
		// 消失するまでの総フレーム数の設定
		void SetFrameNum( unsigned num );
		// フレームカウントの取得
		unsigned GetFrameCount() const;
		// フレームカウントの設定
		void SetFrameCount( unsigned count );

	private:
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		float mMaxAlpha;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();
	};
}
}
}
}