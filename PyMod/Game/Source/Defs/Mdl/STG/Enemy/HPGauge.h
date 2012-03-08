#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/STG/Vector2D.h"
#include "Util/Sprite/DrawParameter.h"
#include "Defs/Mdl/STG/Auxs.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------
namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Enemy
{
	class HPGauge
	{
	public:
		HPGauge( float maxValue );

		void Update();
		void Draw() const;

		void Appear();
		void Disappear();

		float GetMaxValue() const;
		void SetMaxValue( float value );
		float GetValue() const;
		void SetValue( float value );

		float GetVisibleValue() const;

	private:
		Game::Util::STG::Vector2DF mPos;
		Game::Util::Sprite::DrawParameter mDrawParam;
		Auxs mAuxs;

		float mMaxValue;
		float mValue;

		enum STATE
		{
			ST_DISAPPEAR, 
			ST_APPEARING, 
			ST_APPEARED, 
		};
		STATE mState;

		float mVisibleValue;

		void UpdateDrawParam();
	};
}
}
}
}