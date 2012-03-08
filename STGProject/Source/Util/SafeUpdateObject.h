#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <cassert>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	template <class Type>
	class SafeUpdateObject
	{
	public:
		// 引数にshared_ptrのコピーを渡しておくことで、UpdateState()内で
		// このオブジェクトを参照しているshared_ptrをすべて破棄するようにしても
		// Update()のスコープを抜けるまではこのオブジェクトが破棄されないようにする
		void Update( typename Ptr<Type>::Shared p )
		{
			assert( p );

			UpdateState();
		}

		virtual ~SafeUpdateObject() {}

	private:
		virtual void UpdateState() = 0;
	};
}
}