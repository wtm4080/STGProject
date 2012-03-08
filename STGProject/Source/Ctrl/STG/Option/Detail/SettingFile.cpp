#include "PCH.h"
#include "SettingFile.h"
#include "../Parameter.h"

using namespace Game;
using namespace Ctrl::STG::Option;
using namespace Detail;
using namespace std;
using namespace Selene;

namespace
{
	static const string ROOT = "Settings";

	static const string FULL_SCREEN = ".FullScreen";
	static const string BGM_VOLUME = ".Volume.BGM";
	static const string SE_VOLUME = ".Volume.SE";
	static const string AXIS_X_MINUS = ".Axis.XMinus";
	static const string AXIS_X_PLUS = ".Axis.XPlus";
	static const string AXIS_Y_MINUS = ".Axis.YMinus";
	static const string AXIS_Y_PLUS = ".Axis.YPlus";
	static const string KEY_Z = ".Key.Z";
	static const string KEY_X = ".Key.X";
	static const string KEY_C = ".Key.C";
	static const string KEY_LSHIFT = ".Key.LShift";
	static const string KEY_SPACE = ".Key.Space";
	static const string MAX_FILE_CACHE_SIZE = ".MaxFileCacheSize";
}


// 設定ファイルを読み込む
void SettingFile::Read( const string &path, Parameter &param )
{
	param = Parameter();

	using namespace boost::property_tree;

	try
	{
		ptree pt;
		read_xml( path, pt );

		if( auto elem = pt.get_optional<bool>( ROOT + FULL_SCREEN ) )
		{
			param.SetFullScreen( elem.get() );
		}
		if( auto elem = pt.get_optional<unsigned>( ROOT + BGM_VOLUME ) )
		{
			param.SetBGMVolume( elem.get() );
		}
		if( auto elem = pt.get_optional<unsigned>( ROOT + SE_VOLUME ) )
		{
			param.SetSEVolume( elem.get() );
		}
		if( auto elem = pt.get_optional<Uint32>( ROOT + AXIS_X_MINUS ) )
		{
			param.SetVKeyXMinus( elem.get() );
		}
		if( auto elem = pt.get_optional<Uint32>( ROOT + AXIS_X_PLUS ) )
		{
			param.SetVKeyXPlus( elem.get() );
		}
		if( auto elem = pt.get_optional<Uint32>( ROOT + AXIS_Y_MINUS ) )
		{
			param.SetVKeyYMinus( elem.get() );
		}
		if( auto elem = pt.get_optional<Uint32>( ROOT + AXIS_Y_PLUS ) )
		{
			param.SetVKeyYPlus( elem.get() );
		}
		if( auto elem = pt.get_optional<Uint32>( ROOT + KEY_Z ) )
		{
			param.SetVKeyZ( elem.get() );
		}
		if( auto elem = pt.get_optional<Uint32>( ROOT + KEY_X ) )
		{
			param.SetVKeyX( elem.get() );
		}
		if( auto elem = pt.get_optional<Uint32>( ROOT + KEY_C ) )
		{
			param.SetVKeyC( elem.get() );
		}
		if( auto elem = pt.get_optional<Uint32>( ROOT + KEY_LSHIFT ) )
		{
			param.SetVKeyLShift( elem.get() );
		}
		if( auto elem = pt.get_optional<Uint32>( ROOT + KEY_SPACE ) )
		{
			param.SetVKeySpace( elem.get() );
		}
		if( auto elem = pt.get_optional<unsigned>( ROOT + MAX_FILE_CACHE_SIZE ) )
		{
			param.SetMaxFileCacheSize( elem.get() );
		}
	}
	catch( const xml_parser_error & )
	{
		// 何もしない
	}
}

// 設定ファイルを書き込む
void SettingFile::Write( const string &path, const Parameter &param )
{
	using namespace boost::property_tree;

	ptree pt;
	pt.add( ROOT + FULL_SCREEN, param.IsFullScreen() );
	pt.add( ROOT + BGM_VOLUME, param.GetBGMVolume() );
	pt.add( ROOT + SE_VOLUME, param.GetSEVolume() );
	pt.add( ROOT + AXIS_X_MINUS, param.GetVKeyXMinus() );
	pt.add( ROOT + AXIS_X_PLUS, param.GetVKeyXPlus() );
	pt.add( ROOT + AXIS_Y_MINUS, param.GetVKeyYMinus() );
	pt.add( ROOT + AXIS_Y_PLUS, param.GetVKeyYPlus() );
	pt.add( ROOT + KEY_Z, param.GetVKeyZ() );
	pt.add( ROOT + KEY_X, param.GetVKeyX() );
	pt.add( ROOT + KEY_C, param.GetVKeyC() );
	pt.add( ROOT + KEY_LSHIFT, param.GetVKeyLShift() );
	pt.add( ROOT + KEY_SPACE, param.GetVKeySpace() );
	pt.add( ROOT + MAX_FILE_CACHE_SIZE, param.GetMaxFileCacheSize() );

	using namespace xml_parser;
	write_xml( path, pt, std::locale(), 
		xml_writer_make_settings( '\t', 1, widen<char>( "utf-8" ) ) );
}