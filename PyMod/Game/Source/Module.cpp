#include "PCH.h"

#include "Defs/Ctrl/Scene.h"
#include "Defs/Ctrl/STG/Conf.h"
#include "Defs/Ctrl/STG/STG.h"
#include "Defs/Mdl/STG/Actor/ActorDefs.h"
#include "Defs/Mdl/STG/Bullet/BulletDefs.h"
#include "Defs/Mdl/STG/Enemy/EnemyDefs.h"
#include "Defs/Mdl/STG/Item/ItemDefs.h"
#include "Defs/Mdl/STG/MyShip/MyShipDefs.h"
#include "Defs/Mdl/STG/MyShot/MyShotDefs.h"
#include "Defs/Mdl/STG/Object.h"
#include "Defs/Util/BulletML/BulletML.h"
#include "Defs/Util/Common.h"
#include "Defs/Util/Console.h"
#include "Defs/Util/Exception.h"
#include "Defs/Util/File/File.h"
#include "Defs/Util/Font/Font.h"
#include "Defs/Util/HitObject.h"
#include "Defs/Util/Input/Input.h"
#include "Defs/Util/LocatorObject.h"
#include "Defs/Util/Sound/Sound.h"
#include "Defs/Util/Sprite/Sprite.h"
#include "Defs/Util/Vector.h"

using namespace boost::python;


BOOST_PYTHON_MODULE( Game )
{
	{
		using namespace Defs::Util;

		BulletML::BulletML::Configurate();
		Common::Configurate();
		Console::Configurate();
		Exception::Configurate();
		File::File::Configurate();
		Font::Font::Configurate();
		HitObject::Configurate();
		Input::Input::Configurate();
		LocatorObject::Configurate();
		Sound::Sound::Configurate();
		Sprite::Sprite::Configurate();
		Vector::Configurate();
	}

	{
		using namespace Defs::Mdl::STG;

		Object::Configurate();

		Actor::ActorDefs::Configurate();
		Bullet::BulletDefs::Configurate();
		Enemy::EnemyDefs::Configurate();
		Item::ItemDefs::Configurate();
		MyShip::MyShipDefs::Configurate();
		MyShot::MyShotDefs::Configurate();
	}

	{
		using namespace Defs::Ctrl;

		Scene::Configurate();
		STG::STG::Configurate();
		STG::Conf::Configurate();
	}
}