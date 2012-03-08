#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IEvent.h"
#include <cassert>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Stage
{
namespace Event
{
	template <class Stage>
	class Base
		: public IEvent
	{
	public:
		virtual void Update()
		{
			OnUpdate();
		}
		virtual void Draw() const
		{
			OnDraw();
		}

		virtual bool IsEnd() const
		{
			return mEnd;
		}
		void SetEnd( bool end = true )
		{
			mEnd = end;
		}

		Stage *GetStage() const
		{
			return mpStage;
		}
		typename Stage::StageSetType *GetStageSet() const
		{
			return mpStage->GetStageSet();
		}
		typedef Ctrl::STG::Mode::IMode *PMode;
		PMode GetMode() const
		{
			return mpStage->GetMode();
		}
		typedef Util::Ptr<Mdl::STG::Resource::Common>::Shared PCommonResource;
		PCommonResource GetCommonResource() const
		{
			return mpStage->GetCommonResource();
		}
		Ctrl::STG::Actors &GetActors() const
		{
			return mpStage->GetActors();
		}

	protected:
		virtual void OnUpdate() = 0;
		virtual void OnDraw() const = 0;

		Base( Stage *pStage )
			: mpStage( pStage )
			, mEnd( false )
		{
			assert( mpStage );
		}

	private:
		Stage *mpStage;
		bool mEnd;
	};
}
}
}
}
}