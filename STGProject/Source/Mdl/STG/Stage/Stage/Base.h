#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IStage.h"
#include "Parameter.h"
#include "Mdl/STG/Stage/Event/IEvent.h"
#include <boost/cast.hpp>
#include <cassert>
#include <list>


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
namespace Stage
{
	template <class StageSet>
	class Base
		: public IStage
	{
	public:
		typedef StageSet StageSetType;

		virtual void Update()
		{
			if( !mpEventList.empty() )
			{
				mpEventList.front()->Update();
			}

			OnUpdate();

			if( !mpEventList.empty() && mpEventList.front()->IsEnd() )
			{
				mpEventList.pop_front();
			}
		}
		virtual void Draw() const
		{
			OnDraw();

			if( !mpEventList.empty() )
			{
				mpEventList.front()->Draw();
			}
		}

		virtual bool IsEnd() const
		{
			return mpEventList.empty();
		}

		virtual boost::python::object GetInternalPyObject()
		{
			return boost::python::object();
		}

		StageSet *GetStageSet() const
		{
			return mpStageSet;
		}
		typedef Ctrl::STG::Mode::IMode *PMode;
		PMode GetMode() const
		{
			return mpStageSet->GetMode();
		}
		typedef Util::Ptr<Mdl::STG::Resource::Common>::Shared PCommonResource;
		PCommonResource GetCommonResource() const
		{
			return mpStageSet->GetCommonResource();
		}
		Ctrl::STG::Actors &GetActors() const
		{
			return mpStageSet->GetActors();
		}

	protected:
		virtual void OnUpdate() = 0;
		virtual void OnDraw() const = 0;

		Base( const Parameter &param )
		{
			mpStageSet = 
				boost::polymorphic_downcast<StageSet *>( param.GetStageSet() );

			assert( mpStageSet );
		}

		typedef Util::Ptr<Mdl::STG::Stage::Event::IEvent>::Shared PEvent;
		std::list<PEvent> &GetEventList()
		{
			return mpEventList;
		}

	private:
		StageSet *mpStageSet;
		std::list<PEvent> mpEventList;
	};
}
}
}
}
}