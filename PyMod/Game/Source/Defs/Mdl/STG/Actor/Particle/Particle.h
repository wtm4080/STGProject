#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Defs/Mdl/STG/Actor/Base.h"
#include "Defs/Mdl/STG/Actor/ActorDefs.h"
#include "Defs/Mdl/STG/Auxs.h"
#include "Util/STG/Locator/Linear.h"
#include "Util/Sprite/DrawParameter.h"


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
namespace Particle
{
	class Particle
		: public Base
	{
	public:
		// コンストラクタ
		typedef Game::Util::Sprite::DrawParameter DrawParameter;
		Particle( const Game::Util::STG::Vector2DF &pos, 
			const DrawParameter &dParam );

		// 位置の取得
		virtual Game::Util::STG::Vector2DF GetPosition() const;
		// 外力の適用
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( 
			const Game::Util::STG::Vector2DF &vec );

		// ロケータの取得
		Game::Util::STG::Locator::LinearF &GetLocator();
		// 描画パラメータの取得
		DrawParameter GetDrawParameter() const;
		// 描画パラメータの設定
		void SetDrawParameter( const DrawParameter &param );
		// 拡大率の取得
		float GetZoomRate() const;
		// 拡大率の設定
		void SetZoomRate( float rate );
		// 拡大率の減少率の取得
		float GetZoomDecRate() const;
		// 拡大率の減少率の設定
		void SetZoomDecRate( float rate );
		// 回転速度の取得
		float GetRotSpeed() const;
		// 回転速度の設定
		void SetRotSpeed( float speed );

	private:
		Game::Util::STG::Locator::LinearF mLocator;
		DrawParameter mDrawParam;
		float mZoomDecRate, mZoomRateCount;
		float mRotSpeed;
		Auxs mAuxs;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();

		DrawParameter CreateDrawParam() const;
		void ModifyValidRect();

		friend ActorDefs;
	};
}
}
}
}
}