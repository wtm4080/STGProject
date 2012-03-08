#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/Sprite/DrawParameter.h"
#include "Util/STG/Vector2D.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
	class Auxs
	{
	public:
		typedef Ctrl::STG::Mode::IMode *PMode;
		Auxs( PMode pMode );

		void SetMode( PMode pMode );

		void CreateFadeOut( const Util::Sprite::DrawParameter &drawParam ) const;
		void CreateParticle( const Util::Sprite::DrawParameter &drawParam, 
			unsigned num = 10 ) const;
		void CreateExplosion( const Util::STG::Vector2DF &pos, 
			const Util::STG::Vector2DF &size = Util::STG::Vector2DF( 96.0f, 96.0f ), 
			float frameItv = 1.5f ) const;

		Util::Sprite::DrawParameter GetBulletRedDrawParam( 
			const Util::STG::Vector2DF &pos, 
			const Util::STG::Vector2DF &size ) const;
		Util::Sprite::DrawParameter GetBulletGreenDrawParam( 
			const Util::STG::Vector2DF &pos, 
			const Util::STG::Vector2DF &size ) const;
		Util::Sprite::DrawParameter GetBulletBlueDrawParam( 
			const Util::STG::Vector2DF &pos, 
			const Util::STG::Vector2DF &size ) const;
		Util::Sprite::DrawParameter GetBulletWhiteDrawParam( 
			const Util::STG::Vector2DF &pos, 
			const Util::STG::Vector2DF &size ) const;

	private:
		PMode mpMode;
	};
}
}
}