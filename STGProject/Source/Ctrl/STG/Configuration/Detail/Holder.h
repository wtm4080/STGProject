#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IInstantiation.h"
#include <map>
#include <set>
#include "Util/Common.h"
#include <boost/noncopyable.hpp>
#include <cassert>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Configuration
{
namespace Detail
{
	template <class Data, class Target, class Parameter>
	class Holder
		: public boost::noncopyable
	{
	public:
		typedef typename Util::Ptr<IInstantiation<Target, Parameter>>::Shared 
			PInstantiation;

		typename Data::Id Add( const Data &data, PInstantiation pInstantiation )
		{
			Data addData( data );
			addData.SetId( mIdCount );

			mConf[ addData ] = pInstantiation;

			return mIdCount++;
		}
		Target Get( const typename Data::Id &id, const Parameter &param ) const
		{
			auto itr = mConf.find( Data( id ) );

			if( itr != mConf.end() )
			{
				return itr->second->GetInstance( param );
			}
			else
			{
				return Target();
			}
		}
		void GetDataSet( std::set<Data> &dataSet ) const
		{
			dataSet.clear();

			typedef std::pair<Data, PInstantiation> MapElem;
			foreach( const MapElem elem, mConf )
			{
				dataSet.insert( elem.first );
			}
		}
		Data GetData( const typename Data::Id &id ) const
		{
			auto itr = mConf.find( Data( id ) );
			assert( itr != mConf.end() );

			return itr->first;
		}
		void Clear()
		{
			mConf.clear();
		}

	private:
		std::map<Data, PInstantiation> mConf;
		typename Data::Id mIdCount;
	};
}
}
}
}
}