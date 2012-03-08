#include "PCH.h"
#include "Base.h"

#include "Defs/Ctrl/STG/STG.h"

using namespace Defs::Mdl::STG::Actor;
using namespace Game::Util::STG;
using namespace Game::Util::Consts;
using namespace Selene;


namespace
{
	// 有効領域の余白
	static const int VALIDAREA_MARGIN = 100;
	// 有効フレーム数
	static const int VALID_FRAME_NUM = 60 * 10;

	typedef Defs::Ctrl::STG::STG STGControl;
}


// コンストラクタ
Base::Base( const Hit::RectI &validRect )
: mId( STGControl::genObjectId() )
, mValidFlag( true )
, mValidArea( -VALIDAREA_MARGIN, -VALIDAREA_MARGIN, 
			 SCREEN_SIZE.x - STG_INFAREA_SIZE.x + VALIDAREA_MARGIN*2, 
			 SCREEN_SIZE.y + VALIDAREA_MARGIN*2, 
			 false )
, mValidRect( validRect )
, mValidFrameNum( VALID_FRAME_NUM )
, mFrameCount( 0 )
, mFrameCounting( true )
{
}


// 一意な整数値を取得
Uint64 Base::GetId() const
{
	return mId;
}


// 更新
void Base::Update()
{
	mValidRect.SetPosition( GetPosition() );

	if( !mValidRect.IsHit( mValidArea ) )
	{
		mValidFlag = false;
	}

	if( mFrameCount > mValidFrameNum )
	{
		Erase();
	}

	UpdateMiddle();

	OnUpdate();

	if( mFrameCount <= mValidFrameNum && 
		mFrameCounting )
	{
		mFrameCount++;
	}
}

// 描画
void Base::Draw() const
{
	DrawMiddle();

	OnDraw();
}


// 有効フラグの取得
bool Base::IsValid() const
{
	return mValidFlag;
}


// 消去
void Base::Erase()
{
	mValidFlag = false;

	OnErase();
}


// 有効フラグの設定
void Base::SetValid( bool flag )
{
	mValidFlag = flag;
}

// 有効領域判定の取得
Hit::RectI Base::GetValidRect() const
{
	return mValidRect;
}

// 有効領域判定の設定
void Base::SetValidRect( const Hit::RectI &rect )
{
	mValidRect = rect;
}

// 有効領域の余白の設定
void Base::SetValidAreaMargin( int margin )
{
	mValidArea = Hit::RectI( 
		-margin, -margin, 
		SCREEN_SIZE.x - STG_INFAREA_SIZE.x + margin*2, 
		SCREEN_SIZE.y + margin*2, 
		false );
}

// 現在のフレームカウントを取得
unsigned Base::GetFrameCount() const
{
	return mFrameCount;
}

// 現在のフレームカウントを設定
void Base::SetFrameCount( unsigned count )
{
	mFrameCount = count;
}

// 有効上限フレームカウントの取得
unsigned Base::GetValidFrameNum() const
{
	return mValidFrameNum;
}

// 有効上限フレームカウントの設定
void Base::SetValidFrameNum( unsigned frameNum )
{
	mValidFrameNum = frameNum;
}


// フレームカウントするかどうか取得
bool Base::IsFrameCounting() const
{
	return mFrameCounting;
}

// フレームカウントするかどうか設定
void Base::SetFrameCounting( bool counting )
{
	mFrameCounting = counting;
}