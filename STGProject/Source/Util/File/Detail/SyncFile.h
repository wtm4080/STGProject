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
namespace Util
{
namespace File
{
namespace Detail
{
	class SyncFile
		: public Selene::Kernel::Object::ReferenceObject
		, public Selene::Engine::File::IFile
	{
	public:
		virtual Selene::Sint32 Release() { return ReferenceObject::Release(); }
		virtual Selene::Sint32 AddRef() { return ReferenceObject::AddRef(); }
		virtual Selene::Sint32 GetReferenceCount() { return ReferenceObject::GetReferenceCount(); }

		SyncFile( const wchar_t *pFileName, const void *pData, Selene::Sint32 size );
		virtual ~SyncFile();

		virtual bool IsLoaded() const;
		virtual const wchar_t* GetFileName() const;
		virtual Selene::Sint32 GetSize() const;
		virtual const void* GetData() const;

	private:
		std::wstring mName;
		const void *mpData;
		Selene::Sint32 mSize;
	};
}
}
}
}