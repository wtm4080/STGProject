#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <cfloat>
#include <set>
#include <vector>
#include "Util/STG/Vector2D.h"


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
	template <class PObject>
	class Node
	{
	public:
		Node()
			: mDirection( DIR_NONE )
			, mAreaRange()
			, mLeft( 0 )
			, mRight( 0 )
			, mIndexOffset( 0 )
			, mIndexNumber( 0 )
		{}

		void Build( 
			float xMin, float xMax, 
			float yMin, float yMax, 
			std::vector<PObject> &indexVector, 
			Node *pNodes, 
			int *pNodePos, 
			int restLevel 
			)
		{
			//ここでは一番単純な方法で割る。
			//x,yの長い方で割るのだ。
			float divLine; //分割線
			if ( ( xMax - xMin ) > ( yMax - yMin ) ){
				mDirection = DIR_X;
				divLine = ( xMin + xMax ) * 0.5f;

				// 領域範囲の設定
				mAreaRange.first = xMin;
				mAreaRange.second = xMax;
			}else{
				mDirection = DIR_Y;
				divLine = ( yMin + yMax ) * 0.5f;

				mAreaRange.first = yMin;
				mAreaRange.second = yMax;
			}

			//数える準備
			int leftCircleNum, rightCircleNum;
			//左右ノードに割り振るオブジェクトの数
			leftCircleNum = rightCircleNum = 0;

			//子ノード確保
			mLeft = &pNodes[ *pNodePos + 0 ];
			mRight = &pNodes[ *pNodePos + 1 ];
			*pNodePos += 2;

			//後は方向に応じて分岐
			if ( mDirection == DIR_X ){
				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
					PObject pObject = indexVector[ i ];
					Util::STG::Vector2DF pos = pObject->GetPosition();
					float r = pObject->GetHitRadius();

					// 位置で左右判定し、カウント
					if ( pos.x - r <= divLine + FLT_EPSILON && 
						pos.x + r >= xMin - FLT_EPSILON ){ 
						++leftCircleNum;
					}
					if ( pos.x + r >= divLine - FLT_EPSILON && 
						pos.x - r <= xMax + FLT_EPSILON ){ 
						++rightCircleNum;
					}
				}

				//子配列切り出し
				mLeft->mIndexOffset = static_cast<int>( indexVector.size() );
				indexVector.insert( indexVector.end(), leftCircleNum, PObject() );
				mRight->mIndexOffset = static_cast<int>( indexVector.size() );
				indexVector.insert( indexVector.end(), rightCircleNum, PObject() );

				//分配
				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
					PObject pObject = indexVector[ i ];
					Util::STG::Vector2DF pos = pObject->GetPosition();
					float r = pObject->GetHitRadius();

					if ( pos.x - r <= divLine + FLT_EPSILON && 
						pos.x + r >= xMin - FLT_EPSILON ){
						indexVector[ 
							mLeft->mIndexOffset + mLeft->mIndexNumber 
						] = pObject;
						++mLeft->mIndexNumber;
					}
					if ( pos.x + r >= divLine - FLT_EPSILON && 
						pos.x - r <= xMax + FLT_EPSILON ){
						indexVector[ 
							mRight->mIndexOffset + mRight->mIndexNumber 
						] = pObject;
						++mRight->mIndexNumber;
					}
				}

				//子にまだ分割させるなら(>0でない理由を考えてみよう)
				if ( restLevel > 1 ){
					if ( leftCircleNum > 1 ){ //2個以上ないと割る意味はない
						mLeft->Build( 
							xMin, divLine, 
							yMin, yMax, 
							indexVector, 
							pNodes, 
							pNodePos, 
							restLevel - 1 );
					}
					if ( rightCircleNum > 1 ){
						mRight->Build( 
							divLine, xMax, 
							yMin, yMax, 
							indexVector, 
							pNodes, 
							pNodePos, 
							restLevel - 1 );
					}
				}
			}
			else{
				int &topCircleNum = leftCircleNum;
				int &bottomCircleNum = rightCircleNum;

				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
					PObject pObject = indexVector[ i ];
					Util::STG::Vector2DF pos = pObject->GetPosition();
					float r = pObject->GetHitRadius();

					// 位置で上下判定し、カウント
					if ( pos.y - r <= divLine + FLT_EPSILON && 
						pos.y + r >= yMin - FLT_EPSILON ){ 
						++topCircleNum;
					}
					if ( pos.y + r >= divLine - FLT_EPSILON && 
						pos.y - r <= yMax + FLT_EPSILON ){ 
						++bottomCircleNum;
					}
				}

				//子配列切り出し
				mLeft->mIndexOffset = static_cast<int>( indexVector.size() );
				indexVector.insert( indexVector.end(), topCircleNum, PObject() );
				mRight->mIndexOffset = static_cast<int>( indexVector.size() );
				indexVector.insert( indexVector.end(), bottomCircleNum, PObject() );

				//分配
				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
					PObject pObject = indexVector[ i ];
					Util::STG::Vector2DF pos = pObject->GetPosition();
					float r = pObject->GetHitRadius();

					if ( pos.y - r <= divLine + FLT_EPSILON && 
						pos.y + r >= yMin - FLT_EPSILON ){
						indexVector[ 
							mLeft->mIndexOffset + mLeft->mIndexNumber 
						] = pObject;
						++mLeft->mIndexNumber;
					}
					if ( pos.y + r >= divLine - FLT_EPSILON && 
						pos.y - r <= yMax + FLT_EPSILON ){
						indexVector[ 
							mRight->mIndexOffset + mRight->mIndexNumber 
						] = pObject;
						++mRight->mIndexNumber;
					}
				}

				//子にまだ分割させるなら(>0でない理由を考えてみよう)
				if ( restLevel > 1 ){
					if ( topCircleNum > 1 ){ //2個以上ないと割る意味はない
						mLeft->Build( 
							xMin, xMax, 
							yMin, divLine, 
							indexVector, 
							pNodes, 
							pNodePos, 
							restLevel - 1 );
					}
					if ( bottomCircleNum > 1 ){
						mRight->Build( 
							xMin, xMax, 
							divLine, yMax, 
							indexVector, 
							pNodes, 
							pNodePos, 
							restLevel - 1 );
					}
				}
			}

			//自分の配列は要らない。しかし開放はできないので、間違いが起こらぬよう0にしておく。
			//なお、ここを後の部分で再利用するようにコードを書くことも出来、
			//そうすれば前もって確保する配列をかなり短くできるが、かなり複雑になる。
			mIndexOffset = 0;
			mIndexNumber = 0;
		}

		template <class Detector>
		PObject Detect( 
			const std::vector<PObject> &indexVector, 
			const Detector &detector
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
			, int *pTestCount = 0, 
			int *pHitCount = 0 
#endif
			) const
		{
			//分割がないイコールここが終点。
			if ( mDirection == DIR_NONE ){
				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
					if( pTestCount ) { ++( *pTestCount ); }
#endif

					PObject pObject = indexVector[ i ];
					if ( detector.Detect( pObject ) ){
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
						if( pHitCount ) { ++( *pHitCount ); }
#endif

						return pObject;
					}
				}
			}
			//子がいるので子に渡す。
			else{
				Vector2DF pos = detector.GetPosition();
				float r = detector.GetRadius();
				float divLine = ( mAreaRange.first + mAreaRange.second ) * 0.5f;
				PObject result;

				if( mDirection == DIR_X )
				{
					if ( pos.x - r <= divLine + FLT_EPSILON && 
						pos.x + r >= mAreaRange.first - FLT_EPSILON ){
						result = mLeft->Detect( 
							indexVector, detector
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							,  pTestCount, pHitCount 
#endif
							);
					}

					if ( !result && 
						pos.x + r >= divLine - FLT_EPSILON && 
						pos.x - r <= mAreaRange.second + FLT_EPSILON ){
						return mRight->Detect( 
							indexVector, detector
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							, pTestCount, pHitCount 
#endif
							);
					}
					else
					{
						return result;
					}
				}
				else
				{
					if ( pos.y - r <= divLine + FLT_EPSILON && 
						pos.y + r >= mAreaRange.first - FLT_EPSILON ){
						result = mLeft->Detect( 
							indexVector, detector
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							, pTestCount, pHitCount 
#endif
							);
						}

					if ( !result && 
						pos.y + r >= divLine - FLT_EPSILON && 
						pos.y - r <= mAreaRange.second + FLT_EPSILON ){
						return mRight->Detect( 
							indexVector, detector
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							, pTestCount, pHitCount 
#endif
							);
					}
					else
					{
						return result;
					}
				}
			}

			return PObject();
		}
		template <class Detector>
		void DetectAll( 
			const std::vector<PObject> &indexVector, 
			const Detector &detector, 
			std::set<PObject> &resultSet
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
			, int *pTestCount = 0, 
			int *pHitCount = 0 
#endif
			) const
		{
			//分割がないイコールここが終点。
			if ( mDirection == DIR_NONE ){
				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
					if( pTestCount ) { ++( *pTestCount ); }
#endif

					PObject pObject = indexVector[ i ];
					if ( detector.Detect( pObject ) ){
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
						if( pHitCount ) { ++( *pHitCount ); }
#endif

						resultSet.insert( pObject );
					}
				}
			}
			//子がいるので子に渡す。
			else{
				Vector2DF pos = detector.GetPosition();
				float r = detector.GetRadius();
				float divLine = ( mAreaRange.first + mAreaRange.second ) * 0.5f;

				if( mDirection == DIR_X )
				{
					if ( pos.x - r <= divLine + FLT_EPSILON && 
						pos.x + r >= mAreaRange.first - FLT_EPSILON ){
						mLeft->DetectAll( indexVector, detector, resultSet
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							 ,pTestCount, pHitCount 
#endif
							);
					}
					if ( pos.x + r >= divLine - FLT_EPSILON && 
						pos.x - r <= mAreaRange.second + FLT_EPSILON ){
						mRight->DetectAll( indexVector, detector, resultSet
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							 ,pTestCount, pHitCount 
#endif
							 );
					}
				}
				else
				{
					if ( pos.y - r <= divLine + FLT_EPSILON && 
						pos.y + r >= mAreaRange.first - FLT_EPSILON ){
						mLeft->DetectAll( indexVector, detector, resultSet
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							 ,pTestCount, pHitCount 
#endif
							);
					}
					if ( pos.y + r >= divLine - FLT_EPSILON && 
						pos.y - r <= mAreaRange.second + FLT_EPSILON ){
						mRight->DetectAll( indexVector, detector, resultSet
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							 ,pTestCount, pHitCount 
#endif
							);
					}
				}
			}
		}

		void SetIndexOffset( int value ) { mIndexOffset = value; }
		void SetIndexNumber( int value ) { mIndexNumber = value; }
		void SetAreaRange( const std::pair<float, float> &range ) { mAreaRange = range; }

		void GetObjects( 
			const std::vector<PObject> &indexVector, std::set<PObject> &resultSet ) const
		{
			if( mDirection == DIR_NONE )
			{
				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
					resultSet.insert( indexVector[ i ] );
				}
			}
			else
			{
				mLeft->GetObjects( indexVector, resultSet );
				mRight->GetObjects( indexVector, resultSet );
			}
		}
	private:
		enum Direction
		{
			DIR_X, 
			DIR_Y, 
			DIR_NONE, 
		};

		Direction mDirection;
		std::pair<float, float> mAreaRange;
		Node *mLeft;
		Node *mRight;
		int mIndexOffset;
		int mIndexNumber;
	};
}
}
}
}