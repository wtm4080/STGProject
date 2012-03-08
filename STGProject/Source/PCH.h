#pragma once

#pragma warning( disable:4996 )


#include "Fwd.h"

// Selene
#include <Selene.h>

// c
#include <cassert>
#include <cmath>
#include <cstdlib>

// std
#include <stdexcept>
#include <string>

// STL
#include <map>
#include <set>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <functional>

// tr1
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <utility>

// Boost
#pragma warning( push )
#pragma warning( disable:4819 )
#pragma warning( disable:4250 )

#define BOOST_SP_USE_QUICK_ALLOCATOR
#define BOOST_PYTHON_STATIC_LIB

#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/cast.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/function.hpp>
#include <boost/functional/hash.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/interval.hpp>
#include <boost/optional.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/python.hpp>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/thread.hpp>
#include <boost/throw_exception.hpp>
#include <boost/tokenizer.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/utility.hpp>
#include <boost/variant.hpp>
#include <boost/weak_ptr.hpp>

#pragma warning( pop )

// BulletML
#include <bulletmlparser.h>
#include <bulletmlparser-tinyxml.h>
#include <bulletmlrunner.h>

// Game::Ctrl
#include "Ctrl/Scene/Manager.h"

// Game::Util
#include "Util/Common.h"
#include "Util/Console.h"
#include "Util/Consts.h"
#include "Util/Core/Manager.h"
#include "Util/Delegate/Delegate.h"
#include "Util/Exception.h"
#include "Util/File/Exception/NotFound.h"
#include "Util/File/IDynamicFile.h"
#include "Util/File/Manager.h"
#include "Util/File/Stream.h"
#include "Util/Font/Exception/Invalid.h"
#include "Util/Font/IFont.h"
#include "Util/Font/Manager.h"
#include "Util/FunctionList.h"
#include "Util/FunctionQueue.h"
#include "Util/Input/Manager.h"
#include "Util/Pager.h"
#include "Util/Python/Manager.h"
#include "Util/Random/Impl/SLN.h"
#include "Util/Random/IRandom.h"
#include "Util/RepeatCounter.h"
#include "Util/RepeatQueue.h"
#include "Util/Resource/Manager.h"
#include "Util/SafeUpdateObject.h"
#include "Util/Sound/Exception/Invalid.h"
#include "Util/Sound/Exception/InvalidLayer.h"
#include "Util/Sound/IStatic.h"
#include "Util/Sound/IStream.h"
#include "Util/Sound/Manager.h"
#include "Util/Sprite/Animation.h"
#include "Util/Sprite/DrawParameter.h"
#include "Util/Sprite/Exception/InvalidTexture.h"
#include "Util/Sprite/Manager.h"
#include "Util/Sprite/SrcDef.h"

// Game::View
#include "View/FadeIn.h"
#include "View/FadeOut.h"