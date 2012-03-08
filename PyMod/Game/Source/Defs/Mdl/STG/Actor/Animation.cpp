#include "PCH.h"
#include "Animation.h"

using namespace Defs::Mdl::STG::Actor;
using namespace Game::Util::STG;
using namespace Selene;


// コンストラクタ
Animation::Animation( const Hit::RectI &validRect, 
	const Defs::Util::Sprite::Animation::Manager &animationManager )
: Base( validRect )
, mAnimationManager( animationManager )
{
	mLocator.GetPosition() = Base::GetValidRect().GetPosition();

	mAnimationManager.Play();
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
Defs::Util::Sprite::Animation::Manager &Animation::GetAnimationManager()
{
	return mAnimationManager;
}

// ロケータの取得
Locator::LinearF &Animation::GetLocator()
{
	return mLocator;
}


void Animation::OnUpdate()
{
	mLocator.Update();

	mAnimationManager.Update();

	if( !mAnimationManager.IsPlaying() )
	{
		Base::SetValid( false );
	}

	{
		auto frameHolder = mAnimationManager.GetFrameHolder();
		auto drawParam = frameHolder->GetDrawParameter();

		RectF dst = drawParam.GetDst();
		drawParam.SetDst( mLocator.GetPosition().MakeRect( dst.w, dst.h ) );

		frameHolder->SetDrawParameter( drawParam );
	}
}

void Animation::OnDraw() const
{
	mAnimationManager.Draw();
}

void Animation::OnErase()
{
	mAuxs.CreateFadeOut( 
		mAnimationManager.GetFrameHolder()->GetDrawParameter() );
}