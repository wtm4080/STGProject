#include "PCH.h"
#include "STG.h"

#include "Mdl/STG/MyShip/Parameter.h"
#include "Mdl/STG/Stage/Stage/IStage.h"
#include "Mdl/STG/Stage/StageSet/Parameter.h"
#include "View/STG/DrawPriority.h"

#include "Defs/Util/Console.h"

using namespace boost::python;
using namespace Game;
using namespace Ctrl::STG::Python;
using namespace Selene;
using namespace std;
using namespace Defs::Ctrl::STG;

namespace
{
	class Instance
	{
	public:
		Instance( ISTG *pSTG )
			: mpSTG( pSTG )
			, mpActors( STG::PActors( new Actors( pSTG->GetActors() ) ) )
		{}

		ISTG *GetSTG() const
		{
			return mpSTG;
		}
		STG::PActors GetActors() const
		{
			return mpActors;
		}

	private:
		ISTG *mpSTG;
		STG::PActors mpActors;
	};

	boost::optional<Instance> currentInstance;
	boost::optional<Instance> nextInstance;

	void CheckInstance()
	{
		if( !currentInstance )
		{
			wstring message( L"Invalid STG scene instance" );
			throw exception( Util::ToMultiByte( message ).c_str() );
		}
	}
}


void STG::Configurate()
{
	class_<STG>( "STG", no_init )
		.def( "_setInstance", &STG::_setInstance )
		.def( "getActors", &STG::getActors )
		.def( "getController", &STG::getController )
		.def( "getRandom", &STG::getRandom )
		.def( "getNextStage", &STG::getNextStage )
		.def( "getDebugStrFlag", &STG::getDebugStrFlag )
		.def( "setDebugStrFlag", &STG::setDebugStrFlag )
		.def( "restart", &STG::restart )
		.def( "genObjectId", &STG::genObjectId )
		;
	typedef Game::Util::STG::Hit::CircleI CircleI;
	typedef Game::Util::STG::Hit::RectI RectI;
	class_<Actors, boost::noncopyable, PActors>( "STGActors", no_init )
		.def( "getMyShip", &Actors::GetMyShip )
		.def( "getActorRange", range( &Actors::GetActorListBegin, &Actors::GetActorListEnd ) )
		.def( "getBulletRange", range( &Actors::GetBulletListBegin, &Actors::GetBulletListEnd ) )
		.def( "detectBulletHit", static_cast<Actors::PBullet (Actors::*)( const CircleI & ) const>( &Actors::DetectBulletHit ) )
		.def( "detectBulletHit", static_cast<Actors::PBullet (Actors::*)( const RectI & ) const>( &Actors::DetectBulletHit ) )
		.def( "getEnemyRange", range( &Actors::GetEnemyListBegin, &Actors::GetEnemyListEnd ) )
		.def( "detectEnemyHit", &Actors::DetectEnemyHit )
		.def( "getItemRange", range( &Actors::GetItemListBegin, &Actors::GetItemListEnd ) )
		.def( "detectItemHit", &Actors::DetectItemHit )
		.def( "getMyShotRange", range( &Actors::GetMyShotListBegin, &Actors::GetMyShotListEnd ) )
		.def( "detectMyShotHit", static_cast<Actors::PMyShot (Actors::*)( const CircleI & ) const>( &Actors::DetectMyShotHit ) )
		.def( "detectMyShotHit", static_cast<Actors::PMyShot (Actors::*)( const RectI & ) const>( &Actors::DetectMyShotHit ) )
		.def( "registerActor", static_cast<void (Actors::*)( const object & ) const>( &Actors::RegisterActor ) )
		.def( "registerActor", static_cast<void (Actors::*)( Actors::PActor ) const>( &Actors::RegisterActor ) )
		.def( "registerBullet", static_cast<void (Actors::*)( const object & ) const>( &Actors::RegisterBullet ) )
		.def( "registerBullet", static_cast<void (Actors::*)( Actors::PBullet ) const>( &Actors::RegisterBullet ) )
		.def( "registerEnemy", static_cast<void (Actors::*)( const object & ) const>( &Actors::RegisterEnemy ) )
		.def( "registerEnemy", static_cast<void (Actors::*)( Actors::PEnemy ) const>( &Actors::RegisterEnemy ) )
		.def( "registerItem", static_cast<void (Actors::*)( const object & ) const>( &Actors::RegisterItem ) )
		.def( "registerItem", static_cast<void (Actors::*)( Actors::PItem ) const>( &Actors::RegisterItem ) )
		.def( "registerMyShot", static_cast<void (Actors::*)( const object & ) const>( &Actors::RegisterMyShot ) )
		.def( "registerMyShot", static_cast<void (Actors::*)( Actors::PMyShot ) const>( &Actors::RegisterMyShot ) )
		;

	{
		using namespace View::STG;
		enum_<DRAW_PRIORITY>( "STGDrawPriority" )
			.value( "backgroundB3", PRI_BACKGROUND_B3 )
			.value( "backgroundB2", PRI_BACKGROUND_B2 )
			.value( "backgroundB1", PRI_BACKGROUND_B1 )
			.value( "background", PRI_BACKGROUND )
			.value( "background2", PRI_BACKGROUND_2 )
			.value( "background3", PRI_BACKGROUND_3 )
			.value( "background4", PRI_BACKGROUND_4 )
			.value( "enemyB3", PRI_ENEMY_B3 )
			.value( "enemyB2", PRI_ENEMY_B2 )
			.value( "enemyB1", PRI_ENEMY_B1 )
			.value( "enemy", PRI_ENEMY )
			.value( "enemy2", PRI_ENEMY_2 )
			.value( "enemy3", PRI_ENEMY_3 )
			.value( "enemy4", PRI_ENEMY_4 )
			.value( "scoreRate", PRI_SCORE_RATE )
			.value( "scoreRate2", PRI_SCORE_RATE_2 )
			.value( "scoreRate3", PRI_SCORE_RATE_3 )
			.value( "myShipOptionB3", PRI_MYSHIP_OPTION_B3 )
			.value( "myShipOptionB2", PRI_MYSHIP_OPTION_B2 )
			.value( "myShipOptionB1", PRI_MYSHIP_OPTION_B1 )
			.value( "myShipOption", PRI_MYSHIP_OPTION )
			.value( "myShipOption2", PRI_MYSHIP_OPTION_2 )
			.value( "myShipOption3", PRI_MYSHIP_OPTION_3 )
			.value( "myShipOption4", PRI_MYSHIP_OPTION_4 )
			.value( "myShotB3", PRI_MYSHOT_B3 )
			.value( "myShotB2", PRI_MYSHOT_B2 )
			.value( "myShotB1", PRI_MYSHOT_B1 )
			.value( "myShot", PRI_MYSHOT )
			.value( "myShot2", PRI_MYSHOT_2 )
			.value( "myShot3", PRI_MYSHOT_3 )
			.value( "myShot4", PRI_MYSHOT_4 )
			.value( "itemB3", PRI_ITEM_B3 )
			.value( "itemB2", PRI_ITEM_B2 )
			.value( "itemB1", PRI_ITEM_B1 )
			.value( "item", PRI_ITEM )
			.value( "item2", PRI_ITEM_2 )
			.value( "item3", PRI_ITEM_3 )
			.value( "item4", PRI_ITEM_4 )
			.value( "lockMarkerB3", PRI_LOCKMARKER_B3 )
			.value( "lockMarkerB2", PRI_LOCKMARKER_B2 )
			.value( "lockMarkerB1", PRI_LOCKMARKER_B1 )
			.value( "lockMarker", PRI_LOCKMARKER )
			.value( "lockMarker2", PRI_LOCKMARKER_2 )
			.value( "lockMarker3", PRI_LOCKMARKER_3 )
			.value( "lockMarker4", PRI_LOCKMARKER_4 )
			.value( "myShipB3", PRI_MYSHIP_B3 )
			.value( "myShipB2", PRI_MYSHIP_B2 )
			.value( "myShipB1", PRI_MYSHIP_B1 )
			.value( "myShip", PRI_MYSHIP )
			.value( "myShip2", PRI_MYSHIP_2 )
			.value( "myShip3", PRI_MYSHIP_3 )
			.value( "myShip4", PRI_MYSHIP_4 )
			.value( "myBarrier", PRI_MYBARRIER )
			.value( "paEffect", PRI_PA_EFFECT )
			.value( "explosion", PRI_EXPLOSION )
			.value( "enemyBulletB3", PRI_ENEMYBULLET_B3 )
			.value( "enemyBulletB2", PRI_ENEMYBULLET_B2 )
			.value( "enemyBulletB1", PRI_ENEMYBULLET_B1 )
			.value( "enemyBullet", PRI_ENEMYBULLET )
			.value( "enemyBullet2", PRI_ENEMYBULLET_2 )
			.value( "enemyBullet3", PRI_ENEMYBULLET_3 )
			.value( "enemyBullet4", PRI_ENEMYBULLET_4 )
			.value( "enemyBulletDamaged", PRI_ENEMYBULLET_DAMAGED )
			.value( "myShipHitMark", PRI_MYSHIP_HITMARK )
			.value( "enemyHpGauge", PRI_ENEMY_HPGAUGE )
			.value( "warning", PRI_WARNING )
			.value( "resultB3", PRI_RESULT_B3 )
			.value( "resultB2", PRI_RESULT_B2 )
			.value( "resultB1", PRI_RESULT_B1 )
			.value( "result", PRI_RESULT )
			.value( "result2", PRI_RESULT_2 )
			.value( "result3", PRI_RESULT_3 )
			.value( "result4", PRI_RESULT_4 )
			.value( "infAreaBackB3", PRI_INFAREA_BACK_B3 )
			.value( "infAreaBackB2", PRI_INFAREA_BACK_B2 )
			.value( "infAreaBackB1", PRI_INFAREA_BACK_B1 )
			.value( "infAreaBack", PRI_INFAREA_BACK )
			.value( "infAreaBack2", PRI_INFAREA_BACK_2 )
			.value( "infAreaBack3", PRI_INFAREA_BACK_3 )
			.value( "infAreaBack4", PRI_INFAREA_BACK_4 )
			.value( "infAreaStr", PRI_INFAREA_STR )
			.value( "pauseBackB3", PRI_PAUSE_BACK_B3 )
			.value( "pauseBackB2", PRI_PAUSE_BACK_B2 )
			.value( "pauseBackB1", PRI_PAUSE_BACK_B1 )
			.value( "pauseBack", PRI_PAUSE_BACK )
			.value( "pauseBack2", PRI_PAUSE_BACK_2 )
			.value( "pauseBack3", PRI_PAUSE_BACK_3 )
			.value( "pauseBack4", PRI_PAUSE_BACK_4 )
			.value( "pauseStr", PRI_PAUSE_STR )
			.value( "fadeEffect", PRI_FADE_EFFECT )
			.value( "debugStr", PRI_DEBUG_STR )
			;
	}
}


