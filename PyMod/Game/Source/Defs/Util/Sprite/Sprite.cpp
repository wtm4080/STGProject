#include "PCH.h"
#include "Sprite.h"

#include "Defs/Util/Sprite/Animation/Manager.h"
#include "Defs/Util/Sprite/Animation/FrameHolder/Sequence.h"
#include "Defs/Util/Sprite/Animation/FrameHolder/Texture.h"

#include "Util/Python/Wrapper/ISprite.h"

using namespace boost::python;
using namespace Game;
using namespace Util::Python::Wrapper;
using namespace std;
using namespace Defs::Util::Sprite;

namespace
{
	ISprite *pSprite;

	typedef Defs::Util::File::FileObject FileObject;
}


void Sprite::Configurate()
{
	using namespace Game::Util::Sprite;
	using Selene::ColorF;
	using Selene::Point2DF;

	class_<Sprite>( "Sprite", no_init )
		.def( "_setInstance", &Sprite::_setInstance )
		.def( "draw", &Sprite::draw )
		.def( "loadTexture", static_cast<PTexture (*)( const wstring & )>( &Sprite::loadTexture ) )
		.def( "loadTexture", static_cast<PTexture (*)( const wstring &, bool )>( &Sprite::loadTexture ) )
		.def( "loadTexture", static_cast<PTexture (*)( const wstring &, bool, const ColorF & )>( &Sprite::loadTexture ) )
		.def( "loadTexture", static_cast<PTexture (*)( const FileObject & )>( &Sprite::loadTexture ) )
		.def( "loadTexture", static_cast<PTexture (*)( const FileObject &, bool )>( &Sprite::loadTexture ) )
		.def( "loadTexture", static_cast<PTexture (*)( const FileObject &, bool, const ColorF & )>( &Sprite::loadTexture ) )
		.def( "setShake", static_cast<void (*)( float )>( &Sprite::setShake ) )
		.def( "setShake", static_cast<void (*)( float, float )>( &Sprite::setShake ) )
		.def( "setShake", static_cast<void (*)( const Point2DF & )>( &Sprite::setShake ) )
		.def( "setShake", static_cast<void (*)( const Point2DF &, float )>( &Sprite::setShake ) )
		.def( "stopShake", &Sprite::stopShake )
		.def( "startShake", &Sprite::startShake )
		.def( "resetShake", &Sprite::resetShake )
		.def( "getCurrentShakeAmount", &Sprite::getCurrentShakeAmount )
		;

	typedef Game::Util::Sprite::AlphaBlend GameAlphaBlend;
	enum_<GameAlphaBlend>( "AlphaBlend" )
		.value( "Opacity", AB_OPACITY )
		.value( "Blend", AB_BLEND )
		.value( "Add", AB_ADD )
		.value( "Sub", AB_SUB )
		.value( "Mul", AB_MUL )
		.value( "Screen", AB_SCREEN )
		;
	{
		using namespace Selene::Engine::Graphics::Resource;
		class_<ITexture, boost::noncopyable, PTexture>( "SpriteTexture", no_init )
			.def( "getRequestSize", &ITexture::GetRequestSize, return_value_policy<copy_const_reference>() )
			.def( "getTextureSize", &ITexture::GetTextureSize, return_value_policy<copy_const_reference>() )
			.def( "getTexel2UVTransform", &ITexture::GetTexel2UVTransform, return_value_policy<copy_const_reference>() )
			.def( "saveToBMP", &ITexture::SaveToBMP )
			.def( "saveToPNG", &ITexture::SaveToPNG )
			.def( "saveToDDS", &ITexture::SaveToDDS )
			;
	}

	using Selene::RectF;
	using Selene::Sint32;

	class_<DrawParameter>( "SpriteDrawParam", init<>() )
		.def( init<const DrawParameter &>() )
		.def( init<PTexture, const RectF &, const RectF &, Sint32>() )
		.def( init<PTexture, const RectF &, const RectF &, Sint32, GameAlphaBlend>() )
		.def( init<PTexture, const RectF &, const RectF &, Sint32, GameAlphaBlend, bool>() )
		.def( init<PTexture, const RectF &, const RectF &, Sint32, GameAlphaBlend, bool, float>() )
		.def( init<PTexture, const RectF &, const RectF &, Sint32, GameAlphaBlend, bool, float, const Point2DF &>() )
		.def( init<PTexture, const RectF &, const RectF &, Sint32, GameAlphaBlend, bool, float, const Point2DF &, const ColorF &>() )
		.def( init<PTexture, const RectF &, const RectF &, Sint32, GameAlphaBlend, bool, float, const Point2DF &, const ColorF &, bool>() )
		.add_property( "texture", &DrawParameter::GetTexture, &DrawParameter::SetTexture )
		.def_readwrite( "src", &DrawParameter::mSrc )
		.def_readwrite( "dst", &DrawParameter::mDst )
		.add_property( "priority", &DrawParameter::GetPriority, &DrawParameter::SetPriority )
		.add_property( "alphaBlend", &DrawParameter::GetAlphaBlend, &DrawParameter::SetAlphaBlend )
		.add_property( "filtering", &DrawParameter::IsFiltering, &DrawParameter::SetFiltering )
		.add_property( "rotDegree", &DrawParameter::GetRotDegree, &DrawParameter::SetRotDegree )
		.def_readwrite( "rotOffset", &DrawParameter::mRotOffset )
		.def_readwrite( "color", &DrawParameter::mColor )
		.add_property( "shakable", &DrawParameter::IsShakable, &DrawParameter::SetShakable )
		.def( "flipX", &DrawParameter::FlipX )
		.add_property( "flipedX", &DrawParameter::IsFlipedX )
		.def( "flipY", &DrawParameter::FlipY )
		.add_property( "flipedY", &DrawParameter::IsFlipedY )
		;

	{
		using namespace Animation;
		using Selene::Point2DI;

		class_<FrameHolder::IFrameHolder, boost::noncopyable, PFrameHolder>( 
			"SpriteAnimationFrameHolder", no_init )
			.add_property( "frameNum", &FrameHolder::IFrameHolder::GetFrameNum )
			.add_property( "framePos", &FrameHolder::IFrameHolder::GetFramePos, &FrameHolder::IFrameHolder::SetFramePos )
			.add_property( "drawParameter", &FrameHolder::IFrameHolder::GetDrawParameter, &FrameHolder::IFrameHolder::SetDrawParameter )
			;
		class_<FrameHolder::Sequence, bases<FrameHolder::IFrameHolder>>( 
			"SpriteAnimationSequenceFrameHolder", 
			init<object, const DrawParameter &>() )
			;
		class_<FrameHolder::Texture, bases<FrameHolder::IFrameHolder>>( 
			"SpriteAnimationTextureFrameHolder", 
			init<const Point2DI &, unsigned, const DrawParameter &>() )
			;

		class_<Manager>( "SpriteAnimationManager", init<PFrameHolder>() )
			.def( init<PFrameHolder, float>() )
			.add_property( "frameHolder", &Manager::GetFrameHolder )
			.add_property( "frameInterval", &Manager::GetFrameInterval, &Manager::SetFrameInterval )
			.add_property( "playing", &Manager::IsPlaying )
			.def( "update", &Manager::Update )
			.def( "draw", &Manager::Draw )
			.def( "play", static_cast<void (Manager::*)()>( &Manager::Play ) )
			.def( "play", static_cast<void (Manager::*)( unsigned )>( &Manager::Play ) )
			.def( "stop", &Manager::Stop )
			;
	}
}


