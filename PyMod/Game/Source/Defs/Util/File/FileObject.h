#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/intrusive_ptr.hpp>
#include <Selene.h>
#include "Fwd.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace File
{
	class FileObject
	{
	public:
		typedef Game::Util::File::PFile PFile;
		FileObject( PFile pFile )
			: mpFile( pFile )
		{}

		PFile GetFilePtr() const
		{
			return mpFile;
		}

		bool IsLoaded() const
		{
			return mpFile->IsLoaded();
		}
		std::wstring GetFileName() const
		{
			return std::wstring( mpFile->GetFileName() );
		}
		Selene::Sint32 GetSize() const
		{
			return mpFile->GetSize();
		}

	private:
		PFile mpFile;
	};
}
}
}