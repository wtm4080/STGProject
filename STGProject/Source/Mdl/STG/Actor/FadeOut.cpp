#include "PCH.h"
#include "FadeOut.h"

using namespace Game;
using namespace Mdl::STG::Actor;
using namespace Util::STG;
using namespace Selene;

namespace
{
	static const unsigned INIT_FRAME_NUM = 60;
}


// コンストラクタ
FadeOut::FadeOut( PMode pMode, const Hit::RectI &validRect )
: Base( pMode, validRect )
, mLocator()
, mDrawParam()
{
	Base::SetValidFrameNum( INIT_FRAME_NUM );
	mLocator.GetPosition() = Base::GetValidRect().GetPosition();
}


// 位置の取得
Vector2DF FadeOut::GetPosition() const
{
	return mLocator.GetPosition();
}

// 外力の適用
Vector2DF FadeOut::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


// 描画パラメータの取得
Util::Sprite::DrawParameter FadeOut::GetDrawParameter() const
{
	return mDrawParam;
}

// 描画パラメータの設定
void FadeOut::SetDrawParameter( const Util::Sprite::DrawParameter &param )
{
	mDrawParam = param;

	mMaxAlpha = param.GetColor().a;
}

// 消失するまでの総フレーム数の取得
unsigned FadeOut::GetFrameNum() const
{
	return Base::GetValidFrameNum();
}

// 消失するまでの総フレーム数の設定
void FadeOut::SetFrameNum( unsigned num )
{
	Base::SetValidFrameNum( num );
}

// フレームカウントの取得
unsigned FadeOut::GetFrameCount() const
{
	return Base::GetFrameCount();
}

// フレームカウントの設定
void FadeOut::SetFrameCount( unsigned count )
{
	Base::SetFrameCount( count );
}


void FadeOut::OnUpdate()
{
	mLocator.Update();
}

void FadeOut::OnDraw() const
{
	Util::Sprite::DrawParameter dParam = mDrawParam;

	RectF dst = dParam.GetDst();
	dst = mLocator.GetPosition().MakeRect( dst.w, dst.h );
	dParam.SetDst( dst );

	ColorF color = dParam.GetColor();
	color.a = mMaxAlpha/GetFrameNum() * ( GetFrameNum() - GetFrameCount() );
	dParam.SetColor( color );

	Util::Sprite::Manager::Draw( dParam );
}

void FadeOut::OnErase()
{
}