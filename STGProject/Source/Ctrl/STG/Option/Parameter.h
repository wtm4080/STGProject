#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <Selene.h>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Option
{
	class Parameter
	{
	public:
		Parameter()
			: mFullScreen( false )
			, mBgmVolume( 80 )
			, mSeVolume( 80 )
			, mVKeyXMinus( 32 )
			, mVKeyXPlus( 33 )
			, mVKeyYMinus( 40 )
			, mVKeyYPlus( 41 )
			, mVKeyZ( 1 )
			, mVKeyX( 0 )
			, mVKeyC( 2 )
			, mVKeyLShift( 7 )
			, mVKeySpace( 6 )
			, mMaxFileCacheSize( 1024 * 1024 * 100 )
		{}

		bool IsFullScreen() const { return mFullScreen; }
		void SetFullScreen( bool isFull ) { mFullScreen = isFull; }

		unsigned GetBGMVolume() const { return mBgmVolume; }
		void SetBGMVolume( unsigned volume ) { mBgmVolume = volume; }
		unsigned GetSEVolume() const { return mSeVolume; }
		void SetSEVolume( unsigned volume ) { mSeVolume = volume; }

		Selene::Uint32 GetVKeyXMinus() const { return mVKeyXMinus; }
		void SetVKeyXMinus( Selene::Uint32 vKey ) { mVKeyXMinus = vKey; }
		Selene::Uint32 GetVKeyXPlus() const { return mVKeyXPlus; }
		void SetVKeyXPlus( Selene::Uint32 vKey ) { mVKeyXPlus = vKey; }
		Selene::Uint32 GetVKeyYMinus() const { return mVKeyYMinus; }
		void SetVKeyYMinus( Selene::Uint32 vKey ) { mVKeyYMinus = vKey; }
		Selene::Uint32 GetVKeyYPlus() const { return mVKeyYPlus; }
		void SetVKeyYPlus( Selene::Uint32 vKey ) { mVKeyYPlus = vKey; }

		Selene::Uint32 GetVKeyZ() const { return mVKeyZ; }
		void SetVKeyZ( Selene::Uint32 vKey ) { mVKeyZ = vKey; }
		Selene::Uint32 GetVKeyX() const { return mVKeyX; }
		void SetVKeyX( Selene::Uint32 vKey ) { mVKeyX = vKey; }
		Selene::Uint32 GetVKeyC() const { return mVKeyC; }
		void SetVKeyC( Selene::Uint32 vKey ) { mVKeyC = vKey; }
		Selene::Uint32 GetVKeyLShift() const { return mVKeyLShift; }
		void SetVKeyLShift( Selene::Uint32 vKey ) { mVKeyLShift = vKey; }
		Selene::Uint32 GetVKeySpace() const { return mVKeySpace; }
		void SetVKeySpace( Selene::Uint32 vKey ) { mVKeySpace = vKey; }

		unsigned GetMaxFileCacheSize() const { return mMaxFileCacheSize; }
		void SetMaxFileCacheSize( unsigned size ) { mMaxFileCacheSize = size; }

	private:
		bool mFullScreen;

		unsigned mBgmVolume;
		unsigned mSeVolume;

		Selene::Uint32 mVKeyXMinus;
		Selene::Uint32 mVKeyXPlus;
		Selene::Uint32 mVKeyYMinus;
		Selene::Uint32 mVKeyYPlus;

		Selene::Uint32 mVKeyZ;
		Selene::Uint32 mVKeyX;
		Selene::Uint32 mVKeyC;
		Selene::Uint32 mVKeyLShift;
		Selene::Uint32 mVKeySpace;

		unsigned mMaxFileCacheSize;
	};
}
}
}
}