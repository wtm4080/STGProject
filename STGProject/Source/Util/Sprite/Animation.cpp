#include "PCH.h"
#include "Animation.h"

using namespace Game;
using namespace Util::Sprite;
using namespace Selene;


// コンストラクタ
Animation::Animation()
{
}

Animation::Animation( const Point2DI &frameSize, unsigned frameNum, float frameInterval, 
					 const DrawParameter &param )
					 : mFrameSize( frameSize )
					 , mFrameNum( frameNum )
					 , mDrawParam( param )
					 , mCounter( frameInterval )
					 , mFrameCount( 0 )
					 , mPlayFlag( false )
{
	assert( mFrameSize.x > 0 );
	assert( mFrameSize.y > 0 );
	assert( mFrameNum > 0 );
	assert( mDrawParam.GetTexture() );
	assert( mDrawParam.GetTexture()->GetTextureSize().x % mFrameSize.x == 0 );
	assert( mDrawParam.GetTexture()->GetTextureSize().y % mFrameSize.y == 0 );
	assert( ( mDrawParam.GetTexture()->GetTextureSize().x / mFrameSize.x ) * 
		( mDrawParam.GetTexture()->GetTextureSize().y / mFrameSize.y ) 
		>= static_cast<int>( mFrameNum ) );
}


// フレームの更新
void Animation::Update()
{
	if( mPlayFlag && mFrameCount < mFrameNum )
	{
		mFrameCount += mCounter.GetRepeatCount();
		mCounter.UpdateState();

		mDrawParam.SetSrc( GetCurrentTextureSrc() );

		if( mFrameCount == mFrameNum )
		{
			mPlayFlag = false;
		}
	}
}

// フレームの描画
void Animation::Draw() const
{
	if( mFrameCount < mFrameNum )
	{
		Manager::Draw( mDrawParam );
	}
}


// フレームサイズの取得
Point2DI Animation::GetFrameSize() const
{
	return mFrameSize;
}

// フレームサイズの設定
void Animation::SetFrameSize( const Point2DI &size )
{
	mFrameSize = size;
}

// 総フレーム数の取得
unsigned Animation::GetFrameNum() const
{
	return mFrameNum;
}

// 総フレーム数の設定
void Animation::SetFrameNum( unsigned num )
{
	mFrameNum = num;
}

// 現在のフレーム位置の取得
unsigned Animation::GetFramePos() const
{
	return mFrameCount;
}

// フレーム位置の設定
void Animation::SetFramePos( unsigned framePos )
{
	assert( framePos < mFrameNum );

	if( framePos < mFrameNum )
	{
		mFrameCount = framePos;
	}
	else
	{
		mFrameCount = mFrameNum - 1;
	}

	mDrawParam.SetSrc( GetCurrentTextureSrc() );
}


// アニメーション開始
void Animation::Play( unsigned framePos )
{
	SetFramePos( framePos );

	mPlayFlag = true;
}

// アニメーション停止
void Animation::Stop()
{
	mPlayFlag = false;
}

// アニメーション開始フラグの取得
bool Animation::IsPlay() const
{
	return mPlayFlag;
}


// フレーム間隔の取得
float Animation::GetFrameInterval() const
{
	return mCounter.GetInterval();
}

// フレーム間隔の設定
void Animation::SetFrameInterval( float interval )
{
	mCounter.SetInterval( interval );
}


// 描画パラメータの取得
const DrawParameter &Animation::GetDrawParameter() const
{
	return mDrawParam;
}

// 描画パラメータの設定
void Animation::SetDrawParameter( const DrawParameter &param )
{
	PTexture pTexture = mDrawParam.GetTexture();

	mDrawParam = param;

	assert( mDrawParam.GetTexture() );
	assert( mDrawParam.GetTexture() == pTexture );
}

// 描画先の設定
void Animation::SetDst( const RectF &dst )
{
	mDrawParam.SetDst( dst );
}

// 描画優先度の設定
void Animation::SetPriority( Sint32 priority )
{
	mDrawParam.SetPriority( priority );
}

// アルファブレンドの種類の設定
void Animation::SetAlphaBlend( Util::Sprite::AlphaBlend alphaBlend )
{
	mDrawParam.SetAlphaBlend( alphaBlend );
}

// 回転角度の設定
void Animation::SetRotDegree( float degree )
{
	mDrawParam.SetRotDegree( degree );
}

// 回転時の中心からのオフセットの設定
void Animation::SetRotOffset( const Point2DF &rotOffset )
{
	mDrawParam.SetRotOffset( rotOffset );
}

// 描画色の設定
void Animation::SetColor( const ColorF &color )
{
	mDrawParam.SetColor( color );
}


// 描画するテクスチャ位置の取得
RectF Animation::GetCurrentTextureSrc() const
{
	RectF src;
	src.x = static_cast<float>( mFrameSize.x ) * 
		( mFrameCount % 
		( mDrawParam.GetTexture()->GetTextureSize().x / mFrameSize.x ) );
	src.y = static_cast<float>( mFrameSize.y ) * 
		( mFrameCount / 
		( mDrawParam.GetTexture()->GetTextureSize().x / mFrameSize.x ) );
	src.w = static_cast<float>( mFrameSize.x );
	src.h = static_cast<float>( mFrameSize.y );

	return src;
}