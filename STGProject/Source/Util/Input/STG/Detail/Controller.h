#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Input/STG/IController.h"
#include <boost/bimap.hpp>
#include <boost/noncopyable.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Input
{
namespace STG
{
namespace Detail
{
	enum AXIS_ID
	{
		AXIS_X_MINUS	= Selene::Engine::Input::CONTROLLER_AXIS_02_MINUIS, 
		AXIS_X_PLUS		= Selene::Engine::Input::CONTROLLER_AXIS_02_PLUS, 
		AXIS_Y_MINUS	= Selene::Engine::Input::CONTROLLER_AXIS_01_MINUIS, 
		AXIS_Y_PLUS		= Selene::Engine::Input::CONTROLLER_AXIS_01_PLUS, 
	};

	// 入力を受け取る仮想的なコントローラー
	class Controller
		: public IController
		, public boost::noncopyable
	{
	public:
		// フリー状態かを取得
		virtual bool IsFree( KEY_ID key ) const;
		// 離した瞬間かを取得
		virtual bool IsPull( KEY_ID key ) const;
		// 押した瞬間かを取得
		virtual bool IsPush( KEY_ID key ) const;
		// ホールド状態かを取得
		virtual bool IsHold( KEY_ID key ) const;

		// 方向の取得
		virtual Util::STG::Vector2DF GetDirection() const;

		// ゲームパッドのアナログスティックをコントローラーに割り当てる
		// 戻り値は、現在入力されているゲームパッドの仮想キー
		// -1でどれも入力されていない状態
		Selene::Sint32 SetAxis( AXIS_ID axis );
		// ゲームパッドのボタンをコントローラーに割り当てる
		// Axisに割り当てられている仮想キーは無視される
		Selene::Sint32 SetButton( KEY_ID key );

		// 割り当てる仮想キーが分かっている場合はこちらを使う
		void SetAxis( AXIS_ID axis, Selene::Uint32 virtualKey );
		void SetButton( KEY_ID key, Selene::Uint32 virtualKey );

		// 割り当てられている仮想キーを取得する
		// 割り当てられていない場合、-1が返される
		Selene::Sint32 GetAxisVirtualKey( AXIS_ID axis ) const;
		Selene::Sint32 GetButtonVirtualKey( KEY_ID key ) const;

		// コンストラクタ
		Controller();

	private:
		// コントローラーのインターフェース
		typedef Ptr<Selene::Engine::Input::IInputController>::Intrusive 
			PController;
		PController mpController;

		// Axisに割り当てられている仮想キーの集合
		boost::bimap<AXIS_ID, Selene::Uint32> mAxisVKeyMap;
		typedef boost::bimap<AXIS_ID, Selene::Uint32>::value_type AVKMapValueType;
		// キーに割り当てられている仮想キーの集合
		boost::bimap<KEY_ID, Selene::Uint32> mKeyVKeyMap;
		typedef boost::bimap<KEY_ID, Selene::Uint32>::value_type KVKMapValueType;
	};
}
}
}
}
}