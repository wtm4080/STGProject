#include "PCH.h"
#include "Manager.h"

#include "Wrapper/ConsoleImpl.h"
#include "Wrapper/FileImpl.h"
#include "Wrapper/FontImpl.h"
#include "Wrapper/InputImpl.h"
#include "Wrapper/SoundImpl.h"
#include "Wrapper/SpriteImpl.h"

#include "Wrapper/SceneImpl.h"
#include "Ctrl/STG/Python/ConfImpl.h"

using namespace Game;
using namespace Util::Python;
namespace py = boost::python;
namespace fs = boost::filesystem;
using namespace std;

namespace
{
	typedef Util::Ptr<Wrapper::IConsole>::Shared PConsoleWrapper;
	PConsoleWrapper pConsoleWrapper;
	typedef Util::Ptr<Wrapper::IFile>::Shared PFileWrapper;
	PFileWrapper pFileWrapper;
	typedef Util::Ptr<Wrapper::IFont>::Shared PFontWrapper;
	PFontWrapper pFontWrapper;
	typedef Util::Ptr<Wrapper::IInput>::Shared PInputWrapper;
	PInputWrapper pInputWrapper;
	typedef Util::Ptr<Wrapper::ISound>::Shared PSoundWrapper;
	PSoundWrapper pSoundWrapper;
	typedef Util::Ptr<Wrapper::ISprite>::Shared PSpriteWrapper;
	PSpriteWrapper pSpriteWrapper;

	typedef Util::Ptr<Wrapper::IScene>::Shared PSceneWrapper;
	PSceneWrapper pSceneWrapper;
	typedef Util::Ptr<Ctrl::STG::Python::IConf>::Shared PSTGConfWrapper;
	PSTGConfWrapper pSTGConfWrapper;
}

namespace
{
	static void AppendPath( py::list &pathList, const py::list &configPathList )
	{
		for( int i = 0; i < py::len( configPathList ); i++ )
		{
			string path = 
				py::extract<string>( configPathList[ i ] );
			pathList.append( fs::absolute( path ).string() );
		}
	}
}

bool Manager::Initialize()
{
	Py_Initialize();

	try
	{
		py::object sys = 
			py::import( "sys" ).attr( "__dict__" );

		py::list pathList;
		{
			sys[ "path" ] = py::list();
			sys[ "path" ].attr( "append" )( 
				fs::absolute( "./Script/Python/src" ).string() );
			sys[ "path" ].attr( "append" )( 
				fs::absolute( "../Script/Python/src" ).string() );
			py::object config = py::import( "Config" );

#if defined(SLN_DEBUG)
#if defined(__X64__)
			AppendPath( pathList, 
				py::list( config.attr( "debugModulePathListX64" ) ) );
#else
			AppendPath( pathList, 
				py::list( config.attr( "debugModulePathList" ) ) );
#endif
#elif defined(SLN_DEVELOP)
#if defined(__X64__)
			AppendPath( pathList, 
				py::list( config.attr( "developModulePathListX64" ) ) );
#else
			AppendPath( pathList, 
				py::list( config.attr( "developModulePathList" ) ) );
#endif
#endif

#if defined(__X64__)
			AppendPath( pathList, 
				py::list( config.attr( "modulePathListX64" ) ) );
#endif
			AppendPath( pathList, 
				py::list( config.attr( "modulePathList" ) ) );
		}
		sys[ "path" ] = pathList;

#ifdef SLN_DEBUG
		{
			boost::wformat fm( L"ImportPathListCount: %d" );
			fm % len( pathList );
			Util::Console::WriteLine( fm.str() );

			for( int i = 0; i < len( pathList ); i++ )
			{
				Util::Console::WriteLine( 
					py::extract<std::wstring>( 
					pathList[ i ] ) );
			}

			Util::Console::WriteLine( L"" );
		}
#endif

		{
			py::object gameModule = py::import( "Game" );

			pConsoleWrapper = 
				PConsoleWrapper( new Wrapper::ConsoleImpl() );
			gameModule.attr( "Console" ).attr( "_setInstance" )( 
				reinterpret_cast<uintptr_t>( 
				pConsoleWrapper.get() ) );
			sys[ "stdout" ] = gameModule.attr( "stdout" );
			sys[ "stderr" ] = gameModule.attr( "stdout" );

			pFileWrapper = 
				PFileWrapper( new Wrapper::FileImpl() );
			gameModule.attr( "File" ).attr( "_setInstance" )( 
				reinterpret_cast<uintptr_t>( 
				pFileWrapper.get() ) );

			pFontWrapper = 
				PFontWrapper( new Wrapper::FontImpl() );
			gameModule.attr( "Font" ).attr( "_setInstance" )( 
				reinterpret_cast<uintptr_t>( 
				pFontWrapper.get() ) );

			pInputWrapper = 
				PInputWrapper( new Wrapper::InputImpl() );
			gameModule.attr( "Input" ).attr( "_setInstance" )( 
				reinterpret_cast<uintptr_t>( 
				pInputWrapper.get() ) );

			pSoundWrapper = 
				PSoundWrapper( new Wrapper::SoundImpl() );
			gameModule.attr( "Sound" ).attr( "_setInstance" )( 
				reinterpret_cast<uintptr_t>( 
				pSoundWrapper.get() ) );

			pSpriteWrapper = 
				PSpriteWrapper( new Wrapper::SpriteImpl() );
			gameModule.attr( "Sprite" ).attr( "_setInstance" )( 
				reinterpret_cast<uintptr_t>( 
				pSpriteWrapper.get() ) );

			pSceneWrapper = 
				PSceneWrapper( new Wrapper::SceneImpl() );
			gameModule.attr( "Scene" ).attr( "_setInstance" )( 
				reinterpret_cast<uintptr_t>( 
				pSceneWrapper.get() ) );

			pSTGConfWrapper = 
				PSTGConfWrapper( new Ctrl::STG::Python::ConfImpl() );
			gameModule.attr( "STGConf" ).attr( "_setInstance" )( 
				reinterpret_cast<uintptr_t>( 
				pSTGConfWrapper.get() ) );
		}
	}
	catch( py::error_already_set const & )
	{
		PyErr_Print();

		return false;
	}

	return true;
}