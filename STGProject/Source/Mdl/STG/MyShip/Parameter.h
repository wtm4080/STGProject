#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace MyShip
{
	class Parameter
	{
	public:
		typedef Ctrl::STG::Mode::IMode *PMode;
		PMode GetMode() const { return mpMode; }
		void SetMode( PMode pMode ) { mpMode = pMode; }

		typedef Util::Ptr<Util::Input::STG::IController>::Shared PController;
		PController GetController() const { return mpController; }
		void SetController( PController pController ) { mpController = pController; }

	private:
		PMode mpMode;
		PController mpController;
	};
}
}
}
}