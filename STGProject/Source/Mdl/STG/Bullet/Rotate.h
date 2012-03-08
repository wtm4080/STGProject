#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"
#include "Mdl/STG/Auxs.h"
#include "Util/STG/Locator/Rotate.h"


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
	class Rotate
		: public Base
	{
	public:
		// コンストラクタ
		Rotate( PMode pMode, 
			const Util::STG::Locator::RotateF &locator, int hitRadius, 
			const Util::Sprite::DrawParameter &drawParam );

		// 位置の取得
		virtual Util::STG::Vector2DF GetPosition() const;
		// 外力の適用
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

		// ロケータの取得
		Util::STG::Locator::RotateF &GetLocator();
		// 描画パラメータの取得
		const Util::Sprite::DrawParameter &GetDrawParameter() const;
		// 描画パラメータの設定
		void SetDrawParameter( const Util::Sprite::DrawParameter &drawParam );

	private:
		Util::STG::Locator::RotateF mLocator;
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