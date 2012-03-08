#include "PCH.h"
#include "Rotate.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Bullet;
using namespace Util::STG;


 // コンストラクタ
Rotate::Rotate( PMode pMode, const Locator::RotateF &locator, int hitRadius, 
			   const Util::Sprite::DrawParameter &drawParam )
: Base( pMode, locator.GetPosition(), hitRadius )
, mLocator( locator )
, mDrawParam( drawParam )
, mAuxs( pMode )
{
}


// 位置の取得
Vector2DF Rotate::GetPosition() const
{
	return mLocator.GetPosition();
}

// 外力の適用
Vector2DF Rotate::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


// ロケータの取得
Locator::RotateF &Rotate::GetLocator()
{
	return mLocator;
}

// 描画パラメータの取得
const Util::Sprite::DrawParameter &Rotate::GetDrawParameter() const
{
	return mDrawParam;
}

// 描画パラメータの設定
void Rotate::SetDrawParameter( const Util::Sprite::DrawParameter &drawParam )
{
	mDrawParam = drawParam;
}


void Rotate::OnUpdate()
{
	mLocator.Update();

	mDrawParam.SetDst( 
		mLocator.GetPosition().MakeRect( 
		mDrawParam.GetDst().w, mDrawParam.GetDst().h ) );
}

void Rotate::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}

void Rotate::OnDestruct()
{
	mAuxs.CreateParticle( mDrawParam );
}

void Rotate::OnDestruct( float hp )
{
	mAuxs.CreateFadeOut( mDrawParam );
}

void Rotate::OnErase()
{
	mAuxs.CreateFadeOut( mDrawParam );
}