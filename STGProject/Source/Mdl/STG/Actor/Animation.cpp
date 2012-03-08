#include "PCH.h"
#include "Animation.h"

using namespace Game;
using namespace Mdl::STG::Actor;
using namespace Util::STG;
using namespace Selene;


// コンストラクタ
Animation::Animation( PMode pMode, const Hit::RectI &validRect, 
					 const Util::Sprite::Animation &animation )
: Base( pMode, validRect )
, mAnimation( animation )
, mAuxs( pMode )
{
	mLocator.GetPosition() = Base::GetValidRect().GetPosition();

	mAnimation.Play();
}


// 位置の取得
Vector2DF Animation::GetPosition() const
{
	return mLocator.GetPosition();
}

// 外力の適用
Vector2DF Animation::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


// アニメーション設定の取得
Util::Sprite::Animation &Animation::GetAnimation()
{
	return mAnimation;
}


void Animation::OnUpdate()
{
	mLocator.Update();

	mAnimation.Update();

	if( !mAnimation.IsPlay() )
	{
		Base::SetValid( false );
	}

	{
		RectF dst = mAnimation.GetDrawParameter().GetDst();
		mAnimation.SetDst( mLocator.GetPosition().MakeRect( dst.w, dst.h ) );
	}
}

void Animation::OnDraw() const
{
	mAnimation.Draw();
}

void Animation::OnErase()
{
	mAuxs.CreateFadeOut( mAnimation.GetDrawParameter() );
}