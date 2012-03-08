#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace View
{
namespace STG
{
namespace Pause
{
	class IPause
	{
	public:
		virtual bool Update() = 0;
		virtual void Draw() const = 0;

		virtual bool Update_Continue() = 0;
		virtual void Draw_Continue() const = 0;

		virtual ~IPause() {}
	};
}
}
}
}