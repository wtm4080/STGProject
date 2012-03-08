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
	class Circle
	{
	public:
		typedef Util::Delegate::Delegate1<float> Generator;
		Circle();
		Circle( const Generator &generator );

		void Launch();

		float GetAngle() const;
		void SetAngle( float angle );
		unsigned GetNum() const;
		void SetNum( unsigned num );

		Generator GetGenerator() const;
		void SetGenerator( const Generator &generator );

	private:
		Generator mGenerator;
		float mAngle;
		unsigned mNum;
	};
}
}
}
}
}