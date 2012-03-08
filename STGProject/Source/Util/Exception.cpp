#include "PCH.h"
#include "Exception.h"

using namespace Game;
using namespace std;


// エラー情報の追加
void Util::Exception::AddErrorInfo( const wstring &errInfo )
{
	*this << errmsg_info( 
		"\n\n--- Error Infomation ---\n" + Util::ToMultiByte( errInfo ) );
}


// エラーメッセージボックスで表示する文字列の取得
wstring Util::Exception::GetErrorMessageBoxInfo() const
{
	return mErrMBoxInfo;
}

// エラーメッセージボックスで表示する文字列の設定
void Util::Exception::SetErrorMessageBoxInfo( const wstring &info )
{
	mErrMBoxInfo = info;
}