void Sprite::_setInstance( uintptr_t p )
{
	pSprite = reinterpret_cast<ISprite *>( p );
}


void Sprite::draw( 
	const Game::Util::Sprite::DrawParameter &param )
{
	pSprite->Draw( param );
}


Util::Sprite::PTexture Sprite::loadTexture( const wstring &path )
{
	return pSprite->LoadTexture( path );
}

Util::Sprite::PTexture Sprite::loadTexture( 
	const wstring &path, bool mipmap )
{
	return pSprite->LoadTexture( path, mipmap );
}

Util::Sprite::PTexture Sprite::loadTexture( 
	const wstring &path, bool mipmap, const Selene::ColorF &transColor )
{
	return pSprite->LoadTexture( path, mipmap, transColor );
}

Util::Sprite::PTexture Sprite::loadTexture( const FileObject &fileObject )
{
	return pSprite->LoadTexture( fileObject.GetFilePtr() );
}

Util::Sprite::PTexture Sprite::loadTexture( 
	const FileObject &fileObject, bool mipmap )
{
	return pSprite->LoadTexture( fileObject.GetFilePtr(), mipmap );
}

Util::Sprite::PTexture Sprite::loadTexture( 
	const FileObject &fileObject, bool mipmap, const Selene::ColorF &transColor )
{
	return pSprite->LoadTexture( fileObject.GetFilePtr(), mipmap, transColor );
}


void Sprite::setShake( float amount )
{
	pSprite->SetShake( amount );
}

void Sprite::setShake( float amount, float decAmount )
{
	pSprite->SetShake( amount, decAmount );
}

void Sprite::setShake( const Selene::Point2DF &amount )
{
	pSprite->SetShake( amount );
}

void Sprite::setShake( const Selene::Point2DF &amount, float decAmount )
{
	pSprite->SetShake( amount, decAmount );
}

void Sprite::stopShake()
{
	pSprite->StopShake();
}

void Sprite::startShake()
{
	pSprite->StartShake();
}

void Sprite::resetShake()
{
	pSprite->ResetShake();
}

Selene::Point2DF Sprite::getCurrentShakeAmount()
{
	return pSprite->GetCurrentShakeAmount();
}