#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <vector>
#include <utility>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	template <class ElemType>
	class Pager
	{
	public:
		// コンストラクタ
		Pager( unsigned pageSize )
			: mElems()
			, mPageSize( pageSize )
		{
			if( mPageSize == 0 )
			{
				mPageSize = 1;
			}
		}
		template <class Iterator>
		Pager( unsigned pageSize, Iterator begin, Iterator end )
			: mElems( begin, end )
			, mPageSize( pageSize )
		{
			if( mPageSize == 0 )
			{
				mPageSize = 1;
			}
		}

		// 1ページ当たりの要素数を設定する
		// 0は設定できない
		void SetPageSize( unsigned pageSize )
		{
			mPageSize = pageSize != 0 ? pageSize : 1;
		}

		// 1ページ当たりの要素数を取得する
		unsigned GetPageSize() const
		{
			return mPageSize;
		}

		// 総ページ数を取得する
		std::size_t GetPageNum() const
		{
			std::size_t pageNum = mElems.size() / mPageSize;

			if( mElems.size() % mPageSize != 0 )
			{
				pageNum++;
			}

			return pageNum;
		}

		// 指定したページを取得する(ページ番号は0起算)
		typedef typename std::vector<ElemType>::iterator ElemIterator;
		typedef std::pair<ElemIterator, ElemIterator> PageLocator;
		PageLocator GetPage( unsigned page )
		{
			unsigned pageBegin = page * mPageSize;
			if( pageBegin >= mElems.size() )
			{
				return PageLocator( mElems.end(), mElems.end() );
			}

			PageLocator itrPair;
			itrPair.first = mElems.begin() + pageBegin;

			itrPair.second = itrPair.first;
			for( unsigned i = 0; 
				itrPair.second != mElems.end() && i < mPageSize; 
				itrPair.second++, i++ );

			return itrPair;
		}
		typedef typename std::vector<ElemType>::const_iterator ConstElemIterator;
		typedef std::pair<ConstElemIterator, ConstElemIterator> ConstPageLocator;
		ConstPageLocator GetPage( unsigned page ) const
		{
			unsigned pageBegin = page * mPageSize;
			if( pageBegin >= mElems.size() )
			{
				return ConstPageLocator( mElems.end(), mElems.end() );
			}

			ConstPageLocator itrPair;
			itrPair.first = mElems.begin() + pageBegin;

			itrPair.second = itrPair.first;
			for( unsigned i = 0; 
				itrPair.second != mElems.end() && i < mPageSize; 
				itrPair.second++, i++ );

			return itrPair;
		}

		// 要素コンテナへの参照を取得する
		typedef std::vector<ElemType> ElemCollection;
		ElemCollection &GetElemCollection()
		{
			return mElems;
		}
		const ElemCollection &GetElemCollection() const
		{
			return mElems;
		}

	private:
		std::vector<ElemType> mElems;
		unsigned mPageSize;
	};
}
}