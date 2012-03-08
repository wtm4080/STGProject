#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Mdl/STG/Auxs.h"
#include "Util/Sprite/DrawParameter.h"
#include "Util/STG/Locator/Trace.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace MyShip
{
namespace TypeA
{
	class Option
	{
	public:
		typedef Ctrl::STG::Mode::IMode *PMode;
		Option( PMode pMode, const Util::STG::Vector2DF &pos, 
			Util::Sprite::PTexture pOptionTexture, 
			Util::Sprite::PTexture pMissileTexture, 
			Util::Sprite::PTexture pExplosionTexture, 
			float rotAngle = 0 );

		void Update();
		void Draw() const;

		static const Util::STG::Vector2DF &GetDrawSize();
		void SetTargetPosition( const Util::STG::Vector2DF &pos );
		float GetRotateAngle() const;
		void SetRotateAngle( float angle = 0 );

		void LaunchMissile( float circlingAngle ) const;
		void LaunchSpMissile( bool aiming );
		bool IsExistSpMissile();

	private:
		PMode mpMode;
		Util::Sprite::DrawParameter mDrawParam;
		Util::STG::Locator::TraceF mLocator;
		float mRotAngle;
		Util::Sprite::PTexture mpMissileTexture;
		Util::Sprite::PTexture mpExplosionTexture;
		Util::Ptr<MyShot::IMyShot>::Weak mwpSpMissile;
		Auxs mAuxs;
	};
}
}
}
}
}