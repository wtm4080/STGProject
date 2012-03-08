#include "PCH.h"
#include "Sequence.h"

using namespace Defs::Util::Sprite::Animation::FrameHolder;
namespace py = boost::python;


Sequence::Sequence( const TextureList &textureList, 
	const DrawParameter &drawParam )
	: mTextureList( textureList )
	, mFramePos( 0 )
	, mDrawParam( drawParam )
{
	mDrawParam.SetTexture( mTextureList.front() );
}

Sequence::Sequence( py::object pyTextureList, 
	const DrawParameter &drawParam )
	: mTextureList()
	, mFramePos( 0 )
	, mDrawParam( drawParam )
{
	for( int i = 0; i < py::len( pyTextureList ); i++ )
	{
		mTextureList.push_back( 
			py::extract<PTexture>( pyTextureList[ i ] ) );
	}

	mDrawParam.SetTexture( mTextureList.front() );
}


unsigned Sequence::GetFrameNum() const
{
	return static_cast<unsigned>( mTextureList.size() );
}


unsigned Sequence::GetFramePos() const
{
	return mFramePos;
}

void Sequence::SetFramePos( unsigned framePos )
{
	if( framePos < GetFrameNum() )
	{
		mFramePos = framePos;
	}
	else
	{
		mFramePos = GetFrameNum() - 1;
	}

	mDrawParam.SetTexture( mTextureList[ mFramePos ] );
}


Sequence::DrawParameter Sequence::GetDrawParameter() const
{
	return mDrawParam;
}

void Sequence::SetDrawParameter( const DrawParameter &drawParam )
{
	mDrawParam = drawParam;
}