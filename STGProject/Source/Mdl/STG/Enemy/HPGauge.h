#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/STG/Vector2D.h"
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
namespace Enemy
{
	class HPGauge
	{
	public:
		typedef Ctrl::STG::Mode::IMode *PMode;
		HPGauge( PMode pMode, float maxValue );

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
		PMode mpMode;
		Util::STG::Vector2DF mPos;
		Util::Sprite::DrawParameter mDrawParam;

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