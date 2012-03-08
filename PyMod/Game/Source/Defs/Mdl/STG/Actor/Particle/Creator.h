#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Parameter.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Actor
{
namespace Particle
{
	class Creator
	{
	public:
		// コンストラクタ
		Creator( const Parameter &param );

		// パラメータの取得
		Parameter GetParameter() const;
		// パラメータの設定
		void SetParameter( const Parameter &param );

		// パーティクル生成
		void Create( unsigned num ) const;

	private:
		Parameter mParam;
	};
}
}
}
}
}