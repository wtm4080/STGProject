#include "PCH.h"
#include "Linear.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Bullet;
using namespace Util::STG;


// コンストラクタ
Linear::Linear( PMode pMode, const Locator::LinearF &locator, int hitRadius, 
			   const Util::Sprite::DrawParameter &drawParam )
: Base( pMode, locator.GetPosition(), hitRadius )
, mLocator( locator )
, mDrawParam( drawParam )
, mAuxs( pMode )
{
}


// 位置の取得
Vector2DF Linear::GetPosition() const
{
	return mLocator.GetPosition();
}

// 外力の適用
Vector2DF Linear::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


// ロケータの取得
Locator::LinearF &Linear::GetLocator()
{
	return mLocator;
}

// 描画パラメータの取得
const Util::Sprite::DrawParameter &Linear::GetDrawParameter() const
{
	return mDrawParam;
}

// 描画パラメータの設定
void Linear::SetDrawParameter( const Util::Sprite::DrawParameter &drawParam )
{
	mDrawParam = drawParam;
}


void Linear::OnUpdate()
{
	mLocator.Update();

	mDrawParam.SetDst( 
		mLocator.GetPosition().MakeRect( 
		mDrawParam.GetDst().w, mDrawParam.GetDst().h ) );
}

void Linear::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}

void Linear::OnDestruct()
{
	mAuxs.CreateParticle( mDrawParam );
}

void Linear::OnDestruct( float hp )
{
	mAuxs.CreateFadeOut( mDrawParam );
}

void Linear::OnErase()
{
	mAuxs.CreateFadeOut( mDrawParam );
}