#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Forward.h"


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
		enum BMLParserType;

		class BMLParserHolder;
		class StageCore;
	}

	class Background;
	class Resource;
	class StageSetCore;

	typedef Util::Ptr<Background>::Shared PBackground;
	typedef Util::Ptr<Resource>::Shared PResource;
}
}
}
}
}