#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Parameter.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
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
		typedef Ctrl::STG::Mode::IMode *PMode;

		// コンストラクタ
		Creator( PMode pMode, const Parameter &param = Parameter() );

		// パラメータの取得
		const Parameter &GetParameter() const;
		// パラメータの設定
		void SetParameter( const Parameter &param );

		// パーティクル生成
		void Create( unsigned num ) const;
		void Create( unsigned num, const Parameter &param ) const;

	private:
		PMode mpMode;
		Parameter mParam;
	};
}
}
}
}
}