#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
#include "Ctrl/STG/Python/IActors.h"
#include "Mdl/STG/MyShip/IMyShip.h"
#include "Util/Common.h"
#include <list>

#include "Defs/Mdl/STG/Forward.h"
#include "Defs/Mdl/STG/Actor/PyActor.h"
#include "Defs/Mdl/STG/Bullet/BulletML/MLActor.h"
#include "Defs/Mdl/STG/Bullet/PyBullet.h"
#include "Defs/Mdl/STG/Enemy/PyEnemy.h"
#include "Defs/Mdl/STG/Item/PyItem.h"
#include "Defs/Mdl/STG/MyShot/PyMyShot.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Ctrl
{
namespace STG
{
	class Actors
	{
	public:
		typedef Game::Ctrl::STG::Python::IActors IActors;
		typedef Game::Util::Ptr<IActors>::Shared PActors;
		Actors( PActors pActors )
			: mpActors( pActors )
		{}

		typedef IActors::PMyShip PMyShip;
		PMyShip GetMyShip() const
		{
			return mpActors->GetMyShip();
		}

		typedef IActors::ActorList ActorList;
		ActorList &GetActorList() const
		{
			return mpActors->GetActorList();
		}
		ActorList::iterator GetActorListBegin() const
		{
			return mpActors->GetActorList().begin();
		}
		ActorList::iterator GetActorListEnd() const
		{
			return mpActors->GetActorList().end();
		}

		typedef IActors::PBullet PBullet;
		typedef IActors::BulletList BulletList;
		BulletList &GetBulletList() const
		{
			return mpActors->GetBulletList();
		}
		BulletList::iterator GetBulletListBegin() const
		{
			return mpActors->GetBulletList().begin();
		}
		BulletList::iterator GetBulletListEnd() const
		{
			return mpActors->GetBulletList().end();
		}
		PBullet DetectBulletHit( 
			const Game::Util::STG::Hit::CircleI &circle ) const
		{
			return mpActors->DetectBulletHit( circle );
		}
		Game::Util::Ptr<std::set<PBullet>>::Shared DetectBulletHitAll( 
			const Game::Util::STG::Hit::CircleI &circle ) const
		{
			return mpActors->DetectBulletHitAll( circle );
		}
		PBullet DetectBulletHit( 
			const Game::Util::STG::Hit::RectI &rect ) const
		{
			return mpActors->DetectBulletHit( rect );
		}
		Game::Util::Ptr<std::set<PBullet>>::Shared DetectBulletHitAll( 
			const Game::Util::STG::Hit::RectI &rect ) const
		{
			return mpActors->DetectBulletHitAll( rect );
		}

		typedef IActors::PEnemy PEnemy;
		typedef IActors::EnemyList EnemyList;
		EnemyList &GetEnemyList() const
		{
			return mpActors->GetEnemyList();
		}
		EnemyList::iterator GetEnemyListBegin() const
		{
			return mpActors->GetEnemyList().begin();
		}
		EnemyList::iterator GetEnemyListEnd() const
		{
			return mpActors->GetEnemyList().end();
		}
		PEnemy DetectEnemyHit( 
			const Game::Util::STG::Hit::RectI &rect ) const
		{
			return mpActors->DetectEnemyHit( rect );
		}
		Game::Util::Ptr<std::set<PEnemy>>::Shared DetectEnemyHitAll( 
			const Game::Util::STG::Hit::RectI &rect ) const
		{
			return mpActors->DetectEnemyHitAll( rect );
		}

		typedef IActors::PItem PItem;
		typedef IActors::ItemList ItemList;
		ItemList &GetItemList() const
		{
			return mpActors->GetItemList();
		}
		ItemList::iterator GetItemListBegin() const
		{
			return mpActors->GetItemList().begin();
		}
		ItemList::iterator GetItemListEnd() const
		{
			return mpActors->GetItemList().end();
		}
		PItem DetectItemHit( 
			const Game::Util::STG::Hit::CircleI &circle ) const
		{
			return mpActors->DetectItemHit( circle );
		}
		Game::Util::Ptr<std::set<PItem>>::Shared DetectItemHitAll( 
			const Game::Util::STG::Hit::CircleI &circle ) const
		{
			return mpActors->DetectItemHitAll( circle );
		}

		typedef IActors::PMyShot PMyShot;
		typedef IActors::MyShotList MyShotList;
		MyShotList &GetMyShotList() const
		{
			return mpActors->GetMyShotList();
		}
		MyShotList::iterator GetMyShotListBegin() const
		{
			return mpActors->GetMyShotList().begin();
		}
		MyShotList::iterator GetMyShotListEnd() const
		{
			return mpActors->GetMyShotList().end();
		}
		PMyShot DetectMyShotHit( 
			const Game::Util::STG::Hit::CircleI &circle ) const
		{
			return mpActors->DetectMyShotHit( circle );
		}
		Game::Util::Ptr<std::set<PMyShot>>::Shared DetectMyShotHitAll( 
			const Game::Util::STG::Hit::CircleI &circle ) const
		{
			return mpActors->DetectMyShotHitAll( circle );
		}
		PMyShot DetectMyShotHit( 
			const Game::Util::STG::Hit::RectI &rect ) const
		{
			return mpActors->DetectMyShotHit( rect );
		}
		Game::Util::Ptr<std::set<PMyShot>>::Shared DetectMyShotHitAll( 
			const Game::Util::STG::Hit::RectI &rect ) const
		{
			return mpActors->DetectMyShotHitAll( rect );
		}

		typedef Game::Mdl::STG::Actor::PActor PActor;
		void RegisterActor( const boost::python::object &object ) const
		{
			mpActors->GetActorList().push_back( 
				PActor( new Mdl::STG::Actor::PyActor( object ) ) );
		}
		void RegisterActor( PActor pActor ) const
		{
			mpActors->GetActorList().push_back( pActor );
		}

		typedef Game::Mdl::STG::Bullet::PBullet PBullet;
		void RegisterBullet( const boost::python::object &object ) const
		{
			mpActors->GetBulletList().push_back( 
				PBullet( new Mdl::STG::Bullet::PyBullet( object ) ) );
		}
		void RegisterBullet( PBullet pBullet ) const
		{
			mpActors->GetBulletList().push_back( pBullet );
		}

		typedef Game::Mdl::STG::Enemy::PEnemy PEnemy;
		void RegisterEnemy( const boost::python::object &object ) const
		{
			mpActors->GetEnemyList().push_back( 
				PEnemy( new Mdl::STG::Enemy::PyEnemy( object ) ) );
		}
		void RegisterEnemy( PEnemy pEnemy ) const
		{
			mpActors->GetEnemyList().push_back( pEnemy );
		}

		typedef Game::Mdl::STG::Item::PItem PItem;
		void RegisterItem( const boost::python::object &object ) const
		{
			mpActors->GetItemList().push_back( 
				PItem( new Mdl::STG::Item::PyItem( object ) ) );
		}
		void RegisterItem( PItem pItem ) const
		{
			mpActors->GetItemList().push_back( pItem );
		}

		typedef Game::Mdl::STG::MyShot::PMyShot PMyShot;
		void RegisterMyShot( const boost::python::object &object ) const
		{
			mpActors->GetMyShotList().push_back( 
				PMyShot( new Mdl::STG::MyShot::PyMyShot( object ) ) );
		}
		void RegisterMyShot( PMyShot pMyShot ) const
		{
			mpActors->GetMyShotList().push_back( pMyShot );
		}

	private:
		PActors mpActors;
	};
}
}
}