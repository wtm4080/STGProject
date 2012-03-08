#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "StdFwd.h"
#include "SLNFwd.h"
#include "Delegate/Forward.h"
#include "STG/Forward.h"
#include "Input/STG/Forward.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	class Console;
	class Exception;
	class FunctionList;
	class FunctionQueue;
	template <class ElemType>
	class Pager;
	template <class Type>
	class Pool;
	class RepeatCounter;
	template <class Type>
	class SafeUpdateObject;

	template <class T>
	struct Ptr
	{
		typedef boost::shared_ptr<T> Shared;
		typedef boost::weak_ptr<T> Weak;
		typedef boost::intrusive_ptr<T> Intrusive;
	};

	namespace Core
	{
		// コアのインターフェイス
		typedef Ptr<Selene::Engine::ICore>::Intrusive PCore;
		// スプライト用インターフェイス
		typedef Ptr<Selene::Engine::Graphics::Simple::ISpriteRenderer>::Intrusive 
			PSpriteRenderer;
		// グラフィクスマネージャーのインターフェイス
		typedef Selene::Engine::Graphics::IManager *PGraphicsManager;
		// ファイルマネージャーのインターフェイス
		typedef Selene::Engine::File::IManager *PFileManager;
		// サウンドマネージャーのインターフェイス
		typedef Selene::Engine::Sound::IManager *PSoundManager;
		// インプットマネージャーのインターフェイス
		typedef Selene::Engine::Input::IManager *PInputManager;

		class Manager;
	}

	namespace File
	{
		// ファイルのインターフェイス
		typedef Ptr<Selene::Engine::File::IFile>::Intrusive PFile;
		// パックファイルのインターフェイス
		typedef Ptr<Selene::Engine::File::IPackFile>::Intrusive PPackFile;
		// ファイルパスとPFileのマップ
		typedef std::map<std::wstring, PFile, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, PFile>>> 
			FileMap;
		typedef std::pair<std::wstring, PFile> FileMapElemType;

		typedef std::map<std::string, std::string, 
			std::less<std::string>, 
			std::allocator<std::pair<const std::string, std::string>>> 
			PropertyMap;
		typedef std::pair<std::string, std::string> PropMapElem;

		class Manager;
		class Property;
		class IDynamicFile;

		namespace Detail
		{
			class DeviceOfDynamicFile;
			class DynamicFile;
			class ICrypt;
			class SourceOfFile;
			class SyncFile;
		}

		namespace Exception
		{
			class NotFound;
		}
	}

	namespace Font
	{
		class Manager;
		class IFont;

		// フォントデータ
		typedef Ptr<IFont>::Shared PFont;
		// ファイルのパスとIFontのマップ
		typedef std::map<std::wstring, PFont, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, PFont>>> FontMap;
		typedef std::pair<std::wstring, PFont> FontMapElemType;

		namespace Detail
		{
			class TextureLoader;
			class SLNFont;

			typedef Ptr<Selene::Engine::Graphics::Resource::Text::ITextData>::Intrusive 
				PSLNFont;
		}

		namespace Exception
		{
			class Invalid;
		}
	}

	namespace Input
	{
		class Manager;
	}

	namespace Random
	{
		class IRandom;

		namespace Impl
		{
			class SLN;

			typedef Ptr<SLN>::Shared PSLN;
		}

		typedef Ptr<IRandom>::Shared PRandom;
	}

	namespace Resource
	{
		class Manager;

		namespace Exception
		{
			class Duplicate;
			class NotFound;
		}
	}

	namespace Sound
	{
		class Manager;
		class IStatic;
		class IStream;

		namespace Detail
		{
			class Static;
			class Stream;
		}

		namespace Exception
		{
			class Invalid;
			class InvalidLayer;
		}

		typedef Ptr<IStatic>::Shared PStatic;
		typedef Ptr<IStream>::Shared PStream;

		// ファイルのパスとサウンドのレイヤ数のマップ
		typedef std::map<std::wstring, Selene::Uint32, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, Selene::Uint32>>> 
			StaticSrcMap;
		typedef std::pair<std::wstring, Selene::Uint32> StaticSrcMapElemType;
		// ファイルのパスとIStaticSoundのマップ
		typedef std::map<std::wstring, PStatic, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, PStatic>>> 
			StaticMap;
		typedef std::pair<std::wstring, PStatic> StaticMapElemType;

		// ファイルのパスとメモリコピーフラグのマップ
		typedef std::map<std::wstring, bool, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, bool>>> 
			StreamSrcMap;
		typedef std::pair<std::wstring, bool> StreamSrcMapElemType;
		// ファイルのパスとIStreamSoundのマップ
		typedef std::map<std::wstring, PStream, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, PStream>>> 
			StreamMap;
		typedef std::pair<std::wstring, PStream> StreamMapElemType;
	}

	namespace Sprite
	{
		class Manager;
		class DrawParameter;
		class SrcDef;
		class Animation;

		namespace Exception
		{
			class InvalidTexture;
		}

		// テクスチャ
		typedef Ptr<Selene::Engine::Graphics::Resource::ITexture>::Intrusive PTexture;

		// ファイルのパスと透過色のマップ
		typedef std::map<std::wstring, Selene::ColorF, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, Selene::ColorF>>> 
			TextureSrcMap;
		typedef std::pair<std::wstring, Selene::ColorF> TextureSrcMapElemType;
		// ファイルのパスとITextureのマップ
		typedef std::map<std::wstring, PTexture, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, PTexture>>> 
			TextureMap;
		typedef std::pair<std::wstring, PTexture> TextureMapElemType;
	}
}
}