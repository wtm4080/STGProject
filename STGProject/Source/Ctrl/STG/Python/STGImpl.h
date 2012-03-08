#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "ISTG.h"
#include "ActorsImpl.h"
#include "Ctrl/STG/Mode/IMode.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Python
{
	class STGImpl
		: public ISTG
	{
	public:
		typedef Util::Ptr<Mode::IMode>::Shared PMode;
		STGImpl( PMode pMode )
			: mpMode( pMode )
			, mpActors( new ActorsImpl( pMode->GetActors() ) )
		{}

		virtual PActors GetActors() const
		{
			return mpActors;
		}
		virtual PController GetController() const
		{
			return mpMode->GetController();
		}
		virtual PRandom GetRandom() const
		{
			return mpMode->GetRandom();
		}
		virtual PStage GetNextStage()
		{
			return mpMode->GetNextStage();
		}
		virtual bool GetDebugStrFlag() const
		{
			return mpMode->GetDebugStrFlag();
		}
		virtual void SetDebugStrFlag( bool flag )
		{
			mpMode->SetDebugStrFlag( flag );
		}
		virtual void Restart() const
		{
			mpMode->Restart();
		}
		virtual Selene::Uint64 GenObjectId()
		{
			return mpMode->GenObjectId();
		}

	private:
		PMode mpMode;
		PActors mpActors;
	};
}
}
}
}