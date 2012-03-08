#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"


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
	class IActors
	{
	public:
		typedef Mdl::STG::MyShip::PMyShip PMyShip;
		virtual PMyShip GetMyShip() = 0;

		typedef Mdl::STG::Actor::PActor PActor;
		typedef std::list<PActor, boost::fast_pool_allocator<PActor>> ActorList;
		virtual ActorList &GetActorList() = 0;

		typedef Mdl::STG::Bullet::PBullet PBullet;
		typedef std::list<PBullet, boost::fast_pool_allocator<PBullet>> BulletList;
		virtual BulletList &GetBulletList() = 0;
		virtual PBullet DetectBulletHit( 
			const Util::STG::Hit::CircleI &circle ) const = 0;
		virtual Util::Ptr<std::set<PBullet>>::Shared DetectBulletHitAll( 
			const Util::STG::Hit::CircleI &circle ) const = 0;
		virtual PBullet DetectBulletHit( 
			const Util::STG::Hit::RectI &rect ) const = 0;
		virtual Util::Ptr<std::set<PBullet>>::Shared DetectBulletHitAll( 
			const Util::STG::Hit::RectI &rect ) const = 0;

		typedef Mdl::STG::Enemy::PEnemy PEnemy;
		typedef std::list<PEnemy, boost::fast_pool_allocator<PEnemy>> EnemyList;
		virtual EnemyList &GetEnemyList() = 0;
		virtual PEnemy DetectEnemyHit( 
			const Util::STG::Hit::RectI &rect ) const = 0;
		virtual Util::Ptr<std::set<PEnemy>>::Shared DetectEnemyHitAll( 
			const Util::STG::Hit::RectI &rect ) const = 0;

		typedef Mdl::STG::Item::PItem PItem;
		typedef std::list<PItem, boost::fast_pool_allocator<PItem>> ItemList;
		virtual ItemList &GetItemList() = 0;
		virtual PItem DetectItemHit( 
			const Util::STG::Hit::CircleI &circle ) const = 0;
		virtual Util::Ptr<std::set<PItem>>::Shared DetectItemHitAll( 
			const Util::STG::Hit::CircleI &circle ) const = 0;

		typedef Mdl::STG::MyShot::PMyShot PMyShot;
		typedef std::list<PMyShot, boost::fast_pool_allocator<PMyShot>> MyShotList;
		virtual MyShotList &GetMyShotList() = 0;
		virtual PMyShot DetectMyShotHit( 
			const Util::STG::Hit::CircleI &circle ) const = 0;
		virtual Util::Ptr<std::set<PMyShot>>::Shared DetectMyShotHitAll( 
			const Util::STG::Hit::CircleI &circle ) const = 0;
		virtual PMyShot DetectMyShotHit( 
			const Util::STG::Hit::RectI &rect ) const = 0;
		virtual Util::Ptr<std::set<PMyShot>>::Shared DetectMyShotHitAll( 
			const Util::STG::Hit::RectI &rect ) const = 0;

		virtual ~IActors() {}
	};
}
}
}
}