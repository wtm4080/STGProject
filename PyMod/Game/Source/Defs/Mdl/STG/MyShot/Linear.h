#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/optional.hpp>
#include "Base.h"
#include "MyShotDefs.h"
#include "Util/Sprite/DrawParameter.h"
#include "Util/STG/Locator/Linear.h"
#include "Defs/Mdl/STG/Auxs.h"
#include "Defs/Util/Sound/Static.h"
#include "Defs/Util/Sprite/Animation/Manager.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace MyShot
{
	class Linear
		: public Base
	{
	public:
		typedef Game::Util::STG::Locator::LinearF Locator;
		typedef Game::Util::Sprite::DrawParameter DrawParameter;
		typedef Util::Sprite::Animation::Manager Animation;
		Linear( const Locator &locator, int hitRadius, 
			const DrawParameter &drawParam, 
			float baseDamage, 
			const boost::optional<Animation> &vanishAnimation = boost::optional<Animation>() );

		typedef Game::Util::STG::Vector2DF Vector2DF;
		virtual Vector2DF GetPosition() const;
		virtual Vector2DF ApplyExternalForce( const Vector2DF &v );

		Locator &GetLocator();

		const DrawParameter &GetDrawParameter() const;
		void SetDrawParameter( const DrawParameter &drawParam );

		float GetRotDegreeCorrection() const;
		void SetRotDegreeCorrection( float degree );

		void SetDestructionCallback( const boost::python::object &callback );

		float GetDamageToBullet() const;
		void SetDamageToBullet( float damage );
		float GetDamageKickbackRateToBullet() const;
		void SetDamageKickbackRateToBullet( float rate );
		void SetDamageToBulletCallback( const boost::python::object &callback );

	private:
		Auxs mAuxs;
		Locator mLocator;
		const float mSpeed;
		DrawParameter mDrawParam;
		float mRotDegreeCorrection;
		boost::optional<Animation> mVanishAnimation;
		boost::python::object mDestructionCallback;
		boost::optional<float> mDamageToBullet, mDamageKickbackRateToBullet;
		boost::python::object mDamageToBulletCallback;

		virtual void OnUpdate();
		virtual void OnDraw() const;

		virtual void OnErase();
		virtual void OnDestruct();
		virtual void OnDestruct( float damage );

		void CreateVanishAnimation() const;

		friend MyShotDefs;
	};
}
}
}
}