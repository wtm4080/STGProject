#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/exception/all.hpp>
#include <exception>
#include <string>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	// 基本的な例外クラス
	class Exception
		: public std::exception
		, public boost::exception
	{
	public:
		// string型のエラー情報
		typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info;

		// エラー情報の追加
		virtual void AddErrorInfo( const std::wstring &errInfo );

		// エラーメッセージボックスで表示する文字列の取得
		virtual std::wstring GetErrorMessageBoxInfo() const;
		// エラーメッセージボックスで表示する文字列の設定
		// 詳細な情報は AddErrorInfo で追加すること
		virtual void SetErrorMessageBoxInfo( const std::wstring &info );

		// デストラクタ
		virtual ~Exception() {}

	protected:
		std::wstring mErrMBoxInfo;
	};
}
}