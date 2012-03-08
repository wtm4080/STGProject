#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"
#include "Mdl/STG/Auxs.h"
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
namespace Bullet
{
	class Linear
		: public Base
	{
	public:
		// コンストラクタ
		Linear( PMode pMode, 
			const Util::STG::Locator::LinearF &locator, int hitRadius, 
			const Util::Sprite::DrawParameter &drawParam );

		// 位置の取得
		virtual Util::STG::Vector2DF GetPosition() const;
		// 外力の適用
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

		// ロケータの取得
		Util::STG::Locator::LinearF &GetLocator();
		// 描画パラメータの取得
		const Util::Sprite::DrawParameter &GetDrawParameter() const;
		// 描画パラメータの設定
		void SetDrawParameter( const Util::Sprite::DrawParameter &drawParam );

	private:
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		Auxs mAuxs;

	protected:
		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnDestruct();
		virtual void OnDestruct( float hp );
		virtual void OnErase();
	};
}
}
}
}