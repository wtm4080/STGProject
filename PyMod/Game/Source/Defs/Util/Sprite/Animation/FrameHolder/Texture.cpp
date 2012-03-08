#include "PCH.h"
#include "Texture.h"

using namespace Defs::Util::Sprite::Animation::FrameHolder;
using namespace Selene;


Texture::Texture( const Point2DI &frameSize, unsigned frameNum, 
	const DrawParameter &drawParam )
	: mFrameSize( frameSize )
	, mFrameNum( frameNum )
	, mFramePos( 0 )
	, mDrawParam( drawParam )
{
	mDrawParam.SetSrc( GetCurrentTextureSrc() );

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


unsigned Texture::GetFrameNum() const
{
	return mFrameNum;
}


unsigned Texture::GetFramePos() const
{
	return mFramePos;
}

void Texture::SetFramePos( unsigned framePos )
{
	if( framePos < mFrameNum )
	{
		mFramePos = framePos;
	}
	else
	{
		mFramePos = mFrameNum - 1;
	}

	mDrawParam.SetSrc( GetCurrentTextureSrc() );
}


Texture::DrawParameter Texture::GetDrawParameter() const
{
	return mDrawParam;
}

void Texture::SetDrawParameter( const DrawParameter &drawParam )
{
	mDrawParam = drawParam;
}


RectF Texture::GetCurrentTextureSrc() const
{
	RectF src;
	src.x = static_cast<float>( mFrameSize.x ) * 
		( mFramePos % 
		( mDrawParam.GetTexture()->GetTextureSize().x / mFrameSize.x ) );
	src.y = static_cast<float>( mFrameSize.y ) * 
		( mFramePos / 
		( mDrawParam.GetTexture()->GetTextureSize().x / mFrameSize.x ) );
	src.w = static_cast<float>( mFrameSize.x );
	src.h = static_cast<float>( mFrameSize.y );

	return src;
}