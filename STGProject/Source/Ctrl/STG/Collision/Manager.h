#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Node.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Collision
{
	template <class PObject, class Container>
	class Manager
	{
	public:
		static const unsigned MAX_LEVEL = 6; //ç≈ëÂï™äÑíiêî
		static const unsigned MAX_NODE_NUM = ( 1 << MAX_LEVEL ) - 1;
		static const unsigned INDEX_RESERVE_NUM = 10000;
		typedef Node<PObject> NodeType;

		Manager( 
			float xMin, float xMax, 
			float yMin, float yMax, 
			const Container &container )
			: mXRange( xMin, xMax )
			, mYRange( yMin, yMax )
			, mContainer( container )
		{
			mIndexVector.reserve( INDEX_RESERVE_NUM );
		}

		void Update()
		{
			for( int i = 0; i < MAX_NODE_NUM; i++ )
			{
				mNodeArray[ i ] = NodeType();
			}
			mIndexVector.clear();

			NodeType &root = mNodeArray[ 0 ];
			mIndexVector.assign( mContainer.begin(), mContainer.end() );
			root.SetIndexOffset( 0 );
			root.SetIndexNumber( static_cast<int>( mContainer.size() ) );

			int nodePos = 1;
			root.Build( 
				mXRange.first, mXRange.second, 
				mYRange.first, mYRange.second, 
				mIndexVector, 
				mNodeArray, 
				&nodePos, 
				MAX_LEVEL - 1 );
		}

#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
		template <class Detector>
		PObject Detect( 
			const Detector &detector, 
			int *pTestCount = 0, 
			int *pHitCount = 0 
			) const
		{
			const NodeType &root = mNodeArray[ 0 ];

			return root.Detect( 
				mIndexVector, 
				detector, 
				pTestCount, 
				pHitCount 
				);
		}
#else
		template <class Detector>
		PObject Detect( 
			const Detector &detector
			) const
		{
			const NodeType &root = mNodeArray[ 0 ];

			return root.Detect( 
				mIndexVector, 
				detector
				);
		}
#endif
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
		template <class Detector>
		void DetectAll( 
			const Detector &detector, 
			std::set<PObject> &resultSet, 
			int *pTestCount = 0, 
			int *pHitCount = 0 
			) const
		{
			const NodeType &root = mNodeArray[ 0 ];
			resultSet.clear();

			root.DetectAll( 
				mIndexVector, 
				detector, 
				resultSet, 
				pTestCount, 
				pHitCount 
				);
		}
#else
		template <class Detector>
		void DetectAll( 
			const Detector &detector, 
			std::set<PObject> &resultSet
			) const
		{
			const NodeType &root = mNodeArray[ 0 ];
			resultSet.clear();

			root.DetectAll( 
				mIndexVector, 
				detector, 
				resultSet 
				);
		}
#endif

		template <class Detector>
		PObject Detect_BruteForce( 
			const Detector &detector, 
			int *pTestCount = 0, 
			int *pHitCount = 0 
			) const
		{
			if( IsInValidArea( detector.GetPosition(), detector.GetRadius() ) )
			{
				foreach( PObject pObject, mContainer )
				{
					if( pTestCount ) { ( *pTestCount )++; }

					if( IsInValidArea( 
						pObject->GetPosition(), pObject->GetHitRadius() ) && 
						detector.Detect( pObject ) )
					{
						if( pHitCount ) { ( *pHitCount )++; }

						return pObject;
					}
				}
			}

			return PObject();
		}
		template <class Detector>
		void DetectAll_BruteForce( 
			const Detector &detector, 
			std::set<PObject> &resultSet, 
			int *pTestCount = 0, 
			int *pHitCount = 0 
			) const
		{
			if( IsInValidArea( detector.GetPosition(), detector.GetRadius() ) )
			{
				resultSet.clear();

				foreach( PObject pObject, mContainer )
				{
					if( pTestCount ) { ( *pTestCount )++; }

					if( IsInValidArea( 
						pObject->GetPosition(), pObject->GetHitRadius() ) && 
						detector.Detect( pObject ) )
					{
						if( pHitCount ) { ( *pHitCount )++; }

						resultSet.insert( pObject );
					}
				}
			}
		}

		int GetObjectNumInValidArea( bool inTree ) const
		{
			if( inTree )
			{
				std::set<PObject> resultSet;
				const NodeType &root = mNodeArray[ 0 ];
				root.GetObjects( mIndexVector, resultSet );

				return resultSet.size();
			}
			else
			{
				int objectNum = 0;

				foreach( PObject pObject, mContainer )
				{
					if( IsInValidArea( 
						pObject->GetPosition(), pObject->GetHitRadius() ) )
					{
						objectNum++;
					}
				}

				return objectNum;
			}
		}

	private:
		NodeType mNodeArray[ MAX_NODE_NUM ];
		std::vector<PObject> mIndexVector;
		const std::pair<float, float> mXRange, mYRange;
		const Container &mContainer;

		bool IsInValidArea( const Util::STG::Vector2DF &pos, float r ) const
		{
			return 
				pos.x + r >= mXRange.first - FLT_EPSILON && 
				pos.x - r <= mXRange.second + FLT_EPSILON && 
				pos.y + r >= mYRange.first - FLT_EPSILON && 
				pos.y - r <= mYRange.second + FLT_EPSILON;
		}
	};
}
}
}
}