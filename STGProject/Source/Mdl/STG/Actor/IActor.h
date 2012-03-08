#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/STG/Hit/Rect.h"
#include "Util/STG/Vector2D.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Actor
{
	class IActor
	{
	public:
		// 一意な整数値を取得
		virtual Selene::Uint64 GetId() const = 0;

		// 更新
		virtual void Update() = 0;
		// 描画
		virtual void Draw() const = 0;

		// 有効フラグの取得
		virtual bool IsValid() const = 0;
		// 有効フラグの設定
		virtual void SetValid( bool flag ) = 0;

		// 消去
		virtual void Erase() = 0;

		// 位置の取得
		virtual Util::STG::Vector2DF GetPosition() const = 0;
		// 外力の適用
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec ) = 0;
		// 有効領域判定の取得
		virtual Util::STG::Hit::RectI GetValidRect() const = 0;
		// 有効領域判定の設定
		virtual void SetValidRect( const Util::STG::Hit::RectI &rect ) = 0;
		// 有効領域の余白の設定
		virtual void SetValidAreaMargin( int margin ) = 0;
		// 現在のフレームカウントを取得
		virtual unsigned GetFrameCount() const = 0;
		// 現在のフレームカウントを設定
		virtual void SetFrameCount( unsigned count ) = 0;
		// 有効上限フレームカウントの取得
		virtual unsigned GetValidFrameNum() const = 0;
		// 有効上限フレームカウントの設定
		virtual void SetValidFrameNum( unsigned frameNum ) = 0;

		virtual ~IActor() {}
	};
}
}
}
}