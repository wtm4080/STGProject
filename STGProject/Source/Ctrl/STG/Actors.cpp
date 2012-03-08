#include "PCH.h"
#include "Actors.h"
#include "Mdl/STG/MyShip/IMyShip.h"
#include "Mdl/STG/Actor/IActor.h"
#include "Mdl/STG/Bullet/IBullet.h"
#include "Mdl/STG/Enemy/IEnemy.h"
#include "Mdl/STG/Item/IItem.h"
#include "Mdl/STG/MyShot/IMyShot.h"

#include "Collision/Detector.h"

using namespace std;
using namespace Game;
using namespace Ctrl::STG;
using namespace Mdl::STG;
using namespace Util::STG;
using namespace Selene;

namespace
{
	template <class ObjectContainer>
	void Update( ObjectContainer &oc )
	{
		foreach( ObjectContainer::value_type ptr, oc )
		{
			if( ptr->IsValid() )
			{
				ptr->Update();
			}
		}
	}

	template <class ObjectContainer>
	void Remove( ObjectContainer &oc )
	{
		auto itr = oc.begin();
		while( itr != oc.end() )
		{
			if( !(*itr)->IsValid() )
			{
				oc.erase( itr++ );
			}
			else
			{
				itr++;
			}
		}
	}

	template <class ObjectContainer>
	void Draw( ObjectContainer &oc )
	{
		foreach( ObjectContainer::value_type ptr, oc )
		{
			ptr->Draw();
		}
	}
}


Actors::Actors( const RectF &area )
	: mBulletCollManager( 
	area.x, area.x + area.w, area.y, area.y + area.h, mBullets )
	, mEnemyCollManager( 
	area.x, area.x + area.w, area.y, area.y + area.h, mEnemies )
	, mItemCollManager( 
	area.x, area.x + area.w, area.y, area.y + area.h, mItems )
	, mMyShotCollManager( 
	area.x, area.x + area.w, area.y, area.y + area.h, mMyShots )
{
}


void Actors::Update()
{
	//boost::thread bulletThread( 
	//	boost::bind( 
	//	&Collision::Manager<PBullet, BulletList>::Update, &mBulletCollManager ) );
	//boost::thread enemyThread( 
	//	boost::bind( 
	//	&Collision::Manager<PEnemy, EnemyList>::Update, &mEnemyCollManager ) );
	//boost::thread itemThread( 
	//	boost::bind( 
	//	&Collision::Manager<PItem, ItemList>::Update, &mItemCollManager ) );
	//boost::thread myShotThread( 
	//	boost::bind( 
	//	&Collision::Manager<PMyShot, MyShotList>::Update, &mMyShotCollManager ) );

	//bulletThread.join();
	//enemyThread.join();
	//itemThread.join();
	//myShotThread.join();

	mBulletCollManager.Update();
	mEnemyCollManager.Update();
	mItemCollManager.Update();
	mMyShotCollManager.Update();

	mpMyShip->Update();
	::Update( mActors );
	::Update( mBullets );
	::Update( mEnemies );
	::Update( mItems );
	::Update( mMyShots );

	::Remove( mActors );
	::Remove( mBullets );
	::Remove( mEnemies );
	::Remove( mItems );
	::Remove( mMyShots );
}

void Actors::Draw() const
{
	mpMyShip->Draw();
	::Draw( mActors );
	::Draw( mBullets );
	::Draw( mEnemies );
	::Draw( mItems );
	::Draw( mMyShots );
}


Actors::PMyShip Actors::GetMyShip() const
{
	return mpMyShip;
}

void Actors::SetMyShip( PMyShip pMyShip )
{
	mpMyShip = pMyShip;
}


Actors::ActorList &Actors::GetActors()
{
	return mActors;
}

const Actors::ActorList &Actors::GetActors() const
{
	return mActors;
}


Actors::BulletList &Actors::GetBullets()
{
	return mBullets;
}

const Actors::BulletList &Actors::GetBullets() const
{
	return mBullets;
}

Actors::PBullet Actors::DetectBulletHit( const Hit::CircleI &circle ) const
{
	Collision::Detector_Circle<PBullet> detector( circle );
	return mBulletCollManager.Detect( detector );
}

void Actors::DetectBulletHitAll( 
	const Hit::CircleI &circle, set<PBullet> &resultSet ) const
{
	Collision::Detector_Circle<PBullet> detector( circle );
	mBulletCollManager.DetectAll( detector, resultSet );
}

Actors::PBullet Actors::DetectBulletHit( const Hit::RectI &rect ) const
{
	Collision::Detector_Rect<PBullet> detector( rect );
	return mBulletCollManager.Detect( detector );
}

void Actors::DetectBulletHitAll( 
	const Hit::RectI &rect, set<PBullet> &resultSet ) const
{
	Collision::Detector_Rect<PBullet> detector( rect );
	mBulletCollManager.DetectAll( detector, resultSet );
}


Actors::EnemyList &Actors::GetEnemies()
{
	return mEnemies;
}

const Actors::EnemyList &Actors::GetEnemies() const
{
	return mEnemies;
}

Actors::PEnemy Actors::DetectEnemyHit( const Hit::RectI &rect ) const
{
	Collision::Detector_Rect<PEnemy> detector( rect );
	return mEnemyCollManager.Detect( detector );
}

void Actors::DetectEnemyHitAll( 
	const Hit::RectI &rect, set<PEnemy> &resultSet ) const
{
	Collision::Detector_Rect<PEnemy> detector( rect );
	mEnemyCollManager.DetectAll( detector, resultSet );
}


Actors::ItemList &Actors::GetItems()
{
	return mItems;
}

const Actors::ItemList &Actors::GetItems() const
{
	return mItems;
}

Actors::PItem Actors::DetectItemHit( const Hit::CircleI &circle ) const
{
	Collision::Detector_Circle<PItem> detector( circle );
	return mItemCollManager.Detect( detector );
}

void Actors::DetectItemHitAll( 
	const Hit::CircleI &circle, set<PItem> &resultSet ) const
{
	Collision::Detector_Circle<PItem> detector( circle );
	mItemCollManager.DetectAll( detector, resultSet );
}


Actors::MyShotList &Actors::GetMyShots()
{
	return mMyShots;
}

const Actors::MyShotList &Actors::GetMyShots() const
{
	return mMyShots;
}

Actors::PMyShot Actors::DetectMyShotHit( const Hit::CircleI &circle ) const
{
	Collision::Detector_Circle<PMyShot> detector( circle );
	return mMyShotCollManager.Detect( detector );
}

void Actors::DetectMyShotHitAll( 
	const Hit::CircleI &circle, set<PMyShot> &resultSet ) const
{
	Collision::Detector_Circle<PMyShot> detector( circle );
	mMyShotCollManager.DetectAll( detector, resultSet );
}

Actors::PMyShot Actors::DetectMyShotHit( const Hit::RectI &rect ) const
{
	Collision::Detector_Rect<PMyShot> detector( rect );
	return mMyShotCollManager.Detect( detector );
}

void Actors::DetectMyShotHitAll( 
	const Hit::RectI &rect, set<PMyShot> &resultSet ) const
{
	Collision::Detector_Rect<PMyShot> detector( rect );
	mMyShotCollManager.DetectAll( detector, resultSet );
}