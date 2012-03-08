#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/Delegate/Delegate.h"


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
namespace Launcher
{
	class NWay
	{
	public:
		typedef Util::Delegate::Delegate1<float> Generator;
		NWay();
		NWay( const Generator &generator );

		void Launch();

		float GetAngle() const;
		void SetAngle( float angle );
		float GetIntervalAngle() const;
		void SetIntervalAngle( float interval );
		unsigned GetNum() const;
		void SetNum( unsigned num );

		Generator GetGenerator() const;
		void SetGenerator( const Generator &generator );

	private:
		Generator mGenerator;
		float mAngle;
		float mIntervalAngle;
		unsigned mNum;
	};
}
}
}
}
}