#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "IActor.h"
#include "Util/STG/Hit/Rect.h"


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
	class Base
		: virtual public IActor
	{
	public:
		// 一意な整数値を取得
		virtual Selene::Uint64 GetId() const;

		// 更新
		virtual void Update();
		// 描画
		virtual void Draw() const;

		// 有効フラグの取得
		virtual bool IsValid() const;
		// 有効フラグの設定
		virtual void SetValid( bool flag );

		// 消去
		virtual void Erase();

		// 有効領域判定の取得
		virtual Util::STG::Hit::RectI GetValidRect() const;
		// 有効領域判定の設定
		virtual void SetValidRect( const Util::STG::Hit::RectI &rect );
		// 有効領域の余白の設定
		virtual void SetValidAreaMargin( int margin );
		// 現在のフレームカウントを取得
		virtual unsigned GetFrameCount() const;
		// 現在のフレームカウントを設定
		virtual void SetFrameCount( unsigned count );
		// 有効上限フレームカウントの取得
		virtual unsigned GetValidFrameNum() const;
		// 有効上限フレームカウントの設定
		virtual void SetValidFrameNum( unsigned frameNum );

	protected:
		// コンストラクタ
		typedef Ctrl::STG::Mode::IMode *PMode;
		Base( PMode pMode, const Util::STG::Hit::RectI &validRect );

		// プレイモードクラスの取得
		PMode GetMode() const;
		// プレイモードクラスの設定
		void SetMode( PMode pMode );
		// STG構成オブジェクトの取得
		Ctrl::STG::Actors &GetActors() const;

		// フレームカウントするかどうか取得
		bool IsFrameCounting() const;
		// フレームカウントするかどうか設定
		void SetFrameCounting( bool counting );

	private:
		const Selene::Uint64 mId;
		PMode mpMode;
		bool mValidFlag;
		Util::STG::Hit::RectI mValidArea, mValidRect;
		unsigned mValidFrameNum, mFrameCount;
		bool mFrameCounting;

		virtual void UpdateMiddle() {}
		virtual void DrawMiddle() const {}

		virtual void OnUpdate() = 0;
		virtual void OnDraw() const = 0;
		virtual void OnErase() = 0;
	};
}
}
}
}