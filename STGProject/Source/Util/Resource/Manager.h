#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Common.h"
#include <unordered_map>
#include <boost/any.hpp>
#include <vector>
#include "Exception/Duplicate.h"
#include "Exception/NotFound.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Resource
{
	// ヒープに作成したインスタンスに任意の名前を付けて管理する
	class Manager
	{
	public:
		// リソースの追加
		// すでに同じ名前のリソースが存在する場合、ResourceDuplicateExceptionをスロー
		template <class ResourceType>
		static void Add( const std::wstring &name, std::tr1::shared_ptr<ResourceType> newPtr )
		{
			if( !IsExist( name ) )
			{
				mResourceMap[ name ] = boost::any( newPtr );
			}
			else
			{
				THROW( Resource::Exception::Duplicate( name ) );
			}
		}

		// 指定のリソースが存在するかどうか
		static bool IsExist( const std::wstring &name )
		{
			return mResourceMap.find( name ) != mResourceMap.end();
		}

		// リソースの取得
		// 見つからなければResourceNotFoundExceptionがスローされる
		template <class ResourceType>
		static std::tr1::shared_ptr<ResourceType> Get( const std::wstring &name )
		{
			if( !IsExist( name ) )
			{
				THROW( Resource::Exception::NotFound( name ) );
			}

			return boost::any_cast<std::tr1::shared_ptr<ResourceType>>( mResourceMap[ name ] );
		}

		// リソースが空かどうか
		static bool IsEmpty()
		{
			return mResourceMap.empty();
		}

		// リソースを削除する
		static bool Erase( const std::wstring &name )
		{
			if( IsExist( name ) )
			{
				mResourceMap.erase( name );

				return true;
			}
			else
			{
				return false;
			}
		}

		// リソースをクリアする
		static void Clear()
		{
			mResourceMap.clear();
		}

		// リソースの一覧を取得する
		static void GetList( std::vector<std::wstring> &resourceList )
		{
			resourceList.clear();

			typedef const std::pair<std::wstring, boost::any> rMapElem;
			foreach( rMapElem &resource, mResourceMap )
			{
				resourceList.push_back( resource.first );
			}
		}

	private:
		// リソースの保持
		// キーは任意の文字列
		static std::tr1::unordered_map<std::wstring, boost::any> mResourceMap;
	};
}
}
}