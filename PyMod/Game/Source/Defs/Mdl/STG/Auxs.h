#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Forward.h"
#include <boost/python.hpp>
#include "Ctrl/STG/Python/ISTG.h"
#include "Util/Sprite/DrawParameter.h"
#include "Util/STG/Consts.h"
#include "Util/STG/Vector2D.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
	class Auxs
	{
	public:
		Auxs();

		typedef Game::Util::Sprite::DrawParameter DrawParameter;
		Actor::PFadeOut CreateFadeOut( const DrawParameter &drawParam ) const
		{
			return CreateFadeOut( drawParam, 
				Game::Util::STG::Consts::ONERASE_FADEOUT_FRAMENUM );
		}
		Actor::PFadeOut CreateFadeOut( const DrawParameter &drawParam, unsigned frameNum ) const;

		void CreateParticle( const DrawParameter &drawParam ) const
		{
			CreateParticle( drawParam, 10 );
		}
		void CreateParticle( const DrawParameter &drawParam, 
			unsigned num ) const;

		typedef Game::Util::STG::Vector2DF Vector2DF;
		Actor::PAnimation CreateExplosion( const Vector2DF &pos ) const
		{
			return CreateExplosion( pos, Vector2DF( 96.0f, 96.0f ), 1.5f );
		}
		Actor::PAnimation CreateExplosion( const Vector2DF &pos, 
			const Vector2DF &size ) const
		{
			return CreateExplosion( pos, size, 1.5f );
		}
		Actor::PAnimation CreateExplosion( const Vector2DF &pos, 
			const Vector2DF &size, float frameItv ) const;

		Actor::PAnimation CreateExplosion2( const Vector2DF &pos, 
			const Vector2DF &size, float frameItv ) const;
		Actor::PAnimation CreateExplosion2( const Vector2DF &pos, 
			const Vector2DF &size, float frameItv, 
			Selene::Sint32 priority ) const;

		Actor::PAnimation CreateSmoke( const Vector2DF &pos, 
			const Vector2DF &size, float frameItv, 
			Selene::Sint32 priority, float alpha ) const;

		typedef Game::Util::STG::Hit::CircleI CircleI;
		typedef Game::Util::STG::Hit::RectI RectI;

		unsigned EraseActors() const;
		unsigned EraseBullets() const;
		unsigned EraseBullets( const CircleI &hit ) const;
		unsigned EraseBullets( const RectI &hit ) const;
		unsigned EraseEnemies() const;
		unsigned EraseEnemies( const RectI &hit ) const;
		unsigned EraseItems() const;
		unsigned EraseItems( const CircleI &hit ) const;
		unsigned EraseMyShots() const;
		unsigned EraseMyShots( const CircleI &hit ) const;
		unsigned EraseMyShots( const RectI &hit ) const;

		Vector2DF ApplyExRadialForceToMyShip( 
			float force, 
			const Vector2DF &center ) const;
		Vector2DF ApplyExRadialForceToMyShip( 
			float force, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExRadialForceToMyShip( 
			const CircleI &hit, 
			float force ) const;
		Vector2DF ApplyExRadialForceToMyShip( 
			const CircleI &hit, 
			float force, 
			float linearAttenuation, float quadraticAttenuation ) const;

		Vector2DF ApplyExForceToActors( 
			const Vector2DF &force ) const;
		Vector2DF ApplyExForceToActors( 
			const Vector2DF &force, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExRadialForceToActors( 
			float force, 
			const Vector2DF &center ) const;
		Vector2DF ApplyExRadialForceToActors( 
			float force, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;

		Vector2DF ApplyExForceToBullets( 
			const Vector2DF &force ) const;
		Vector2DF ApplyExForceToBullets( 
			const Vector2DF &force, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExForceToBullets( 
			const CircleI &hit, 
			const Vector2DF &force ) const;
		Vector2DF ApplyExForceToBullets( 
			const CircleI &hit, 
			const Vector2DF &force, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExForceToBullets( 
			const RectI &hit, 
			const Vector2DF &force ) const;
		Vector2DF ApplyExForceToBullets( 
			const RectI &hit, 
			const Vector2DF &force, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExRadialForceToBullets( 
			float force, 
			const Vector2DF &center ) const;
		Vector2DF ApplyExRadialForceToBullets( 
			float force, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExRadialForceToBullets( 
			const CircleI &hit, 
			float force ) const;
		Vector2DF ApplyExRadialForceToBullets( 
			const CircleI &hit, 
			float force, 
			float linearAttenuation, float quadraticAttenuation ) const;

		Vector2DF ApplyExForceToEnemies( 
			const Vector2DF &force ) const;
		Vector2DF ApplyExForceToEnemies( 
			const Vector2DF &force, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExForceToEnemies( 
			const RectI &hit, 
			const Vector2DF &force ) const;
		Vector2DF ApplyExForceToEnemies( 
			const RectI &hit, 
			const Vector2DF &force, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExRadialForceToEnemies( 
			float force, 
			const Vector2DF &center ) const;
		Vector2DF ApplyExRadialForceToEnemies( 
			float force, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;

		Vector2DF ApplyExForceToItems( 
			const Vector2DF &force ) const;
		Vector2DF ApplyExForceToItems( 
			const Vector2DF &force, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExForceToItems( 
			const CircleI &hit, 
			const Vector2DF &force ) const;
		Vector2DF ApplyExForceToItems( 
			const CircleI &hit, 
			const Vector2DF &force, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExRadialForceToItems( 
			float force, 
			const Vector2DF &center ) const;
		Vector2DF ApplyExRadialForceToItems( 
			float force, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExRadialForceToItems( 
			const CircleI &hit, 
			float force ) const;
		Vector2DF ApplyExRadialForceToItems( 
			const CircleI &hit, 
			float force, 
			float linearAttenuation, float quadraticAttenuation ) const;

		Vector2DF ApplyExForceToMyShots( 
			const Vector2DF &force ) const;
		Vector2DF ApplyExForceToMyShots( 
			const Vector2DF &force, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExForceToMyShots( 
			const CircleI &hit, 
			const Vector2DF &force ) const;
		Vector2DF ApplyExForceToMyShots( 
			const CircleI &hit, 
			const Vector2DF &force, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExForceToMyShots( 
			const RectI &hit, 
			const Vector2DF &force ) const;
		Vector2DF ApplyExForceToMyShots( 
			const RectI &hit, 
			const Vector2DF &force, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExRadialForceToMyShots( 
			float force, 
			const Vector2DF &center ) const;
		Vector2DF ApplyExRadialForceToMyShots( 
			float force, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Vector2DF ApplyExRadialForceToMyShots( 
			const CircleI &hit, 
			float force ) const;
		Vector2DF ApplyExRadialForceToMyShots( 
			const CircleI &hit, 
			float force, 
			float linearAttenuation, float quadraticAttenuation ) const;

		unsigned DestructBullets() const;
		unsigned DestructBullets( const CircleI &hit ) const;
		unsigned DestructBullets( const RectI &hit ) const;
		float ApplyDamageToBullets( float damage ) const;
		float ApplyDamageToBullets( float damage, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;
		float ApplyDamageToBullets( const CircleI &hit, float damage ) const;
		float ApplyDamageToBullets( const CircleI &hit, float damage, 
			float linearAttenuation, float quadraticAttenuation ) const;
		float ApplyDamageToBullets( const RectI &hit, float damage ) const;
		float ApplyDamageToBullets( const RectI &hit, float damage, 
			float linearAttenuation, float quadraticAttenuation ) const;

		unsigned DestructEnemies() const;
		unsigned DestructEnemies( const RectI &hit ) const;
		float ApplyDamageToEnemies( float damage ) const;
		float ApplyDamageToEnemies( float damage, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;
		float ApplyDamageToEnemies( const RectI &hit, float damage ) const;
		float ApplyDamageToEnemies( const RectI &hit, float damage, 
			float linearAttenuation, float quadraticAttenuation ) const;
		Game::Mdl::STG::Enemy::PEnemy ApplyDamageAndGetEnemy( 
			const RectI &hit, float damage ) const;

		unsigned DestructMyShots() const;
		unsigned DestructMyShots( const CircleI &hit ) const;
		unsigned DestructMyShots( const RectI &hit ) const;
		float ApplyDamageToMyShots( float damage ) const;
		float ApplyDamageToMyShots( float damage, 
			const Vector2DF &center, 
			float linearAttenuation, float quadraticAttenuation ) const;
		float ApplyDamageToMyShots( const CircleI &hit, float damage ) const;
		float ApplyDamageToMyShots( const CircleI &hit, float damage, 
			float linearAttenuation, float quadraticAttenuation ) const;
		float ApplyDamageToMyShots( const RectI &hit, float damage ) const;
		float ApplyDamageToMyShots( const RectI &hit, float damage, 
			float linearAttenuation, float quadraticAttenuation ) const;
		float AffectMyShotsByPA( const CircleI &hit, float force, float damage, 
			float linearAttenuation, float quadraticAttenuation, 
			const boost::python::object &callback ) const;
		float GetMyShotsForcibleDamageForPA( const CircleI &hit ) const;

		DrawParameter GetBulletRedDrawParam( 
			const Vector2DF &pos, 
			const Vector2DF &size ) const;
		DrawParameter GetBulletGreenDrawParam( 
			const Vector2DF &pos, 
			const Vector2DF &size ) const;
		DrawParameter GetBulletBlueDrawParam( 
			const Vector2DF &pos, 
			const Vector2DF &size ) const;
		DrawParameter GetBulletWhiteDrawParam( 
			const Vector2DF &pos, 
			const Vector2DF &size ) const;
		DrawParameter GetBulletPurpleDrawParam( 
			const Vector2DF &pos, 
			const Vector2DF &size ) const;

		boost::python::object GetCommonResource() const;

	private:
		boost::python::object mCommonResource;
	};
}
}
}