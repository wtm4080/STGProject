#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Stage/Stage/Base.h"
#include "../StageSetCore.h"
#include "BMLParserHolder.h"


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
namespace Test
{
namespace TestStage1
{
	class StageCore
		: public Stage::Base<StageSetCore>
	{
	public:
		StageCore( const Stage::Parameter &param );

		const BMLParserHolder &GetBMLParsers() const;

	private:
		BMLParserHolder mBMLParserHolder;

		virtual void OnUpdate();
		virtual void OnDraw() const;
	};
}
}
}
}
}
}