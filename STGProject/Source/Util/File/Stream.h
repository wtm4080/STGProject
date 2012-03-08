#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <boost/iostreams/stream.hpp>
#include "Util/File/Detail/SourceOfFile.h"
#include "Util/File/Detail/DeviceOfDynamicFile.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace File
{
	// コンストラクタにPFileを渡すことでストリームを作成できる
	typedef boost::iostreams::stream<Detail::SourceOfFile> FileStream;
	// コンストラクタにIDynamicFile::SharedPtrを渡すことでストリームを作成できる
	typedef boost::iostreams::stream<Detail::DeviceOfDynamicFile> DynamicFileStream;
}
}
}