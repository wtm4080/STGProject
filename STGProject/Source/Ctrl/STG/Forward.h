#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
	class Pause;
	class Actors;

	namespace Configuration
	{
		class Manager;

		namespace Data
		{
			class MyShip;
			class StageSet;
			class Stage;
		}

		namespace Detail
		{
			template <class Data, class Target, class Parameter>
			class Holder;
			template <class Target, class Parameter>
			class IInstantiation;
			template <class Target, class Parameter, class Type>
			class Instantiation;
		}
	}

	namespace Mode
	{
		class IMode;
		class Base;
		class Regular;
		class StageSelect;
		class Replay;

		namespace Conf
		{
			class Regular;
			class StageSelect;
			class Replay;
		}
	}

	namespace Option
	{
		class Manager;
		class Parameter;

		namespace Detail
		{
			class SettingFile;
		}
	}

	namespace Python
	{
		class IActors;
		class IConf;
		class ISTG;
	}
}
}
}