void STG::_setInstance( uintptr_t p )
{
	if( p )
	{
		if( !currentInstance )
		{
			currentInstance = 
				Instance( reinterpret_cast<ISTG *>( p ) );
		}
		else
		{
			nextInstance = 
				Instance( reinterpret_cast<ISTG *>( p ) );
		}
	}
	else
	{
		if( nextInstance )
		{
			currentInstance = nextInstance;
			nextInstance = boost::optional<Instance>();
		}
		else
		{
			currentInstance = boost::optional<Instance>();
			nextInstance = boost::optional<Instance>();
		}
	}
}

STG::PActors STG::getActors()
{
	CheckInstance();

	return currentInstance->GetActors();
}

Defs::Util::Input::Controller STG::getController()
{
	CheckInstance();

	return Defs::Util::Input::Controller::Controller( 
		currentInstance->GetSTG()->GetController() );
}

STG::PRandom STG::getRandom()
{
	CheckInstance();

	return currentInstance->GetSTG()->GetRandom();
}

STG::PStage STG::getNextStage()
{
	CheckInstance();

	return currentInstance->GetSTG()->GetNextStage();
}

bool STG::getDebugStrFlag()
{
	CheckInstance();

	return currentInstance->GetSTG()->GetDebugStrFlag();
}

void STG::setDebugStrFlag( bool flag )
{
	CheckInstance();

	currentInstance->GetSTG()->SetDebugStrFlag( flag );
}

void STG::restart()
{
	CheckInstance();

	currentInstance->GetSTG()->Restart();
}

Uint64 STG::genObjectId()
{
	CheckInstance();

	return currentInstance->GetSTG()->GenObjectId();
}