#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <Selene.h>
#include "Collision/Manager.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
	class Actors
	{
	public:
		Actors( const Selene::RectF &area );

		void Update();
		void Draw() const;

		typedef Mdl::STG::MyShip::PMyShip PMyShip;
		PMyShip GetMyShip() const;
		void SetMyShip( PMyShip pMyShip );

		typedef Mdl::STG::Actor::PActor PActor;
		typedef std::list<PActor, boost::fast_pool_allocator<PActor>> ActorList;
		ActorList &GetActors();
		const ActorList &GetActors() const;

		typedef Mdl::STG::Bullet::PBullet PBullet;
		typedef std::list<PBullet, boost::fast_pool_allocator<PBullet>> BulletList;
		BulletList &GetBullets();
		const BulletList &GetBullets() const;
		PBullet DetectBulletHit( const Util::STG::Hit::CircleI &circle ) const;
		void DetectBulletHitAll( 
			const Util::STG::Hit::CircleI &circle, 
			std::set<PBullet> &resultSet ) const;
		PBullet DetectBulletHit( const Util::STG::Hit::RectI &rect ) const;
		void DetectBulletHitAll( 
			const Util::STG::Hit::RectI &rect, 
			std::set<PBullet> &resultSet ) const;

		typedef Mdl::STG::Enemy::PEnemy PEnemy;
		typedef std::list<PEnemy, boost::fast_pool_allocator<PEnemy>> EnemyList;
		EnemyList &GetEnemies();
		const EnemyList &GetEnemies() const;
		PEnemy DetectEnemyHit( const Util::STG::Hit::RectI &rect ) const;
		void DetectEnemyHitAll( 
			const Util::STG::Hit::RectI &rect, 
			std::set<PEnemy> &resultSet ) const;

		typedef Mdl::STG::Item::PItem PItem;
		typedef std::list<PItem, boost::fast_pool_allocator<PItem>> ItemList;
		ItemList &GetItems();
		const ItemList &GetItems() const;
		PItem DetectItemHit( const Util::STG::Hit::CircleI &circle ) const;
		void DetectItemHitAll( 
			const Util::STG::Hit::CircleI &circle, 
			std::set<PItem> &resultSet ) const;

		typedef Mdl::STG::MyShot::PMyShot PMyShot;
		typedef std::list<PMyShot, boost::fast_pool_allocator<PMyShot>> MyShotList;
		MyShotList &GetMyShots();
		const MyShotList &GetMyShots() const;
		PMyShot DetectMyShotHit( const Util::STG::Hit::CircleI &circle ) const;
		void DetectMyShotHitAll( 
			const Util::STG::Hit::CircleI &circle, 
			std::set<PMyShot> &resultSet ) const;
		PMyShot DetectMyShotHit( const Util::STG::Hit::RectI &rect ) const;
		void DetectMyShotHitAll( 
			const Util::STG::Hit::RectI &rect, 
			std::set<PMyShot> &resultSet ) const;

	private:
		PMyShip mpMyShip;
		ActorList mActors;
		BulletList mBullets;
		EnemyList mEnemies;
		ItemList mItems;
		MyShotList mMyShots;

		Collision::Manager<PBullet, BulletList> mBulletCollManager;
		Collision::Manager<PEnemy, EnemyList> mEnemyCollManager;
		Collision::Manager<PItem, ItemList> mItemCollManager;
		Collision::Manager<PMyShot, MyShotList> mMyShotCollManager;
	};
}
}
}