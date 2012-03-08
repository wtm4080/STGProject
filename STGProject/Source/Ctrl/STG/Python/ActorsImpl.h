#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IActors.h"
#include "Ctrl/STG/Actors.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Python
{
	class ActorsImpl
		: public IActors
	{
	public:
		ActorsImpl( Actors &actors )
			: mActors( actors )
		{}

		virtual PMyShip GetMyShip()
		{
			return mActors.GetMyShip();
		}

		virtual ActorList &GetActorList()
		{
			return mActors.GetActors();
		}

		virtual BulletList &GetBulletList()
		{
			return mActors.GetBullets();
		}
		virtual PBullet DetectBulletHit( 
			const Util::STG::Hit::CircleI &circle ) const
		{
			return mActors.DetectBulletHit( circle );
		}
		virtual Util::Ptr<std::set<PBullet>>::Shared DetectBulletHitAll( 
			const Util::STG::Hit::CircleI &circle ) const
		{
			Util::Ptr<std::set<PBullet>>::Shared pResultSet( new std::set<PBullet>() );
			mActors.DetectBulletHitAll( circle, *pResultSet );
			return pResultSet;
		}
		virtual PBullet DetectBulletHit( 
			const Util::STG::Hit::RectI &rect ) const
		{
			return mActors.DetectBulletHit( rect );
		}
		virtual Util::Ptr<std::set<PBullet>>::Shared DetectBulletHitAll( 
			const Util::STG::Hit::RectI &rect ) const
		{
			Util::Ptr<std::set<PBullet>>::Shared pResultSet( new std::set<PBullet>() );
			mActors.DetectBulletHitAll( rect, *pResultSet );
			return pResultSet;
		}

		virtual EnemyList &GetEnemyList()
		{
			return mActors.GetEnemies();
		}
		virtual PEnemy DetectEnemyHit( 
			const Util::STG::Hit::RectI &rect ) const
		{
			return mActors.DetectEnemyHit( rect );
		}
		virtual Util::Ptr<std::set<PEnemy>>::Shared DetectEnemyHitAll( 
			const Util::STG::Hit::RectI &rect ) const
		{
			Util::Ptr<std::set<PEnemy>>::Shared pResultSet( new std::set<PEnemy>() );
			mActors.DetectEnemyHitAll( rect, *pResultSet );
			return pResultSet;
		}

		virtual ItemList &GetItemList()
		{
			return mActors.GetItems();
		}
		virtual PItem DetectItemHit( 
			const Util::STG::Hit::CircleI &circle ) const
		{
			return mActors.DetectItemHit( circle );
		}
		virtual Util::Ptr<std::set<PItem>>::Shared DetectItemHitAll( 
			const Util::STG::Hit::CircleI &circle ) const
		{
			Util::Ptr<std::set<PItem>>::Shared pResultSet( new std::set<PItem>() );
			mActors.DetectItemHitAll( circle, *pResultSet );
			return pResultSet;
		}

		virtual MyShotList &GetMyShotList()
		{
			return mActors.GetMyShots();
		}
		virtual PMyShot DetectMyShotHit( 
			const Util::STG::Hit::CircleI &circle ) const
		{
			return mActors.DetectMyShotHit( circle );
		}
		virtual Util::Ptr<std::set<PMyShot>>::Shared DetectMyShotHitAll( 
			const Util::STG::Hit::CircleI &circle ) const
		{
			Util::Ptr<std::set<PMyShot>>::Shared pResultSet( new std::set<PMyShot>() );
			mActors.DetectMyShotHitAll( circle, *pResultSet );
			return pResultSet;
		}
		virtual PMyShot DetectMyShotHit( 
			const Util::STG::Hit::RectI &rect ) const
		{
			return mActors.DetectMyShotHit( rect );
		}
		virtual Util::Ptr<std::set<PMyShot>>::Shared DetectMyShotHitAll( 
			const Util::STG::Hit::RectI &rect ) const
		{
			Util::Ptr<std::set<PMyShot>>::Shared pResultSet( new std::set<PMyShot>() );
			mActors.DetectMyShotHitAll( rect, *pResultSet );
			return pResultSet;
		}

	private:
		Actors &mActors;
	};
}
}
}
}