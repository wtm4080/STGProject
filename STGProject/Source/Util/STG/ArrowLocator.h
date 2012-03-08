#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/RepeatCounter.h"
#include <boost/numeric/interval.hpp>
#include "Util/STG/Vector2D.h"
#include <boost/python.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace STG
{
	class ArrowLocator
	{
	public:
		// コンストラクタ
		typedef Ptr<Input::STG::IController>::Shared PController;
		ArrowLocator( PController pController, int initArrowPos, 
			int top, int bottom, bool loop = true, bool horizontal = false );

		// 1フレーム毎の状態更新
		void UpdateState();

		// 位置の取得
		int GetPosition() const;
		// 位置の設定
		void SetPosition( int pos );

		// 上限と下限の設定
		void SetInterval( int top, int bottom );
		// 上限と下限の取得
		const boost::numeric::interval<int> &GetInterval() const;

		// 上を左、下を右の入力とする
		bool GetHorizontal() const;
		void SetHorizontal( bool flag = false );

		// リピート待ち間隔の取得
		float GetRepeatWait() const;
		// リピート待ち間隔の設定
		void SetRepeatWait( float wait = 20.0f );
		// リピート間隔の取得
		float GetRepeatInterval() const;
		// リピート間隔の設定
		void SetRepeatInterval( float itv = 6.0f );

		// 入力コントローラーの取得
		PController GetController() const;
		// 入力コントローラーの設定
		void SetController( PController pController );

		// 移動コールバックの設定
		void SetMoveCallback( const boost::python::object &callback );

	private:
		// 矢印の位置
		int mArrowPos;
		// リピート間隔
		Util::RepeatCounter mArwMovRepCnt1;
		Util::RepeatCounter mArwMovRepCnt2;
		bool mRep2Flag;
		// 上限と下限
		boost::numeric::interval<int> mPosItv;
		// 矢印の移動
		void MoveUp();
		void MoveDown();
		// 移動コールバック
		boost::python::object mMoveCallback;

		// 入力している方向
		Vector2DF mPrevDir, mDir;
		void UpdateDirection();
		bool mLoopFlag;
		bool mHorizontalFlag;
		bool IsPushUp() const;
		bool IsPushDown() const;
		bool IsHoldUp() const;
		bool IsHoldDown() const;

		// 入力コントローラー
		PController mpController;
	};
}
}
}