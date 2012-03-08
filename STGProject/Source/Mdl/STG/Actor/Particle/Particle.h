#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "../Base.h"
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
namespace Actor
{
namespace Particle
{
	class Particle
		: public Base
	{
	public:
		// コンストラクタ
		Particle( Base::PMode pMode, 
			const Util::STG::Vector2DF &pos, 
			const Util::Sprite::DrawParameter &dParam );

		// 位置の取得
		virtual Util::STG::Vector2DF GetPosition() const;
		// 外力の適用
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

		// ロケータの取得
		Util::STG::Locator::LinearF &GetLocator();
		// 描画パラメータの取得
		Util::Sprite::DrawParameter GetDrawParameter() const;
		// 描画パラメータの設定
		void SetDrawParameter( const Util::Sprite::DrawParameter &param );
		// 拡大率の取得
		float GetZoomRate() const;
		// 拡大率の設定
		void SetZoomRate( float rate );
		// 拡大率の減少率の取得
		float GetZoomDecRate() const;
		// 拡大率の減少率の設定
		void SetZoomDecRate( float rate );

	private:
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		float mZoomDecRate, mZoomRateCount;
		Auxs mAuxs;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();

		Util::Sprite::DrawParameter CreateDrawParam() const;
		void ModifyValidRect();
	};
}
}
}
}
}